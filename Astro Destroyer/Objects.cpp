#include "Objects.h"

Bullet::Bullet()
{
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = 7;
    sourceRect.h = 7;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 8;
    destRect.h = 8;
    velX = 0.0;
    velY = 0.0;
    posX = 960.0;
    posY = 540.0;
}


void Bullet::Update()
{
    if (bulletDieTime.GetTicks() > 5000)
    {
        bulletDieTime.resetTicksTimer();
        active = false;
    }
    posX += velX;
    posY -= velY;
    destRect.x = round(posX);
    destRect.y = round(posY);
}

void Bullet::Render(SDL_Renderer* renderer, SDL_Texture* bulletTex)
{
    SDL_RenderCopyEx(renderer, bulletTex, &sourceRect, &destRect, 0, &origin, SDL_FLIP_NONE);
}

Player::Player(SDL_Renderer* renderer)
{
	sourceRect.x = 31 * spriteState;
	sourceRect.y = 0;
	sourceRect.w = 31;
	sourceRect.h = 31;
	destRect.x = 960;
	destRect.y = 540;
	destRect.w = 32;
	destRect.h = 32;
    acceleration = 0.075;
    angle = 0.0;
    velX = 0.0;
    velY = 0.0;
	CreateTex(renderer);
	posX = 960.0;
	posY = 540.0;
}

void Player :: Init()
{

}

void Player :: CreateTex(SDL_Renderer* renderer)
{
    playerSurface = IMG_Load("content/graphics/shipSprite.png");
    if (playerSurface == NULL)
    {
        SDL_Log("Null pointer returned loading shipSprite.png");
    }
    else
    {
        SDL_Log("Loaded shipSprite.png successfully");
    }

    playerTex = SDL_CreateTextureFromSurface(renderer, playerSurface);
    if (playerTex == NULL)
    {
        SDL_Log("Null pointer returned converting surface to texture");
    }
    else
    {
        SDL_Log("playerTexture created successfully");
        SDL_FreeSurface(playerSurface);
    }

    bulletSurface = IMG_Load("content/graphics/Bullet.png");
    if (bulletSurface == NULL)
    {
        SDL_Log("Null pointer returned loading Bullet.png");
    }
    else
    {
        SDL_Log("Loaded bullet.png successfully");
    }

    bulletTex = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    if (bulletTex == NULL)
    {
        SDL_Log("Null pointer returned converting surface to texture");
    }
    else
    {
        SDL_Log("playerTexture created successfully");
        SDL_FreeSurface(bulletSurface);
    }
}

void Player::Update(bool keyboardInputs[], int windowWidth, int windowHeight)
{
    if ((destRect.x + (8 * sin(angle * M_PI / 180))) > windowWidth + 100) {
        destRect.x = -75;
        posX = -75;
        SDL_Log("Player left right of screen");
    }
    else if ((destRect.x - (8 * sin(angle * M_PI / 180))) < -100) {
        destRect.x = windowWidth;
        posX = windowWidth;
        SDL_Log("Player left left of screen");
    }
    if ((destRect.y + (8 *cos(angle * M_PI / 180))) > windowHeight + 100) {
        destRect.y = -75;
        posY = -75;
        SDL_Log("Player has left top of screen");
    }
    else if ((destRect.y - (8 * cos(angle * M_PI / 180))) < -100) {
        destRect.y = windowHeight;
        posY = windowHeight;
        SDL_Log("Player has left bottom of screen");
    }
    if (keyboardInputs[SDLK_w])
    {
        velX += (sin(angle * M_PI / 180)) * acceleration;
        velY += (cos(angle * M_PI / 180)) * acceleration;
        
        if (animTimer.GetTicks() > 75)
        {

            animTimer.resetTicksTimer();
            spriteState++;
            if (spriteState > 3)
            {
                spriteState = 0;
            }
            sourceRect.x = 31 * spriteState;
        }
    }
    else
    {
        spriteState = 0;
        sourceRect.x = 0;
    }
    if (keyboardInputs[SDLK_s])
    {
        velX += (sin(angle * M_PI / 180)) * -acceleration;
        velY += (cos(angle * M_PI / 180)) * -acceleration;
    }
    if (keyboardInputs[SDLK_a])
    {
        angle -= 1.69;
    }
    if (keyboardInputs[SDLK_d])
    {
        angle += 1.69;
    }
    if (keyboardInputs[SDLK_SPACE])
    {
        if (shotCooldown.GetTicks() > 300)
        {
            shotCooldown.resetTicksTimer();
            Shoot();
        }
    }
    velX *= 0.99;
    velY *= 0.99;
    posX += velX;
    posY -= velY;
    if (bullet.active)
    {
        bullet.Update();
    }
    destRect.x = round(posX);
    destRect.y = round(posY);
}

void Player :: Render(SDL_Renderer* renderer) 
{
    SDL_RenderCopyEx(renderer, playerTex, &sourceRect, &destRect, angle, &origin, SDL_FLIP_NONE);
    if (bullet.active)
    {
        bullet.Render(renderer, bulletTex);
    }
}

void Player :: Shoot()
{
    bullet.active = true;
    bullet.bulletDieTime.resetTicksTimer();
    bullet.velX = velX + (sin(angle * M_PI / 180)) * 6;
    bullet.velY = velY + (cos(angle * M_PI / 180)) * 6;
    velX -= bullet.velX / 8;
    velY -= bullet.velY / 8;
    bullet.posX = posX + (sin(angle * M_PI / 180)) * 16 + 12;
    bullet.posY = posY - (cos(angle * M_PI / 180)) * 16 + 12;
}


Asteroid::Asteroid(int windowWidth, int windowHeight, int playerPosX, int playerPosY, SDL_Renderer renderer)
{
    srand(time(NULL));
    void CreateTex(renderer);
    velX = rand() % 8 + 1;
    velY = rand() % 8 + 1;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = 31;
    sourceRect.h = 31;
    destRect.w = rand() %25 +32;
    destRect.h = destRect.h;
    bool safespawn = false;
    /*while (!safespawn)
    {*/
        destRect.x = rand() % windowWidth;
        destRect.y = rand() % windowHeight;
        /*if ((destRect.x - playerPosX) < (destRect.x/2) || (destRect.x - playerPosX) > (destRect.x / 2))
        {

        }*/
    /*}*/

}
void Asteroid::Update()
{
    posX += velX;
    posY -= velY;
    destRect.x = round(posX);
    destRect.y = round(posY);
}
void Asteroid::Render(SDL_Renderer* renderer, SDL_Texture* asteroidTex)
{

}
