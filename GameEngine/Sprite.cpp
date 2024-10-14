#include "Sprite.h"

void Sprite::LoadTexture(Texture* param_texture)
{
	texture = param_texture;
	rect.base_size = param_texture->size;
	rect.size = param_texture->size;
}

void Sprite::LoadAnimation(Animation* param_animation)
{
	param_animation->frame_progression = 0.0;

	animation = param_animation;

	Size2D temp_size_scale = rect.GetSizeScale();
	rect.base_size = param_animation->dimentions;
	rect.SetSizeWithSizeScale(temp_size_scale);

	rect.offset = param_animation->offset;
}

Sprite::Sprite()
{
	texture = nullptr;
	animation = nullptr;
}