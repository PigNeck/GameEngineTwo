#pragma once
#include "Texture.h"
#include "Animation.h"

struct Sprite {
	Texture* texture;
	Animation* animation;
	Rectangle rect;
	void LoadTexture(Texture* param_texture);
	void LoadAnimation(Animation* param_animation);
	Sprite();
};