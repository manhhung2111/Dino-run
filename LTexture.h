#ifndef L_TEXTURE_H_
#define L_TEXTURE_H_

#include "common_functions.h"

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

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};
#endif // L_TEXTURE_H_
