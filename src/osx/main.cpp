#include <stdio.h>
#include "JSInterpreter.h"
#include <SDL2/SDL.h>
#include "Window.h"

int main(int argc, char** argv) {
  printf("Hello world\n");
    JSInterpreter* jsi = new JSInterpreter();
    jsi->InitializeVM();
    string test = "/Users/ryan/src/mmg/flatland/tests/test_1.js";
    jsi->LoadFile(test);
    bool running = true;
    while(running) {
        SDL_Event evt;
        if(SDL_PollEvent(&evt)) {
            printf("event type: %d\n", evt.type);
            if (evt.type == SDL_WINDOWEVENT) {
                switch (evt.window.event) {
                    case SDL_WINDOWEVENT_SHOWN:
                        printf("Window %d shown\n", evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        printf("Window %d hidden\n", evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        printf("Window %d exposed\n", evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        printf("Window %d moved to %d,%d\n",
                                evt.window.windowID, evt.window.data1,
                                evt.window.data2);
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                        printf("Window %d resized to %dx%d\n",
                                evt.window.windowID, evt.window.data1,
                                evt.window.data2);
                        Window::GetWindow()->SetSize(evt.window.data1, evt.window.data2);
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED:
                        printf("Window %d minimized\n", evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        printf("Window %d maximized\n", evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_RESTORED:
                        printf("Window %d restored\n", evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        printf("Mouse entered window %d\n",
                                evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        printf("Mouse left window %d\n", evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        printf("Window %d gained keyboard focus\n",
                                evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        printf("Window %d lost keyboard focus\n",
                                evt.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        printf("Window %d closed\n", evt.window.windowID);
                        break;
                    default:
                        printf("Window %d got unknown event %d\n",
                                evt.window.windowID, evt.window.event);
                        break;
                }
            }
            if(evt.type == SDL_QUIT) {
                running = false;
            }
            else if(evt.type == SDL_WINDOWEVENT && evt.window.type == SDL_WINDOWEVENT_RESIZED) {
                GLfloat w = evt.window.data1;
                GLfloat h = evt.window.data2;
                Window::GetWindow()->SetSize(w, h);
            }
        }
        Window::GetWindow()->Test();
    }
}
