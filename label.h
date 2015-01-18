#ifndef label_INCLUDE
#define label_INCLUDE
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

class Label{
public:
	Label(); //declaring constructor member
	~Label();//declaring deconstructor member

	bool textToTexture(const char* text, TTF_Font* textFont, SDL_Color colour);
	void draw(float x, float y);
	GLuint getWidth(){ return width; } //accessor function for width
	GLuint getHeight(){ return height; } //accessor function for height

private:
	GLuint texID;
	GLuint height;
	GLuint width;

	int powerOfTwo(int x);

};



#endif
