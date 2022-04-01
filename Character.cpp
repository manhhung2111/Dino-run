#include"Functions.h"
#include"Character.h"
#include"Threats.h"

Character::Character()
{
    //Initialize
    mVelY = 0;
    is_pause = false;
    jumpDirection = 0; // On the ground

    // Character position
    mPosX = 20;
    mPosY = ground_level;

    // Collide box
    mCollider.w = player_width;
    mCollider.h = player_height;
}

bool Character::is_on_ground()
{
    return (jumpDirection == 0);
}

void Character::handle_event( SDL_Event& e )
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE)
    {
        if(jumpDirection == 0)
        {
            jumpDirection = -1;
            mVelY = 5 ;
        }
    }
}

bool Character::check_collision(SDL_Rect& threat)
{
    bool is_collide = true;
    // The sides of character
    int left_player = mPosX;
    int right_player = mPosX + player_width;
    int top_player = mPosY;
    int bottom_player = mPosY + player_height;

    // The sides of threat
    int left_threat = threat.x;
    int right_threat = threat.x + threat.w;
    int top_threat = threat.y;
    int bottom_threat = threat.y + threat.h;

    // Condition when 2 objects collide
    if(bottom_player <= top_threat) is_collide = false;
    if(top_player >= bottom_threat) is_collide = false;
    if(right_player <= left_threat) is_collide = false;
    if(left_player >= right_threat) is_collide = false;

    return is_collide;
}

void Character::jump()
{
    if(jumpDirection == 0) return; // Do nothing

    // Jump up
    if(jumpDirection == -1 && mPosY >= (ground_level-player_jump))
    {
        if(!is_pause)
        {
            mPosY -= mVelY;
        }
        else
        {
            mPosY = mPosY;
        }

    }

    // When character position is at the highest point
    if(mPosY <= (ground_level-player_jump))
    {
        jumpDirection = 1;
    }

    // Fall back
    if(jumpDirection == 1 && mPosY <= ground_level)
    {
        if(!is_pause)
        {
            mPosY += mVelY;
        }
        else
        {
            mPosY = mPosY;
        }
    }

    // When character position is on the ground
    if (mPosY >= ground_level)
    {
        jumpDirection = 0;
    }
}

void Character::render_when_jump(LTexture &gPlayer_jump, SDL_Renderer *&gRenderer)
{
    gPlayer_jump.render(mPosX, mPosY, gRenderer);
}

void Character::render_on_ground(LTexture &gPlayer_ground, SDL_Renderer *&gRenderer, SDL_Rect &player_position,
                                 SDL_Rect &player_rect, int &frame_width, int &frame)
{
    player_position.x = 20;
    player_position.y = ground_level;
    player_position.w = frame_width;
    player_position.h = gPlayer_ground.getHeight() ;

    // Render current frame
    if(!is_pause)
    {
        frame++;
        if(FPS/frame == 15)
        {
            frame = 0;
            player_rect.x += frame_width;
            if(player_rect.x >= gPlayer_ground.getWidth())
            {
                player_rect.x = 0;
            }
        }
    }
    else
    {
        player_rect.x = player_rect.x;
    }
    SDL_RenderCopy(gRenderer, gPlayer_ground.getTexture(), &player_rect, &player_position);
}



void Character::pause(SDL_Event e)
{
    // pause the character
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p)
    {
        if(is_pause == false) is_pause = true;
        else is_pause = false;
    }
}

void Character::gameOver()
{
    mPosY = mPosY;
    mPosX = mPosX;
}

void Character::reset()
{
    mVelY = 0;
    is_pause = false;
    jumpDirection = 0;
    mPosX = 20;
    mPosY = ground_level;
    mCollider.w = player_width;
    mCollider.h = player_height;
}
