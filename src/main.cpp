
#include <stdio.h>
#include "JSInterpreter.h"
#include <SDL_events.h>
#include "Window.h"
#include "Renderer.h"
#include "EntityRegistry.h"
#include "PhysicsSystem.h"
#include "FileIO.h"
#include "ProgramArguments.h"

void printErrorAndExit(string toPrint) {
    printf("Error: %s\n", toPrint.c_str());
    exit(1);
}

void printHelp() {
    printf("flatland [command] [options]\n");
    printf("Available commands:\n");
    printf("  run:     Runs file specified. flatland run <javascript_file> <app args>.\n");
    printf("             Default command if only a file is specified on the command line.\n");
    printf("\n");
    printf("  new:     Create new game scaffolding. flatland new <game_name>\n");
    printf("\n");
    printf("  package: Package the game for a given platform.\n");
    printf("             flatland package <game_directory> <system>\n");
    printf("\n");
    printf("  help:    Prints this message\n");
    printf("\n");
}

GLboolean isQuit(SDL_Event& evt) {
    return evt.type == SDL_QUIT || 
            (evt.type == SDL_KEYDOWN && 
             evt.key.keysym.scancode == SDL_SCANCODE_Q && 
             evt.key.keysym.mod && KMOD_GUI);
}

void runGameLoop() {
    bool running = true;
    uint32_t oldTicks = SDL_GetTicks();
    
    while(running) {
        SDL_Event evt;
        if(SDL_PollEvent(&evt)) {
            if(isQuit(evt)) {
                running = false;
            }
            else if(evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                GLfloat w = evt.window.data1;
                GLfloat h = evt.window.data2;
                Window::GetWindow()->SetSize(w, h);
            }
        }
        uint32_t newTicks = SDL_GetTicks();
        GLfloat delta = (newTicks - oldTicks) / 1000.0f;
        Window::GetWindow()->HandleUpdates();
        PhysicsSystem::instance()->DoStep();
        Renderer* r = Window::GetWindow()->GetRenderer();
        EntityRegistry::instance()->DestroyMarked();
        EntityRegistry::instance()->CallUpdates(delta);
        oldTicks = newTicks;
        r->Prepare();
        r->Draw();
        PhysicsSystem::instance()->DrawDebugData();
        r->Flush();
    }
}

void loadJavascriptLibrary(char* argv0) {
    FileIO::DetermineExecutableDirectory(argv0);
    StringVector libraryFiles = FileIO::FindRequiredLibraryFiles();
    for(StringVectorIter i = libraryFiles.begin(); i != libraryFiles.end(); i++) {
        string toLoad = *i;
        JSInterpreter::Instance()->LoadFile(toLoad);
    }
}

void runGame(StringVector& arguments) {
    string fileArg = arguments[0];
    if(!arguments[0].compare("run")) {
        if(arguments.size() < 2) {
            printErrorAndExit("Please specify a file");
        }
        fileArg = arguments[1];
    }
    string fullPath = FileIO::GetExpandedPath(fileArg);
    if(!FileIO::IsFile(fullPath)) {
        printErrorAndExit("Not a valid file path");
    }
    string dir = FileIO::GetPathComponent(fullPath);
    string file = FileIO::GetFileComponent(fullPath);
    FileIO::SetWorkingDirectory(dir);
    JSInterpreter::Instance()->LoadFile(file);
    JSInterpreter::Instance()->CallMain();
    runGameLoop();
}

void createGameScaffold(StringVector& arguments) {
    if(arguments.size() < 2) {
        printErrorAndExit("Please specify a directory name for your new game");
    }
    string fullPath = FileIO::GetExpandedPath(arguments[1]);
    if(FileIO::IsFile(fullPath) || FileIO::IsDirectory(fullPath)) {
        printErrorAndExit("Cannot specify an existing file or directory for the new command");
    }
    FileIO::MakeDirectory(fullPath);
    StringVector scaffoldFiles = FileIO::GetScaffoldFiles();
    for(StringVectorIter i = scaffoldFiles.begin(); i != scaffoldFiles.end(); i++) {
        string src = *i;
        string name = FileIO::GetFileComponent(src);
        string dst = fullPath + FileIO::sep + name;
        FileIO::CopyFile(src, dst);
    }
}

int main(int argc, char** argv) {
    Window::GetWindow();
    loadJavascriptLibrary(argv[0]);
    ProgramArguments* args = new ProgramArguments(argc, argv);
    StringVector arglist = args->GetArguments();
    
    if(arglist.size() == 0) {
        arglist.push_back("app.js");
    }
    
    if(!arglist[0].compare("new")) {
        createGameScaffold(arglist);
    }
    else if(!arglist[0].compare("package")) {
        // FIXME: implement packaging for various system types
    }
    else if(!arglist[0].compare("help")) {
        printHelp(); 
    }
    else {
        runGame(arglist);
    }
    
    delete args;
    return 0;
}
