#pragma once
#include "Texture.h"
#include <iostream>

using namespace std;

string GetTextureName(char char_value);

struct FontChar
{
	Texture* texture;

	char char_value;

	int default_width;
	int default_height;

	int default_unscaled_x_offset;
	int default_unscaled_y_offset;

	int default_char_spacing;

	FontChar(Texture* param_texture, char param_char_value, int param_default_char_spacing);
};

