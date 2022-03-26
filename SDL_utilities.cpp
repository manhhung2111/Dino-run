#include"SDL_utilities.h"
#include"LTexture.h"

bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const char* WINDOW_TITLE)
{
    // Initialize flag
    bool success = true;
    // Initialize SDL and SDL_mixer
    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0){
        cout << "Could not initialize SDL! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }else{
        // Create window
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(gWindow == NULL){
            cout << "Could not create window! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }else{
            //Set texture filtering to linear
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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

bool loadMedia(LTexture &gDino, LTexture &gDino_background, LTexture &gThreat1, LTexture &gThreat2,
               LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &Start_game, LTexture &game_over,LTexture &play_again,
               LTexture &exit_game, Mix_Music *&gMusic, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, SDL_Renderer* &gRenderer)
{
    bool success = true;

    // Load character
    if(!gDino.load_media_from_file("img\\Dino.png", gRenderer)){
        cout << "Could not load Dino" << endl;
        success = false;
    }

    // Load background
    if(!gDino_background.load_media_from_file("img\\Dino-background.png", gRenderer)){
        cout << "Could not load Dino background" << endl;
        success = false;
    }

    // Load threat_1
    if(!gThreat1.load_media_from_file("img\\Threat_1.png", gRenderer)){
        cout << "Could not load Threats" << endl;
        success = false;
    }

    // Load threat_2
    if(!gThreat2.load_media_from_file("img\\Threat_2.png", gRenderer)){
        cout << "Could not load Threats" << endl;
        success = false;
    }

    // Load pause img
    if(!gPause.load_media_from_file("img\\pause.png", gRenderer)){
        cout << "Could not load pause img" << endl;
        success = false;
    }

    // Load resume img
    if(!gResume.load_media_from_file("img\\resume.png", gRenderer)){
        cout << "Could not load resume img" << endl;
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
        if(!gScore.load_from_rendered_text("Score:", textColor, gRenderer, gFont)){
            cout << "Unable to render score texture!" << endl;
            success = false;
        }
        if(!Start_game.load_from_rendered_text("Press S to play game", textColor, gRenderer, gFont)){
            cout << "Unable to render start game texture!" << endl;
            success = false;
        }
        if(!game_over.load_from_rendered_text("GAME OVER!", textColor, gRenderer, gFont)){
            cout << "Unable to render game over texture!" << endl;
            success = false;
        }
        if(!play_again.load_from_rendered_text("To play again, press R", textColor, gRenderer, gFont)){
            cout << "Unable to render play again texture!" << endl;
            success = false;
        }
        if(!exit_game.load_from_rendered_text("To exit the game, press ESC", textColor, gRenderer, gFont)){
            cout << "Unable to render exit game texture!" << endl;
            success = false;
        }

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

    return success;
}

void close(LTexture &gDino, LTexture &gDino_background, LTexture &gThreat1, LTexture &gThreat2,
            LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &Start_game, LTexture &game_over,
            LTexture &play_again, LTexture &exit_game, Mix_Music *&gMusic, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont,
            LTexture &current_score, SDL_Window *&gWindow, SDL_Renderer* &gRenderer)
{
    gDino.free(); gDino_background.free();
    gScore.free(); current_score.free();
    gPause.free(); gResume.free();
    gThreat1.free(); gThreat2.free();
    Start_game.free();
    game_over.free();
    play_again.free();
    exit_game.free();

    TTF_CloseFont(gFont); gFont = NULL;
    Mix_FreeMusic(gMusic); gMusic = NULL;
    Mix_FreeChunk(gjump); gjump = NULL;
    Mix_FreeChunk(gdeath); gdeath = NULL;
    SDL_DestroyRenderer(gRenderer); gRenderer = NULL;
    SDL_DestroyWindow(gWindow); gWindow = NULL;

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}
