#pragma once
#include "Font.h"

struct TextBoxChar
{
	FontChar* font_char;
	Rectangle rect;
	double char_spacing;

	Uint8 r_mod;
	Uint8 g_mod;
	Uint8 b_mod;

	TextBoxChar();

	void InitWithFontChar(Rectangle* reference_rect, FontChar* param_font_char);
	void InitWithFontChar(Rectangle* reference_rect, FontChar* param_font_char, Uint8 param_r_mod, Uint8 param_g_mod, Uint8 param_b_mod);
	void GetRectangleWithSpacing(bool include_left_spacing, bool include_right_spacing);
};