#include "TextBoxChar.h"

void TextBoxChar::InitLeast(RectangleOld* const reference_rect, FontChar* const param_font_char)
{
	font_char = param_font_char;

	rect.base_size.width = (double)param_font_char->default_width;
	rect.base_size.height = (double)param_font_char->default_height;
	rect.SetSizeWithSizeScale({ 1.0, 1.0 });

	rect.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rect.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rect.reference_rectangle = reference_rect;

	char_spacing = (double)param_font_char->default_char_spacing;
}
void TextBoxChar::InitMost(RectangleOld* const reference_rect, FontChar* const param_font_char, const Uint8 param_r_mod, const Uint8 param_g_mod, const Uint8 param_b_mod, const Uint8 param_a_mod)
{
	font_char = param_font_char;

	rect.base_size.width = (double)param_font_char->default_width;
	rect.base_size.height = (double)param_font_char->default_height;
	rect.SetSizeWithSizeScale({ 1.0, 1.0 });

	rect.offset.x = (double)param_font_char->default_unscaled_x_offset;
	rect.offset.y = (double)param_font_char->default_unscaled_y_offset;

	rect.reference_rectangle = reference_rect;

	char_spacing = (double)param_font_char->default_char_spacing;


	r_mod = param_r_mod;
	g_mod = param_g_mod;
	b_mod = param_b_mod;
	a_mod = param_a_mod;
}

void TextBoxChar::GetRectangleWithSpacing(const bool include_left_spacing, const bool include_right_spacing) const
{

}

void TextBoxChar::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list)
{
	debug_data_container.InitMost(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &rect, param_debug_data_container_active_scenes, param_white_list, 2.0, 2.0);
	debug_data_container.AddRectangleData(&rect, "Rect");
}
















BasicTextBoxChar::BasicTextBoxChar(const BasicFontChar* const i_font_char_template)
	: font_char_template(i_font_char_template),
	texture(font_char_template->texture),
	char_value(font_char_template->char_value),
	unscaled_pixel_width(font_char_template->template_unscaled_pixel_width),
	scale(font_char_template->template_scale),
	unscaled_pixel_offset(font_char_template->template_unscaled_pixel_offset),
	unscaled_pixel_spacing_left(font_char_template->template_unscaled_pixel_spacing_left),
	unscaled_pixel_spacing_right(font_char_template->template_unscaled_pixel_spacing_right),
	color_mod(font_char_template->template_color_mod)
{
	rect.centering = { 1.0, 1.0 };
}
BasicTextBoxChar::BasicTextBoxChar()
{
	rect.centering = { 1.0, 1.0 };
}
BasicTextBoxChar::BasicTextBoxChar(const char i_char_value, const Texture* const i_texture, const double i_unscaled_pixel_spacing_left, const double i_unscaled_pixel_spacing_right, const Point2DNew i_unscaled_pixel_offset, const Scale90 i_scale, const GLColor i_color_mod)
	: texture(i_texture),
	char_value(i_char_value),
	unscaled_pixel_width((double)texture->width),
	scale(i_scale),
	unscaled_pixel_offset(i_unscaled_pixel_offset),
	unscaled_pixel_spacing_left(i_unscaled_pixel_spacing_left),
	unscaled_pixel_spacing_right(i_unscaled_pixel_spacing_right),
	color_mod(i_color_mod)
{
	rect.centering = { 1.0, 1.0 };
}
BasicTextBoxChar::BasicTextBoxChar(const double i_unscaled_pixel_width, const char i_char_value, const Texture* const i_texture, const double i_unscaled_pixel_spacing_left, const double i_unscaled_pixel_spacing_right, const Point2DNew i_unscaled_pixel_offset, const Scale90 i_scale, const GLColor i_color_mod)
	: texture(i_texture),
	char_value(i_char_value),
	unscaled_pixel_width(i_unscaled_pixel_width),
	scale(i_scale),
	unscaled_pixel_offset(i_unscaled_pixel_offset),
	unscaled_pixel_spacing_left(i_unscaled_pixel_spacing_left),
	unscaled_pixel_spacing_right(i_unscaled_pixel_spacing_right),
	color_mod(i_color_mod)
{
	rect.centering = { 1.0, 1.0 };
}

void BasicTextBoxChar::Init(const BasicFontChar* const i_font_char_template)
{
	font_char_template = i_font_char_template;
	texture = font_char_template->texture;
	char_value = font_char_template->char_value;
	unscaled_pixel_width = font_char_template->template_unscaled_pixel_width;
	scale = font_char_template->template_scale;
	unscaled_pixel_offset = font_char_template->template_unscaled_pixel_offset;
	unscaled_pixel_spacing_left = font_char_template->template_unscaled_pixel_spacing_left;
	unscaled_pixel_spacing_right = font_char_template->template_unscaled_pixel_spacing_right;
	color_mod = font_char_template->template_color_mod;
}
void BasicTextBoxChar::InitLeast(const char i_char_value, const Texture* const i_texture, const double i_unscaled_pixel_spacing_left, const double i_unscaled_pixel_spacing_right, const Point2DNew i_unscaled_pixel_offset, const Scale90 i_scale, const GLColor i_color_mod)
{
	texture = i_texture;
	char_value = i_char_value;
	unscaled_pixel_width = (double)texture->width;
	scale = i_scale;
	unscaled_pixel_offset = i_unscaled_pixel_offset;
	unscaled_pixel_spacing_left = i_unscaled_pixel_spacing_left;
	unscaled_pixel_spacing_right = i_unscaled_pixel_spacing_right;
	color_mod = i_color_mod;
}
void BasicTextBoxChar::InitMost(const double i_unscaled_pixel_width, const char i_char_value, const Texture* const i_texture, const double i_unscaled_pixel_spacing_left, const double i_unscaled_pixel_spacing_right, const Point2DNew i_unscaled_pixel_offset, const Scale90 i_scale, const GLColor i_color_mod)
{
	texture = i_texture;
	char_value = i_char_value;
	unscaled_pixel_width = i_unscaled_pixel_width;
	scale = i_scale;
	unscaled_pixel_offset = i_unscaled_pixel_offset;
	unscaled_pixel_spacing_left = i_unscaled_pixel_spacing_left;
	unscaled_pixel_spacing_right = i_unscaled_pixel_spacing_right;
	color_mod = i_color_mod;
}


double BasicTextBoxChar::GetScaledPixelWidth() const
{
	return (unscaled_pixel_width * scale.width_scale);
}
double BasicTextBoxChar::GetScaledPixelSpacingLeft() const
{
	return (unscaled_pixel_spacing_left * scale.width_scale);
}
double BasicTextBoxChar::GetScaledPixelSpacingRight() const
{
	return (unscaled_pixel_spacing_right * scale.width_scale);
}
Point2DNew BasicTextBoxChar::GetScaledPixelOffset() const
{
	return { unscaled_pixel_offset.x * scale.width_scale, unscaled_pixel_offset.y * scale.height_scale };
}