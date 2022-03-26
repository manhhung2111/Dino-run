#ifndef SDL_UTILITIES_H_
#define SDL_UTILITIES_H_

#include"LTexture.h"
#include"Functions.h"

// Initialize
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const char* WINDOW_TITLE);
bool loadMedia(LTexture &gDino, LTexture &gDino_background, LTexture &gThreat1, LTexture &gThreat2,
               LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &Start_game, LTexture &game_over,LTexture &play_again,
               LTexture &exit_game, Mix_Music *&gMusic, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, SDL_Renderer* &gRenderer);
void close(LTexture &gDino, LTexture &gDino_background, LTexture &gThreat1, LTexture &gThreat2,
            LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &Start_game, LTexture &game_over,
            LTexture &play_again, LTexture &exit_game, Mix_Music *&gMusic, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont,
            LTexture &current_score, SDL_Window *&gWindow, SDL_Renderer* &gRenderer);



#endif // SDL_UTILITIES_H_
