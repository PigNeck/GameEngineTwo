#include "TextButton.h"

SimpleTextButton::SimpleTextButton()
{
	scaled_border_width = 0.0;
	scaled_drop_amount = 0.0;
}
SimpleTextButton::~SimpleTextButton()
{
	//Do nothing lmao
}

void SimpleTextButton::InitLeast()
{
	//Do nothing lmao
}
void SimpleTextButton::InitMost(Rectangle param_parent_rect, TextBox param_text_box, double param_scaled_border_width, double param_scaled_drop_amount)
{
	parent_rect = param_parent_rect;
	text_box = param_text_box;
	scaled_border_width = param_scaled_border_width;
	scaled_drop_amount = param_scaled_drop_amount;
}
void SimpleTextButton::InitWithMargin(Size2D parent_size_scale, string text, Font* param_font, Size2D param_scaled_margin_size, double param_scaled_border_width, double param_scaled_drop_amount)
{
	RectangleData temp_rectangle_data;

	text_box.BasicInitTextBox(temp_rectangle_data, param_font, text);

	text_box.UpdateCharPos();

	temp_rectangle_data.base_size.width = text_box.GetActualBaseWidth();
	temp_rectangle_data.size.width = temp_rectangle_data.base_size.width;

	temp_rectangle_data.base_size.height = text_box.GetActualBaseHeight();
	temp_rectangle_data.size.height = temp_rectangle_data.base_size.height;

	text_box.parent_rect.data = temp_rectangle_data;
	text_box.parent_rect.SetReferenceRectangle(&parent_rect);

	temp_rectangle_data.base_size.width += ((param_scaled_margin_size.width / parent_size_scale.width) * 2.0);
	temp_rectangle_data.base_size.height += ((param_scaled_margin_size.height / parent_size_scale.height) * 2.0);

	temp_rectangle_data.SetSizeWithSizeScale(parent_size_scale);

	parent_rect.data = temp_rectangle_data;

	scaled_border_width = param_scaled_border_width;
	scaled_drop_amount = param_scaled_drop_amount;
}
void SimpleTextButton::InitWithBaseSize(Size2D parent_size_scale, string text, Font* param_font, Size2D param_parent_rect_base_size, double param_scaled_border_width, double param_scaled_drop_amount, Size2D param_scaled_margin_size, bool text_wrap)
{
	RectangleData temp_rectangle_data;
	temp_rectangle_data.base_size.width = param_parent_rect_base_size.width - (param_scaled_margin_size.width / parent_size_scale.width);
	temp_rectangle_data.base_size.height = param_parent_rect_base_size.height - ((param_scaled_margin_size.height + param_scaled_drop_amount) / parent_size_scale.height);

	text_box.BasicInitTextBox(temp_rectangle_data, param_font, text);
	text_box.text_wrap = text_wrap;

	text_box.UpdateCharPos();

	temp_rectangle_data.base_size.width = text_box.GetActualBaseWidth();
	temp_rectangle_data.size.width = temp_rectangle_data.base_size.width;

	temp_rectangle_data.base_size.height = text_box.GetActualBaseHeight();
	temp_rectangle_data.size.height = temp_rectangle_data.base_size.height;

	text_box.parent_rect.data = temp_rectangle_data;
	text_box.parent_rect.SetReferenceRectangle(&parent_rect);

	temp_rectangle_data.base_size.width = param_parent_rect_base_size.width;
	temp_rectangle_data.base_size.height = param_parent_rect_base_size.height;

	temp_rectangle_data.SetSizeWithSizeScale(parent_size_scale);

	parent_rect.data = temp_rectangle_data;

	scaled_border_width = param_scaled_border_width;
	scaled_drop_amount = param_scaled_drop_amount;
}

void SimpleTextButton::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes)
{
	debug_data_container.Init(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &parent_rect.data, param_debug_data_container_active_scenes);
	debug_data_container.AddRectangleData(&parent_rect.data, "Parent Rect");
	//Add stuff like default_font name and so on later
}








void TextButton::InitLeast()
{
	//Do nothing lmao
}
void TextButton::InitMost(const Button param_button, const TextBox param_text_box, const Point2D param_additional_offset_released, const Point2D param_additional_offset_hovering, const Point2D param_additional_offset_pressed)
{
	button = param_button;
	text_box = param_text_box;

	additional_offset_released = param_additional_offset_released;
	additional_offset_hovering = param_additional_offset_hovering;
	additional_offset_pressed = param_additional_offset_pressed;
}

void TextButton::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes)
{
	debug_data_container.Init(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &button.parent_rect.data, param_debug_data_container_active_scenes);
	debug_data_container.AddRectangleData(&button.parent_rect.data, "Button Parent Rect");
	//Add stuff like default_font name and so on later
}







void TextButtonEx::Init(const Button param_button, const TextBox param_text_box_released, const TextBox param_text_box_hovering, const TextBox param_text_box_pressed)
{
	//FIX LATER
}

void TextButtonEx::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes)
{
	debug_data_container.Init(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, nullptr, param_debug_data_container_active_scenes);
	//FIX LATER
}