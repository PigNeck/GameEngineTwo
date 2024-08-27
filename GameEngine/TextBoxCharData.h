#pragma once
#include "RectangleData.h"
#include "FontChar.h"


struct TextBoxCharData
{
	FontChar* font_char;
	RectangleData rectangle_data;
	double char_spacing;

	Uint8 r_mod;
	Uint8 g_mod;
	Uint8 b_mod;

	TextBoxCharData();

	void InitWithFontChar(RectangleData* reference_rectangle_data, FontChar* param_font_char);
	void InitWithFontChar(RectangleData* reference_rectangle_data, FontChar* param_font_char, Uint8 param_r_mod, Uint8 param_g_mod, Uint8 param_b_mod);
	void GetRectangleWithSpacing(bool include_left_spacing, bool include_right_spacing);
};
