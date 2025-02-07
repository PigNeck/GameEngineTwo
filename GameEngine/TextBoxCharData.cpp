#include "TextBoxCharData.h"

void TextBoxCharData::InitLeast(RectangleOld* const reference_rectangle, FontChar* const param_font_char)
{
	font_char = param_font_char;

	rectangle.base_size.width = (double)param_font_char->default_width;
	rectangle.base_size.height = (double)param_font_char->default_height;
	rectangle.SetSizeWithSizeScale({ 1.0, 1.0 });

	rectangle.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rectangle.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rectangle.reference_rectangle = reference_rectangle;

	char_spacing = (double)param_font_char->default_char_spacing;
}
void TextBoxCharData::InitMost(RectangleOld* const reference_rectangle, FontChar* const param_font_char, const Uint8 param_r_mod, const Uint8 param_g_mod, const Uint8 param_b_mod, const Uint8 param_a_mod)
{
	font_char = param_font_char;

	rectangle.base_size.width = (double)param_font_char->default_width;
	rectangle.base_size.height = (double)param_font_char->default_height;
	rectangle.SetSizeWithSizeScale({ 1.0, 1.0 });

	rectangle.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rectangle.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rectangle.reference_rectangle = reference_rectangle;

	char_spacing = (double)param_font_char->default_char_spacing;


	r_mod = param_r_mod;
	g_mod = param_g_mod;
	b_mod = param_b_mod;
	a_mod = param_a_mod;
}
void TextBoxCharData::GetRectangleWithSpacing(const bool include_left_spacing, const bool include_right_spacing) const
{

}
