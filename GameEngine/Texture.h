#pragma once
#include "RectangleNew.h"
#include <iostream>
#include "SDL_image.h"

struct Texture
{
	//SDL_Texture* sdl_texture;

	unsigned int width = 0; //In pixels!
	unsigned int height = 0; //In pixels!

	~Texture();

	void LoadTexture(const char* const path);

	//void LoadTexture(SDL_Renderer* const renderer, const char* path);

	//PSEUDO PRIVATE;  Don't mess with this unless you know what you are doing!
	GLuint gl_texture_id = 0;
};

