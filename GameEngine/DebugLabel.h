#pragma once
#include "RectangleData.h"
#include "TextBoxData.h"

struct DebugLabel
{
	RectangleData* describing_rectangle_data = nullptr;

	Point2D target_pos;	//UNI POINT ONLY

	//Text box rules: No relativity
	TextBoxData text_box_data;

	RectangleData rectangle_data;

	double text_scale = 1.0;

	double scaled_margin_size = 0.0;

	void InitWithDescribingRectangleData(Font* const default_font, RectangleData* const param_describing_rectangle_data, const char* const chars, const double param_text_scale, const double param_scaled_margin_size);
};

