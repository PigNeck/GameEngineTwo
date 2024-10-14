#pragma once
#pragma warning(suppress : 6387)
#include "Tools.h"

using namespace std;

// -----------------   CONVERSION FUNCTIONS   -----------------

SDL_Rect RectStructTwoToSDLRect(const RectStructTwo* const param_rectangle, const Camera* const camera)
{
	SDL_Rect temp_rect;

	temp_rect.x = UniXToSDLX(param_rectangle->pos.x, { 0 }, camera);
	temp_rect.y = UniYToSDLY(param_rectangle->pos.y, { 2 }, camera);
	temp_rect.w = UniXToSDLX(param_rectangle->pos.x + param_rectangle->size.width, { 2 }, camera) - temp_rect.x;
	temp_rect.h = UniYToSDLY(param_rectangle->pos.y - param_rectangle->size.height, { 0 }, camera) - temp_rect.y;

	return temp_rect;
}



double SDLXToUniX(const int param_sdl_x, const RigidCentering pixel_side, const Camera* const camera)
{
	const double temp_cam_width_scale = camera->rect.GetUniWidthScale();

	double temp_pixel_side_offset_value = 0.0;
	switch (pixel_side.value)
	{
	case 0:
		temp_pixel_side_offset_value = 0.0;
		break;
	case 1:
		temp_pixel_side_offset_value = 0.5;
		break;
	case 2:
		temp_pixel_side_offset_value = 1.0;
		break;
	case 3:
		//UNDEFINED
		break;
	}

	return (camera->rect.pos.x + ((((double)param_sdl_x + temp_pixel_side_offset_value) - (camera->rect.base_size.width / 2.0) + camera->rect.offset.x) * temp_cam_width_scale));
}
double SDLYToUniY(const int param_sdl_y, const RigidCentering pixel_side, const Camera* const camera)
{
	const double temp_cam_height_scale = camera->rect.GetUniHeightScale();

	double temp_pixel_side_offset_value = 0.0;
	switch (pixel_side.value)
	{
	case 0:
		temp_pixel_side_offset_value = -1.0;
		break;
	case 1:
		temp_pixel_side_offset_value = -0.5;
		break;
	case 2:
		temp_pixel_side_offset_value = 0.0;
		break;
	case 3:
		//UNDEFINED
		break;
	}

	return (camera->rect.pos.y + ((-((double)param_sdl_y) + temp_pixel_side_offset_value + (camera->rect.base_size.height / 2.0) + camera->rect.offset.y) * temp_cam_height_scale));
}
Point2D SDLPointToUniPoint(const SDL_Point param_sdl_point, const RigidCentering pixel_side_horizontal, const RigidCentering pixel_side_vertical, const Camera* const camera)
{
	return { SDLXToUniX(param_sdl_point.x, pixel_side_horizontal, camera), SDLYToUniY(param_sdl_point.y, pixel_side_vertical, camera) };
}

//Assumed outer_pixel_side
double SDLWidthToUniWidth(const int param_sdl_width, const Camera* const camera)
{
	return (double)param_sdl_width * camera->rect.GetUniWidthScale();
}
//Assumed outer_pixel_side
double SDLHeightToUniHeight(const int param_sdl_height, const Camera* const camera)
{
	return (double)param_sdl_height * camera->rect.GetUniHeightScale();
}
//Assumed outer_pixel_side
Size2D SDLSizeToUniSize(const SDL_Size param_sdl_size, const Camera* const camera)
{
	return { SDLWidthToUniWidth(param_sdl_size.w, camera), SDLHeightToUniHeight(param_sdl_size.h, camera) };
}


int UniXToSDLX(const double param_uni_x, const RigidCentering pixel_side, const Camera* const camera)
{
	const double temp_cam_width_scale = camera->rect.GetUniWidthScale();

	double temp_pixel_side_offset_value = 0.0;
	switch (pixel_side.value)
	{
	case 0:
		temp_pixel_side_offset_value = 0.0;
		break;
	case 1:
		temp_pixel_side_offset_value = 0.5;
		break;
	case 2:
		temp_pixel_side_offset_value = 1.0;
		break;
	case 3:
		//UNDEFINED
		break;
	}

	return (int)round((((param_uni_x - camera->rect.pos.x) / temp_cam_width_scale) - camera->rect.offset.x + (camera->rect.base_size.width / 2.0)) - temp_pixel_side_offset_value);
}
int UniYToSDLY(const double param_uni_y, const RigidCentering pixel_side, const Camera* const camera)
{
	const double temp_cam_height_scale = camera->rect.GetUniHeightScale();

	double temp_pixel_side_offset_value = 0.0;
	switch (pixel_side.value)
	{
	case 0:
		temp_pixel_side_offset_value = -1.0;
		break;
	case 1:
		temp_pixel_side_offset_value = -0.5;
		break;
	case 2:
		temp_pixel_side_offset_value = 0.0;
		break;
	case 3:
		//UNDEFINED
		break;
	}

	//return -(((param_uni_y - camera->rect.pos.y) / temp_cam_height_scale) - camera->rect.offset.y) + (camera->rect.base_size.height / 2.0);

	return (int)round(nextafter(-(((param_uni_y - camera->rect.pos.y) / temp_cam_height_scale) - camera->rect.offset.y) + (camera->rect.base_size.height / 2.0) + temp_pixel_side_offset_value, 0.0));
}
SDL_Point UniPointToSDLPoint(const Point2D param_uni_point, const RigidCentering pixel_side_horizontal, const RigidCentering pixel_side_vertical, const Camera* camera)
{
	return { UniXToSDLX(param_uni_point.x, pixel_side_horizontal, camera), UniYToSDLY(param_uni_point.y, pixel_side_vertical, camera) };

	/*
	Point2D temp_pos = { param_uni_point.x, -param_uni_point.y };
	Point2D temp_point = GetRelativePoint(&temp_pos, Point2D{ camera->rect.GetUniEdge({ 2 }), camera->rect.GetUniEdge({ 3 }) }, camera->rect.GetSizeScale());

	SDL_Point temp_sdl_point;
	temp_sdl_point.x = temp_point.x;
	temp_sdl_point.y = temp_point.y;

	return temp_sdl_point;
	*/
}

//-- USE GETSDLWIDTHWITHTWOSDLX INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_width of a "Rectangle," provide uni_left_edge.  If not, pass NULL for "param_uni_left_edge"
int UniWidthToSDLWidth(const double param_uni_width, const double param_uni_left_edge, const Camera* camera)
{
	if (param_uni_left_edge != NULL)
	{
		const double temp_cam_width_scale = camera->rect.GetUniWidthScale();

		double temp_double_sdl_x = (((param_uni_left_edge - camera->rect.pos.x) / temp_cam_width_scale) - camera->rect.offset.x + (camera->rect.base_size.width / 2.0));

		const double one_less_double = nextafter(0.5, 0.0);
		double fraction_portion = modf(temp_double_sdl_x + one_less_double, nullptr);
		fraction_portion -= one_less_double;

		return (int)round((param_uni_width / temp_cam_width_scale) + fraction_portion);
	}
	else
	{
		return (int)round((param_uni_width / camera->rect.GetUniWidthScale()));
	}
}
//-- USE GETSDLHEIGHTWITHTWOSDLY INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_height of a "Rectangle," provide uni_top_edge.  If not, pass NULL for "param_uni_top_edge"
int UniHeightToSDLHeight(const double param_uni_height, const double param_uni_top_edge, const Camera* camera)
{
	if (param_uni_top_edge != NULL)
	{
		const double temp_cam_height_scale = camera->rect.GetUniHeightScale();
		
		double temp_double_sdl_y = (((-param_uni_top_edge + camera->rect.pos.y) / temp_cam_height_scale) + camera->rect.offset.y + (camera->rect.base_size.height / 2.0));

		const double one_less_double = nextafter(0.5, 0.0);

		double fraction_portion = modf(temp_double_sdl_y + one_less_double, nullptr);
		fraction_portion -= one_less_double;

		return (int)round((param_uni_height / temp_cam_height_scale) + fraction_portion);
	}
	else
	{
		return (int)round(param_uni_height / camera->rect.GetUniHeightScale());
	}
}
//-- USE GETSDLSIZEWITHTWOSDLPOINTS INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_size of a "Rectangle," provide uni_top_left_corner.  If not, pass NULL for "param_uni_top_left_corner"
SDL_Size UniSizeToSDLSize(const Size2D param_uni_size, const Point2D param_uni_top_left_corner, const Camera* camera)
{
	return { UniWidthToSDLWidth(param_uni_size.width, param_uni_top_left_corner.x, camera), UniHeightToSDLHeight(param_uni_size.height, param_uni_top_left_corner.y, camera) };

	/*
	Size2D temp_size = GetRelativeSize(&param_uni_size, camera->rect.GetSizeScale());

	SDL_Size temp_sdl_size;
	temp_sdl_size.w = temp_size.width;
	temp_sdl_size.h = temp_size.height;

	return temp_sdl_size;
	*/
}



int GetSDLWidthWithTwoSDLX(const int param_lesser_sdl_x, const int param_greater_sdl_x)
{
	int temp_true_width = param_greater_sdl_x - param_lesser_sdl_x + 1;

	if (temp_true_width >= 0)
	{
		return temp_true_width;
	}
	else
	{
		return 0;
	}
}
int GetSDLHeightWithTwoSDLY(const int param_lesser_sdl_y, const int param_greater_sdl_y)
{
	int temp_true_height = param_greater_sdl_y - param_lesser_sdl_y + 1;

	if (temp_true_height >= 0)
	{
		return temp_true_height;
	}
	else
	{
		return 0;
	}
}
SDL_Size GetSDLSizeWithTwoSDLPoints(const SDL_Point param_top_left_sdl_corner, const SDL_Point param_bottom_right_sdl_corner)
{
	SDL_Size temp_size;
	temp_size.w = GetSDLWidthWithTwoSDLX(param_top_left_sdl_corner.x, param_bottom_right_sdl_corner.x);
	temp_size.h = GetSDLHeightWithTwoSDLY(param_top_left_sdl_corner.y, param_bottom_right_sdl_corner.y);

	return temp_size;
}



SDL_Rect GetSDLRectWithEdges(const int right_edge, const int bottom_edge, const int left_edge, const int top_edge)
{
	return {
		left_edge,
		top_edge,
		GetSDLWidthWithTwoSDLX(left_edge, right_edge),
		GetSDLHeightWithTwoSDLY(top_edge, bottom_edge)
	};
}



SDL_Rect RectangleToSDLRect(const Rectangle* const param_rectangle, const Camera* const camera)
{
	const int sdl_right = UniXToSDLX(param_rectangle->GetUniEdge({ 0 }), { 2 }, camera);
	const int sdl_bottom = UniYToSDLY(param_rectangle->GetUniEdge({ 1 }), { 0 }, camera);
	const int sdl_left = UniXToSDLX(param_rectangle->GetUniEdge({ 2 }), { 0 }, camera);
	const int sdl_top = UniYToSDLY(param_rectangle->GetUniEdge({ 3 }), { 2 }, camera);

	return GetSDLRectWithEdges(sdl_right, sdl_bottom, sdl_left, sdl_top);
}
SDL_Point RectangleToSDLCenterOfRotation(const Rectangle* const param_rectangle, const Camera* const camera)
{
	Point2D temp_uni_offset = param_rectangle->GetUniScaledOffset();

	Point2D temp_sdl_center;
	temp_sdl_center.x = (param_rectangle->GetUniWidth() / 2.0) - temp_uni_offset.x;
	temp_sdl_center.y = (param_rectangle->GetUniHeight() / 2.0) - temp_uni_offset.y;

	temp_sdl_center.x /= camera->rect.GetWidthScale();
	temp_sdl_center.y /= camera->rect.GetHeightScale();

	return { (int)temp_sdl_center.x, (int)temp_sdl_center.y };
}


SDL_Rect RectStructOneToSDLRect(const RectStructOne* const param_rect_struct_one, Camera* const camera)
{
	const int sdl_right = UniXToSDLX(param_rect_struct_one->uni_right_edge, { 2 }, camera);
	const int sdl_bottom = UniYToSDLY(param_rect_struct_one->uni_bottom_edge, { 0 }, camera);
	const int sdl_left = UniXToSDLX(param_rect_struct_one->uni_left_edge, { 0 }, camera);
	const int sdl_top = UniYToSDLY(param_rect_struct_one->uni_top_edge, { 2 }, camera);

	return GetSDLRectWithEdges(sdl_right, sdl_bottom, sdl_left, sdl_top);
}


RectStructTwo RectangleToBasicRectangle(const Rectangle* const param_rectangle)
{
	RectStructTwo temp_basic_rect;

	temp_basic_rect.pos.x = param_rectangle->GetUniEdge({ 2 });
	temp_basic_rect.pos.y = param_rectangle->GetUniEdge({ 3 });

	switch (param_rectangle->flip.value)
	{
	case 1:
		temp_basic_rect.pos.x -= param_rectangle->GetUniScaledXOffset() * 2.0;
		break;
	case 2:
		temp_basic_rect.pos.y -= param_rectangle->GetUniScaledYOffset() * 2.0;
		break;
	}

	temp_basic_rect.size = param_rectangle->GetUniSize();

	return temp_basic_rect;
}

RectStructOne RectangleToRectStructOne(const Rectangle* const param_rectangle)
{
	return {
	param_rectangle->GetUniEdge({ 2 }),
	param_rectangle->GetUniEdge({ 0 }),
	param_rectangle->GetUniEdge({ 1 }),
	param_rectangle->GetUniEdge({ 3 })
	};
}


Rectangle RectStructOneToRectangle(const RectStructOne* const param_rect_struct_one)
{
	Rectangle temp_rectangle;

	temp_rectangle.size.width = (param_rect_struct_one->uni_right_edge - param_rect_struct_one->uni_left_edge);
	temp_rectangle.size.height = (param_rect_struct_one->uni_top_edge - param_rect_struct_one->uni_bottom_edge);

	temp_rectangle.pos.x = (param_rect_struct_one->uni_right_edge + param_rect_struct_one->uni_left_edge) / 2.0;
	temp_rectangle.pos.y = (param_rect_struct_one->uni_top_edge + param_rect_struct_one->uni_bottom_edge) / 2.0;

	temp_rectangle.SetBaseSizeWithSizeScale({ 1.0, 1.0 });

	return temp_rectangle;
}






// -----------------   COLLISION FUNCTIONS   -----------------

bool OverlapPoint2DWithRectangle(const Point2D* const param_point, const Rectangle* const param_rectangle, const bool include_edge)
{
	RectStructOne temp_rect_struct_one = RectangleToRectStructOne(param_rectangle);

	return OverlapPoint2DWithRectStructOne(param_point, &temp_rect_struct_one, include_edge);

	/*
	if (include_edge)
	{
		const double left_edge = param_rectangle->GetUniEdge({ 2 });
		const double right_edge = param_rectangle->GetUniEdge({ 0 });;
		const double bottom_edge = param_rectangle->GetUniEdge({ 1 });;
		const double top_edge = param_rectangle->GetUniEdge({ 3 });;

		const bool x_overlap = (param_point->x >= left_edge) && (param_point->x <= right_edge);
		const bool y_overlap = (param_point->y >= bottom_edge) && (param_point->y <= top_edge);

		return (x_overlap && y_overlap);
	}
	else
	{
		const double left_edge = param_rectangle->GetUniEdge({ 2 });
		const double right_edge = param_rectangle->GetUniEdge({ 0 });;
		const double bottom_edge = param_rectangle->GetUniEdge({ 1 });;
		const double top_edge = param_rectangle->GetUniEdge({ 3 });;

		const bool x_overlap = (param_point->x > left_edge) && (param_point->x < right_edge);
		const bool y_overlap = (param_point->y > bottom_edge) && (param_point->y < top_edge);

		return (x_overlap && y_overlap);
	}
	*/
}

bool OverlapPoint2DWithRectStructOneEx(const Point2D* const param_point, const RectStructOne* const param_rect_struct_one, const bool include_edge_on_rect_struct_one_right, const bool include_edge_on_rect_struct_one_bottom, const bool include_edge_on_rect_struct_one_left, const bool include_edge_on_rect_struct_one_top)
{
	//Initialize all check bools. If all are true by the end of the function, rects are overlaping!
	bool right_edge_check;
	bool bottom_edge_check;
	bool left_edge_check;
	bool top_edge_check;

	//Determining value of right_edge_check
	if (include_edge_on_rect_struct_one_right)
	{
		right_edge_check = (param_point->x <= param_rect_struct_one->uni_right_edge);
	}
	else
	{
		right_edge_check = (param_point->x < param_rect_struct_one->uni_right_edge);
	}

	//Determining value of bottom_edge_check
	if (include_edge_on_rect_struct_one_bottom)
	{
		bottom_edge_check = (param_point->y >= param_rect_struct_one->uni_bottom_edge);
	}
	else
	{
		bottom_edge_check = (param_point->y > param_rect_struct_one->uni_bottom_edge);
	}

	//Determining value of left_edge_check
	if (include_edge_on_rect_struct_one_left)
	{
		left_edge_check = (param_point->x >= param_rect_struct_one->uni_left_edge);
	}
	else
	{
		left_edge_check = (param_point->x > param_rect_struct_one->uni_left_edge);
	}

	//Determining value of top_edge_check
	if (include_edge_on_rect_struct_one_top)
	{
		top_edge_check = (param_point->y <= param_rect_struct_one->uni_top_edge);
	}
	else
	{
		top_edge_check = (param_point->y < param_rect_struct_one->uni_top_edge);
	}

	//Returns true if all checks were true and returns false if not
	return (right_edge_check && bottom_edge_check && left_edge_check && top_edge_check);
}
bool OverlapPoint2DWithRectStructOne(const Point2D* const param_point, const RectStructOne* const param_rect_struct_one, const bool include_edge)
{
	return OverlapPoint2DWithRectStructOneEx(param_point, param_rect_struct_one, include_edge, include_edge, include_edge, include_edge);
}

bool OverlapRectStructOneWithRectStructOneEx(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge_on_first_rect_struct_right, const bool include_edge_on_first_rect_struct_bottom, const bool include_edge_on_first_rect_struct_left, const bool include_edge_on_first_rect_struct_top)
{
	//Initialize all check bools. If all are true by the end of the function, rects are overlaping!
	bool first_rect_struct_right_check;
	bool first_rect_struct_bottom_check;
	bool first_rect_struct_left_check;
	bool first_rect_struct_top_check;

	//Determining value of first_rect_struct_right_check
	if (include_edge_on_first_rect_struct_right)
	{
		first_rect_struct_right_check = (first_rect_struct_one->uni_right_edge >= second_rect_struct_one->uni_left_edge);
	}
	else
	{
		first_rect_struct_right_check = (first_rect_struct_one->uni_right_edge > second_rect_struct_one->uni_left_edge);
	}

	//Determining value of first_rect_struct_bottom_check
	if (include_edge_on_first_rect_struct_bottom)
	{
		first_rect_struct_bottom_check = (first_rect_struct_one->uni_bottom_edge <= second_rect_struct_one->uni_top_edge);
	}
	else
	{
		first_rect_struct_bottom_check = (first_rect_struct_one->uni_bottom_edge < second_rect_struct_one->uni_top_edge);
	}

	//Determining value of first_rect_struct_left_check
	if (include_edge_on_first_rect_struct_left)
	{
		first_rect_struct_left_check = (first_rect_struct_one->uni_left_edge <= second_rect_struct_one->uni_right_edge);
	}
	else
	{
		first_rect_struct_left_check = (first_rect_struct_one->uni_left_edge < second_rect_struct_one->uni_right_edge);
	}

	//Determining value of first_rect_struct_top_check
	if (include_edge_on_first_rect_struct_top)
	{
		first_rect_struct_top_check = (first_rect_struct_one->uni_top_edge >= second_rect_struct_one->uni_bottom_edge);
	}
	else
	{
		first_rect_struct_top_check = (first_rect_struct_one->uni_top_edge > second_rect_struct_one->uni_bottom_edge);
	}

	//Returns true if all checks were true and returns false if not
	return (first_rect_struct_right_check && first_rect_struct_bottom_check && first_rect_struct_left_check && first_rect_struct_top_check);
}
bool OverlapRectStructOneWithRectStructOne(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge)
{
	return OverlapRectStructOneWithRectStructOneEx(first_rect_struct_one, second_rect_struct_one, include_edge, include_edge, include_edge, include_edge);
}





// -----------------   OBSELETE FUNCTIONS   -----------------

Point2D GetRelativePoint(const Point2D* const param_point, const Point2D reference_point, const Size2D reference_size_scale)
{
	Point2D temp_point = {};
	temp_point.x = ((param_point->x - reference_point.x) / reference_size_scale.width);
	temp_point.y = ((param_point->y + reference_point.y) / reference_size_scale.height);

	return temp_point;
}
Size2D GetRelativeSize(const Size2D* const param_size, const Size2D reference_size)
{
	Size2D temp_size = {};
	temp_size.width = param_size->width / reference_size.width;
	temp_size.height = param_size->height / reference_size.height;

	return temp_size;
}
