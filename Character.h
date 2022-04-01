#ifndef CHARACTER_H_
#define CHARACTER_H_
#include"LTexture.h"

static const int player_jump = 110;
static const int player_height = 45;
static const int player_width = 38;

class Character
{
public:
    Character(); // Constructor

    bool is_on_ground();
    void handle_event(SDL_Event &e);
    bool check_collision(SDL_Rect& threat);

    void pause(SDL_Event e);

    void jump(); // Falls back to the ground
    void render_when_jump(LTexture &gPlayer_jump, SDL_Renderer *&gRenderer);
    void render_on_ground(LTexture &gPlayer_ground, SDL_Renderer *&gRenderer, SDL_Rect &player_position,
                          SDL_Rect &player_rect, int &frame_width, int &frame);

    void reset();
    void gameOver();

private:
    bool is_pause; // Pause game
    int jumpDirection; // 1 = Jump down, 0 = On ground, -1 = Jump up
    int mPosX, mPosY; // Position
    int mVelY;
    SDL_Rect mCollider; // Collision box
};
#endif // CHARACTER_H_
