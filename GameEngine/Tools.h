#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Camera.h"
#include <iostream>
#include <algorithm>

using namespace std;

struct SDL_Size
{
	int w;
	int h;
};

// -----------------   CONVERSION FUNCTIONS   -----------------

SDL_Rect BasicRectangleToSDLRect(BasicRectangle* param_rectangle, Camera* camera);



double SDLXToUniX(int param_sdl_x, RigidCentering pixel_side, Camera* camera);
double SDLYToUniY(int param_sdl_y, RigidCentering pixel_side, Camera* camera);
Point2D SDLPointToUniPoint(SDL_Point param_sdl_point, RigidCentering pixel_side_horizontal, RigidCentering pixel_side_vertical, Camera* camera);

//Assumed outer_pixel_side
double SDLWidthToUniWidth(int param_sdl_width, Camera* camera);
//Assumed outer_pixel_defined_side
double SDLHeightToUniHeight(int param_sdl_height, Camera* camera);
//Assumed outer_pixel_side
Size2D SDLSizeToUniSize(SDL_Size param_sdl_size, Camera* camera);


int UniXToSDLX(double param_uni_x, RigidCentering pixel_side, Camera* camera);
int UniYToSDLY(double param_uni_y, RigidCentering pixel_side, Camera* camera);
SDL_Point UniPointToSDLPoint(Point2D param_uni_point, RigidCentering pixel_side_horizontal, RigidCentering pixel_side_vertical, Camera* camera);

//Assumed outer_pixel_side.  If finding the sdl_width of a "Rectangle," provide uni_left_edge.  If not, pass NULL for "param_uni_left_edge"
int UniWidthToSDLWidth(double param_uni_width, double param_uni_left_edge, Camera* camera);
//Assumed outer_pixel_side.  If finding the sdl_height of a "Rectangle," provide uni_top_edge.  If not, pass NULL for "param_uni_top_edge"
int UniHeightToSDLHeight(double param_uni_height, double param_uni_top_edge, Camera* camera);
//Assumed outer_pixel_side.  If finding the sdl_size of a "Rectangle," provide uni_top_left_corner.  If not, pass NULL for "param_uni_top_left_corner"
SDL_Size UniSizeToSDLSize(Size2D param_uni_size, Point2D param_uni_top_left_corner, Camera* camera);



int GetSDLWidthWithTwoSDLX(int param_lesser_sdl_x, int param_greater_sdl_x);
int GetSDLHeightWithTwoSDLY(int param_lesser_sdl_y, int param_greater_sdl_y);
SDL_Size GetSDLSizeWithTwoSDLPoints(SDL_Point param_top_left_sdl_corner, SDL_Point param_bottom_right_sdl_corner);



SDL_Rect GetSDLRectWithEdges(int right_edge, int bottom_edge, int left_edge, int top_edge);



SDL_Rect RectangleDataToSDLRect(RectangleData* param_rectangle_data, Camera* camera);
SDL_Point RectangleDataToSDLCenterOfRotation(RectangleData* param_rectangle_data, Camera* camera);






// -----------------   COLLISION FUNCTIONS   -----------------

bool OverlapPoint2DWithRectangleData(Point2D* param_point, RectangleData* param_rectangle_data, bool include_edge);

bool OverlapRectStructOneWithRectStructOneEx(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge_on_first_rect_struct_right, const bool include_edge_on_first_rect_struct_bottom, const bool include_edge_on_first_rect_struct_left, const bool include_edge_on_first_rect_struct_top);
bool OverlapRectStructOneWithRectStructOne(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge);






// -----------------   OBSELETE FUNCTIONS   -----------------

Point2D GetRelativePoint(Point2D* param_point, Point2D reference_point, Size2D reference_size_scale);
Size2D GetRelativeSize(Size2D* param_size, Size2D reference_size);