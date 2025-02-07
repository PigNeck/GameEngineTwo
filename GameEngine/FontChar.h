#pragma once
#include "Texture.h"
#include <iostream>

using namespace std;

string GetTextureName(char char_value);

struct FontChar
{
	Texture* texture;

	char char_value;

	double default_width;
	double default_height;

	double default_unscaled_x_offset;
	double default_unscaled_y_offset;

	double default_char_spacing;

	FontChar(Texture* param_texture, char param_char_value, double param_default_char_spacing);
};



struct BasicFontChar //Serves as a template for BasicTextBoxChars. Font chars primarily hold default data for text box chars.
{
	const Texture* texture = nullptr;

	char char_value = 0;

	double template_pixel_width = 0.0; //Should usually be set to texture->width, but technicallyyy doesn't have to (if sub-int precision is wanted or you just want to engage in some funky business).
	double template_pixel_height = 0.0; //Should usually be set to texture->height, but technicallyyy doesn't have to (if sub-int precision is wanted or you just want to engage in some funky business).

	double template_pixel_x_offset = 0.0; //[pixel_x_offset] moves the char from its default x position, but DOES NOT change the generated positions of any of the other letters. [pixel_x_offset] should almost always equal 0.0.
	double template_pixel_y_offset = 0.0; //[pixel_y_offset] moves the char from its default y position. When being drawn, chars are snapped to the bottom of their text_box_line, but some chars like asterisk and apostrophe should not be bottom-bound, so their [pixel_y_offset] values should typically be set to be above 0.0.

	double template_pixel_spacing = 0.0; //Spacing applied to both sides to the char.

	BasicFontChar();
	//Just sets [char_value] to [i_char_value]! [texture] remains nullptr and [pixel_width], [pixel_height], [pixel_x_offset], and [pixel_y_offset] all remain 0.0.
	BasicFontChar(const char i_char_value);
	//IMPORTANT: Sets [pixel_width] and [pixel_height] based on the dimentions of the texture!;  Sets [char_value] and [texture] to their corresponding arguments. [pixel_x_offset] and [pixel_y_offset] stay as 0.0 though.
	BasicFontChar(const char i_char_value, const Texture* const i_texture);
	//Sets [char_value], [texture], [pixel_width] and [pixel_height] to their corresponding arguments. [pixel_x_offset] and [pixel_y_offset] stay as 0.0.
	BasicFontChar(const char i_char_value, const Texture* const i_texture, const double i_template_pixel_width, const double i_template_pixel_height);
	//IMPORTANT: Sets [pixel_width] and [pixel_height] based on the dimentions of the texture!;  Sets [char_value], [texture], [pixel_x_offset] and [pixel_y_offset] to their corresponding arguments.
	BasicFontChar(const char i_char_value, const Texture* const i_texture, const double i_template_pixel_x_offset, const double i_template_pixel_y_offset);
	//Sets all the member variables to initial values!
	BasicFontChar(const char i_char_value, const Texture* const i_texture, const double i_template_pixel_width, const double i_template_pixel_height, const double i_template_pixel_x_offset, const double i_template_pixel_y_offset);

	void InitLeast(const Texture* const i_texture, const char i_char_value);
	void InitWithOffset(const Texture* const i_texture, const char i_char_value, const double i_template_pixel_x_offset, const double i_template_pixel_y_offset);
	void InitMost(const Texture* const i_texture, const char i_char_value, const double i_template_pixel_width, const double i_template_pixel_height, const double i_template_pixel_x_offset, const double i_template_pixel_y_offset);

	//IMPORTANT: Sets [pixel_width] and [pixel_height] to fit the dimentions of [i_texture]!;  Also obviously sets [texture] to [i_texture].
	void SetTexture(const Texture* const i_texture);
};