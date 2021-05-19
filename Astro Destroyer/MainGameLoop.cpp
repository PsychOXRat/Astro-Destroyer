// MainGameLoop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "Timer.h"
#include "Objects.h"
#include <vector>

Timer tickTimer;
Timer asteroidSpawnRate;
bool done = false;
const int msUntilFrameUpdate = 10;
bool keyboardInputs[256];
int windowWidth, windowHeight = 0;
std::vector <Asteroid> asteroids;
int maxAsteroids = 10;

int main(int argc, char *argv[])
{
    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Pew", 250, 250, 1280, 720, flags);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Player player(renderer);
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
                case SDLK_i:
                    SDL_Log("I has been pressed");
                    keyboardInputs[SDLK_i] = true;
                    break;
                case SDLK_k:
                    SDL_Log("K has been pressed");
                    keyboardInputs[SDLK_k] = true;
                    break;
                case SDLK_SPACE:
                    SDL_Log("SPACE has been pressed");
                    keyboardInputs[SDLK_SPACE] = true;
                    break;
                case SDLK_PERIOD:
                    SDL_Log("PERIOD has been pressed");
                    keyboardInputs[SDLK_PERIOD] = true;
                    break;
                case SDLK_COMMA:
                    SDL_Log("COMMA has been pressed");
                    keyboardInputs[SDLK_COMMA] = true;
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
                case SDLK_i:
                    SDL_Log("I has been un pressed");
                    keyboardInputs[SDLK_i] = false;
                    break;
                case SDLK_k:
                    SDL_Log("K has been un pressed");
                    keyboardInputs[SDLK_k] = false;
                    break;
                case SDLK_SPACE:
                    SDL_Log("SPACE has been un pressed");
                    keyboardInputs[SDLK_SPACE] = false;
                    break;
                case SDLK_PERIOD:
                    SDL_Log("PERIOD has been un pressed");
                    keyboardInputs[SDLK_PERIOD] = false;
                    break;
                case SDLK_COMMA:
                    SDL_Log("COMMA has been un pressed");
                    keyboardInputs[SDLK_COMMA] = false;
                    break;
                }
            }
        }
        if (asteroidSpawnRate.GetTicks() > 1000)
        {
            if (asteroids.size() < maxAsteroids)
            {
                asteroids.push_back(Asteroid(windowWidth, windowHeight, player.posX, player.posY));
            }
        }
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        player.Update(keyboardInputs, windowWidth, windowHeight);
        for (int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].Update();
        }
        SDL_RenderClear(renderer);
        player.Render(renderer);
        SDL_RenderPresent(renderer);

        if (tickTimer.GetTicks() < msUntilFrameUpdate)
        {
            SDL_Delay(msUntilFrameUpdate - tickTimer.GetTicks());
        }
    }
    
    


    return 0;
}
