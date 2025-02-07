#include "Sprite.h"

void Sprite::LoadTexture(Texture* const param_texture)
{
	if (param_texture == nullptr)
	{
		cerr << "param_texture was nullptr!!! Sent from void Sprite::LoadTexture(Texture* const param_texture)\n";
		throw;
	}

	texture = param_texture;
	rect.base_size = { (double)param_texture->width, (double)param_texture->height };
	rect.size = rect.base_size;
}

void Sprite::LoadAnimation(Animation* const param_animation)
{
	if (param_animation == nullptr)
	{
		cerr << "param_animation was nullptr!!! Sent from void Sprite::LoadAnimation(Animation* const param_animation)\n";
		throw;
	}

	param_animation->frame_progression = 0.0;

	animation = param_animation;

	Size2D temp_size_scale = rect.GetSizeScale();
	rect.base_size = param_animation->dimentions;
	rect.SetSizeWithSizeScale(temp_size_scale);

	rect.offset = param_animation->offset;
}