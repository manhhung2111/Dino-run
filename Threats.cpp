#include"Threats.h"

Threat::Threat()
{
    // Initialize
    is_pause = false;
    mPosX_1 = SCREEN_WIDTH;
    mPosY_1 = 250; // ground
    mWidth_1 = THREAT_1_WIDTH;
    mHeight_1 = THREAT_1_HEIGHT;

    mPosX_2 = SCREEN_WIDTH + 300 + rand() % 200;
    mPosY_2 = 250;
    mWidth_2 = THREAT_2_WIDTH;
    mHeight_2 = THREAT_2_HEIGHT;
}



void Threat::pause(SDL_Event e)
{
    // pause threat
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p){
        if(is_pause == false) is_pause = true;
        else is_pause = false;
    }
}

SDL_Rect Threat::obstacle_1(){
    SDL_Rect res;
    res.x = mPosX_1;
    res.y = mPosY_1;
    res.w = mWidth_1;
    res.h = mHeight_1;
    return res;
}

SDL_Rect Threat::obstacle_2(){
    SDL_Rect res;
    res.x = mPosX_2;
    res.y = mPosY_2;
    res.w = mWidth_2;
    res.h = mHeight_2;
    return res;
}


void Threat::gameOver(){
    mPosX_1= mPosX_1;
    mPosX_2 = mPosX_2;
}

void Threat::reset()
{
    // Reset
    // Initialize
    is_pause = false;
    mPosX_1 = SCREEN_WIDTH;
    mPosY_1 = 250; // ground
    mWidth_1 = THREAT_1_WIDTH;
    mHeight_1 = THREAT_1_HEIGHT;

    mPosX_2 = SCREEN_WIDTH + 300 + rand() % 200;
    mPosY_2 = 250;
    mWidth_2 = THREAT_2_WIDTH;
    mHeight_2 = THREAT_2_HEIGHT;
}
