#include"LTexture.h"
#include"Functions.h"
#include"LTimer.h"
#include"Character.h"
#include"Threats.h"
#include"SDL_utilities.h"

const char *WINDOW_TITLE = "Snowball-Adventure";

// Font and text color
TTF_Font *gFont = NULL;
SDL_Color textColor = {0, 0, 0, 255}; // Black

// Music
Mix_Music *gMusic = NULL;
// The sound effects that will be used
Mix_Chunk *gjump = NULL;
Mix_Chunk *gdeath = NULL;

// Images
LTexture gPlayer_jump, gPlayer_background;
LTexture gThreat1, gThreat2;
LTexture gPause, gResume;

// Texts on screen
LTexture gScore, current_score;
LTexture gHiscore, hi_score;
LTexture Start_game;
LTexture game_over;
LTexture play_again;
LTexture exit_game;

// Game checks
bool is_game_over = false, is_exit = false, is_pause = false;
bool is_start_game = false, is_timer_start = false, is_music_play = false;

// Player animation
LTexture gPlayer_ground;
SDL_Rect player_rect;
int frame_width;

Character character; // Character
Threat obstacle1, obstacle2; // Threats

LTimer timer; // Score
SDL_Rect threat1; // Threat1's location after each game loop
SDL_Rect threat2; // Threat2's location after each game loop
stringstream timeText;

// Game functions
void playAgain(SDL_Event e, SDL_Renderer* &gRenderer, SDL_Rect &player_position, SDL_Rect &player_rect, int &frame_width, int &frame);
void render_before_and_while_play(SDL_Renderer* &gRenderer, SDL_Rect &player_position, SDL_Rect &player_rect, int &frame_width, int &frame);
void render_gameover(SDL_Renderer* &gRenderer);
void handle_keyboard_events(SDL_Event e, SDL_Renderer* &gRenderer, SDL_Rect &player_position, SDL_Rect &player_rect, int &frame_width, int &frame);
void update_game();
void gameLoop(SDL_Event e, SDL_Renderer* &gRenderer, SDL_Rect &player_position, SDL_Rect &player_rect, int &frame_width, int &frame);

// File to read and write high score
ifstream input;
ofstream output;
int best_score;

// Background aniamtion
int scrolling_offset = 0;

int main(int argc, char* argv[])
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Event e;
    int frame = 0;
    SDL_Rect player_position;
    srand(time(NULL));
    if(!init(gWindow, gRenderer, WINDOW_TITLE))
    {
        cout << "Failed to initialize SDL!" << endl;
    }
    else
    {
        if(!loadMedia(gPlayer_jump, gPlayer_background, gThreat1, gThreat2, gPause, gResume, gScore, Start_game, game_over, play_again
                      , exit_game, gMusic, gjump, gdeath, gFont, gRenderer, gPlayer_ground, player_rect, frame_width, gHiscore))
        {
            cout << "Failed to load media!" << endl;
        }
        else
        {
            gameLoop(e, gRenderer, player_position, player_rect, frame_width, frame);
        }
    }
    close(gPlayer_jump, gPlayer_background, gThreat1, gThreat2, gPause, gResume, gScore, Start_game, game_over, play_again, exit_game
          , gMusic, gjump, gdeath, gFont, current_score, gWindow, gRenderer, gPlayer_ground, gHiscore);
    return 0;
}
void gameLoop(SDL_Event e, SDL_Renderer* &gRenderer, SDL_Rect &player_position, SDL_Rect &player_rect, int &frame_width, int &frame)
{
    while(!is_exit)
    {
        update_game();
        handle_keyboard_events(e, gRenderer, player_position, player_rect, frame_width, frame);
        render_before_and_while_play(gRenderer,player_position, player_rect, frame_width, frame);
        render_gameover(gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}
void handle_keyboard_events(SDL_Event e, SDL_Renderer* &gRenderer, SDL_Rect &player_position, SDL_Rect &player_rect, int &frame_width, int &frame)
{
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT) is_exit = true;
        else if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE) is_exit = true;
            else if(e.key.keysym.sym == SDLK_s) is_start_game = true;
            if(is_start_game && !is_game_over)
            {
                if(!is_music_play)
                {
                    Mix_PlayMusic(gMusic, -1);
                    is_music_play = true;
                }
                if(e.key.keysym.sym == SDLK_SPACE && !is_pause)
                {
                    if(character.is_on_ground()) Mix_PlayChannel(-1, gjump, 0);
                    character.handle_event(e);
                }
                //Start/stop the timer
                if( e.key.keysym.sym == SDLK_s && !is_timer_start )
                {
                    timer.start();
                    is_timer_start = true;
                }
                //Pause/unpause
                else if( e.key.keysym.sym == SDLK_p )
                {
                    // pause/resume music
                    if(Mix_PausedMusic() == 1) Mix_ResumeMusic();
                    else Mix_PauseMusic();

                    is_pause = !is_pause;

                    character.pause(e);
                    obstacle1.pause(e);
                    obstacle2.pause(e);

                    // pause/resume timer
                    if( timer.isPaused() ) timer.unpause();
                    else timer.pause();
                }
            }
            if(is_game_over) playAgain(e, gRenderer, player_position, player_rect, frame_width, frame);
        }
    }
}

void playAgain(SDL_Event e, SDL_Renderer* &gRenderer, SDL_Rect &player_position, SDL_Rect &player_rect, int &frame_width, int &frame)
{
    if(e.key.keysym.sym == SDLK_r)
    {
        is_start_game = false;
        is_game_over = false;
        is_timer_start = false;
        is_music_play = false;
        is_pause = false;
        // reposition
        character.reset();
        obstacle1.reset();
        obstacle2.reset();

        timer.stop();
        // play again
        gameLoop(e, gRenderer, player_position, player_rect, frame_width, frame);
    }
    else if(e.key.keysym.sym == SDLK_ESCAPE) is_exit = true;
}

void render_before_and_while_play(SDL_Renderer* &gRenderer, SDL_Rect &player_position,
                                  SDL_Rect &player_rect, int &frame_width, int &frame)
{
    //Set text to be rendered
    timeText.str("");
    timeText << (timer.getTicks() / 300);

    // Render score (time)
    if(!current_score.load_from_rendered_text(timeText.str().c_str(), textColor, gRenderer, gFont))
    {
        cout << "Unable to render current score texture!" << endl;
    }

    // Render hi score
    if(is_start_game)
    {
        input.open("best_score.txt");
        input >> best_score;
        input.close();
        if (is_game_over && best_score < timer.getTicks()/300 )
        {
            output.open("best_score.txt");
            best_score = timer.getTicks()/300;
            output.seekp(0); // shift pointer to the beginning
            output << best_score;
            output.close();
        }

        stringstream h;
        h.str("");
        h << best_score;
        if(!hi_score.load_from_rendered_text(h.str().c_str(), textColor, gRenderer, gFont))
        {
            cout << "Unable to render high score texture!" << endl;
        }
    }


    // Background animation
    if(is_start_game && !is_game_over && !is_pause)
    {
        scrolling_offset -= 2; // = 0
        if(scrolling_offset < -gPlayer_background.getWidth())
        {
            scrolling_offset = 0;
        }
    }
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(gRenderer);

    // Render background and threats
    gPlayer_background.render(scrolling_offset, 0, gRenderer);
    gPlayer_background.render(scrolling_offset + gPlayer_background.getWidth(), 0, gRenderer);
    obstacle1.render_threat_1(gThreat1, gRenderer);
    obstacle2.render_threat_2(gThreat2, gRenderer);

    // Render before game
    if(!is_start_game)
    {
        Start_game.render(300, 150, gRenderer);
        exit_game.render(300, 180, gRenderer);
        character.render_when_jump(gPlayer_jump, gRenderer);
    }

    // Render while playing
    if(is_start_game)
    {
        if(!character.is_on_ground() || is_game_over) character.render_when_jump(gPlayer_jump, gRenderer);
        else if(!is_game_over)character.render_on_ground(gPlayer_ground, gRenderer, player_position, player_rect, frame_width, frame);

        if(!is_game_over)
        {
            obstacle1.threat_move();
            obstacle2.threat_move();
            if(is_pause) gPause.render(10, 10, gRenderer);
            else gResume.render(10, 10, gRenderer);

        }
        // Render hi score
        gHiscore.render(650, 15, gRenderer);
        hi_score.render(675, 15, gRenderer);
        // Render current score
        gScore.render(720, 15, gRenderer);
        current_score.render(770, 15, gRenderer);
    }
}

void render_gameover(SDL_Renderer* &gRenderer)
{
    // Check collision
    if((character.check_collision(threat1) || character.check_collision(threat2)) && !is_game_over)
    {
        Mix_PlayChannel(-1, gdeath, 0);
        is_game_over = true;
    }
    // When game is over
    if(is_game_over)
    {
        // Render text
        game_over.render(320, 140, gRenderer);
        play_again.render(300,160, gRenderer);
        exit_game.render(300, 180, gRenderer);

        //stop music
        if(Mix_PausedMusic() != 1) Mix_PauseMusic();

        // Stop character, threats, and time
        character.gameOver();
        obstacle1.gameOver();
        obstacle2.gameOver();
        timer.gameOver();
    }
}

void update_game()
{
    if(!is_game_over)
    {
        threat1 = obstacle1.get_obstacle_1_dimension(); // update threat position
        threat2 = obstacle2.get_obstacle_2_dimension();
        character.jump(); // character falls back to ground
    }
}
