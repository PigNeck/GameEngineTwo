#pragma once
#pragma warning(suppress : 6387)
#include "Tools.h"

using namespace std;

GLColor::GLColor() {}
GLColor::GLColor(const float i_r, const float i_g, const float i_b) : r(i_r), g(i_g), b(i_b), a(1.0) {}
GLColor::GLColor(const float i_r, const float i_g, const float i_b, const float i_a) : r(i_r), g(i_g), b(i_b), a(i_a) {}






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

//-- USE GETSDLWIDTHWITHTWOSDLX INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_width of a "RectangleOld," provide uni_left_edge.  If not, pass NULL for "param_uni_left_edge"
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
//-- USE GETSDLHEIGHTWITHTWOSDLY INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_height of a "RectangleOld," provide uni_top_edge.  If not, pass NULL for "param_uni_top_edge"
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
//-- USE GETSDLSIZEWITHTWOSDLPOINTS INSTEAD -- Assumed outer_pixel_side.  If finding the sdl_size of a "RectangleOld," provide uni_top_left_corner.  If not, pass NULL for "param_uni_top_left_corner"
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



SDL_Rect RectangleToSDLRect(const RectangleOld* const param_rectangle, const Camera* const camera)
{
	const int sdl_right = UniXToSDLX(param_rectangle->GetUniEdge({ 0 }), { 2 }, camera);
	const int sdl_bottom = UniYToSDLY(param_rectangle->GetUniEdge({ 1 }), { 0 }, camera);
	const int sdl_left = UniXToSDLX(param_rectangle->GetUniEdge({ 2 }), { 0 }, camera);
	const int sdl_top = UniYToSDLY(param_rectangle->GetUniEdge({ 3 }), { 2 }, camera);

	return GetSDLRectWithEdges(sdl_right, sdl_bottom, sdl_left, sdl_top);
}
SDL_Point RectangleToSDLCenterOfRotation(const RectangleOld* const param_rectangle, const Camera* const camera)
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


RectStructTwo RectangleToBasicRectangle(const RectangleOld* const param_rectangle)
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

RectStructOne RectangleToRectStructOne(const RectangleOld* const param_rectangle)
{
	return {
	param_rectangle->GetUniEdge({ 2 }),
	param_rectangle->GetUniEdge({ 0 }),
	param_rectangle->GetUniEdge({ 1 }),
	param_rectangle->GetUniEdge({ 3 })
	};
}


RectangleOld RectStructOneToRectangle(const RectStructOne* const param_rect_struct_one)
{
	RectangleOld temp_rectangle;

	temp_rectangle.size.width = (param_rect_struct_one->uni_right_edge - param_rect_struct_one->uni_left_edge);
	temp_rectangle.size.height = (param_rect_struct_one->uni_top_edge - param_rect_struct_one->uni_bottom_edge);

	temp_rectangle.pos.x = (param_rect_struct_one->uni_right_edge + param_rect_struct_one->uni_left_edge) / 2.0;
	temp_rectangle.pos.y = (param_rect_struct_one->uni_top_edge + param_rect_struct_one->uni_bottom_edge) / 2.0;

	temp_rectangle.SetBaseSizeWithSizeScale({ 1.0, 1.0 });

	return temp_rectangle;
}






// -----------------   POINT CONVERSION FUNCTIONS BASED ON BASE WINDOW SIZE   -----------------

double XToProportionX(const double x)
{
	return (x / HALF_BASE_WINDOW_PIXEL_WIDTH);
}
double YToProportionY(const double y)
{
	return (y / HALF_BASE_WINDOW_PIXEL_HEIGHT);
}

GLColor SDLColorToGLColor(const SDL_Color sdl_color)
{
	return GLColor((float)sdl_color.r / 255.f, (float)sdl_color.g / 255.f, (float)sdl_color.b / 255.f, (float)sdl_color.a / 255.f);
}
GLColor* SDLColorToGLColor(const SDL_Color* const sdl_color)
{
	if (sdl_color)
	{
		return new GLColor((float)sdl_color->r / 255.f, (float)sdl_color->g / 255.f, (float)sdl_color->b / 255.f, (float)sdl_color->a / 255.f);
	}
	else
	{
		return nullptr;
	}
}
SDL_Color GLColorToSDLColor(const GLColor gl_color)
{
	return { (Uint8)round(gl_color.r * 255.f), (Uint8)round(gl_color.g * 255.f), (Uint8)round(gl_color.b * 255.f), (Uint8)round(gl_color.a * 255.f) };
}
SDL_Color* GLColorToSDLColor(const GLColor* const gl_color)
{
	if (gl_color)
	{
		return new SDL_Color{ (Uint8)round(gl_color->r * 255.f), (Uint8)round(gl_color->g * 255.f), (Uint8)round(gl_color->b * 255.f), (Uint8)round(gl_color->a * 255.f) };
	}
	else
	{
		return nullptr;
	}
}



Point2DNew UniPointToScreenPoint(const Point2DNew* const uni_point, const CameraNew* const camera)
{
	if (camera)
	{
		const RefPoint2DNewest temp_point(*uni_point, &camera->rect.pos, &camera->rect.transformations);
		//TO-DO: make this "temp_point.SetUniValue(...), return temp_point.x, temp_point.y";
		return temp_point.GetUniValue();
	}
	else
	{
		return (*uni_point);
	}
}

Quad UniQuadToScreenQuad(const Quad* const uni_quad, const CameraNew* const camera)
{
	if (camera)
	{
		return Quad(
			UniPointToScreenPoint(&uni_quad->top_right, camera),
			UniPointToScreenPoint(&uni_quad->bottom_right, camera),
			UniPointToScreenPoint(&uni_quad->bottom_left, camera),
			UniPointToScreenPoint(&uni_quad->top_left, camera)
		);
	}
	else
	{
		return (*uni_quad);
	}
}






// -----------------   COLLISION FUNCTIONS   -----------------

bool OverlapPoint2DWithRectangleEx(const Point2D* const param_point, const RectangleOld* const param_rectangle, const bool include_rectangle_right_edge, const bool include_rectangle_bottom_edge, const bool include_rectangle_left_edge, const bool include_rectangle_top_edge)
{
	RectStructOne temp_rect_struct_one = RectangleToRectStructOne(param_rectangle);

	return OverlapPoint2DWithRectStructOneEx(param_point, &temp_rect_struct_one, include_rectangle_right_edge, include_rectangle_bottom_edge, include_rectangle_left_edge, include_rectangle_top_edge);
}
bool OverlapPoint2DWithRectangle(const Point2D* const param_point, const RectangleOld* const param_rectangle, const bool include_edge)
{
	return OverlapPoint2DWithRectangleEx(param_point, param_rectangle, include_edge, include_edge, include_edge, include_edge);
}

bool OverlapPoint2DWithRectStructOneEx(const Point2D* const param_point, const RectStructOne* const param_rect_struct_one, const bool include_rect_struct_one_right_edge, const bool include_rect_struct_one_bottom_edge, const bool include_rect_struct_one_left_edge, const bool include_rect_struct_one_top_edge)
{
	//Initialize all check bools. If all are true by the end of the function, rects are overlaping!
	bool right_edge_check;
	bool bottom_edge_check;
	bool left_edge_check;
	bool top_edge_check;

	//Determining value of right_edge_check
	if (include_rect_struct_one_right_edge)
	{
		right_edge_check = (param_point->x <= param_rect_struct_one->uni_right_edge);
	}
	else
	{
		right_edge_check = (param_point->x < param_rect_struct_one->uni_right_edge);
	}

	//Determining value of bottom_edge_check
	if (include_rect_struct_one_bottom_edge)
	{
		bottom_edge_check = (param_point->y >= param_rect_struct_one->uni_bottom_edge);
	}
	else
	{
		bottom_edge_check = (param_point->y > param_rect_struct_one->uni_bottom_edge);
	}

	//Determining value of left_edge_check
	if (include_rect_struct_one_left_edge)
	{
		left_edge_check = (param_point->x >= param_rect_struct_one->uni_left_edge);
	}
	else
	{
		left_edge_check = (param_point->x > param_rect_struct_one->uni_left_edge);
	}

	//Determining value of top_edge_check
	if (include_rect_struct_one_top_edge)
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

bool OverlapRectStructOneWithRectStructOneEx(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_first_rect_struct_one_right_edge, const bool include_first_rect_struct_one_bottom_edge, const bool include_first_rect_struct_one_left_edge, const bool include_first_rect_struct_one_top_edge)
{
	//Initialize all check bools. If all are true by the end of the function, rects are overlaping!
	bool first_rect_struct_right_check;
	bool first_rect_struct_bottom_check;
	bool first_rect_struct_left_check;
	bool first_rect_struct_top_check;

	//Determining value of first_rect_struct_right_check
	if (include_first_rect_struct_one_right_edge)
	{
		first_rect_struct_right_check = (first_rect_struct_one->uni_right_edge >= second_rect_struct_one->uni_left_edge);
	}
	else
	{
		first_rect_struct_right_check = (first_rect_struct_one->uni_right_edge > second_rect_struct_one->uni_left_edge);
	}

	//Determining value of first_rect_struct_bottom_check
	if (include_first_rect_struct_one_bottom_edge)
	{
		first_rect_struct_bottom_check = (first_rect_struct_one->uni_bottom_edge <= second_rect_struct_one->uni_top_edge);
	}
	else
	{
		first_rect_struct_bottom_check = (first_rect_struct_one->uni_bottom_edge < second_rect_struct_one->uni_top_edge);
	}

	//Determining value of first_rect_struct_left_check
	if (include_first_rect_struct_one_left_edge)
	{
		first_rect_struct_left_check = (first_rect_struct_one->uni_left_edge <= second_rect_struct_one->uni_right_edge);
	}
	else
	{
		first_rect_struct_left_check = (first_rect_struct_one->uni_left_edge < second_rect_struct_one->uni_right_edge);
	}

	//Determining value of first_rect_struct_top_check
	if (include_first_rect_struct_one_top_edge)
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






// -----------------   RECTANGLENEW CONVERSIONS   -----------------

SDL_Point Point2DNewToSDLPoint(const Point2DNew point, const RigidCentering pixel_side_horizontal, const RigidCentering pixel_side_vertical, const Camera* const camera)
{
	return { UniXToSDLX(point.x, pixel_side_horizontal, camera), UniYToSDLY(point.y, pixel_side_vertical, camera) };
}
SDL_Size Size2DNewToSDLSize(const Size2DNew size, const Point2DNew top_left_corner, const Camera* camera)
{
	return { UniWidthToSDLWidth(size.width, top_left_corner.x, camera), UniHeightToSDLHeight(size.height, top_left_corner.y, camera) };
}

SDL_Rect RectangleNewToSDLRect(const RectangleNew* const rect, Camera* const camera)
{
	const int right = UniXToSDLX(rect->GetEdge({ 0 }), { 2 }, camera);
	const int bottom = UniYToSDLY(rect->GetEdge({ 1 }), { 0 }, camera);
	const int left = UniXToSDLX(rect->GetEdge({ 2 }), { 0 }, camera);
	const int top = UniYToSDLY(rect->GetEdge({ 3 }), { 2 }, camera);

	return GetSDLRectWithEdges(right, bottom, left, top);
}

SDL_RectWithRotation RectangleNewToSDLRectWithRotation(const RectangleNew* const rect, Camera* const camera)
{
	const double uni_left_edge = rect->GetEdge({ 2 });
	const double uni_top_edge = rect->GetEdge({ 3 });

	const int right = UniXToSDLX(rect->GetEdge({ 0 }), { 2 }, camera);
	const int bottom = UniYToSDLY(rect->GetEdge({ 1 }), { 0 }, camera);
	const int left = UniXToSDLX(uni_left_edge, { 0 }, camera);
	const int top = UniYToSDLY(uni_top_edge, { 2 }, camera);

	const int center_x = UniXToSDLX(uni_left_edge + ((-rect->centering.x_centering + 1.0) * rect->GetScaledWidth() / 2.0), { 1 }, camera) - left;
	const int center_y = UniYToSDLY(uni_top_edge - ((rect->centering.y_centering + 1.0) * rect->GetScaledHeight() / 2.0), { 1 }, camera) - top;

	const SDL_RendererFlip flip = rect->total_flip.GetSDLFlip();

	return { GetSDLRectWithEdges(right, bottom, left, top),
		{ center_x, center_y },
		rect->rotation.radians + ((rect->total_flip.flip_horizontally && rect->total_flip.flip_vertically) * M_PI),
		flip
	};
}
SDL_RectWithRotation RectangleNewToSDLRectWithRotation(const Point2DNew* const pos, const Size2DNew* const unscaled_size, const Scale2DNew* const scale, const Centering2DNew* const centering, const Rotation2DNew* const rotation, const TotalFlip* const total_flip, Camera* const camera)
{
	RectangleNew temp_rect;
	if (pos)
	{
		temp_rect.pos = *pos;
	}
	if (unscaled_size)
	{
		temp_rect.unscaled_size = *unscaled_size;
	}
	if (scale)
	{
		temp_rect.scale = *scale;
	}
	if (centering)
	{
		temp_rect.centering = *centering;
	}
	if (rotation)
	{
		temp_rect.rotation = *rotation;
	}
	if (total_flip)
	{
		temp_rect.total_flip = *total_flip;
	}

	return RectangleNewToSDLRectWithRotation(&temp_rect, camera);
}


SDL_RectWithRotation RefRectangleNewToSDLRectWithRotation(const RefRectangleNew* const rect, Camera* const camera)
{
	const RectangleNew temp_rectangle_new = rect->GetRectangleNew();

	return RectangleNewToSDLRectWithRotation(&temp_rectangle_new, camera);
}
SDL_RectWithRotation RefRectangleNewToSDLRectWithRotation(const RefPoint2DNew* const pos, const Size2DNew* const unscaled_size, const RefScale2DNew* const scale, const Centering2DNew* const centering, const RefRotation2DNew* const rotation, const RefTotalFlip* const total_flip, Camera* const camera)
{
	RectangleNew temp_rect;
	if (pos)
	{
		temp_rect.pos = pos->GetPoint2DNew();
	}
	if (unscaled_size)
	{
		temp_rect.unscaled_size = *unscaled_size;
	}
	if (scale)
	{
		temp_rect.scale = scale->GetScale2DNew();
	}
	if (centering)
	{
		temp_rect.centering = *centering;
	}
	if (rotation)
	{
		temp_rect.rotation = rotation->GetRotation2DNew();
	}
	if (total_flip)
	{
		temp_rect.total_flip = total_flip->GetUniValue();
	}

	return RectangleNewToSDLRectWithRotation(&temp_rect, camera);
}

SDL_RectWithRotation RefRectangleNewNewToSDLRectWithRotation(const RefRectangleNewNew* const rect, Camera* const camera)
{
	const RectangleNew temp_rectangle_new = rect->GetRectangleNew();

	return RectangleNewToSDLRectWithRotation(&temp_rectangle_new, camera);
}
SDL_RectWithRotation RefRectangleNewNewToSDLRectWithRotation(const RefPoint2DNewNew* const pos, const RefSize2DNewNew* const unscaled_size, const RefScale2DNewNew* const scale, const Centering2DNew* const centering, const RefRotation2DNewNew* const rotation, const RefTotalFlip* const total_flip, Camera* const camera)
{
	RectangleNew temp_rect;
	if (pos)
	{
		temp_rect.pos = pos->GetUniValue();
	}
	if (unscaled_size)
	{
		temp_rect.unscaled_size = { unscaled_size->width, unscaled_size->height };
	}
	if (scale)
	{
		temp_rect.scale = scale->GetUniValue();
	}
	if (centering)
	{
		temp_rect.centering = *centering;
	}
	if (rotation)
	{
		temp_rect.rotation = rotation->GetUniValue();
	}
	if (total_flip)
	{
		temp_rect.total_flip = total_flip->GetUniValue();
	}

	return RectangleNewToSDLRectWithRotation(&temp_rect, camera);
}