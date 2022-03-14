#include"Threats.h"

Threat::Threat()
{
    mPosX = SCREEN_WIDTH;
    mPosY = 250; // ground
    mWidth = THREAT_WIDTH;
    mHeight = THREAT_HEIGHT;
}

void Threat::handle_move()
{
    mPosX -= RUN_DISTANCE;
    //SDL_Delay(100);
    if(mPosX < 0) mPosX = SCREEN_WIDTH; // Hết màn hình quay lại đi tiếp
}

SDL_Rect Threat::obstacle(){
    SDL_Rect res;
    res.x = mPosX;
    res.y = mPosY;
    res.w = mWidth;
    res.h = mHeight;
    return res;
}
