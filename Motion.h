#ifndef MOTION_H_
#define MOTION_H_


class Dino
{
public:
    static const int Dino_jump = 70;
    static const int Dino_height = 39;
    static const int Dino_width = 60;
    Dino();

    void setJump_press(SDL_Event &e);
    void setJump_release(SDL_Event &e);
    bool isJump();
    bool isOnGround();
    void move();

    void render();
private:
    bool is_on_ground;
    bool is_jump;
    int mPosX, mPosY;
    int mVelX, mVelY;
};
#endif // MOTION_H_

