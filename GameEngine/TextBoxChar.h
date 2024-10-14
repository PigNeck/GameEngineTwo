#pragma once
#include "Font.h"
#include "DebugDataContainer.h"

struct TextBoxChar
{
	FontChar* font_char = nullptr;
	Rectangle rect;
	double char_spacing = 0.0;

	Uint8 r_mod = 0;
	Uint8 g_mod = 0;
	Uint8 b_mod = 0;
	Uint8 a_mod = 255;

	DebugDataContainer debug_data_container;

	void InitLeast(Rectangle* const reference_rect, FontChar* const param_font_char);
	void InitMost(Rectangle* const reference_rect, FontChar* const param_font_char, const Uint8 param_r_mod, const Uint8 param_g_mod, const Uint8 param_b_mod, const Uint8 param_a_mod);

	void GetRectangleWithSpacing(const bool include_left_spacing, const bool include_right_spacing) const;

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list);
};