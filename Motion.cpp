#include"common_functions.h"
#include"Motion.h"

Dino::Dino(){
    //Initialize the offsets
    mVelY = 0;
    mVelX = 0;

    is_jump = false;
    is_on_ground = true;
    mPosX = 0;
    mPosY = 250;
}

bool Dino::isJump(){
    return is_jump;
}

bool Dino::isOnGround(){
    return is_on_ground;
}
void Dino::setJump_press( SDL_Event& e )
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE){
        if(is_on_ground && !is_jump){
            is_jump = true;
            is_on_ground = false;
            mPosY -=Dino_jump;
        }
    }
}

void Dino::setJump_release(SDL_Event& e)
{
    if(e.type == SDL_KEYUP && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE){
        if(!is_on_ground && is_jump){
            is_jump = false;
            is_on_ground = true;
            SDL_Delay(200);
            mPosY += Dino_jump;
        }
    }
}


