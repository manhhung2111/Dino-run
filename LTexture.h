#ifndef L_TEXTURE_H_
#define L_TEXTURE_H_

#include "Functions.h"

class LTexture
{
public:
    LTexture(); // constructor
    ~LTexture(); // destructor

    // load media
    bool load_media_from_file(string path );
    bool load_from_rendered_text(string textureText, SDL_Color textColor );

    void free();

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL);
    SDL_Texture* GetTexture();
    //Gets texture dimensions
    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    //Texture dimensions
    int mWidth;
    int mHeight;
};
#endif // L_TEXTURE_H_
