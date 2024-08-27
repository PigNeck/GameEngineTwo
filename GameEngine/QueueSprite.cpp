#include "QueueSprite.h"

QueueSprite::QueueSprite()
{
	texture = nullptr;
	rect = Rectangle();
	camera = nullptr;
	flip = SDL_FLIP_NONE;
	rotation = 0.0;
	layer = 0;
}