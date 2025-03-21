#pragma once
#include "Texture.h"
#include "ColorFormats.h"
#include <iostream>

using namespace std;

string GetTextureName(char char_value);

struct BasicFont;

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
	// -------------  Primary data  -------------

	const Texture* texture = nullptr;

	char char_value = 0;

	double template_unscaled_pixel_width = 0.0; //Should usually be set to [texture->width] unless the texture doesn't cover the whole area it is given. DOES change the generated positions of the other letters.
	Scale90 template_scale; //Should typically be { 1.0, 1.0 }.

	Point2DNew template_unscaled_pixel_offset; //[template_pixel_offset] moves the char from its default position, but DOES NOT change the generated positions of any of the other letters. [template_pixel_offset.x] should almost always equal 0.0, but [template_pixel_offset.y] is typically nonzero for chars some chars like asterisk and apostrophe. If [template_pixel_offset.y] is 0.0, then the char is snapped to the bottom edge of its text_box_line.

	double template_unscaled_pixel_spacing_left = 0.0; //Scales with [template_scale].
	double template_unscaled_pixel_spacing_right = 0.0; //Scales with [template_scale].

	GLColor template_color_mod = { 0.f, 0.f, 0.f, 1.f };




	// -------------  Metadata  -------------

	const BasicFont* parent_font = nullptr;




	// -------------  Functions  -------------

	BasicFontChar();
	//IMPORTANT: Sets [template_pixel_width] based on the dimentions of the texture. Make sure the texture is loaded before it's pointer is passed to this constructor!
	BasicFontChar(const BasicFont* const i_parent_font, const char i_char_value, const double i_template_unscaled_pixel_spacing_left = 0.0, const double i_template_unscaled_pixel_spacing_right = 0.0, const Point2DNew i_template_unscaled_pixel_offset = { 0.0, 0.0 }, const Scale90 i_template_scale = { 1.0, 1.0 }, const GLColor i_template_color_mod = { 0.f, 0.f, 0.f, 1.f });
	//Sets all member variables to initial values.
	BasicFontChar(const double i_template_unscaled_pixel_width, const BasicFont* const i_parent_font, const char i_char_value, const double i_template_unscaled_pixel_spacing_left = 0.0, const double i_template_pixel_unscaled_spacing_right = 0.0, const Point2DNew i_template_unscaled_pixel_offset = {0.0, 0.0}, const Scale90 i_template_scale = { 1.0, 1.0 }, const GLColor i_template_color_mod = { 0.f, 0.f, 0.f, 1.f });

	//IMPORTANT: Sets [template_pixel_width] based on the dimentions of the texture. Make sure the texture is loaded before it's pointer is passed to this method!
	void InitLeast(const BasicFont* const i_parent_font, const char i_char_value, const Texture* const i_texture, const double i_template_unscaled_pixel_spacing_left = 0.0, const double i_template_unscaled_pixel_spacing_right = 0.0, const Point2DNew i_template_unscaled_pixel_offset = { 0.0, 0.0 }, const Scale90 i_template_scale = { 1.0, 1.0 }, const GLColor i_template_color_mod = { 0.f, 0.f, 0.f, 1.f });
	//Sets all member variables to initial values.
	void InitMost(const double i_template_unscaled_pixel_width, const BasicFont* const i_parent_font, const char i_char_value, const Texture* const i_texture, const double i_template_unscaled_pixel_spacing_left = 0.0, const double i_template_unscaled_pixel_spacing_right = 0.0, const Point2DNew i_template_unscaled_pixel_offset = { 0.0, 0.0 }, const Scale90 i_template_scale = { 1.0, 1.0 }, const GLColor i_template_color_mod = { 0.f, 0.f, 0.f, 1.f });

	//IMPORTANT: If [template_pixel_width] has not already been set, it is set to fit the dimentions of [i_texture]. Make sure the texture is loaded before it's pointer is passed to this method!
	void SetTexture(const Texture* const i_texture);


	double GetTemplateScaledPixelWidth() const;
	double GetTemplateScaledPixelSpacingLeft() const;
	double GetTemplateScaledPixelSpacingRight() const;
	Point2DNew GetTemplateScaledPixelOffset() const;
};