#pragma once
#include "Texture.h"
#include "Animation.h"

struct Sprite {
	Texture* texture = nullptr;
	Animation* animation = nullptr;
	RectangleOld rect;
	void LoadTexture(Texture* const param_texture);
	void LoadAnimation(Animation* const param_animation);
};