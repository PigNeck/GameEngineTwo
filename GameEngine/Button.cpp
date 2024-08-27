#include "Button.h"

void Button::InitLeast()
{
	//Do nothing lmao
}
void Button::InitMost(const Rectangle param_parent_rect, const Rectangle param_hitbox, const Sprite param_released_sprite, const Sprite param_hovering_sprite, const Sprite param_pressed_sprite)
{
	parent_rect = param_parent_rect;
	hitbox = param_hitbox;
	released_sprite = param_released_sprite;
	hovering_sprite = param_hovering_sprite;
	pressed_sprite = param_pressed_sprite;
}
void Button::InitWithTexturesAndSizeScale(Texture* param_released_texture, Texture* param_hovering_texture, Texture* param_pressed_texture, Size2D texture_size_scale)
{
	released_sprite.LoadTexture(param_released_texture);
	released_sprite.rect.data.SetSizeWithSizeScale(texture_size_scale);
	released_sprite.rect.SetReferenceRectangle(&parent_rect);

	hovering_sprite.LoadTexture(param_hovering_texture);
	hovering_sprite.rect.data.SetSizeWithSizeScale(texture_size_scale);
	hovering_sprite.rect.SetReferenceRectangle(&parent_rect);

	pressed_sprite.LoadTexture(param_pressed_texture);
	pressed_sprite.rect.data.SetSizeWithSizeScale(texture_size_scale);
	pressed_sprite.rect.SetReferenceRectangle(&parent_rect);

	hitbox.data.base_size = released_sprite.rect.data.base_size;
	hitbox.data.size = released_sprite.rect.data.size;
	hitbox.SetReferenceRectangle(&parent_rect);

	parent_rect.data.base_size = released_sprite.rect.data.size;
	parent_rect.data.size = released_sprite.rect.data.size;
}

void Button::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes)
{
	debug_data_container.Init(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &parent_rect.data, param_debug_data_container_active_scenes);
	debug_data_container.AddRectangleData(&parent_rect.data, "Parent Rect");
	debug_data_container.AddRectangleData(&released_sprite.rect.data, "Released Sprite Rect");
	debug_data_container.AddRectangleData(&hovering_sprite.rect.data, "Hovering Sprite Rect");
	debug_data_container.AddRectangleData(&pressed_sprite.rect.data, "Pressed Sprite Rect");
	//Add stuff like default_font name and so on later
}
