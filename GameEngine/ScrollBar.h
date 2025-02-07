#pragma once
#include "Rectangle.h"


struct ScrollBar
{
	RectangleOld scroll_area;
	RectangleOld full_bar_rect;
	RectangleOld bar_rect;

	bool horizontal_scroll_bar = 0;

	double total_scroll_length = 0.0;
	double scroll_length_limiter = 0.0;

	double scroll_value = 0.0;

	double scroll_rate = 0.0;

	double saved_mouse_y_bar_rect_y_diff = 0.0;
	bool clicked_on_bar = 0;

	double GetMaxScrollValue();

	void SetBarRectPosWithScrollValue();
	void SetScrollValueWithBarRectPos();

	void InitBasic(const double param_total_scroll_length, const double param_scroll_length_limiter, RectangleOld param_scroll_area_rectangle_data, const double param_bar_thickness, const bool param_horizontal_scroll_bar);

	void SetScrollLength(const double param_total_scroll_length, const double param_scroll_length_limiter, const double param_scroll_area_length);
};