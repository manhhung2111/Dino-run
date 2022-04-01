#ifndef L_TEXTURE_H_
#define L_TEXTURE_H_

#include "Functions.h"
using namespace std;

class LTexture
{
public:
    LTexture(); // Constructor
    ~LTexture(); // Destructor

    void free();

    // Load media
    bool load_media_from_file(string path, SDL_Renderer* &gRenderer);
    // Load texts
    bool load_from_rendered_text(string textureText, SDL_Color textColor, SDL_Renderer* &gRenderer, TTF_Font *&gFont);

    //Renders texture at given point
    void render( int x, int y,SDL_Renderer* &gRenderer);

    //Gets texture dimensions
    SDL_Texture* getTexture();
    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    //Texture dimensions
    int mWidth;
    int mHeight;
};
#endif // L_TEXTURE_H_
