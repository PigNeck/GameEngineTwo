#pragma once
#include "Rectangle.h"
#include <iostream>
#include "SDL_image.h"

struct Texture
{
	SDL_Texture* sdl_texture;
	Size2D size;

	Texture();
	void LoadTexture(SDL_Renderer* const renderer, const char* path);
};

