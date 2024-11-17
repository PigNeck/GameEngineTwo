#include "TextBoxChar.h"

void TextBoxChar::InitLeast(Rectangle* const reference_rect, FontChar* const param_font_char)
{
	font_char = param_font_char;

	rect.base_size.width = (double)param_font_char->default_width;
	rect.base_size.height = (double)param_font_char->default_height;
	rect.SetSizeWithSizeScale({ 1.0, 1.0 });

	rect.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rect.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rect.reference_rectangle = reference_rect;

	char_spacing = (double)param_font_char->default_char_spacing;
}
void TextBoxChar::InitMost(Rectangle* const reference_rect, FontChar* const param_font_char, const Uint8 param_r_mod, const Uint8 param_g_mod, const Uint8 param_b_mod, const Uint8 param_a_mod)
{
	font_char = param_font_char;

	rect.base_size.width = (double)param_font_char->default_width;
	rect.base_size.height = (double)param_font_char->default_height;
	rect.SetSizeWithSizeScale({ 1.0, 1.0 });

	rect.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rect.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rect.reference_rectangle = reference_rect;

	char_spacing = (double)param_font_char->default_char_spacing;


	r_mod = param_r_mod;
	g_mod = param_g_mod;
	b_mod = param_b_mod;
	a_mod = param_a_mod;
}

void TextBoxChar::GetRectangleWithSpacing(const bool include_left_spacing, const bool include_right_spacing) const
{

}

void TextBoxChar::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list)
{
	debug_data_container.InitMost(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &rect, param_debug_data_container_active_scenes, param_white_list, 2.0, 2.0);
	debug_data_container.AddRectangleData(&rect, "Rect");
}
