#ifndef THREATS_H_
#define THREATS_H_

#include"Functions.h"
#include"LTexture.h"

#define THREAT_1_WIDTH 45
#define THREAT_1_HEIGHT 45

#define THREAT_2_WIDTH 64
#define THREAT_2_HEIGHT 45

#define ROCKET_1_WIDTH 75
#define ROCKET_1_HEIGHT 45

#define ROCKET_2_WIDTH 93
#define ROCKET_2_HEIGHT 45

#define RUN_DISTANCE 5;

class Threat
{
public:
    Threat();

    void render_threat_1(LTexture &gThreat1, SDL_Renderer* &gRenderer);
    void render_threat_2(LTexture &gThreat2, SDL_Renderer* &gRenderer);
    void render_rocket_1(LTexture &gRocket1, LTexture &gWarning, SDL_Renderer* & gRenderer);
    void render_rocket_2(LTexture &gRocket2, LTexture &gWarning, SDL_Renderer* & gRenderer);

    void threat_move();
    void pause(SDL_Event e);

    SDL_Rect get_obstacle_1_dimension(); // Get threat's dimension
    SDL_Rect get_obstacle_2_dimension();
    SDL_Rect get_rocket_1_dimension();
    SDL_Rect get_rocket_2_dimension();

    void reset();
    void gameOver();

private:
    bool is_pause;
    //Threat 1
    int mPosX_1, mPosY_1;
    int mWidth_1, mHeight_1;
    //Threat 2
    int mPosX_2, mPosY_2;
    int mWidth_2, mHeight_2;
    //Rocket 1
    int rPosX_1, rPosY_1;
    int rWidth_1, rHeight_1;
    //Rocket 2
    int rPosX_2, rPosY_2;
    int rWidth_2, rHeight_2;
};


#endif // THREATS_H_
