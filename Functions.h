#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include<SDL.h>
#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<sstream>


using namespace std;

//Screen
static const char *WINDOW_TITLE = "Snowball-Adventure";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
static const int ground_level = 332;

// Color key (transparent image)
const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;
const int RENDER_DRAW_COLOR = 255;

const int FPS = 60;

#endif // FUNCTION_H

