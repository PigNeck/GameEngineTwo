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

