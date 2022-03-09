#include"LTexture.h"
#include"common_functions.h"
#include"LTimer.h"
#include"Motion.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;

// Music
Mix_Music *gMusic = NULL;

// The sound effects that will be used
Mix_Chunk *gjump = NULL;
Mix_Chunk *gdeath = NULL;

// Image
LTexture gDino;
LTexture gDino_background;
LTexture gScore;
LTexture hiscore;

bool init();
bool loadMedia();
void close();

int main(int argc, char* argv[])
{
    if(!init()){
        cout << "Failed to initialize SDL!" << endl;
    }else{
        if(!loadMedia()){
            cout << "Failed to load media!" << endl;
        }else{
            bool quit = false;
            SDL_Event e;
            Dino character;
            SDL_Color textColor = {0, 0, 0, 255};
            LTimer timer;
            stringstream timeText;
            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
                        if(e.key.keysym.sym == SDLK_SPACE){
                            Mix_PlayChannel(-1, gjump, 0);
                            character.setJump_press(e);
                        }
						//Start/stop
						if( e.key.keysym.sym == SDLK_s ){
                            if(Mix_PlayingMusic() == 0) {Mix_PlayMusic(gMusic, -1);}

							if( timer.isStarted() ) timer.stop();
							else timer.start();
						}
						//Pause/unpause
						else if( e.key.keysym.sym == SDLK_p ){
						    if(Mix_PausedMusic() == 1) Mix_ResumeMusic();
                            else Mix_PauseMusic();

							if( timer.isPaused() ) timer.unpause();
							else timer.pause();

						}
                    }else if(e.type == SDL_KEYUP){
                        character.setJump_release(e);
                    }
                }
                // Set text to be rendered
                timeText.str("");
                timeText << (timer.getTicks() / 300);
                // Render time
                if(!hiscore.load_from_rendered_text(timeText.str().c_str(), textColor)){
                    cout << "Unable to render time texture!" << endl;
                }

                // clear screen
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                SDL_RenderClear(gRenderer);


                gDino_background.render(0, 0);

                character.render();
                //gDino.render(0, 250);
                gScore.render(700, 30);
                hiscore.render(720, 30);
                SDL_RenderPresent(gRenderer);
                /*
                int real_imp_time = fps_timer.get_ticks();
                int time_one_frame = 1000/FRAME_PER_SECOND; //ms

                if(real_imp_time < time_one_frame){
                    int delay_time = time_one_frame - real_imp_time;
                    SDL_Delay(delay_time);
                }
                */


            }

        }
    }
    close();
    return 0;
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
        cout << "Could not load Dino background"<< endl;
        success =false;
    }

    // Load character
    if(!gDino.load_media_from_file("img\\Dino.png")){
        cout << "Could not load Dino" << endl;
        success = false;
    }

    // Load music
    gMusic = Mix_LoadMUS("music\\mission-imposible.mp3");
    if(gMusic == NULL){
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    gjump = Mix_LoadWAV("music\\jumping.wav");
    if(gjump == NULL){
        cout << "Failed to load jumping sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // Open the font
    gFont = TTF_OpenFont("font.ttf", 14);
    if(gFont == NULL){
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success =false;
    }else{
        SDL_Color textColor = {0, 0, 0, 255};
        // Load high score:
        if(!gScore.load_from_rendered_text("Hi:", textColor)){
            cout << "Unable to render high score texture!" << endl;
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
void Dino::render(){
    gDino.render(mPosX, mPosY);
}
