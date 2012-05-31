#include <stdio.h>
#include "JSInterpreter.h"
#include <SDL.h>
#include "Window.h"
#include "Renderer.h"
#include "EntityRegistry.h"
#include "PhysicsSystem.h"

int main(int argc, char** argv) {
    bool running = true;
    Window::GetWindow();
    string test = "tests/games/breakout/app.js";
		if(argc == 2) {
			test = argv[1];
		}
    JSInterpreter::Instance()->LoadFile(test);
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
        Renderer* r = Window::GetWindow()->GetRenderer();
        PhysicsSystem::instance()->DoStep();
        EntityRegistry::instance()->CallUpdates(delta);
        oldTicks = newTicks;
        r->Prepare();
        r->Draw();
        PhysicsSystem::instance()->DrawDebugData();
        r->Flush();
    }
    return 0;
}
