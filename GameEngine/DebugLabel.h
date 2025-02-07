#pragma once
#include "Rectangle.h"
#include "TextBoxData.h"

struct DebugLabel
{
	RectangleOld* describing_rectangle = nullptr;

	//Point2D target_pos;	//UNI POINT ONLY

	//Text box rules: No relativity, no \n

	TextBoxData text_box_data;

	RectangleOld rectangle;

	double text_scale = 1.0;

	double scaled_margin_size = 0.0;

	void InitWithDescribingRectangleData(Font* const default_font, RectangleOld* const param_describing_rectangle, const char* const chars, const double param_text_scale, const double param_scaled_margin_size);
};

