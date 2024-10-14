#pragma once
#include "Rectangle.h"
#include "FontChar.h"


struct TextBoxCharData
{
	FontChar* font_char = nullptr;
	Rectangle rectangle;
	double char_spacing = 0.0;

	Uint8 r_mod = 0;
	Uint8 g_mod = 0;
	Uint8 b_mod = 0;
	Uint8 a_mod = 255;

	void InitLeast(Rectangle* const reference_rectangle, FontChar* const param_font_char);
	void InitMost(Rectangle* const reference_rectangle, FontChar* const param_font_char, const Uint8 param_r_mod, const Uint8 param_g_mod, const Uint8 param_b_mod, const Uint8 param_a_mod);
	void GetRectangleWithSpacing(const bool include_left_spacing, const bool include_right_spacing) const;
};
