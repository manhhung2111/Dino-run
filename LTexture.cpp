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

int LTexture::getHeight(){
    return mHeight;
}

int LTexture::getWidth(){
    return mWidth;
}

SDL_Texture* LTexture::GetTexture()
{
    return mTexture;
}
