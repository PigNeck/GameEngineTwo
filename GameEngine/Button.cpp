#include "Button.h"

void PressData::Reset()
{
	previous_frame_pressed = 0;
	first_frame_pressed = 0;
	first_frame_released = 0;
	pressed = 0;

	previous_frame_hovering = 0;
	first_frame_hovering = 0;
	first_frame_not_hovering = 0;
	hovering = 0;
}


void Button::InitLeast()
{
	//Do nothing lmao
}
void Button::InitMost(const Rectangle param_parent_rect, const Rectangle param_hitbox, const Sprite param_released_sprite, const Sprite param_hovering_sprite, const Sprite param_pressed_sprite, const ButtonSoundData param_sounds)
{
	parent_rect = param_parent_rect;
	hitbox = param_hitbox;
	released_sprite = param_released_sprite;
	hovering_sprite = param_hovering_sprite;
	pressed_sprite = param_pressed_sprite;

	sounds = param_sounds;
}
void Button::InitWithTexturesAndSizeScale(Texture* param_released_texture, Texture* param_hovering_texture, Texture* param_pressed_texture, Size2D texture_size_scale)
{
	released_sprite.LoadTexture(param_released_texture);
	released_sprite.rect.SetSizeWithSizeScale(texture_size_scale);
	released_sprite.rect.reference_rectangle = &parent_rect;

	hovering_sprite.LoadTexture(param_hovering_texture);
	hovering_sprite.rect.SetSizeWithSizeScale(texture_size_scale);
	hovering_sprite.rect.reference_rectangle = &parent_rect;

	pressed_sprite.LoadTexture(param_pressed_texture);
	pressed_sprite.rect.SetSizeWithSizeScale(texture_size_scale);
	pressed_sprite.rect.reference_rectangle = &parent_rect;

	hitbox.base_size = released_sprite.rect.base_size;
	hitbox.size = released_sprite.rect.size;
	hitbox.reference_rectangle = &parent_rect;

	parent_rect.base_size = released_sprite.rect.size;
	parent_rect.size = released_sprite.rect.size;
}

void Button::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list)
{
	debug_data_container.InitLeast(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &parent_rect, param_debug_data_container_active_scenes, param_white_list);
	debug_data_container.AddRectangleData(&parent_rect, "Parent Rect");
	debug_data_container.AddRectangleData(&released_sprite.rect, "Released Sprite Rect");
	debug_data_container.AddRectangleData(&hovering_sprite.rect, "Hovering Sprite Rect");
	debug_data_container.AddRectangleData(&pressed_sprite.rect, "Pressed Sprite Rect");
	//Add stuff like default_font name and so on later
}
