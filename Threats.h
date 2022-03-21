#ifndef THREATS_H_
#define THREATS_H_
#include"Functions.h"

#define THREAT_1_WIDTH 40
#define THREAT_1_HEIGHT 40
#define THREAT_2_WIDTH 21
#define THREAT_2_HEIGHT 40

#define RUN_DISTANCE 2
#define acceleration 1

class Threat
{
public:
    Threat();

    void move();
    void pause(SDL_Event e);
    void render_1();
    void render_2();

    void reset();
    void gameOver();

    SDL_Rect obstacle_1(); // Get the threat dimension
    SDL_Rect obstacle_2();
private:
    bool is_pause;
    int mPosX_1, mPosY_1;
    int mPosX_2, mPosY_2;
    int mWidth_1, mHeight_1;
    int mWidth_2, mHeight_2;
};


#endif // THREATS_H_
