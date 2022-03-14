#include"common_functions.h"
#include"Motion.h"

Dino::Dino(){
    //Initialize
    mVelY = 0;
    mVelX = 0;

    is_jump = false;
    is_on_ground = true;
    mPosX = 0;
    mPosY = 250;

    mCollider.w = Dino_width;
    mCollider.h = Dino_height;
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

bool Dino::check_collision(SDL_Rect& threat){
    bool is_collide = false;
    // The sides of character
    int left_dino = mPosX;
    int right_dino = mPosX + Dino_width;
    int top_dino = mPosY;
    int bottom_dino = mPosY + Dino_height;

    // The sides of threat
    int left_threat = threat.x;
    int right_threat = threat.x + threat.w;
    int top_threat = threat.y;
    int bottom_threat = threat.y + threat.h;

    // Condition when 2 objects collide
    if(left_dino < right_threat && left_threat < right_dino && top_dino < bottom_threat && top_threat < bottom_dino){
        is_collide = true;
    }
    return is_collide;
}

