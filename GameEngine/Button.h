#pragma once
#include "Sprite.h"
#include "Rectangle.h"
#include "DebugDataContainer.h"
#include "SDL_mixer.h"

struct PressData
{
	bool previous_frame_pressed = 0;
	bool first_frame_pressed = 0;
	bool first_frame_released = 0;
	bool pressed = 0;

	bool previous_frame_hovering = 0;
	bool first_frame_hovering = 0;
	bool first_frame_not_hovering = 0;
	bool hovering = 0;

	bool hoverable = 1;
	bool pressable = 1;

	void Reset();
};

struct ButtonSoundData
{
	Mix_Chunk* hover_sound = nullptr;
	Mix_Chunk* no_hover_sound = nullptr;
	Mix_Chunk* press_sound = nullptr;
	Mix_Chunk* release_sound = nullptr;
	int channel = -1;
};

struct Button
{
	Sprite released_sprite;
	Sprite hovering_sprite;
	Sprite pressed_sprite;

	ButtonSoundData sounds;

	RectangleOld hitbox;

	RectangleOld parent_rect;

	PressData press_data;

	DebugDataContainer debug_data_container;

	bool visable = 1;

	void InitLeast();
	void InitMost(const RectangleOld param_parent_rect, const RectangleOld param_hitbox, const Sprite param_released_sprite, const Sprite param_hovering_sprite, const Sprite param_pressed_sprite, const ButtonSoundData param_sounds);
	void InitWithTexturesAndSizeScale(Texture* param_released_texture, Texture* param_hovering_texture, Texture* param_pressed_texture, Size2D texture_size_scale);

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list);
};

