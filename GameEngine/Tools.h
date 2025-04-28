#pragma once
#include "ColorFormats.h"
#include "RectangleNew.h"
#include "Camera.h"
#include <iostream>
#include <algorithm>
#include <random>

#define BASE_WINDOW_PIXEL_WIDTH 1920
#define BASE_WINDOW_PIXEL_HEIGHT 1080

const unsigned int HALF_BASE_WINDOW_PIXEL_WIDTH = BASE_WINDOW_PIXEL_WIDTH / 2;
const unsigned int HALF_BASE_WINDOW_PIXEL_HEIGHT = BASE_WINDOW_PIXEL_HEIGHT / 2;

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

//Assumed outer_pixel_side.  If finding the sdl_width of a "RectangleOld," provide uni_left_edge.  If not, pass NULL for "param_uni_left_edge"
int UniWidthToSDLWidth(const double param_uni_width, const double param_uni_left_edge, const Camera* camera);
//Assumed outer_pixel_side.  If finding the sdl_height of a "RectangleOld," provide uni_top_edge.  If not, pass NULL for "param_uni_top_edge"
int UniHeightToSDLHeight(const double param_uni_height, const double param_uni_top_edge, const Camera* camera);
//Assumed outer_pixel_side.  If finding the sdl_size of a "RectangleOld," provide uni_top_left_corner.  If not, pass NULL for "param_uni_top_left_corner"
SDL_Size UniSizeToSDLSize(const Size2D param_uni_size, const Point2D param_uni_top_left_corner, const Camera* camera);



int GetSDLWidthWithTwoSDLX(const int param_lesser_sdl_x, const int param_greater_sdl_x);
int GetSDLHeightWithTwoSDLY(const int param_lesser_sdl_y, const int param_greater_sdl_y);
SDL_Size GetSDLSizeWithTwoSDLPoints(const SDL_Point param_top_left_sdl_corner, const SDL_Point param_bottom_right_sdl_corner);



SDL_Rect GetSDLRectWithEdges(const int right_edge, const int bottom_edge, const int left_edge, const int top_edge);



//Only one possible output per input
SDL_Rect RectangleToSDLRect(const RectangleOld* const param_rectangle, const Camera* const camera);
//Only one possible output per input
SDL_Point RectangleToSDLCenterOfRotation(const RectangleOld* const param_rectangle, const Camera* const camera);


//Only one possible output per input
SDL_Rect RectStructOneToSDLRect(const RectStructOne* const param_rect_struct_one, Camera* const camera);


//Only one possible output per input
RectStructTwo RectangleToBasicRectangle(const RectangleOld* const param_rectangle);

//Only one possible output per input
RectStructOne RectangleToRectStructOne(const RectangleOld* const param_rectangle);


//Multiple possible outputs per input SO:   (offset = { 0.0, 0.0 }), (relativity_rules = RelativityRules()), (reference_rectangle = nullptr), (flip =  { 0 }), (base_size = size)
RectangleOld RectStructOneToRectangle(const RectStructOne* const param_rect_struct_one);






// -----------------   POINT CONVERSION FUNCTIONS BASED ON BASE WINDOW SIZE   -----------------

//Returns the proportion x value for a given x value. A proportion x value of -1.0 is at the left edge of the screen and a proportion x value of 1.0 is at the right edge of the screen.
double XToProportionX(const double x);
//Returns the proportion y value for a given y value. A proportion y value of -1.0 is at the bottom edge of the screen and a proportion y value of 1.0 is at the top edge of the screen.
double YToProportionY(const double y);

//Returns the GLColor value that corresponds to a given SDL_Color. GLColor operates on values 0.0f to 1.0f, and SDL_Color operates on Uint8 values.
GLColor SDLColorToGLColor(const SDL_Color sdl_color);
//IMPORTANT!!!: Creates a GLColor object in the heap. Use delete on the return value to avoid memory leaking! Returns the GLColor value that corresponds to a given SDL_Color. GLColor operates on values 0.0f to 1.0f, and SDL_Color operates on Uint8 values.
GLColor* SDLColorToGLColor(const SDL_Color* const sdl_color);
//IMPORTANT!!!: narrowing conversion from float to Uint8 for r, g, b, and a;   Returns the SDL_Color value that corresponds to a given GL_Color. GLColor operates on values 0.0f to 1.0f, and SDL_Color operates on Uint8 values.
SDL_Color GLColorToSDLColor(const GLColor gl_color);
//IMPORTANT!!!: Creates a GLColor object in the heap. Use delete on the return value to avoid memory leaking! ALSO IMPORTANT!!!: narrowing conversion from float to Uint8 for r, g, b, and a;   Returns the SDL_Color value that corresponds to a given GL_Color. GLColor operates on values 0.0f to 1.0f, and SDL_Color operates on Uint8 values.
SDL_Color* GLColorToSDLColor(const GLColor* const gl_color);

//Returns the uni_point after being transformed to screen coords relative to a given camera. Pass nullptr for no camera
Point2DNew UniPointToScreenPoint(const Point2DNew uni_point, const CameraNew* const camera);

Quad UniQuadToScreenQuad(const Quad* const uni_quad, const CameraNew* const camera);






// -----------------   COLLISION FUNCTIONS   -----------------

bool OverlapPoint2DWithRectangleEx(const Point2D* const param_point, const RectangleOld* const param_rectangle, const bool include_rectangle_right_edge, const bool include_rectangle_bottom_edge, const bool include_rectangle_left_edge, const bool include_rectangle_top_edge);
bool OverlapPoint2DWithRectangle(const Point2D* const param_point, const RectangleOld* const param_rectangle, const bool include_edge);

bool OverlapPoint2DWithRectStructOneEx(const Point2D* const param_point, const RectStructOne* const param_rect_struct_one, const bool include_rect_struct_one_right_edge, const bool include_rect_struct_one_bottom_edge, const bool include_rect_struct_one_left_edge, const bool include_rect_struct_one_top_edge);
bool OverlapPoint2DWithRectStructOne(const Point2D* const param_point, const RectStructOne* const param_rect_struct_one, const bool include_edge);

bool OverlapRectStructOneWithRectStructOneEx(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_first_rect_struct_one_right_edge, const bool include_first_rect_struct_one_bottom_edge, const bool include_first_rect_struct_one_left_edge, const bool include_first_rect_struct_one_top_edge);
bool OverlapRectStructOneWithRectStructOne(const RectStructOne* const first_rect_struct_one, const RectStructOne* const second_rect_struct_one, const bool include_edge);






// -----------------   OBSELETE FUNCTIONS   -----------------

Point2D GetRelativePoint(const Point2D* const param_point, const Point2D reference_point, const Size2D reference_size_scale);
Size2D GetRelativeSize(const Size2D* const param_size, const Size2D reference_size);






// -----------------   RECTANGLENEW CONVERSIONS   -----------------

SDL_Point Point2DNewToSDLPoint(const Point2DNew point, const RigidCentering pixel_side_horizontal, const RigidCentering pixel_side_vertical, const Camera* const camera);
//Assumed outer pixel side
SDL_Size Size2DNewToSDLSize(const Size2DNew size, const Point2DNew top_left_corner, const Camera* camera);
//IMPORTANT!!: SDL_Rect does not include rotation or flipping, so essentially rotation is treated as 0 and flipping is treated as SDL_FLIP_NONE in this function!
SDL_Rect RectangleNewToSDLRect(const RectangleNew* const rect, Camera* const camera);

SDL_RectWithRotation RectangleNewToSDLRectWithRotation(const RectangleNew* const rect, Camera* const camera);
SDL_RectWithRotation RectangleNewToSDLRectWithRotation(const Point2DNew* const pos, const Size2DNew* const unscaled_size, const Scale2DNew* const scale, const Centering2DNew* const centering, const Rotation2DNew* const rotation, const TotalFlip* const total_flip, Camera* const camera);


SDL_RectWithRotation RefRectangleNewToSDLRectWithRotation(const RefRectangleNew* const rect, Camera* const camera);
SDL_RectWithRotation RefRectangleNewToSDLRectWithRotation(const RefPoint2DNew* const pos, const Size2DNew* const unscaled_size, const RefScale2DNew* const scale, const Centering2DNew* const centering, const RefRotation2DNew* const rotation, const RefTotalFlip* const total_flip, Camera* const camera);

SDL_RectWithRotation RefRectangleNewNewToSDLRectWithRotation(const RefRectangleNewNew* const rect, Camera* const camera);
SDL_RectWithRotation RefRectangleNewNewToSDLRectWithRotation(const RefPoint2DNewNew* const pos, const RefSize2DNewNew* const unscaled_size, const RefScale2DNewNew* const scale, const Centering2DNew* const centering, const RefRotation2DNewNew* const rotation, const RefTotalFlip* const total_flip, Camera* const camera);