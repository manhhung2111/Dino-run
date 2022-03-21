#ifndef CHARACTER_H_
#define CHARACTER_H_
#include"LTexture.h"

static const int Dino_jump = 100;
static const int Dino_height = 39;
static const int Dino_width = 39;

class Character
{
public:
    Character(); // Constructor

    void handle_event(SDL_Event &e);
    bool check_collision(SDL_Rect& threat);

    void pause(SDL_Event e);
    void jump();
    void render(LTexture gDino, SDL_Renderer *gRenderer);

    void reset();
    void gameOver();
private:
    bool is_pause; // pause game
    int jumpDirection; // 1 = jump down, 0 = on ground, -1 = jump up
    int mPosX, mPosY;
    int mVelY;
    SDL_Rect mCollider; // collision box
};
#endif // CHARACTER_H_

