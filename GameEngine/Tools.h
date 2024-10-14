#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Camera.h"
#include "SDL_mixer.h"
#include <iostream>
#include <algorithm>

using namespace std;

struct SDL_Size
{
	int w;
	int h;
};

// -----------------   CONVERSION FUNCTIONS   -----------------

SDL_Rect RectStructTwoToSDLRect(const RectStructTwo* const param_rectangle, const Camera* const camera);



double SDLXToUniX(const int param_sdl_x, const RigidCentering pixel_side, const Camera* const camera);
double SDLYToUniY(const int param_sdl_y, const RigidCentering pixel_side, const Camera* const camera);
Point2D SDLPointToUniPoint(const SDL_Point param_sdl_point, const RigidCentering pixel_side_horizontal, const RigidCentering pixel_side_vertical, const Camera* const camera);

//Assumed outer_pixel_side
double SDLWidthToUniWidth(const int param_sdl_width, const Camera* const camera);
//Assumed outer_pixel_defined_side
double SDLHeightToUniHeight(const int param_sdl_height, const Camera* const camera);
//Assumed outer_pixel_side
Size2D SDLSizeToUniSize(const SDL_Size param_sdl_size, const Camera* const camera);


int UniXToSDLX(const double param_uni_x, const RigidCentering pixel_side, const Camera* const camera);
int UniYToSDLY(const double param_uni_y, const RigidCentering pixel_side, const Camera* const camera);
SDL_Point UniPointToSDLPoint(const Point2D param_uni_point, const RigidCentering pixel_side_horizontal, const RigidCentering pixel_side_vertical, const Camera* const camera);

//Assumed outer_pixel_side.  If finding the sdl_width of a "Rectangle," provide uni_left_edge.  If not, pass NULL for "param_uni_left_edge"
int UniWidthToSDLWidth(const double param_uni_width, const double param_uni_left_edge, const Camera* camera);
//Assumed outer_pixel_side.  If finding the sdl_height of a "Rectangle," provide uni_top_edge.  If not, pass NULL for "param_uni_top_edge"
int UniHeightToSDLHeight(const double param_uni_height, const double param_uni_top_edge, const Camera* camera);
//Assumed outer_pixel_side.  If finding the sdl_size of a "Rectangle," provide uni_top_left_corner.  If not, pass NULL for "param_uni_top_left_corner"
SDL_Size UniSizeToSDLSize(const Size2D param_uni_size, const Point2D param_uni_top_left_corner, const Camera* camera);



int GetSDLWidthWithTwoSDLX(const int param_lesser_sdl_x, const int param_greater_sdl_x);
int GetSDLHeightWithTwoSDLY(const int param_lesser_sdl_y, const int param_greater_sdl_y);
SDL_Size GetSDLSizeWithTwoSDLPoints(const SDL_Point param_top_left_sdl_corner, const SDL_Point param_bottom_right_sdl_corner);



SDL_Rect GetSDLRectWithEdges(const int right_edge, const int bottom_edge, const int left_edge, const int top_edge);



//Only one possible output per input
SDL_Rect RectangleToSDLRect(const Rectangle* const param_rectangle, const Camera* const camera);
//Only one possible output per input
SDL_Point RectangleToSDLCenterOfRotation(const Rectangle* const param_rectangle, const Camera* const camera);


//Only one possible output per input
SDL_Rect RectStructOneToSDLRect(const RectStructOne* const param_rect_struct_one, Camera* const camera);


//Only one possible output per input
RectStructTwo RectangleToBasicRectangle(const Rectangle* const param_rectangle);

//Only one possible output per input
RectStructOne RectangleToRectStructOne(const Rectangle* const param_rectangle);


//Multiple possible outputs per input SO:   (offset = { 0.0, 0.0 }), (relativity_rules = RelativityRules()), (reference_rectangle = nullptr), (flip =  { 0 }), (base_size = size)
Rectangle RectStructOneToRectangle(const RectStructOne* const param_rect_struct_one);




// -----------------   COLLISION FUNCTIONS   -----------------

bool OverlapPoint2DWithRectangle(const Point2D* const param_point, const Rectangle* const param_rectangle, const bool include_edge);

bool OverlapPoint2DWithRectStructOneEx(const Point2D* const param_point, const RectStructOne* const param_rect_struct_one, const bool include_edge_on_rect_struct_one_right, const bool include_edge_on_rect_struct_one_bottom, const bool include_edge_on_rect_struct_one_left, const bool include_edge_on_rect_struct_one_top);
bool OverlapPoint2DWithRectStructOne(const Point2D* const param_point, const RectStructOne* const param_rect_struct_one, const bool include_edge);

bool OverlapRectStructOneWithRectStructOneEx(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge_on_first_rect_struct_right, const bool include_edge_on_first_rect_struct_bottom, const bool include_edge_on_first_rect_struct_left, const bool include_edge_on_first_rect_struct_top);
bool OverlapRectStructOneWithRectStructOne(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge);






// -----------------   OBSELETE FUNCTIONS   -----------------

Point2D GetRelativePoint(const Point2D* const param_point, const Point2D reference_point, const Size2D reference_size_scale);
Size2D GetRelativeSize(const Size2D* const param_size, const Size2D reference_size);