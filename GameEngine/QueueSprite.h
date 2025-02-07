#pragma once
#include "Texture.h"
#include "Rectangle.h"
#include "Camera.h"
#include "Tools.h"

struct QueueSprite
{
	Texture* texture;
	RectangleOld rect;
	Camera* camera;
	SDL_RendererFlip flip;
	double rotation;
	int layer;

	QueueSprite();
};

struct QueueSpriteQueue
{
	vector<QueueSprite> queue;
	int layer;
};

