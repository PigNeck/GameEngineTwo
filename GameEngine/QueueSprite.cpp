#include "QueueSprite.h"

QueueSprite::QueueSprite()
{
	texture = nullptr;
	camera = nullptr;
	flip = SDL_FLIP_NONE;
	rotation = 0.0;
	layer = 0;
}