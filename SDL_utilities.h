#ifndef SDL_UTILITIES_H_
#define SDL_UTILITIES_H_

#include"LTexture.h"
#include"Functions.h"

// Initialize SDL_Window, SDL_Renderer
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const char* WINDOW_TITLE);

// Load images, texts, music, sounds
bool loadMedia(LTexture &gPlayer_jump, LTexture &gPlayer_background, LTexture &gThreat1, LTexture &gThreat2, LTexture &gPause,
               LTexture &gResume, LTexture &gScore, LTexture &game_over,LTexture &play_again, LTexture &exit_game,
               Mix_Music *&gMusic, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, SDL_Renderer* &gRenderer, LTexture &gPlayer_ground, SDL_Rect &player_rect,
               int &frame_width, LTexture &gHiscore, LTexture &gRocket1, LTexture &gRocket2, LTexture &gWarning, LTexture &how_to_play);

// Free all iamges, texts, music, sounds and SDL libraries
void close(LTexture &gPlayer_jump, LTexture &gPlayer_background, LTexture &gThreat1, LTexture &gThreat2,
           LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over, LTexture &play_again,
           LTexture &exit_game, Mix_Music *&gMusic, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, LTexture &current_score, SDL_Window *&gWindow, SDL_Renderer* &gRenderer,
           LTexture &gPlayer_ground, LTexture &gHiscore, LTexture &gRocket1, LTexture &gRocket2, LTexture &gWarning, LTexture &how_to_play);

#endif // SDL_UTILITIES_H_
