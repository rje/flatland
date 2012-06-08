
#include <stdio.h>
#include "JSInterpreter.h"
#include <SDL_events.h>
#include "Window.h"
#include "Renderer.h"
#include "EntityRegistry.h"
#include "PhysicsSystem.h"
#include "FileIO.h"

int main(int argc, char** argv) {
    bool running = true;
    Window::GetWindow();
    FileIO::DetermineExecutableDirectory(argv[0]);
    std::vector<std::string> libraryFiles = FileIO::FindRequiredLibraryFiles();
    for(std::vector<std::string>::iterator i = libraryFiles.begin(); i != libraryFiles.end(); i++) {
        string toLoad = *i;
        JSInterpreter::Instance()->LoadFile(toLoad);
    }
    string test = "tests/games/breakout/app.js";
    if(argc == 2) {
        test = argv[1];
    }
    string fullPath = FileIO::GetExpandedPath(test);
    string dir = FileIO::GetPathComponent(fullPath);
    string file = FileIO::GetFileComponent(fullPath);
    FileIO::SetWorkingDirectory(dir);
    JSInterpreter::Instance()->LoadFile(file);
    uint32_t oldTicks = SDL_GetTicks();
    while(running) {
        SDL_Event evt;
        if(SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT || 
               (evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_Q && evt.key.keysym.mod && KMOD_GUI)) {
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
    return 0;
}
