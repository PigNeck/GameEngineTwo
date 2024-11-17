#include "ScrollBar.h"

double ScrollBar::GetMaxScrollValue()
{
	return (total_scroll_length - scroll_length_limiter);
}

void ScrollBar::SetBarRectPosWithScrollValue()
{
	if (horizontal_scroll_bar)
	{
		bar_rect.pos.x = -(full_bar_rect.base_size.width / 2.0) + (bar_rect.size.width / 2.0) + (scroll_value * (full_bar_rect.base_size.width / total_scroll_length));
	}
	else
	{
		bar_rect.pos.y = (full_bar_rect.base_size.height / 2.0) - (bar_rect.size.height / 2.0) - (scroll_value * (full_bar_rect.base_size.height / total_scroll_length));
	}
}
void ScrollBar::SetScrollValueWithBarRectPos()
{
	if (horizontal_scroll_bar)
	{
		scroll_value = ((bar_rect.pos.x) - (bar_rect.size.width / 2.0) + (full_bar_rect.base_size.width / 2.0)) * (total_scroll_length / full_bar_rect.base_size.width);
	}
	else
	{
		scroll_value = ((-bar_rect.pos.y) - (bar_rect.size.height / 2.0) + (full_bar_rect.base_size.height / 2.0)) * (total_scroll_length / full_bar_rect.base_size.height);
	}
}

void ScrollBar::InitBasic(const double param_total_scroll_length, const double param_scroll_length_limiter, Rectangle param_scroll_area_rectangle_data, const double param_bar_thickness, const bool param_horizontal_scroll_bar)
{
	horizontal_scroll_bar = param_horizontal_scroll_bar;

	scroll_area = param_scroll_area_rectangle_data;

	if (horizontal_scroll_bar)
	{
		SetScrollLength(param_total_scroll_length, param_scroll_length_limiter, param_scroll_area_rectangle_data.GetUniWidth());

		full_bar_rect.base_size.height = param_bar_thickness;
		full_bar_rect.SetHeightWithHeightScale({ 1.0 });
		full_bar_rect.SetPosWithUniEdge(scroll_area.GetUniEdge({ 1 }), { 1 });

		bar_rect.base_size.height = param_bar_thickness;
		bar_rect.SetHeightWithHeightScale({ 1.0 });
	}
	else
	{
		SetScrollLength(param_total_scroll_length, param_scroll_length_limiter, param_scroll_area_rectangle_data.GetUniHeight());

		full_bar_rect.base_size.width = param_bar_thickness;
		full_bar_rect.SetWidthWithWidthScale({ 1.0 });
		full_bar_rect.SetPosWithUniEdge(scroll_area.GetUniEdge({ 0 }), { 0 });

		bar_rect.base_size.width = param_bar_thickness;
		bar_rect.SetWidthWithWidthScale({ 1.0 });
	}

	scroll_rate = 60.0;
}

void ScrollBar::SetScrollLength(const double param_total_scroll_length, const double param_scroll_length_limiter, const double param_scroll_area_length)
{
	if (horizontal_scroll_bar)
	{
		full_bar_rect.base_size.width = param_scroll_area_length;
		full_bar_rect.SetWidthWithWidthScale({ 1.0 });

		bar_rect.base_size.width = param_scroll_area_length * (param_scroll_area_length / param_total_scroll_length);
		if (bar_rect.base_size.width > param_scroll_area_length)
		{
			bar_rect.base_size.width = param_scroll_area_length;
		}
		bar_rect.SetWidthWithWidthScale({ 1.0 });
		bar_rect.reference_rectangle = &full_bar_rect;

		total_scroll_length = param_total_scroll_length;
		scroll_length_limiter = param_scroll_length_limiter;

		SetBarRectPosWithScrollValue();
	}
	else
	{
		full_bar_rect.base_size.height = param_scroll_area_length;
		full_bar_rect.SetHeightWithHeightScale({ 1.0 });

		bar_rect.base_size.height = param_scroll_area_length * (param_scroll_area_length / param_total_scroll_length);
		if (bar_rect.base_size.height > param_scroll_area_length)
		{
			bar_rect.base_size.height = param_scroll_area_length;
		}
		bar_rect.SetHeightWithHeightScale({ 1.0 });
		bar_rect.reference_rectangle = &full_bar_rect;

		total_scroll_length = param_total_scroll_length;
		scroll_length_limiter = param_scroll_length_limiter;

		SetBarRectPosWithScrollValue();
	}
}