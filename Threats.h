#ifndef THREATS_H_
#define THREATS_H_
#include"common_functions.h"

#define THREAT_WIDTH 40
#define THREAT_HEIGHT 40
#define RUN_DISTANCE 5
class Threat
{
public:
    Threat();

    void handle_move();
    void render();
    SDL_Rect obstacle();

private:
    int mPosX;
    int mPosY;
    int mWidth;
    int mHeight;
};


#endif // THREATS_H_
