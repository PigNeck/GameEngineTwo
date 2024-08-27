#include "Texture.h"

Texture::Texture()
{
	sdl_texture = nullptr;
	size = { 1.0, 1.0 };
}

void Texture::LoadTexture(SDL_Renderer* const renderer, const char* path)
{
	SDL_Surface* tempSurface = IMG_Load(path);
	if (!tempSurface) {
		printf("Unable to load image: %s\n", IMG_GetError());
	}

	sdl_texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface); // Clean up the surface
	if (!sdl_texture) {
		printf("Unable to create texture: %s\n", SDL_GetError());
	}

	int width, height;
	SDL_QueryTexture(sdl_texture, NULL, NULL, &width, &height);
	size.width = width;
	size.height = height;
}