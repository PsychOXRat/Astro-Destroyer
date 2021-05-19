#ifndef OBJECTHEADER

#include "SDL.h"
#include "Timer.h"
#include "SDL_image.h"
#include <math.h>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <random>



class Objects
{
public:
	bool active;
};

class Bullet : public Objects
{
protected:
	SDL_Point origin = { 4,4 };
public:
	Bullet();
	double velX, velY;
	double posX, posY;
	SDL_Rect sourceRect, destRect;
	void Update();
	void Render(SDL_Renderer* renderer, SDL_Texture* bulletTex);
	void Init();
	Timer bulletDieTime;
};

class Player : public Objects
{
protected:
	SDL_Surface* bulletSurface = NULL;
	SDL_Texture* bulletTex = NULL;
	SDL_Surface* playerSurface = NULL;
	SDL_Texture* playerTex = NULL;
	SDL_Point origin = { 16,16 };
	Timer shotCooldown;
	Timer animTimer;
	void CreateTex(SDL_Renderer* renderer);
public: 
	Player(SDL_Renderer* renderer);
	//~Player();
	void Init();
	void Update(bool keyboardInputs[], int windowWidth, int windowHeight);
	void Render(SDL_Renderer* renderer);
	SDL_Rect sourceRect, destRect;
	double posX, posY;
	double angle;
	double velX, velY;
	int spriteState = 0;
	double acceleration;
	void Shoot();
	Bullet bullet;
};

class Asteroid : public Objects
{
protected:
	SDL_Point origin = { 4,4 };
public:
	Asteroid(int windowWidth, int windowHeight, int playerPosX, int playerPosY, SDL_Renderer renderer);
	double velX, velY;
	double posX, posY;
	SDL_Rect sourceRect, destRect;
	void Update();
	void Render(SDL_Renderer* renderer, SDL_Texture* asteroidTex);
	void Init();
};
#endif // !OBJECTHEADER