#include "TextBoxChar.h"

TextBoxChar::TextBoxChar() : font_char(nullptr), char_spacing(0.0), r_mod(0), g_mod(0), b_mod(0) {}

void TextBoxChar::InitWithFontChar(Rectangle* reference_rect, FontChar* param_font_char)
{
	font_char = param_font_char;

	rect.data.base_size.width = (double)param_font_char->default_width;
	rect.data.base_size.height = (double)param_font_char->default_height;
	rect.data.SetSizeWithSizeScale({ 1.0, 1.0 });

	rect.data.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rect.data.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rect.SetReferenceRectangle(reference_rect);

	char_spacing = (double)param_font_char->default_char_spacing;
}
void TextBoxChar::InitWithFontChar(Rectangle* reference_rect, FontChar* param_font_char, Uint8 param_r_mod, Uint8 param_g_mod, Uint8 param_b_mod)
{
	font_char = param_font_char;

	rect.data.base_size.width = (double)param_font_char->default_width;
	rect.data.base_size.height = (double)param_font_char->default_height;
	rect.data.SetSizeWithSizeScale({ 1.0, 1.0 });

	rect.data.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rect.data.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rect.SetReferenceRectangle(reference_rect);

	char_spacing = (double)param_font_char->default_char_spacing;


	r_mod = param_r_mod;
	g_mod = param_g_mod;
	b_mod = param_b_mod;
}
void TextBoxChar::GetRectangleWithSpacing(bool include_left_spacing, bool include_right_spacing)
{

}