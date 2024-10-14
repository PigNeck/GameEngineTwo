#include "DebugLabel.h"

void DebugLabel::InitWithDescribingRectangleData(Font* const default_font, Rectangle* const param_describing_rectangle, const char* const chars, const double param_text_scale, const double param_scaled_margin_size)
{
	describing_rectangle = param_describing_rectangle;

	text_box_data.InitLeast(default_font);

	text_box_data.horizontal_text_centering = 0;
	text_box_data.vertical_text_centering = 0;
	text_box_data.AddCharPtr(chars);

	text_box_data.GenerateLineSizes();
	text_box_data.parent_rectangle.base_size.width = text_box_data.GetActualBaseWidth();
	text_box_data.parent_rectangle.base_size.height = text_box_data.GetActualBaseHeight();

	text_box_data.parent_rectangle.SetOffsetWithCentering({ 1.0, 1.0 }, 0);

	text_box_data.GenerateLinePositions();
	text_box_data.GenerateCharPositions();

	text_scale = param_text_scale;
	scaled_margin_size = param_scaled_margin_size;
}