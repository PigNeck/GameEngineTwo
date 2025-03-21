#include "FontChar.h"

string GetTextureName(char char_value)
{
	string name = "char_";

	switch (char_value)
	{
	case 0: name += ""; break;
	case 1: name += ""; break;
	case 2: name += ""; break;
	case 3: name += ""; break;
	case 4: name += ""; break;
	case 5: name += ""; break;
	case 6: name += ""; break;
	case 7: name += ""; break;
	case 8: name += ""; break;
	case 9: name += ""; break;
	case 10: name += "new_line"; break;
	case 11: name += ""; break;
	case 12: name += ""; break;
	case 13: name += ""; break;
	case 14: name += ""; break;
	case 15: name += ""; break;
	case 16: name += ""; break;
	case 17: name += ""; break;
	case 18: name += ""; break;
	case 19: name += ""; break;
	case 20: name += ""; break;
	case 21: name += ""; break;
	case 22: name += ""; break;
	case 23: name += ""; break;
	case 24: name += ""; break;
	case 25: name += ""; break;
	case 26: name += ""; break;
	case 27: name += ""; break;
	case 28: name += ""; break;
	case 29: name += ""; break;
	case 30: name += ""; break;
	case 31: name += ""; break;
	case 32: name += "space"; break;
	case 33: name += "!"; break;
	case 34: name += "non-direction-dependent_double_quotation"; break;
	case 35: name += "#"; break;
	case 36: name += "$"; break;
	case 37: name += "%"; break;
	case 38: name += "&"; break;
	case 39: name += "non-direction-dependent_single_quotation"; break;
	case 40: name += "("; break;
	case 41: name += ")"; break;
	case 42: name += "asterisk"; break;
	case 43: name += "+"; break;
	case 44: name += ","; break;
	case 45: name += "-"; break;
	case 46: name += "."; break;
	case 47: name += "slash"; break;
	case 48: name += "0"; break;
	case 49: name += "1"; break;
	case 50: name += "2"; break;
	case 51: name += "3"; break;
	case 52: name += "4"; break;
	case 53: name += "5"; break;
	case 54: name += "6"; break;
	case 55: name += "7"; break;
	case 56: name += "8"; break;
	case 57: name += "9"; break;
	case 58: name += "colon"; break;
	case 59: name += ";"; break;
	case 60: name += "less_than"; break;
	case 61: name += "="; break;
	case 62: name += "greater_than"; break;
	case 63: name += "question_mark"; break;
	case 64: name += "@"; break;
	case 65: name += "A"; break;
	case 66: name += "B"; break;
	case 67: name += "C"; break;
	case 68: name += "D"; break;
	case 69: name += "E"; break;
	case 70: name += "F"; break;
	case 71: name += "G"; break;
	case 72: name += "H"; break;
	case 73: name += "I"; break;
	case 74: name += "J"; break;
	case 75: name += "K"; break;
	case 76: name += "L"; break;
	case 77: name += "M"; break;
	case 78: name += "N"; break;
	case 79: name += "O"; break;
	case 80: name += "P"; break;
	case 81: name += "Q"; break;
	case 82: name += "R"; break;
	case 83: name += "S"; break;
	case 84: name += "T"; break;
	case 85: name += "U"; break;
	case 86: name += "V"; break;
	case 87: name += "W"; break;
	case 88: name += "X"; break;
	case 89: name += "Y"; break;
	case 90: name += "Z"; break;
	case 91: name += "["; break;
	case 92: name += "backslash"; break;
	case 93: name += "]"; break;
	case 94: name += "^"; break;
	case 95: name += "_"; break;
	case 96: name += "`"; break;
	case 97: name += "lowercase_a"; break;
	case 98: name += "lowercase_b"; break;
	case 99: name += "lowercase_c"; break;
	case 100: name += "lowercase_d"; break;
	case 101: name += "lowercase_e"; break;
	case 102: name += "lowercase_f"; break;
	case 103: name += "lowercase_g"; break;
	case 104: name += "lowercase_h"; break;
	case 105: name += "lowercase_i"; break;
	case 106: name += "lowercase_j"; break;
	case 107: name += "lowercase_k"; break;
	case 108: name += "lowercase_l"; break;
	case 109: name += "lowercase_m"; break;
	case 110: name += "lowercase_n"; break;
	case 111: name += "lowercase_o"; break;
	case 112: name += "lowercase_p"; break;
	case 113: name += "lowercase_q"; break;
	case 114: name += "lowercase_r"; break;
	case 115: name += "lowercase_s"; break;
	case 116: name += "lowercase_t"; break;
	case 117: name += "lowercase_u"; break;
	case 118: name += "lowercase_v"; break;
	case 119: name += "lowercase_w"; break;
	case 120: name += "lowercase_x"; break;
	case 121: name += "lowercase_y"; break;
	case 122: name += "lowercase_z"; break;
	case 123: name += "{"; break;
	case 124: name += "vertical_slash"; break;
	case 125: name += "}"; break;
	case 126: name += "~"; break;
	case 127: name += ""; break;
	}

	name += ".png";

	return name;
}

FontChar::FontChar(Texture* param_texture, char param_char_value, double param_default_char_spacing)
{
	char_value = param_char_value;
	texture = param_texture;


	//Define default_width and default_height
	int int_width = 5;
	int int_height = 7;
	//SDL_QueryTexture(texture->sdl_texture, NULL, NULL, &int_width, &int_height);
	default_width = (double)int_width;
	default_height = (double)int_height;


	default_unscaled_x_offset = 0;
	default_unscaled_y_offset = 0;

	default_char_spacing = param_default_char_spacing;
}





BasicFontChar::BasicFontChar() {}
BasicFontChar::BasicFontChar(const BasicFont* const i_parent_font, const char i_char_value, const double i_template_unscaled_pixel_spacing_left, const double i_template_unscaled_pixel_spacing_right, const Point2DNew i_template_unscaled_pixel_offset, const Scale90 i_template_scale, const GLColor i_template_color_mod)
	: parent_font(i_parent_font),
	char_value(i_char_value),
	template_unscaled_pixel_spacing_left(i_template_unscaled_pixel_spacing_left),
	template_unscaled_pixel_spacing_right(i_template_unscaled_pixel_spacing_right),
	template_unscaled_pixel_offset(i_template_unscaled_pixel_offset),
	template_scale(i_template_scale),
    template_color_mod(i_template_color_mod) {}
BasicFontChar::BasicFontChar(const double i_template_unscaled_pixel_width, const BasicFont* const i_parent_font, const char i_char_value, const double i_template_unscaled_pixel_spacing_left, const double i_template_unscaled_pixel_spacing_right, const Point2DNew i_template_unscaled_pixel_offset, const Scale90 i_template_scale, const GLColor i_template_color_mod)
	: parent_font(i_parent_font),
	char_value(i_char_value),
	template_unscaled_pixel_width(i_template_unscaled_pixel_width),
	template_unscaled_pixel_spacing_left(i_template_unscaled_pixel_spacing_left),
	template_unscaled_pixel_spacing_right(i_template_unscaled_pixel_spacing_right),
	template_unscaled_pixel_offset(i_template_unscaled_pixel_offset),
	template_scale(i_template_scale),
	template_color_mod(i_template_color_mod) {}

void BasicFontChar::InitLeast(const BasicFont* const i_parent_font, const char i_char_value, const Texture* const i_texture, const double i_template_unscaled_pixel_spacing_left, const double i_template_unscaled_pixel_spacing_right, const Point2DNew i_template_unscaled_pixel_offset, const Scale90 i_template_scale, const GLColor i_template_color_mod)
{
	parent_font = i_parent_font;

	char_value = i_char_value;
	SetTexture(i_texture);

	template_unscaled_pixel_spacing_left = i_template_unscaled_pixel_spacing_left;
	template_unscaled_pixel_spacing_right = i_template_unscaled_pixel_spacing_right;
	template_unscaled_pixel_offset = i_template_unscaled_pixel_offset;
	template_scale = i_template_scale;

	template_color_mod = i_template_color_mod;
}
void BasicFontChar::InitMost(const double i_template_unscaled_pixel_width, const BasicFont* const i_parent_font, const char i_char_value, const Texture* const i_texture, const double i_template_unscaled_pixel_spacing_left, const double i_template_unscaled_pixel_spacing_right, const Point2DNew i_template_unscaled_pixel_offset, const Scale90 i_template_scale, const GLColor i_template_color_mod)
{
	parent_font = i_parent_font;

	char_value = i_char_value;
	texture = i_texture;

	template_unscaled_pixel_width = i_template_unscaled_pixel_width;

	template_unscaled_pixel_spacing_left = i_template_unscaled_pixel_spacing_left;
	template_unscaled_pixel_spacing_right = i_template_unscaled_pixel_spacing_right;
	template_unscaled_pixel_offset = i_template_unscaled_pixel_offset;
	template_scale = i_template_scale;

	template_color_mod = i_template_color_mod;
}

void BasicFontChar::SetTexture(const Texture* const i_texture)
{
	if (i_texture)
	{
		texture = i_texture;

		if (template_unscaled_pixel_width == 0.0)
		{
			template_unscaled_pixel_width = (double)i_texture->width;
		}
	}
	else
	{
		cerr << "Bruh, you passed nullptr. Sent by void BasicFontChar::SetTexture(const Texture* const i_texture)." << endl;
		throw;
	}
}


double BasicFontChar::GetTemplateScaledPixelWidth() const
{
	return (template_unscaled_pixel_width * template_scale.width_scale);
}
double BasicFontChar::GetTemplateScaledPixelSpacingLeft() const
{
	return (template_unscaled_pixel_spacing_left * template_scale.width_scale);
}
double BasicFontChar::GetTemplateScaledPixelSpacingRight() const
{
	return (template_unscaled_pixel_spacing_right * template_scale.width_scale);
}
Point2DNew BasicFontChar::GetTemplateScaledPixelOffset() const
{
	return { template_unscaled_pixel_offset.x * template_scale.width_scale, template_unscaled_pixel_offset.y * template_scale.height_scale };
}