#include"LTexture.h"
#include"Functions.h"
#include"LTimer.h"
#include"Character.h"
#include"Threats.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
SDL_Event e;

// Music
Mix_Music *gMusic = NULL;

// The sound effects that will be used
Mix_Chunk *gjump = NULL;
Mix_Chunk *gdeath = NULL;

// Image
LTexture gDino;
LTexture gDino_background;
LTexture gThreat1;
LTexture gThreat2;
LTexture gPause;
LTexture gResume;

// Text on screen
LTexture gScore;
LTexture Start_game;
LTexture current_score;
LTexture game_over;
LTexture play_again;
LTexture exit_game;

// In game features
bool is_game_over = false, is_exit = false, is_pause = false;
bool is_start_game = false, is_timer_start = false, is_music_play = false;
Character character; // character
Threat catus, tree; // threat
SDL_Color textColor = {0, 0, 0, 255}; // score text color
LTimer timer; // score
stringstream timeText; // score
SDL_Rect threat1; // location of threat after each loop
SDL_Rect threat2;


bool init();
bool loadMedia();
void close();
void playAgain();
void gameloop();
void render_before_and_while_play();
void render_gameover();
void handle_keyboard_events();
void update_game();

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if(!init()){
        cout << "Failed to initialize SDL!" << endl;
    }else{
        if(!loadMedia()){
            cout << "Failed to load media!" << endl;
        }else{
            gameloop();
        }
    }
    close();
    return 0;
}


void gameloop()
{
    while(!is_exit){
        update_game();
        handle_keyboard_events();

        render_before_and_while_play();
        render_gameover();

        SDL_RenderPresent(gRenderer);
    }
}

void playAgain(){
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
        gameloop();
    }else if(e.key.keysym.sym == SDLK_ESCAPE) is_exit = true;
}


bool init()
{
    // Initialize flag
    bool success = true;
    // Initialize SDL and SDL_mixer
    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0){
        cout << "Could not initialize SDL! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }else{
        // Create window
        gWindow = SDL_CreateWindow("Dino run", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(gWindow == NULL){
            cout << "Could not create window! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }else{
            //Set texture filtering to linear
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
            if(gRenderer == NULL){
                cout << "Could not create renderer! SDL Error:" << SDL_GetError() << endl;
                success = false;
            }else{
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                // Initialize SDL_image
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) && imgFlags)){
                    cout << "Could not initialize SDL_image! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }

                //Initialize SDL_mixer
                // Mix_OpenAudio(sound frequency, the sample format, number of hardware channels, size of chunk sound)
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError() << endl;
					success = false;
				}

            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    // Load background
    if(!gDino_background.load_media_from_file("img\\Dino-background.png")){
        cout << "Could not load Dino background" << endl;
        success = false;
    }

    // Load threat
    if(!gThreat1.load_media_from_file("img\\Threat_1.png")){
        cout << "Could not load Threats" << endl;
        success = false;
    }

    if(!gThreat2.load_media_from_file("img\\Threat_2.png")){
        cout << "Could not load Threats" << endl;
        success = false;
    }

    // Load character
    if(!gDino.load_media_from_file("img\\Dino.png")){
        cout << "Could not load Dino" << endl;
        success = false;
    }

    if(!gPause.load_media_from_file("img\\pause.png")){
        cout << "Could not load pause img" << endl;
        success = false;
    }

    if(!gResume.load_media_from_file("img\\resume.png")){
        cout << "Could not load resume img" << endl;
        success = false;
    }

    // Load music
    gMusic = Mix_LoadMUS("music\\mission-imposible.mp3");
    if(gMusic == NULL){
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // load sounds
    gjump = Mix_LoadWAV("music\\jumping.wav");
    if(gjump == NULL){
        cout << "Failed to load jumping sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    gdeath = Mix_LoadWAV("music\\death.wav");
    if(gdeath == NULL){
        cout << "Failed to load death sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }


    // Open the font
    gFont = TTF_OpenFont("font.ttf", 16);
    if(gFont == NULL){
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success =false;
    }else{
        SDL_Color textColor = {0, 0, 0, 255};
        // Load high score:
        if(!gScore.load_from_rendered_text("Score:", textColor)){
            cout << "Unable to render score texture!" << endl;
            success = false;
        }
        if(!Start_game.load_from_rendered_text("Press S to play game", textColor)){
            cout << "Unable to render start game texture!" << endl;
            success = false;
        }
        if(!game_over.load_from_rendered_text("GAME OVER!", textColor)){
            cout << "Unable to render game over texture!" << endl;
            success = false;
        }
        if(!play_again.load_from_rendered_text("To play again, press R", textColor)){
            cout << "Unable to render play again texture!" << endl;
            success = false;
        }
        if(!exit_game.load_from_rendered_text("To exit the game, press ESC", textColor)){
            cout << "Unable to render exit game texture!" << endl;
            success = false;
        }

    }

    return success;
}

void close()
{
    gDino.free();
    gDino_background.free();
    gScore.free();
    current_score.free();
    game_over.free();
    play_again.free();
    exit_game.free();


    TTF_CloseFont(gFont); gFont = NULL;
    Mix_FreeMusic(gMusic); gMusic = NULL;
    Mix_FreeChunk(gjump); gjump = NULL;
    SDL_DestroyRenderer(gRenderer); gRenderer = NULL;
    SDL_DestroyWindow(gWindow); gWindow = NULL;

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}

bool LTexture::load_media_from_file(string path){
    //free();
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        cout << "Could not load image! SDL_image Error: " << IMG_GetError() << endl;
    }else{
        // Transparent picture
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL){
            cout << "Could not create Texture from image! SDL Error: " << SDL_GetError() << endl;
        }else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return (mTexture!=NULL);
}

void LTexture::render(int x, int y, SDL_Rect *clip){
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);

}

bool LTexture::load_from_rendered_text(string textureText, SDL_Color textColor)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if(textSurface != NULL){
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if(mTexture == NULL){
            cout << "Unable to create texture from text surface! SDL Error: " << SDL_GetError() << endl;
        }else{
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return (mTexture!=NULL);
}

void Character::render(){
    gDino.render(mPosX, mPosY);
}

void Threat::render_1(){
    gThreat1.render(mPosX_1, mPosY_1);
}

void Threat::render_2()
{
    gThreat2.render(mPosX_2, mPosY_2);
}

void Threat::move()
{
    if(!is_pause){
        mPosX_1 -= RUN_DISTANCE; //+ acceleration*(timer.getTicks()/10000));//move backward
        mPosX_2 -= RUN_DISTANCE;
        if(mPosX_1 < 0) mPosX_1 = SCREEN_WIDTH; // recreate the threat at the right of the screen
        if(mPosX_2 < 0) mPosX_2 = SCREEN_WIDTH + rand() % 200 + 300;
    }else{
        mPosX_1 = mPosX_1; // pause
        mPosX_2 = mPosX_2;
    }

}

void handle_keyboard_events()
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
            if(is_game_over) playAgain();
        }
    }
}

void render_before_and_while_play()
{
    // Set text to be rendered
    timeText.str("");
    timeText << (timer.getTicks() / 300);

    // Render score (time)
    if(!current_score.load_from_rendered_text(timeText.str().c_str(), textColor)){
        cout << "Unable to render time texture!" << endl;
    }
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(gRenderer);


	gDino_background.render(0, 0);
    character.render();
    catus.render_1();
    tree.render_2();


    if(!is_start_game){
        Start_game.render(300, 150);
        exit_game.render(300, 180);
    }

	if(is_start_game){
        if(!is_game_over) {
            catus.move();
            tree.move();
            if(is_pause) gPause.render(0, 0);
            else gResume.render(0, 0);
        }
        // Render Score
        gScore.render(700, 30);
        current_score.render(750, 30);

    }
}

void render_gameover()
{
    if((character.check_collision(threat1) || character.check_collision(threat2)) && !is_game_over) {
        Mix_PlayChannel(-1, gdeath, 0);
        is_game_over = true;
    }
    if(is_game_over){
        // Render text
        game_over.render(320, 140);
        play_again.render(300,160);
        exit_game.render(300, 180);

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
