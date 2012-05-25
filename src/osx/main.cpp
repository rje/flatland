#include <stdio.h>
#include "JSInterpreter.h"
#include <SDL2/SDL.h>
#include "Window.h"

int main(int argc, char** argv) {
    bool running = true;
    Window::GetWindow();
    string test = "/Users/ryan/src/mmg/flatland/tests/test_1.js";
    JSInterpreter::Instance()->LoadFile(test);
    while(running) {
        SDL_Event evt;
        if(SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT || 
               (evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_Q)) {
                running = false;
            }
            else if(evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                GLfloat w = evt.window.data1;
                GLfloat h = evt.window.data2;
                Window::GetWindow()->SetSize(w, h);
            }
        }
        Window::GetWindow()->HandleUpdates();
        Window::GetWindow()->Test();
    }
}
