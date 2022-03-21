#include"LTexture.h"
#include"Functions.h"
#include"LTimer.h"
#include"Character.h"
#include"Threats.h"
#include"SDL_utilities.h"

const char *WINDOW_TITLE = "Dino run";

TTF_Font *gFont = NULL;
SDL_Color textColor = {0, 0, 0, 255}; // score text color

// Music
Mix_Music *gMusic = NULL;

// The sound effects that will be used
Mix_Chunk *gjump = NULL;
Mix_Chunk *gdeath = NULL;

// Image
LTexture gDino, gDino_background;
LTexture gThreat1, gThreat2;
LTexture gPause, gResume;

// Text on screen
LTexture gScore, current_score;
LTexture Start_game;
LTexture game_over;
LTexture play_again;
LTexture exit_game;

// In game features
bool is_game_over = false, is_exit = false, is_pause = false;
bool is_start_game = false, is_timer_start = false, is_music_play = false;

Character character; // character
Threat catus, tree; // threat

LTimer timer; // score
stringstream timeText; // score
SDL_Rect threat1; // location of threat_1 after each game loop
SDL_Rect threat2; // location of threat_2 after each game loop

void playAgain(SDL_Event e, SDL_Renderer *gRenderer);
void render_before_and_while_play(SDL_Renderer* gRenderer);
void render_gameover(SDL_Renderer* gRenderer);
void handle_keyboard_events(SDL_Event e, SDL_Renderer *gRenderer);
void update_game();
void gameLoop(SDL_Event e, SDL_Renderer* gRenderer);

int main(int argc, char* argv[])
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Event e;
    srand(time(NULL));
    if(!init(gWindow, gRenderer, WINDOW_TITLE)){
        cout << "Failed to initialize SDL!" << endl;
    }else{
        if(!loadMedia(gDino, gDino_background, gThreat1, gThreat2, gPause, gResume, gScore, Start_game, game_over, play_again
                        , exit_game, gMusic, gjump, gdeath, gFont, gRenderer)){
            cout << "Failed to load media!" << endl;
        }else{
            gameLoop(e, gRenderer);
        }
    }
    close(gDino, gDino_background, gThreat1, gThreat2, gPause, gResume, gScore, Start_game, game_over, play_again, exit_game
          , gMusic, gjump, gdeath, gFont, current_score, gWindow, gRenderer);
    return 0;
}
void gameLoop(SDL_Event e, SDL_Renderer *gRenderer)
{
    while(!is_exit){
        update_game();
        handle_keyboard_events(e, gRenderer);
        render_before_and_while_play(gRenderer);
        render_gameover(gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}
void handle_keyboard_events(SDL_Event e, SDL_Renderer *gRenderer)
{
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT) is_exit = true;
        else if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
            if(e.key.keysym.sym == SDLK_ESCAPE) is_exit = true;
            else if(e.key.keysym.sym == SDLK_s) is_start_game = true;
            if(is_start_game && !is_game_over){
                if(!is_music_play){
                    Mix_PlayMusic(gMusic, -1);
                    is_music_play = true;
                }
                if(e.key.keysym.sym == SDLK_SPACE){
                    Mix_PlayChannel(-1, gjump, 0);
                    character.handle_event(e);
                }
                //Start/stop the timer
                if( e.key.keysym.sym == SDLK_s && !is_timer_start ){
                    timer.start();
                    is_timer_start = true;
                }
                //Pause/unpause
                else if( e.key.keysym.sym == SDLK_p ){
                    // pause/resume music
                    if(Mix_PausedMusic() == 1) Mix_ResumeMusic();
                    else Mix_PauseMusic();

                    is_pause = !is_pause;

                    character.pause(e);
                    catus.pause(e);
                    tree.pause(e);

                    // pause/resume timer
                    if( timer.isPaused() ) timer.unpause();
                    else timer.pause();
                }
            }
            if(is_game_over) playAgain(e, gRenderer);
        }
    }
}

void playAgain(SDL_Event e, SDL_Renderer *gRenderer){
    if(e.key.keysym.sym == SDLK_r){
        is_start_game = false;
        is_game_over = false;
        is_timer_start = false;
        is_music_play = false;
        is_pause = false;
        // reposition
        character.reset();
        catus.reset();
        tree.reset();

        timer.stop();
        gameLoop(e, gRenderer);
    }else if(e.key.keysym.sym == SDLK_ESCAPE) is_exit = true;
}

void render_before_and_while_play(SDL_Renderer* gRenderer)
{
    // Set text to be rendered
    timeText.str("");
    timeText << (timer.getTicks() / 300);

    // Render score (time)
    if(!current_score.load_from_rendered_text(timeText.str().c_str(), textColor, gRenderer, gFont)){
        cout << "Unable to render time texture!" << endl;
    }
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(gRenderer);


	gDino_background.render(0, 0, gRenderer);
    character.render(gDino, gRenderer);
    catus.render_1(gThreat1, gRenderer);
    tree.render_2(gThreat2, gRenderer);


    if(!is_start_game){
        Start_game.render(300, 150, gRenderer);
        exit_game.render(300, 180, gRenderer);
    }

	if(is_start_game){
        if(!is_game_over) {
            catus.move();
            tree.move();
            if(is_pause) gPause.render(0, 0, gRenderer);
            else gResume.render(0, 0, gRenderer);
        }
        // Render Score
        gScore.render(700, 30, gRenderer);
        current_score.render(750, 30, gRenderer);

    }
}

void render_gameover(SDL_Renderer* gRenderer)
{
    if((character.check_collision(threat1) || character.check_collision(threat2)) && !is_game_over) {
        Mix_PlayChannel(-1, gdeath, 0);
        is_game_over = true;
    }
    if(is_game_over){
        // Render text
        game_over.render(320, 140, gRenderer);
        play_again.render(300,160, gRenderer);
        exit_game.render(300, 180, gRenderer);

        //stop music
        if(Mix_PausedMusic() != 1) Mix_PauseMusic();

        // Stop character, threat, and time
        character.gameOver();
        catus.gameOver();
        tree.gameOver();
        timer.gameOver();
    }
}

void update_game()
{
    threat1 = catus.obstacle_1(); // update threat position
    threat2 = tree.obstacle_2();
    character.jump();

}
















