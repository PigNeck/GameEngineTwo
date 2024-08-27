#pragma once
#pragma warning(suppress : 6387)
#include "Tools.h"

using namespace std;

// -----------------   CONVERSION FUNCTIONS   -----------------

SDL_Rect BasicRectangleToSDLRect(BasicRectangle* param_rectangle, Camera* camera)
{
	Point2D temp_pos = { param_rectangle->pos.x, -param_rectangle->pos.y };
	Point2D temp_point = GetRelativePoint(&temp_pos, Point2D { camera->rect.data.GetUniEdge({ 2 }), camera->rect.data.GetUniEdge({ 3 })}, camera->rect.data.GetSizeScale());
	Size2D temp_size = GetRelativeSize(&param_rectangle->size, camera->rect.data.GetSizeScale());

	SDL_Rect temp_rect;
	temp_rect.x = temp_point.x;
	temp_rect.y = temp_point.y;
	temp_rect.w = temp_size.width;
	temp_rect.h = temp_size.height;

	return temp_rect;
}



double SDLXToUniX(int param_sdl_x, RigidCentering pixel_side, Camera* camera)
{
	const double temp_cam_width_scale = camera->rect.data.GetUniWidthScale();

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

	return (camera->rect.data.pos.x + ((((double)param_sdl_x + temp_pixel_side_offset_value) - (camera->rect.data.base_size.width / 2.0) + camera->rect.data.offset.x) * temp_cam_width_scale));
}
double SDLYToUniY(int param_sdl_y, RigidCentering pixel_side, Camera* camera)
{
	const double temp_cam_height_scale = camera->rect.data.GetUniHeightScale();

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

	return (camera->rect.data.pos.y + ((-((double)param_sdl_y) + temp_pixel_side_offset_value + (camera->rect.data.base_size.height / 2.0) + camera->rect.data.offset.y) * temp_cam_height_scale));
}
Point2D SDLPointToUniPoint(SDL_Point param_sdl_point, RigidCentering pixel_side_horizontal, RigidCentering pixel_side_vertical, Camera* camera)
{
	return { SDLXToUniX(param_sdl_point.x, pixel_side_horizontal, camera), SDLYToUniY(param_sdl_point.y, pixel_side_vertical, camera) };
}

//Assumed outer_pixel_side
double SDLWidthToUniWidth(int param_sdl_width, Camera* camera)
{
	return (double)param_sdl_width * camera->rect.data.GetUniWidthScale();
}
//Assumed outer_pixel_side
double SDLHeightToUniHeight(int param_sdl_height, Camera* camera)
{
	return (double)param_sdl_height * camera->rect.data.GetUniHeightScale();
}
//Assumed outer_pixel_side
Size2D SDLSizeToUniSize(SDL_Size param_sdl_size, Camera* camera)
{
	return { SDLWidthToUniWidth(param_sdl_size.w, camera), SDLHeightToUniHeight(param_sdl_size.h, camera) };
}


int UniXToSDLX(double param_uni_x, RigidCentering pixel_side, Camera* camera)
{
	const double temp_cam_width_scale = camera->rect.data.GetUniWidthScale();

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

	return round((((param_uni_x - camera->rect.data.pos.x) / temp_cam_width_scale) - camera->rect.data.offset.x + (camera->rect.data.base_size.width / 2.0)) - temp_pixel_side_offset_value);
}
int UniYToSDLY(double param_uni_y, RigidCentering pixel_side, Camera* camera)
{
	const double temp_cam_height_scale = camera->rect.data.GetUniHeightScale();

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

	return round(nextafter(-(((param_uni_y - camera->rect.data.pos.y) / temp_cam_height_scale) - camera->rect.data.offset.y) + (camera->rect.data.base_size.height / 2.0) + temp_pixel_side_offset_value, 0.0));
}
SDL_Point UniPointToSDLPoint(Point2D param_uni_point, RigidCentering pixel_side_horizontal, RigidCentering pixel_side_vertical, Camera* camera)
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
int UniWidthToSDLWidth(double param_uni_width, double param_uni_left_edge, Camera* camera)
{
	if (param_uni_left_edge != NULL)
	{
		const double temp_cam_width_scale = camera->rect.data.GetUniWidthScale();

		double temp_double_sdl_x = (((param_uni_left_edge - camera->rect.data.pos.x) / temp_cam_width_scale) - camera->rect.data.offset.x + (camera->rect.data.base_size.width / 2.0));

		const double one_less_double = nextafter(0.5, 0.0);
		double fraction_portion = modf(temp_double_sdl_x + one_less_double, nullptr);
		fraction_portion -= one_less_double;

		return round((param_uni_width / temp_cam_width_scale) + fraction_portion);
	}
	else
	{
		return round((param_uni_width / camera->rect.data.GetUniWidthScale()));
	}
}
//-- USE GETSDLHEIGHTWITHTWOSDLY INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_height of a "Rectangle," provide uni_top_edge.  If not, pass NULL for "param_uni_top_edge"
int UniHeightToSDLHeight(double param_uni_height, double param_uni_top_edge, Camera* camera)
{
	if (param_uni_top_edge != NULL)
	{
		const double temp_cam_height_scale = camera->rect.data.GetUniHeightScale();

		double temp_double_sdl_y = (((-param_uni_top_edge + camera->rect.data.pos.y) / temp_cam_height_scale) + camera->rect.data.offset.y + (camera->rect.data.base_size.height / 2.0));

		const double one_less_double = nextafter(0.5, 0.0);

		double fraction_portion = modf(temp_double_sdl_y + one_less_double, nullptr);
		fraction_portion -= one_less_double;

		return round((param_uni_height / temp_cam_height_scale) + fraction_portion);
	}
	else
	{
		return round(param_uni_height / camera->rect.data.GetUniHeightScale());
	}
}
//-- USE GETSDLSIZEWITHTWOSDLPOINTS INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_size of a "Rectangle," provide uni_top_left_corner.  If not, pass NULL for "param_uni_top_left_corner"
SDL_Size UniSizeToSDLSize(Size2D param_uni_size, Point2D param_uni_top_left_corner, Camera* camera)
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



int GetSDLWidthWithTwoSDLX(int param_lesser_sdl_x, int param_greater_sdl_x)
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
int GetSDLHeightWithTwoSDLY(int param_lesser_sdl_y, int param_greater_sdl_y)
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
SDL_Size GetSDLSizeWithTwoSDLPoints(SDL_Point param_top_left_sdl_corner, SDL_Point param_bottom_right_sdl_corner)
{
	SDL_Size temp_size;
	temp_size.w = GetSDLWidthWithTwoSDLX(param_top_left_sdl_corner.x, param_bottom_right_sdl_corner.x);
	temp_size.h = GetSDLHeightWithTwoSDLY(param_top_left_sdl_corner.y, param_bottom_right_sdl_corner.y);

	return temp_size;
}



SDL_Rect GetSDLRectWithEdges(int right_edge, int bottom_edge, int left_edge, int top_edge)
{
	return {
		left_edge,
		top_edge,
		GetSDLWidthWithTwoSDLX(left_edge, right_edge),
		GetSDLHeightWithTwoSDLY(top_edge, bottom_edge)
	};
}



SDL_Rect RectangleDataToSDLRect(RectangleData* param_rectangle_data, Camera* camera)
{
	const int sdl_right = UniXToSDLX(param_rectangle_data->GetUniEdge({ 0 }), { 2 }, camera);
	const int sdl_bottom = UniYToSDLY(param_rectangle_data->GetUniEdge({ 1 }), { 0 }, camera);
	const int sdl_left = UniXToSDLX(param_rectangle_data->GetUniEdge({ 2 }), { 0 }, camera);
	const int sdl_top = UniYToSDLY(param_rectangle_data->GetUniEdge({ 3 }), { 2 }, camera);

	return GetSDLRectWithEdges(sdl_right, sdl_bottom, sdl_left, sdl_top);
}
SDL_Point RectangleDataToSDLCenterOfRotation(RectangleData* param_rectangle_data, Camera* camera)
{
	Point2D temp_uni_offset = param_rectangle_data->GetUniScaledOffset();

	Point2D temp_sdl_center;
	temp_sdl_center.x = (param_rectangle_data->GetUniWidth() / 2.0) - temp_uni_offset.x;
	temp_sdl_center.y = (param_rectangle_data->GetUniHeight() / 2.0) - temp_uni_offset.y;

	temp_sdl_center.x /= camera->rect.data.GetWidthScale();
	temp_sdl_center.y /= camera->rect.data.GetHeightScale();

	return { (int)temp_sdl_center.x, (int)temp_sdl_center.y };
}






// -----------------   COLLISION FUNCTIONS   -----------------

bool OverlapPoint2DWithRectangleData(Point2D* param_point, RectangleData* param_rectangle_data, bool include_edge)
{
	if (include_edge)
	{
		const double left_edge = param_rectangle_data->GetUniEdge({ 2 });
		const double right_edge = param_rectangle_data->GetUniEdge({ 0 });;
		const double bottom_edge = param_rectangle_data->GetUniEdge({ 1 });;
		const double top_edge = param_rectangle_data->GetUniEdge({ 3 });;

		const bool x_overlap = (param_point->x >= left_edge) && (param_point->x <= right_edge);
		const bool y_overlap = (param_point->y >= bottom_edge) && (param_point->y <= top_edge);

		return (x_overlap && y_overlap);
	}
	else
	{
		const double left_edge = param_rectangle_data->GetUniEdge({ 2 });
		const double right_edge = param_rectangle_data->GetUniEdge({ 0 });;
		const double bottom_edge = param_rectangle_data->GetUniEdge({ 1 });;
		const double top_edge = param_rectangle_data->GetUniEdge({ 3 });;

		const bool x_overlap = (param_point->x > left_edge) && (param_point->x < right_edge);
		const bool y_overlap = (param_point->y > bottom_edge) && (param_point->y < top_edge);

		return (x_overlap && y_overlap);
	}
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

	//Returns true if all_checks were true. Returns false if not
	return (first_rect_struct_right_check && first_rect_struct_bottom_check && first_rect_struct_left_check && first_rect_struct_top_check);
}
bool OverlapRectStructOneWithRectStructOne(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge)
{
	return OverlapRectStructOneWithRectStructOneEx(first_rect_struct_one, second_rect_struct_one, include_edge, include_edge, include_edge, include_edge);
}





// -----------------   OBSELETE FUNCTIONS   -----------------

Point2D GetRelativePoint(Point2D* param_point, Point2D reference_point, Size2D reference_size_scale)
{
	Point2D temp_point = {};
	temp_point.x = ((param_point->x - reference_point.x) / reference_size_scale.width);
	temp_point.y = ((param_point->y + reference_point.y) / reference_size_scale.height);

	return temp_point;
}
Size2D GetRelativeSize(Size2D* param_size, Size2D reference_size)
{
	Size2D temp_size = {};
	temp_size.width = param_size->width / reference_size.width;
	temp_size.height = param_size->height / reference_size.height;

	return temp_size;
}
