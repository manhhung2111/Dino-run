#include"Functions.h"
#include"Character.h"
#include"Threats.h"



Character::Character(){
    //Initialize
    mVelY = 0;

    is_pause = false;

    jumpDirection = 0;
    mPosX = 0;
    mPosY = 250;

    mCollider.w = Dino_width;
    mCollider.h = Dino_height;
}

void Character::handle_event( SDL_Event& e )
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE){
        if(jumpDirection == 0){
            jumpDirection = -1;
            mVelY = 2 ;
        }
    }
}

void Character::render(LTexture gDino, SDL_Renderer *gRenderer){
    gDino.render(mPosX, mPosY, gRenderer);
}

void Character::pause(SDL_Event e)
{
    // pause the character
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p){
        if(is_pause == false) is_pause = true;
        else is_pause = false;
    }
}




void Character::jump()
{
    if(jumpDirection == 0) return;
    if(jumpDirection == -1 && mPosY >= (250-Dino_jump)){
        if(!is_pause){
            mPosY -= mVelY;
        }else{
            mPosY = mPosY;
        }

    }
    if(mPosY <= (250-Dino_jump)){
        jumpDirection = 1;
    }
    if(jumpDirection == 1 && mPosY <= 250){
        if(!is_pause){
            mPosY += mVelY;
        }else{
            mPosY = mPosY;
        }
    }
    if (mPosY >= 250) {
        jumpDirection = 0;
    }

}
bool Character::check_collision(SDL_Rect& threat){
    bool is_collide = true;
    // The sides of character
    int left_dino = mPosX;
    int right_dino = mPosX + Dino_width;
    int top_dino = mPosY;
    int bottom_dino = mPosY + Dino_height;

    // The sides of threat
    int left_threat = threat.x;
    int right_threat = threat.x + threat.w;
    int top_threat = threat.y;
    int bottom_threat = threat.y + threat.h;

    // Condition when 2 objects collide
    if(bottom_dino <= top_threat) is_collide = false;
    if(top_dino >= bottom_threat) is_collide = false;
    if(right_dino <= left_threat) is_collide = false;
    if(left_dino >= right_threat) is_collide = false;

    return is_collide;
}

void Character::gameOver(){
    mPosY = mPosY;
    mPosX = mPosX;
}

void Character::reset()
{
    mVelY = 0;
    is_pause = false;
    jumpDirection = 0;
    mPosX = 0;
    mPosY = 250;
    mCollider.w = Dino_width;
    mCollider.h = Dino_height;

}

