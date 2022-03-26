#include"Functions.h"
#include"LTexture.h"

LTexture::LTexture(){
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

void LTexture::free(){
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

LTexture::~LTexture(){
    free();
}

void LTexture::render(int x, int y, SDL_Renderer* &gRenderer){
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

bool LTexture::load_media_from_file(string path, SDL_Renderer* &gRenderer){
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

bool LTexture::load_from_rendered_text(string textureText, SDL_Color textColor, SDL_Renderer* &gRenderer, TTF_Font *&gFont)
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

int LTexture::getHeight(){
    return mHeight;
}

int LTexture::getWidth(){
    return mWidth;
}

