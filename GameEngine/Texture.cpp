#include "Texture.h"

/*
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
*/



Texture::~Texture()
{
    glDeleteTextures(1, &gl_texture_id);
}

void Texture::LoadTexture(const char* const path)
{
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
        throw;
    }

    glGenTextures(1, &gl_texture_id);
    glBindTexture(GL_TEXTURE_2D, gl_texture_id);

    // Specify the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Set the proper glTex format
    GLint format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    // Upload the texture to the GPU
    glTexImage2D(
        GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0,
        format, GL_UNSIGNED_BYTE, surface->pixels
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    //Set member dimentions to fit texture dimentions
    width = surface->w;
    height = surface->h;

    //Clean up that doodoo
    SDL_FreeSurface(surface);
    glBindTexture(GL_TEXTURE_2D, 0);
}