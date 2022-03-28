#include"Threats.h"
#include"Functions.h"


Threat::Threat()
{
    // Initialize
    is_pause = false;
    mPosX_1 = SCREEN_WIDTH;
    mPosY_1 = ground_level; // ground
    mWidth_1 = THREAT_1_WIDTH;
    mHeight_1 = THREAT_1_HEIGHT;

    mPosX_2 = SCREEN_WIDTH + 300;
    mPosY_2 = ground_level;
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

SDL_Rect Threat::obstacle_1_dimension(){
    SDL_Rect res;
    res.x = mPosX_1;
    res.y = mPosY_1;
    res.w = mWidth_1;
    res.h = mHeight_1;
    return res;
}

SDL_Rect Threat::obstacle_2_dimension(){
    SDL_Rect res;
    res.x = mPosX_2;
    res.y = mPosY_2;
    res.w = mWidth_2;
    res.h = mHeight_2;
    return res;
}

void Threat::render_1(LTexture &gThreat1, SDL_Renderer* &gRenderer){
    gThreat1.render(mPosX_1, mPosY_1, gRenderer);
}

void Threat::render_2(LTexture &gThreat2, SDL_Renderer* &gRenderer)
{
    gThreat2.render(mPosX_2, mPosY_2, gRenderer);
}



void Threat::move()
{
    if(!is_pause){
        mPosX_1 -= RUN_DISTANCE; //+ acceleration*(timer.getTicks()/10000));//move backward
        mPosX_2 -= RUN_DISTANCE;
        if(mPosX_1+mWidth_1 < 0) mPosX_1 = SCREEN_WIDTH; // recreate the threat at the right of the screen
        if(mPosX_2+mWidth_2 < 0) mPosX_2 = SCREEN_WIDTH + rand()%50;//  + 500;

    }else{
        mPosX_1 = mPosX_1; // pause
        mPosX_2 = mPosX_2;
    }

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
    mPosY_1 = ground_level; // ground
    mWidth_1 = THREAT_1_WIDTH;
    mHeight_1 = THREAT_1_HEIGHT;

    mPosX_2 = SCREEN_WIDTH + 300;
    mPosY_2 = ground_level;
    mWidth_2 = THREAT_2_WIDTH;
    mHeight_2 = THREAT_2_HEIGHT;
}
