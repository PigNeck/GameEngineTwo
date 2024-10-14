#pragma once
#include "Button.h"
#include "TextBox.h"
#include "DebugDataContainer.h"
#include <iostream>

struct SimpleTextButton
{
	Rectangle parent_rect;

	TextBox text_box;

	PressData press_data;

	double scaled_border_width;
	double scaled_drop_amount;

	DebugDataContainer debug_data_container;

	SimpleTextButton();
	~SimpleTextButton();

	void InitLeast();
	void InitMost(Rectangle param_parent_rect, TextBox param_text_box, double param_scaled_border_width, double param_scaled_drop_amount);
	void InitWithMargin(Size2D text_box_size_scale, string text, Font* param_font, Size2D param_scaled_margin_size, double param_scaled_border_width, double param_scaled_drop_amount);
	void InitWithBaseSize(Size2D text_box_size_scale, string text, Font* param_font, Size2D param_parent_rect_base_size, double param_scaled_border_width, double param_scaled_drop_amount, Size2D param_scaled_margin_size, bool text_wrap);

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list);
};

struct TextButton
{
	Button button;
	TextBox text_box;

	Point2D additional_offset_released;
	Point2D additional_offset_hovering;
	Point2D additional_offset_pressed;

	DebugDataContainer debug_data_container;

	void InitLeast();
	void InitMost(const Button param_button, const TextBox param_text_box, const Point2D param_additional_offset_released, const Point2D param_additional_offset_hovering, const Point2D param_additional_offset_pressed);

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list);
};

struct TextButtonEx
{
	Button button;
	TextBox text_box_released;
	TextBox text_box_hovering;
	TextBox text_box_pressed;

	DebugDataContainer debug_data_container;

	void Init(const Button param_button, const TextBox param_text_box_released, const TextBox param_text_box_hovering, const TextBox param_text_box_pressed);

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list);
};

