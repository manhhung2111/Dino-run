#include"Threats.h"
#include"Functions.h"


Threat::Threat()
{
    // Initialize
    is_pause = false;

    // Threat 1 initial position
    mPosX_1 = SCREEN_WIDTH;
    mPosY_1 = ground_level;
    mWidth_1 = THREAT_1_WIDTH;
    mHeight_1 = THREAT_1_HEIGHT;

    // Threat 2 initial position
    mPosX_2 = SCREEN_WIDTH + 300;
    mPosY_2 = ground_level;
    mWidth_2 = THREAT_2_WIDTH;
    mHeight_2 = THREAT_2_HEIGHT;

    // Rocket 1 initial position
    rPosX_1 = - 7000;
    rPosY_1 = ground_level;
    rWidth_1 = ROCKET_1_WIDTH;
    rHeight_1 = ROCKET_1_HEIGHT;

    // Rocket 2 initial position
    rPosX_2 = SCREEN_WIDTH + 2000;
    rPosY_2 = ground_level;
    rWidth_2 = ROCKET_2_WIDTH;
    rHeight_2 = ROCKET_2_HEIGHT;
}

void Threat::render_threat_1(LTexture &gThreat1, SDL_Renderer* &gRenderer)
{
    gThreat1.render(mPosX_1, mPosY_1, gRenderer);
}

void Threat::render_threat_2(LTexture &gThreat2, SDL_Renderer* &gRenderer)
{
    gThreat2.render(mPosX_2, mPosY_2, gRenderer);
}

void Threat::render_rocket_1(LTexture &gRocket1, LTexture &gWarning, SDL_Renderer* & gRenderer)
{
    if(rPosX_1 >= -500 && rPosX_1 <= -rWidth_1) gWarning.render(0, ground_level, gRenderer);
    gRocket1.render(rPosX_1, rPosY_1, gRenderer);
}

void Threat::render_rocket_2(LTexture &gRocket2, LTexture &gWarning, SDL_Renderer* & gRenderer)
{
    if(rPosX_2 >= SCREEN_WIDTH && rPosX_2 <= SCREEN_WIDTH + 500) gWarning.render(SCREEN_WIDTH-55, ground_level, gRenderer);
    gRocket2.render(rPosX_2, rPosY_2, gRenderer);
}

void Threat::threat_move()
{
    if(!is_pause)
    {
        // Move continuously
        mPosX_1 -= RUN_DISTANCE;
        mPosX_2 -= RUN_DISTANCE;
        rPosX_1 += 2*RUN_DISTANCE;
        rPosX_2 -= 2*RUN_DISTANCE;
        // When threat reaches the end of the screen
        if(mPosX_1+mWidth_1 < 0) mPosX_1 = SCREEN_WIDTH + 400; // Recreate the threat at the right of the screen
        if(mPosX_2+mWidth_2 < 0) mPosX_2 = SCREEN_WIDTH + 600 ;
        if(rPosX_1-rWidth_1 > SCREEN_WIDTH) rPosX_1 = -7000 - (rand()%1000 + 100);
        if(rPosX_2+rWidth_2 < 0) rPosX_2 = SCREEN_WIDTH + 2000;
    }
    else
    {
        mPosX_1 = mPosX_1;
        mPosX_2 = mPosX_2;
        rPosX_1 = rPosX_1;
        rPosX_2 = rPosX_2;
    }
}

void Threat::pause(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p)
    {
        if(is_pause == false) is_pause = true;
        else is_pause = false;
    }
}

SDL_Rect Threat::get_obstacle_1_dimension()
{
    SDL_Rect res;
    res.x = mPosX_1;
    res.y = mPosY_1;
    res.w = mWidth_1;
    res.h = mHeight_1;
    return res;
}

SDL_Rect Threat::get_obstacle_2_dimension()
{
    SDL_Rect res;
    res.x = mPosX_2;
    res.y = mPosY_2;
    res.w = mWidth_2;
    res.h = mHeight_2;
    return res;
}

SDL_Rect Threat::get_rocket_1_dimension()
{
    SDL_Rect res;
    res.x = rPosX_1;
    res.y = rPosY_1;
    res.w = rWidth_1;
    res.h = rHeight_1;
    return res;
}

SDL_Rect Threat::get_rocket_2_dimension()
{
    SDL_Rect res;
    res.x = rPosX_2;
    res.y = rPosY_2;
    res.w = rWidth_2;
    res.h = rHeight_2;
    return res;
}

void Threat::gameOver()
{
    mPosX_1= mPosX_1;
    mPosX_2 = mPosX_2;
    rPosX_1 = rPosX_1;
    rPosX_2 = rPosX_2;
}

void Threat::reset()
{
    // Initialize
    is_pause = false;

    // Threat 1 initial position
    mPosX_1 = SCREEN_WIDTH;
    mPosY_1 = ground_level;
    mWidth_1 = THREAT_1_WIDTH;
    mHeight_1 = THREAT_1_HEIGHT;

    // Threat 2 initial position
    mPosX_2 = SCREEN_WIDTH + 300;
    mPosY_2 = ground_level;
    mWidth_2 = THREAT_2_WIDTH;
    mHeight_2 = THREAT_2_HEIGHT;

    // Rocket 1 initial position
    rPosX_1 = - 7000;
    rPosY_1 = ground_level;
    rWidth_1 = ROCKET_1_WIDTH;
    rHeight_1 = ROCKET_1_HEIGHT;

    // Rocket 2 initial position
    rPosX_2 = SCREEN_WIDTH + 2000;
    rPosY_2 = ground_level;
    rWidth_2 = ROCKET_2_WIDTH;
    rHeight_2 = ROCKET_2_HEIGHT;
}
