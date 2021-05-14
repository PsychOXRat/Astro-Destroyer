// Astro Destroyer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "Timer.h"

Timer tickTimer;
bool done = false;
const int msUntilFrameUpdate = 10;
bool keyboardInputs[];

int main(int argc, char *argv[])
{
    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Reece Jones 19698544", 250, 250, 1920, 1080, flags);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event _event;
    while (!done)
    {
        tickTimer.resetTicksTimer();
         
        //Update,
        //Render

        while(SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                done = true;
            }
            if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
            {
                switch (_event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = true;
                    break;
                case SDLK_w:
                    SDL_Log("W has been pressed");
                    keyboardInputs[SDLK_w] = true;
                    break;
                case SDLK_s:
                    SDL_Log("S has been pressed");
                    keyboardInputs[SDLK_s] = true;
                    break;
                case SDLK_a:
                    SDL_Log("A has been pressed");
                    keyboardInputs[SDLK_a] = true;
                    break;
                case SDLK_d:
                    SDL_Log("D has been pressed");
                    keyboardInputs[SDLK_d] = true;
                    break;
                case SDLK_q:
                    SDL_Log("Q has been pressed");
                    keyboardInputs[SDLK_q] = true;
                    break;
                case SDLK_e:
                    SDL_Log("E has been pressed");
                    keyboardInputs[SDLK_e] = true;
                    break;
                }
            }
            if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
            {
                switch (_event.key.keysym.sym)
                {
                case SDLK_w:
                    SDL_Log("W has been un pressed");
                    keyboardInputs[SDLK_w] = false;
                    break;
                case SDLK_s:
                    SDL_Log("S has been un pressed");
                    keyboardInputs[SDLK_s] = false;
                    break;
                case SDLK_a:
                    SDL_Log("A has been un pressed");
                    keyboardInputs[SDLK_a] = false;
                    break;
                case SDLK_d:
                    SDL_Log("D has been un pressed");
                    keyboardInputs[SDLK_d] = false;
                    break;
                case SDLK_q:
                    SDL_Log("LSHIFT has been un pressed");
                    keyboardInputs[SDLK_q] = false;
                    break;
                case SDLK_e:
                    SDL_Log("LCTRL has been un pressed");
                    keyboardInputs[SDLK_e] = false;
                    break;
                }
            }
        }
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        if (tickTimer.GetTicks() < msUntilFrameUpdate)
        {
            SDL_Delay(msUntilFrameUpdate - tickTimer.GetTicks());
        }
    }
    
    


    return 0;
}
