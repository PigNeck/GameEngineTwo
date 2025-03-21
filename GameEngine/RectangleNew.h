#pragma once

#include "GL/glew.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_opengl.h"
#include <iostream>
#include <limits>
#include <vector>
#include "Rectangle.h"


using namespace std;

struct EdgeData
{
    bool y_axis = 0;
    bool subtract_one = 0;
    bool flip = 0;

    double GetSubtractOneDouble() const;
    double GetFlipDouble() const;
};


// -----------------   IDEK WHAT TO CALL THIS. SNAP FUNCTIONS MAYBE?   -----------------

void SnapDouble(double* const double_pointer, const double m, const double b, const unsigned int accepted_epsilon_difference);
void SnapAwayDouble(double* const double_pointer, const double m, const double b, const unsigned int accepted_epsilon_difference);

//IMPORTANT!!!: [degree_snap_factor] must be an int factor of 360! Converts [radians] to a corresponding degree value, and then snaps any value [accepted_epsilon_difference] distance away from a multiple of [degree_snap_factor]. This function always returns values in the range [0.0, 360.0). The [accepted_epsilon_difference] should be greater for lower values of [degree_snap_factor], but also depends on the precision of [radians]. A good (fairly safe) [accepted_epsilon_difference] would be 1000, 
double SnapRadiansToDegrees(const double radians, const unsigned int degree_snap_factor, const unsigned int accepted_epsilon_difference = 1000);















// ----------------------------------   9 0 - S T R U C T S   ----------------------------------

// -----------------   ENUMS   -----------------
enum class CornerEnum : unsigned char
{
    TOP_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT,
    TOP_LEFT
};
enum class DirectionEnum : unsigned char
{
    RIGHT,
    BOTTOM,
    LEFT,
    TOP
};
enum class RotationEnum : unsigned char
{
    DEGREES_0,
    DEGREES_90,
    DEGREES_180,
    DEGREES_270
};




// -----------------   ROTATION90   -----------------
struct Rotation2DNew;
struct Rotation90
{
    RotationEnum val = RotationEnum::DEGREES_0;

    Rotation90();
    Rotation90(const RotationEnum i_val);
    //IMPORTANT: Snaps [rotation_2d_new] to the nearest representable value of RotationEnum.
    Rotation90(const Rotation2DNew& rotation_2d_new);

    double GetRadians() const;
    double GetDegrees() const;
};




// -----------------   FLIP90   -----------------
struct TotalFlip; //TotalFlip should destroyed at some point
struct Flip90
{
    bool flip_horizontally = 0;
    bool flip_vertically = 0;

    Flip90();
    Flip90(const bool i_flip_horizontally, const bool i_flip_vertically);
    Flip90(const TotalFlip& total_flip);
};




// -----------------   SCALE90   -----------------
struct Scale2DNew;
struct Scale90
{
    double width_scale = 1.0;
    double height_scale = 1.0;

    Scale90();
    Scale90(const double i_width_scale, const double i_height_scale);
    //IMPORTANT: [scale_2d_new.width_radian_offset] and [scale_2d_new.height_radian_offset] are ignored (they don't survive the conversion).
    Scale90(const Scale2DNew& scale_2d_new);
};




// -----------------   TRANSFORMATIONS90   -----------------
struct Transformations;
struct Transformations90
{
    Rotation90 rotation;
    Scale90 scale;
    Flip90 flip;

    Transformations90(const Rotation90 i_rotation = Rotation90(), const Scale90 i_scale = Scale90(), const Flip90 i_flip = Flip90());
    Transformations90(const Transformations& transformations);


    void RotateCounterclockwise(const unsigned char number_of_counterclockwise_90_degree_rotations = 1);
    void RotateClockwise(const unsigned char number_of_clockwise_90_degree_rotations = 1);
};












// ----------------------------------   F U L L   D A T A   S T R U C T S   ----------------------------------

// -----------------   POINT 2D   -----------------
struct Point2DNew
{
    double x = 0.0;
    double y = 0.0;

    Point2DNew();
    Point2DNew(const double i_x, const double i_y);
};
struct RefTransformations;
struct RefPoint2DNewest
{
    double x = 0.0;
    double y = 0.0;

    const RefPoint2DNewest* reference_point = nullptr;
    const RefTransformations* reference_transformations = nullptr;



    RefPoint2DNewest();
    RefPoint2DNewest(const double i_x, const double i_y);
    RefPoint2DNewest(const Point2DNew non_ref_point);
    RefPoint2DNewest(const double i_x, const double i_y, const RefPoint2DNewest* const i_reference_point, const RefTransformations* const i_reference_transformations);
    RefPoint2DNewest(const Point2DNew non_ref_point, const RefPoint2DNewest* const i_reference_point, const RefTransformations* const i_reference_transformations);


    //All commented out lines (except for method descriptions) are TO-DO
    Point2DNew GetDepthValue(const unsigned int depth_index) const;
    //double GetDepthX(const unsigned int depth_index) const;
    //double GetDepthY(const unsigned int depth_index) const;

    void SetValueToFitDepthValue(const unsigned int depth_index, const Point2DNew depth_value);
    //Moves point HORIZONTALLY (on the plane defined by depth_index) to fit depth_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
    //void SetValueToFitDepthX(const unsigned int depth_index, const double depth_x);
    //Moves point VERTICALLY (on the plane defined by depth_index) to fit depth_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
    //void SetValueToFitDepthY(const unsigned int depth_index, const double depth_x);


    Point2DNew GetUniValue() const;
    //double GetUniX() const;
    //double GetUniY() const;

    void SetValueToFitUniValue(const Point2DNew uni_value);
    //Moves point HORIZONTALLY to fit uni_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
    //void SetValueToFitUniX(const double uni_x);
    //Moves point VERTICALLY to fit uni_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
    //void SetValueToFitUniY(const double uni_y);


    unsigned int GetDepthIndex(const RefPoint2DNewest* const depth_pointer) const;

    Point2DNew GetDepthValue(const RefPoint2DNewest* const depth_pointer) const;
    //double GetDepthX(const RefPoint2DNewNew* const depth_pointer) const;
    //double GetDepthY(const RefPoint2DNewNew* const depth_pointer) const;

    //void SetValueToFitDepthValue(const RefPoint2DNewNew* const depth_pointer, const Point2DNew depth_value);
    //Moves point HORIZONTALLY (on the plane defined by depth_pointer) to fit depth_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
    //void SetValueToFitDepthX(const RefPoint2DNewNew* const depth_pointer, const double depth_x);
    //Moves point VERTICALLY (on the plane defined by depth_pointer) to fit depth_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
    //void SetValueToFitDepthY(const RefPoint2DNewNew* const depth_pointer, const double depth_y);
};




// -----------------   SIZE 2D   -----------------
struct Size2DNew
{
    double width = 100.0;
    double height = 100.0;

    Size2DNew();
    Size2DNew(const double i_width, const double i_height);
};




// -----------------   CENTERING 2D   -----------------
struct Centering2DNew
{
    double x_centering = 0.0; //-1.0 = right edge of rectangle lines up with x pos; 0.0 = centered on the x axis; 1.0 = left edge of rectangle lines up with x pos
    double y_centering = 0.0; //-1.0 = top edge of rectangle lines up with y pos; 0.0 = centered on the y axis; 1.0 = bottom edge of rectangle lines up with y pos

    Centering2DNew();
    Centering2DNew(const double i_x_centering, const double i_y_centering);
};




// -----------------   SCALE 2D   -----------------
struct Scale2DNew
{
    double width_scale = 1.0;
    double width_radian_offset = 0.0; //In radians

    double height_scale = 1.0;
    double height_radian_offset = 0.0; //In radians

    Scale2DNew();
    Scale2DNew(const double i_width_scale, const double i_height_scale);
    Scale2DNew(const double i_width_scale, const double i_width_direction_offset, const double i_height_scale, const double i_height_direction_offset);
    Scale2DNew(const Scale90 scale_90);
};




// -----------------   ROTATION 2D   -----------------
struct Rotation2DNew
{
    double radians = 0.0;

    Rotation2DNew();
    Rotation2DNew(const double i_radians);
    Rotation2DNew(const RotationEnum rotation_90);

    double GetDegrees() const;
    void SetWithDegrees(const double degrees);
};




// -----------------   TOTAL FLIP   -----------------
struct TotalFlip
{
    bool flip_horizontally = 0;
    bool flip_vertically = 0;

    double horizontal_direction_offset = 0.0;
    double vertical_direction_offset = 0.0;

    TotalFlip(const bool i_flip_horizontally = false, const bool i_flip_vertically = false, const double i_horizontal_direction_offset = 0.0, const double i_vertical_direction_offset = 0.0);
    TotalFlip(const Flip90& flip_90);

    //IMPORTANT!!!: If both flip_horizontally and flip_vertically are true, this function returns SDL_FLIP_NONE (SDL_RendererFlip does not support flipping in both directions). This case should be handled outside the function.
    SDL_RendererFlip GetSDLFlip() const;
};




// -----------------   TRANSFORMATIONS 2D   -----------------
struct Transformations
{
    Rotation2DNew rotation;
    Scale2DNew scale;
    TotalFlip total_flip;

    Transformations();
    Transformations(const Rotation2DNew i_rotation, const Scale2DNew i_scale, const TotalFlip i_total_flip);
    Transformations(const Transformations90 transformations_90);
};
struct RefTransformations
{
    Rotation2DNew rotation;

    Scale2DNew scale;

    TotalFlip total_flip;


    const RefTransformations* reference_transformations = nullptr;


    RefTransformations();
    RefTransformations(const Transformations non_ref_transformations, const RefTransformations* const i_reference_transformations = nullptr);
    RefTransformations(const Rotation2DNew i_rotation, const Scale2DNew i_scale, const TotalFlip i_total_flip);
    RefTransformations(const Rotation2DNew i_rotation, const Scale2DNew i_scale, const TotalFlip i_total_flip, const RefTransformations* const i_reference_transformations);

    Transformations GetDepthValue(const unsigned int depth_index) const;

    //Rotation2DNew GetDepthRotation(...) etc... TO-DO

    //void SetValueToFitDepthValue(const unsigned int depth_index, const Transformations depth_value); TO-DO
    //void SetRotationToFitDepthValue(...) etc... TO-DO


    Transformations GetUniValue() const;
    //Rotation2DNew GetUniRotation(...) etc... TO-DO

    //void SetValueToFitUniValue(const Transformations uni_value); TO-DO
    //void SetRotationToFitUniValue(...) etc... TO-DO


    unsigned int GetDepthIndex(const RefTransformations* const depth_pointer) const;

    Transformations GetDepthValue(const RefTransformations* const depth_pointer) const;
    //Rotation2DNew GetDepthRotation(...) etc... TO-DO

    //void SetValueToFitDepthValue(const RefTransformations* const depth_pointer, const Transformations depth_value); TO-DO
    //void SetRotationToFitDepthValue(...) etc... TO-DO
};




// -----------------   QUAD   -----------------
struct Quad
{
    Point2DNew top_right;
    Point2DNew bottom_right;
    Point2DNew bottom_left;
    Point2DNew top_left;

    Quad();
    Quad(const double right_edge, const double bottom_edge, const double left_edge, const double top_edge);
    Quad(const Point2DNew i_top_right, const Point2DNew i_bottom_right, const Point2DNew i_bottom_left, const Point2DNew i_top_left);

    void Align90(const unsigned int WILL_BE_SCALED_accepted_epsilon_difference);
};












struct Line2D;
struct Offset2DNew;
// ----------------------------------   R E C T A N G L E   ----------------------------------

// -----------------   NON-REFERENCE   -----------------
struct RectangleNewest
{
    //---- Data ----

    Point2DNew pos;
    Transformations transformations;
    Size2DNew unscaled_size;
    Centering2DNew centering;

    Quad GetQuad() const;

    Point2DNew GetCorner(const CornerEnum corner) const;

    //TO-DO: add all the methods for this class


    //---- Edge Functions ----
    
    //Returns a line that contains the two corners of a given edge. The returned [v_2] will be the corner further along clockwise than [v_1], although this rarely matters.
    Line2D GetEdge(const DirectionEnum edge) const;


    //---- Scale Functions ----
    
    //IMPORTANT!!!: Does not account for [width_radian_offset] or [height_radian_offset] in calculation (may produce potentially unexpected results in some cases). For more information, look at function body.
    Size2DNew GetScaledSize() const;
    //IMPORTANT!!!: Does not account for [width_radian_offset] in calculation (may produce potentially unexpected results in some cases). For more information, look at function body.
    double GetScaledWidth() const;
    //IMPORTANT!!!: Does not account for [height_radian_offset] in calculation (may produce potentially unexpected results in some cases). For more information, look at function body.
    double GetScaledHeight() const;


    //---- Centering/Offset Functions ----

    Offset2DNew GetUnscaledOffset() const;
    double GetUnscaledOffsetX() const;
    double GetUnscaledOffsetY() const;

    //IMPORTANT!!!: Does not account for [width_radian_offset] or [height_radian_offset] in calculation (may produce potentially unexpected results in some cases). For more information, look at function body.
    Offset2DNew GetScaledOffset() const;
    //IMPORTANT!!!: Does not account for [width_radian_offset] in calculation (may produce potentially unexpected results in some cases). For more information, look at function body.
    double GetScaledOffsetX() const;
    //IMPORTANT!!!: Does not account for [height_radian_offset] in calculation (may produce potentially unexpected results in some cases). For more information, look at function body.
    double GetScaledOffsetY() const;
};




// -----------------   REFERENCE   -----------------
struct RefRectangleNewest
{
    RefPoint2DNewest pos;
    Size2DNew unscaled_size;
    Centering2DNew centering;
    RefTransformations transformations;


    RefRectangleNewest();
    //Recommended
    RefRectangleNewest(const RefRectangleNewest* const reference_rectangle, const Point2DNew non_ref_pos = Point2DNew(), const Size2DNew i_unscaled_size = Size2DNew(), const Centering2DNew i_centering = Centering2DNew(), const Transformations non_ref_transformations = Transformations());
    //Recommended
    RefRectangleNewest(const RefPoint2DNewest* const reference_point, const RefTransformations* const reference_transformations, const Point2DNew non_ref_pos = Point2DNew(), const Size2DNew i_unscaled_size = Size2DNew(), const Centering2DNew i_centering = Centering2DNew(), const Transformations non_ref_transformations = Transformations());
    //Non-recommended
    RefRectangleNewest(const RefPoint2DNewest i_pos, const RefTransformations i_transformations, const Size2DNew i_unscaled_size, const Centering2DNew i_centering);
    //Non-recommended
    RefRectangleNewest(const RectangleNewest non_ref_rectangle);


    RectangleNewest GetUniValue() const;
    RectangleNewest GetDepthValue(const unsigned int depth_index) const;

    Quad GetUniQuad() const;
    Quad GetDepthQuad(const unsigned int depth_index) const;

    Point2DNew GetUniCorner(const CornerEnum corner) const;
    Point2DNew GetDepthCorner(const CornerEnum corner, const unsigned int depth_index) const;

    void SetPosToFitCurrentPlanePointToDepthPoint(const Point2DNew depth_point, const Point2DNew current_plane_point, const unsigned int depth_index);

    void SetDepthCorner(const Point2DNew depth_corner, const CornerEnum corner_identity, const unsigned int depth_index);
    void SetUniCorner(const Point2DNew uni_corner, const CornerEnum corner_identity);


    Size2DNew GetScaledSize() const;
    double GetScaledWidth() const;
    double GetScaledHeight() const;

    void SetScaledSize(const Size2DNew scaled_size);
    void SetScaledWidth(const double scaled_width);
    void SetScaledHeight(const double scaled_height);


    void SetReference(const RefRectangleNewest* const reference_rectangle);
};

























// ----------------------------------   O L D   S T U F F   ----------------------------------
struct RectangleNew
{
    //---- Data ----
    Point2DNew pos;
    Size2DNew unscaled_size;
    Scale2DNew scale;
    Centering2DNew centering;
    Rotation2DNew rotation; //In radians
    TotalFlip total_flip;


    //---- Edge Functions ----
    double GetEdge(const Direction direction) const;
    Point2DNew GetCorner(const Corner corner) const;

    //set edge, set corner, etc.


    //---- Scale Functions ----
    Size2DNew GetScaledSize() const;
    double GetScaledWidth() const;
    double GetScaledHeight() const;


    //---- Centering/Offset Functions ----
    Offset2DNew GetUnscaledOffset() const;
    double GetUnscaledOffsetX() const;
    double GetUnscaledOffsetY() const;

    Offset2DNew GetScaledOffset() const;
    double GetScaledOffsetX() const;
    double GetScaledOffsetY() const;
};







// -----------------   REFERENCE STRUCTS   -----------------

//struct RefTransformations90;
/*
enum class TransformationsPointerState : unsigned char
{
    TRANSFORMATIONS_POINTER_IS_ACTIVE,
    TRANSFORMATIONS90_POINTER_IS_ACTIVE,
    NEITHER_ARE_ACTIVE
};

class TransformationsPointer //This class contains both a pointer to RefTransformations and RefTransformations90, but it only uses one at a time.
{
    const RefTransformations* transformations_pointer = nullptr;
    const RefTransformations90* transformations90_pointer = nullptr;


public:
    TransformationsPointer();
    TransformationsPointer(const RefTransformations* const i_transformations_pointer);
    TransformationsPointer(const RefTransformations90* const i_transformations90_pointer);

    //If one of the pointers is active, and the other is set, then the first pointer will be set to nullptr (so that only one pointer is active at any given time)
    void SetPointer(const RefTransformations* const new_transformations_pointer);
    //If one of the pointers is active, and the other is set, then the first pointer will be set to nullptr (so that only one pointer is active at any given time)
    void SetPointer(const RefTransformations90* const new_transformations90_pointer);

    TransformationsPointerState GetState() const;
    TransformationsPointerState GetDepthState(const unsigned int depth_index) const;
    TransformationsPointerState GetUniState() const;

    const RefTransformations* GetTransformationsPointer() const;
    const RefTransformations90* GetTransformations90Pointer() const;
};
*/

struct RefTotalFlip //RefTotalFlip is the referenceable version of TotalFlip, which contains data about horizontal and vertical flips or the lack there of;      Ex: If, say, an instance of RefTotalFlip has a flip value of FLIP_HORIZONTAL, and its reference_total_flip also has a flip value of FLIP_HORIZONTAL (and a reference_total_flip of nullptr), then the uni flip value would be FLIP_NONE (they cancel each other out).
{
    TotalFlip v;

    const RefTotalFlip* reference_total_flip = nullptr;

    //PSEUDO PRIVATE;  Essentially, this method does provide functionality unique to itself, but it has basically no use cases. It is meant to be basically just used by other member functions. Unless you know what you are doing, use GetUniValue or GetDepthValue instead :)
    TotalFlip GetDereferencedValue(const unsigned int depth_index, const RefTotalFlip* const depth_pointer) const;
    //PSEUDO PRIVATE;  Essentially, this method does provide functionality unique to itself, but it has basically no use cases. It is meant to be basically just used by other member functions. Unless you know what you are doing, use SetValueToFitUniValue or SetValueToFitDepthValue instead :)
    void SetValueToFitDereferencedValue(const unsigned int depth_index, const RefTotalFlip* const depth_pointer, const TotalFlip dereferenced_value);

    //Returns the fully dereferenced value of v.
    TotalFlip GetUniValue() const;
    //Returns the value of flip dereferenced to the depth defined by depth_index.
    TotalFlip GetDepthValue(const unsigned int depth_index) const;
    //Returns the value of flip dereferenced to the depth defined by depth_pointer (stops dereferencing at the instance of RefTotalFlip that corresponds to depth_pointer).
    TotalFlip GetDepthValue(const RefTotalFlip* const depth_pointer) const;

    //Sets the value of v so that the uni value of v is equal to the parameter "uni_value."
    void SetValueToFitUniValue(const TotalFlip uni_value);
    //Sets the value of v so that the v value dereferenced to the depth defined by depth_index is equal to the parameter "depth_value."
    void SetValueToFitDepthValue(const unsigned int depth_index, const TotalFlip depth_value);
    //Sets the value of v so that the v value dereferenced to the depth defined by depth_value (stops dereferencing at the instance of RefTotalFlip that corresponds to depth_pointer) is equal to the parameter "depth_value." 
    void SetValueToFitDepthValue(const RefTotalFlip* const depth_pointer, const TotalFlip depth_value);
};



/*
struct RefTransformations90
{
    RotationEnum rotation = RotationEnum::DEGREES_0;
    Scale90 scale;
    Flip90 flip;

    TransformationsPointer reference_transformations;


    RefTransformations90();

    RefTransformations90(const RotationEnum i_rotation);
    RefTransformations90(const Scale90 i_scale);
    RefTransformations90(const Flip90 i_flip);

    RefTransformations90(const RotationEnum i_rotation, const Scale90 i_scale);
    RefTransformations90(const RotationEnum i_rotation, const Flip90 i_flip);
    RefTransformations90(const Scale90 i_scale, const Flip90 i_flip);

    RefTransformations90(const RotationEnum i_rotation, const Scale90 i_scale, const Flip90 i_flip);

    RefTransformations90(const RotationEnum i_rotation, const Scale90 i_scale, const Flip90 i_flip, const TransformationsPointer i_reference_transformations);

    RefTransformations90(const Transformations90 i_non_ref_transformations, const TransformationsPointer i_reference_transformations);


    void RotateCounterclockwise(const unsigned char number_of_counterclockwise_90_degree_rotations);
    void RotateClockwise(const unsigned char number_of_clockwise_90_degree_rotations);

    RefTransformations GetRefTransformations() const;

    Transformations90 GetDepthValue90(const unsigned int depth_index) const;
    //Make sure you don't mean GetDepthValue90! This function returns an instance of Transformations, not Transformations90.
    Transformations GetDepthValue(const unsigned int depth_index) const;

    Transformations90 GetUniValue90() const;
    //Make sure you don't mean GetUniValue90! This function returns an instance of Transformations, not Transformations90.
    Transformations GetUniValue() const;
};
*/

//WARNING: When RefScale2DNewNew has different width and height scales and there is a rotated rectangle (in a non-cardinal direction) referencing it, the rectangle would become a rhombus which is ILLEGAL (we have rhombuses). Idk how to solve this problem
struct RefScale2DNewNew
{
    double width_scale = 1.0;
    double width_radian_offset = 0.0; //In radians

    double height_scale = 1.0;
    double height_radian_offset = 0.0; //In radians

    const RefScale2DNewNew* reference_scale = nullptr;



    RefScale2DNewNew();
    RefScale2DNewNew(const double i_width_scale, const double i_height_scale);
    RefScale2DNewNew(const double i_width_scale, const double i_height_scale, const RefScale2DNewNew* const i_reference_scale);



    Scale2DNew GetDepthValue(const unsigned int depth_index) const;
    double GetDepthWidthScale(const unsigned int depth_index) const;
    double GetDepthHeightScale(const unsigned int depth_index) const;
    
    void SetValueToFitDepthValue(const unsigned int depth_index, const Scale2DNew depth_value);
    void SetValueToFitDepthWidthScale(const unsigned int depth_index, const double depth_width_scale);
    void SetValueToFitDepthHeightScale(const unsigned int depth_index, const double depth_height_scale);


    Scale2DNew GetUniValue() const;
    double GetUniWidthScale() const;
    double GetUniHeightScale() const;

    void SetValueToFitUniValue(const Scale2DNew uni_value);
    void SetValueToFitUniWidthScale(const double uni_width_scale);
    void SetValueToFitUniHeightScale(const double uni_height_scale);


    unsigned int GetDepthIndex(const RefScale2DNewNew* const depth_pointer) const;

    Scale2DNew GetDepthValue(const RefScale2DNewNew* const depth_pointer) const;
    double GetDepthWidthScale(const RefScale2DNewNew* const depth_pointer) const;
    double GetDepthHeightScale(const RefScale2DNewNew* const depth_pointer) const;

    void SetValueToFitDepthValue(const RefScale2DNewNew* const depth_pointer, const Scale2DNew depth_value);
    void SetValueToFitDepthWidthScale(const RefScale2DNewNew* const depth_pointer, const double depth_width_scale);
    void SetValueToFitDepthHeightScale(const RefScale2DNewNew* const depth_pointer, const double depth_height_scale);
};

struct RefSize2DNewNew
{
    double width = 100.0;
    double height = 100.0;

    const RefScale2DNewNew* reference_scale = nullptr;



    RefSize2DNewNew();
    RefSize2DNewNew(const double i_width, const double i_height);
    RefSize2DNewNew(const double i_width, const double i_height, const RefScale2DNewNew* const i_reference_scale);



    Size2DNew GetDepthValue(const unsigned int depth_index) const;
    double GetDepthWidth(const unsigned int depth_index) const;
    double GetDepthHeight(const unsigned int depth_index) const;

    void SetValueToFitDepthValue(const unsigned int depth_index, const Size2DNew depth_value);
    void SetValueToFitDepthWidth(const unsigned int depth_index, const double depth_width);
    void SetValueToFitDepthHeight(const unsigned int depth_index, const double depth_height);


    Size2DNew GetUniValue() const;
    double GetUniWidth() const;
    double GetUniHeight() const;

    void SetValueToFitUniValue(const Size2DNew uni_value);
    void SetValueToFitUniWidth(const double uni_width);
    void SetValueToFitUniHeight(const double uni_height);


    unsigned int GetDepthIndex(const RefScale2DNewNew* const depth_pointer) const;

    Size2DNew GetDepthValue(const RefScale2DNewNew* const depth_pointer) const;
    double GetDepthWidth(const RefScale2DNewNew* const depth_pointer) const;
    double GetDepthHeight(const RefScale2DNewNew* const depth_pointer) const;

    void SetValueToFitDepthValue(const RefScale2DNewNew* const depth_pointer, const Size2DNew depth_value);
    void SetValueToFitDepthWidth(const RefScale2DNewNew* const depth_pointer, const double depth_width);
    void SetValueToFitDepthHeight(const RefScale2DNewNew* const depth_pointer, const double depth_height);
};

struct RefRotation2DNewNew
{
    double radians = 0.0; //In radians

    const RefRotation2DNewNew* reference_rotation = nullptr;
    const RefTotalFlip* reference_total_flip = nullptr;


    RefRotation2DNewNew();
    RefRotation2DNewNew(const double i_radians);
    RefRotation2DNewNew(const double i_radians, const RefRotation2DNewNew* const i_reference_rotation, const RefTotalFlip* const i_reference_total_flip);


    Rotation2DNew GetDepthValue(const unsigned int depth_index) const;
    void SetValueToFitDepthValue(const unsigned int depth_index, const Rotation2DNew depth_value);

    Rotation2DNew GetUniValue() const;
    void SetValueToFitUniValue(const Rotation2DNew uni_value);

    unsigned int GetDepthIndex(const RefRotation2DNewNew* const depth_pointer) const;
    Rotation2DNew GetDepthValue(const RefRotation2DNewNew* const depth_pointer) const;
    void SetValueToFitDepthValue(const RefRotation2DNewNew* const depth_pointer, const Rotation2DNew depth_value);
};

struct RefPoint2DNewNew
{
    double x = 0.0;
    double y = 0.0;

    const RefPoint2DNewNew* reference_point = nullptr;
    const RefScale2DNewNew* reference_scale = nullptr;
    const RefRotation2DNewNew* reference_rotation = nullptr;
    const RefTotalFlip* reference_total_flip = nullptr;



    RefPoint2DNewNew();
    RefPoint2DNewNew(const double i_x, const double i_y);
    RefPoint2DNewNew(const double i_x, const double i_y, const RefPoint2DNewNew* const i_reference_point, const RefScale2DNewNew* const i_reference_scale, const RefRotation2DNewNew* const i_reference_rotation, const RefTotalFlip* const i_reference_total_flip);



    Point2DNew GetDepthValue(const unsigned int depth_index) const;
    double GetDepthX(const unsigned int depth_index) const;
    double GetDepthY(const unsigned int depth_index) const;

    void SetValueToFitDepthValue(const unsigned int depth_index, const Point2DNew depth_value);
    //Moves point HORIZONTALLY (on the plane defined by depth_index) to fit depth_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
    void SetValueToFitDepthX(const unsigned int depth_index, const double depth_x);
    //Moves point VERTICALLY (on the plane defined by depth_index) to fit depth_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
    void SetValueToFitDepthY(const unsigned int depth_index, const double depth_x);


    Point2DNew GetUniValue() const;
    double GetUniX() const;
    double GetUniY() const;

    void SetValueToFitUniValue(const Point2DNew uni_value);
    //Moves point HORIZONTALLY to fit uni_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
    void SetValueToFitUniX(const double uni_x);
    //Moves point VERTICALLY to fit uni_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
    void SetValueToFitUniY(const double uni_y);


    unsigned int GetDepthIndex(const RefPoint2DNewNew* const depth_pointer) const;

    Point2DNew GetDepthValue(const RefPoint2DNewNew* const depth_pointer) const;
    double GetDepthX(const RefPoint2DNewNew* const depth_pointer) const;
    double GetDepthY(const RefPoint2DNewNew* const depth_pointer) const;

    void SetValueToFitDepthValue(const RefPoint2DNewNew* const depth_pointer, const Point2DNew depth_value);
    //Moves point HORIZONTALLY (on the plane defined by depth_pointer) to fit depth_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
    void SetValueToFitDepthX(const RefPoint2DNewNew* const depth_pointer, const double depth_x);
    //Moves point VERTICALLY (on the plane defined by depth_pointer) to fit depth_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
    void SetValueToFitDepthY(const RefPoint2DNewNew* const depth_pointer, const double depth_y);
};


/*
struct RefRectangleNewest;
struct RefRectangle90
{
    RefPoint2DNewest pos;
    Size2DNew unscaled_size;
    Centering2DNew centering;
    RefTransformations90 transformations;

    //TO-DO? Currently only includes commonly used constructors
    RefRectangle90();
    RefRectangle90(const RefPoint2DNewest i_pos);
    RefRectangle90(const RefPoint2DNewest i_pos, const Size2DNew i_unscaled_size);
    RefRectangle90(const RefPoint2DNewest i_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering);
    RefRectangle90(const RefPoint2DNewest i_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const RefTransformations90 i_transformations);
    RefRectangle90(const RefRectangle90* const reference_rectangle, const Point2DNew i_non_ref_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const Transformations90 i_non_ref_transformations);
    RefRectangle90(const RefRectangleNewest* const reference_rectangle, const Point2DNew i_non_ref_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const Transformations90 i_non_ref_transformations);


    Rectangle90 GetUniValue() const;
    Rectangle90 GetDepthValue(const unsigned int depth_index) const;

    Quad GetUniQuad() const;
    Quad GetDepthQuad(const unsigned int depth_index) const;

    //IMPORTANT!!!: edge rotates and flips with [transformations.rotation] and [transformations.flip], so for example, DirectionEnum::RIGHT won't always be referencing the edge that appears on the right.
    double GetDepthEdge(const DirectionEnum edge, const unsigned int depth_index) const;
    //Alters [pos] to align the given [edge] to either an x or y value (defined by [target_coord]).
    void SetDepthEdge(const DirectionEnum edge, const double target_depth_coord, const unsigned int depth_index);

    //IMPORTANT!!!: corner rotates and flips with [transformations.rotation] and [transformations.flip], so for example, CornerEnum::TOP_RIGHT won't always be referencing the corner that appears on the top right.
    Point2DNew GetDepthCorner(const CornerEnum corner, const unsigned int depth_index) const;
    //Alters [pos] to align the given [corner] to a given [target_point].
    void SetDepthCorner(const CornerEnum corner, const Point2DNew target_depth_point, const unsigned int depth_index);


    Size2DNew GetScaledSize() const;
    double GetScaledWidth() const;
    double GetScaledHeight() const;

    void SetScaledSize(const Size2DNew scaled_size);
    void SetScaledWidth(const double scaled_width);
    void SetScaledHeight(const double scaled_height);


    void SetReference(const RefRectangle90* const reference_rectangle);
    void SetReference(const RefRectangleNewest* const reference_rectangle);
};
*/

struct RefRectangleNewNew
{
    RefPoint2DNewNew pos;
    RefSize2DNewNew unscaled_size;
    RefScale2DNewNew scale;
    Centering2DNew centering;
    RefRotation2DNewNew rotation; //In radians
    RefTotalFlip total_flip;

    RectangleNew GetRectangleNew() const;

    Point2DNew GetUniCorner(const CornerEnum corner) const;
    Point2DNew GetDepthCorner(const unsigned int depth_index, const CornerEnum corner) const;

    //void SetPosToFitUniCorner(...), SetPosToFitDepthCorner(...) (define later)!

    void SetReference(RefRectangleNewNew* const reference_rectangle);
};




















struct RefDoubleNew
{
    vector<double> v;

    RefDoubleNew();
    RefDoubleNew(vector<double> param_v);
    virtual ~RefDoubleNew();

private:
    // ------------- VIRTUAL FUNCTIONS -------------

    virtual vector<double> GetDereferencedValue(const unsigned int depth_index) const;
    virtual double GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const;
    virtual void SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value);
    virtual void SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value);




public:
    // ------------- IMPORTANT FUNCTIONS -------------

    //Returns the fully dereferenced value of v. It is called a "uni" or "universal" value.
    vector<double> GetUniValue() const;
    //Sets the fully dereferenced value of v. Essentially, this function alters the value of v so that the fully dereferenced value of v equals the passed uni_value variable.
    void SetUniValue(const vector<double> uni_value);

    //Returns the fully dereferenced value of v[v_index]. It is called a "uni" or "universal" value.
    double GetUniIndexedValue(const size_t v_index) const;
    //Sets the fully dereferenced value of v[v_index]. Essentially, this function alters the value of v[v_index] so that the fully dereferenced value of v[v_index] equals the passed uni_indexed_value variable.
    void SetUniIndexedValue(const size_t v_index, const double uni_indexed_value);




    // ---------- SIGNIFICANTLY LESS IMPORTANT FUNCTIONS ----------

    //Finds the value of v dereferenced to the depth defined by depth_index. A depth_index of 1, for example, would find the value of v dereferenced from the RD one rung below this one on the RD ladder. If depth_index is too high, this function returns the fully dereferenced value of v.
    vector<double> GetDepthValue(const unsigned int depth_index) const;
    //Finds the value of v[v_index] dereferenced to the depth defined by depth_index. A depth_index of 1, for example, would find the value of v[v_index] dereferenced from the RD one rung below this one on the RD ladder. If depth_index is too high, this function returns the fully dereferenced value of v[v_index].
    double GetDepthIndexedValue(const unsigned int depth_index, const size_t v_index) const;
    //Sets the value of v dereferenced to the depth defined by depth_index. A depth_index of 1, for example, would set the value of v dereferenced from the RD one rung below this one on the RD ladder. If depth_index is too high, this function sets the fully dereferenced value of v.
    void SetDepthValue(const unsigned int depth_index, const vector<double> depth_value);
    //Sets the value of v[v_index] dereferenced to the depth defined by depth_index. A depth_index of 1, for example, would set the value of v[v_index] dereferenced from the RD one rung below this one on the RD ladder. If depth_index is too high, this function sets the fully dereferenced value of v[v_index].
    void SetDepthIndexedValue(const unsigned int depth_index, const size_t v_index, const double depth_indexed_value);

    //Finds the value of v dereferenced to the depth defined by reverse_depth_index. This method is like GetDepthValue(...) except reverse_depth_index counts up from the bottom of the RD ladder. An inverse_depth_index of 0 would find the value of v dereferenced all the way down, and an inverse_depth_index of 1 would find the value of v dereferenced until the bottom-most rung of the RD ladder. If inverse_depth_index is too high, this function returns v.
    //vector<double> GetReverseDepthValue(const unsigned int reverse_depth_index) const;
    //Finds the value of v[v_index] dereferenced to the depth defined by reverse_depth_index. This method is like GetDepthIndexedValue(...) except reverse_depth_index counts up from the bottom of the RD ladder. An inverse_depth_index of 0 would find the value of v[v_index] dereferenced all the way down, and an inverse_depth_index of 1 would find the value of v[v_index] dereferenced until the bottom-most rung of the RD ladder. If inverse_depth_index is too high, this function just returns v[v_index].
    //double GetReverseDepthIndexedValue(const unsigned int reverse_depth_index, const size_t v_index) const;
    //Sets the value of v dereferenced to the depth defined by reverse_depth_index. This method is like SetDepthValue(...) except reverse_depth_index counts up from the bottom of the RD ladder. An inverse_depth_index of 0 would set the value of v dereferenced all the way down, and an inverse_depth_index of 1 would set the value of v dereferenced until the bottom-most rung of the RD ladder. If inverse_depth_index is too high, this function just sets v.
    //void SetReverseDepthValue(const unsigned int reverse_depth_index, const vector<double> depth_value);
    //Sets the value of v[v_index] dereferenced to the depth defined by reverse_depth_index. This method is like SetDepthIndexedValue(...) except reverse_depth_index counts up from the bottom of the RD ladder. An inverse_depth_index of 0 would set the value of v[v_index] dereferenced all the way down, and an inverse_depth_index of 1 would set the value of v[v_index] dereferenced until the bottom-most rung of the RD ladder. If inverse_depth_index is too high, this function just sets v[v_index].
    //void SetReverseDepthIndexedValue(const unsigned int reverse_depth_index, const size_t v_index, const double depth_indexed_value);
    
    //Finds the value of v dereferenced to the RD defined in depth_rd, given that depth_rd appears in the RD ladder. If it does not appear, then this function returns the fully dereferenced value of v.
    //vector<double> GetDepthValue(const RefDoubleNew* const depth_rd) const;
    //double GetDepthIndexedValue(const RefDoubleNew* const depth_rd, const size_t v_index) const;
    //void SetDepthValue(const RefDoubleNew* const depth_rd, const vector<double> depth_value);
    //void SetDepthIndexedValue(const RefDoubleNew* const depth_rd, const size_t v_index, const double depth_value);

    friend struct RefPoint2DNew;
    friend struct RefScale2DNew;
    friend struct RefRotation2DNew;
};

struct RefPoint2DNew : RefDoubleNew //v.size() should always be 2;  v[0] = x;  v[1] = y;
{
    RefDoubleNew* reference_point = nullptr;
    RefDoubleNew* reference_scale = nullptr;
    RefDoubleNew* reference_rotation = nullptr;
    RefTotalFlip* reference_total_flip = nullptr;

    RefPoint2DNew();
    RefPoint2DNew(const double x, const double y);
    RefPoint2DNew(const double x, const double y, RefDoubleNew* const i_reference_point, RefDoubleNew* const i_reference_scale, RefDoubleNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip);

    vector<double> GetDereferencedValue(const unsigned int depth_index) const override;
    double GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const override;
    void SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value) override;
    void SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value) override;

    Point2DNew GetPoint2DNew() const;
};

/*
struct RefSize2DNew : RefDoubleNew
{
    RefDoubleNew* reference_scale = nullptr;

    RefSize2DNew();
    RefSize2DNew(const double width, const double height);
    RefSize2DNew(const double width, const double height, RefDoubleNew* const i_reference_scale);

    vector<double> GetDerefencedValue() const override;
    void SetReferencedValue(const vector<double> uni_v) override;

    Size2DNew GetSize2DNew() const;
};
*/

struct RefScale2DNew : RefDoubleNew
{
    RefDoubleNew* reference_scale = nullptr;

    RefScale2DNew();
    RefScale2DNew(const double width_scale, const double height_scale);
    RefScale2DNew(const double width_scale, const double height_scale, RefDoubleNew* const i_reference_scale);

    vector<double> GetDereferencedValue(const unsigned int depth_index) const override;
    double GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const override;
    void SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value) override;
    void SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value) override;

    Scale2DNew GetScale2DNew() const;
};

struct RefRotation2DNew : RefDoubleNew
{
    RefDoubleNew* reference_rotation = nullptr;
    RefTotalFlip* reference_total_flip = nullptr;

    RefRotation2DNew();
    RefRotation2DNew(const double rotation);
    RefRotation2DNew(const double rotation, RefDoubleNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip);

    vector<double> GetDereferencedValue(const unsigned int depth_index) const override;
    double GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const override;
    void SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value) override;
    void SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value) override;

    Rotation2DNew GetRotation2DNew() const;
};

struct RefRectangleNew
{
    RefPoint2DNew pos;
    Size2DNew unscaled_size;
    RefScale2DNew scale;
    Centering2DNew centering;
    RefRotation2DNew rotation; //In radians
    RefTotalFlip total_flip;

    RectangleNew GetRectangleNew() const;

    void SetReference(RefRectangleNew* const reference_rectangle);
};















struct RD //Stands for "double with one reference" "v" is the "value" of the RD, "reference" is the RD this RD is relative to, and "reference_type" is the type of relationship this RD has with its reference RD.
{
    double v = 0.0; //This member variable is just the "value" of the RD. It is named "v" to reduce clutter.
    RD* reference = nullptr; //This member variable contains a pointer to the RD that this RD is relative to.
    unsigned char reference_type = 1; //0 = equals; 1 = add; 2 = subtract; 3 = multiply; 4 = divide; 5 = power; 6 = log base; 7 = other (you define by overloading the "Other(...)" and "InverseOther(...)" functions)

    double Other(const double temp_depth_value, const double pathi) const;
    double InverseOther(const double temp_depth_value, const double depth_value) const;

    //Returns the depth value given "depth." The depth value is essentially the value after its relativity has been removed a certain number of "levels" down the RD ladder. A depth of 1 = one step down, a depth of 2 = two steps down. If the depth exceeds the ladder length, it just stops at the end (essentially returning the same as GetUniValue()).
    double GetDepthValue(const size_t depth) const;
    //Returns the "objective" value of value, aka. a fully "deferenced" value. Essentially gets the max depth value. 
    double GetUniValue() const;

    //Sets the "value" member variable to match the given "depth_value" parameter. The depth value is essentially the value after its relativity has been removed a certain number of "levels" down the RD ladder. A depth of 1 = one step down, a depth of 2 = two steps down. If the depth exceeds the ladder length, it just stops at the end (essentially functioning the same as SetUniValue(...)).
    void SetDepthValue(const double depth_value, const size_t depth);
    //Sets the "value" member variable to match the given "uni_value" parameter.
    void SetUniValue(const double uni_value);
};

struct Point2DTwo;
struct Size2DTwo;

struct V2 //Stands for "vector 2." Contains two doubles named x and y. In certain situations, x may represent width, y may represent height, x may represent x_scale, y may represent y_scale, etc.
{
    double x; //May represent x position, width, x scale, etc.
    double y; //May represent y position, height, y scale, etc.

    V2();
    V2(double x, double y);

    //Returns an instance of Point2DTwo that has matching x and y values, no initial reference and reference_type 1 (add) (WARNING).
    Point2DTwo GetPoint2DTwo() const;
    //Returns an instance of Size2DTwo where x -> width and y -> height. It has no initial reference and is given reference_type 3 (multiply) (WARNING).
    Size2DTwo GetSize2DTwo() const;
};

struct Point2DTwo //Should always have reference_type 1 (add) (WARNING).
{
    RD x;
    RD y;

    void SetReferencePoint(Point2DTwo* reference_point);
    V2 GetUniPoint() const;
    void SetUniPoint(V2 uni_point);
};

struct Size2DTwo //Should always have reference_type 3 (multiply) (WARNING).
{
    RD width = { 1.0, nullptr, 3 };
    RD height = { 1.0, nullptr, 3 };

    void SetReferenceSize(Size2DTwo* reference_point);
    V2 GetUniSize() const;
    void SetUniSize(V2 uni_point);
};

struct RectangleTwo
{
    Point2DTwo pos;
    Point2DTwo centering;
    Size2DTwo unscaled_size;
    Size2DTwo scale;
    RD rotation;
};




/*
struct ARD //Stands for "additive reference double." Because it is additive, this.uni_value = the sum of the whole reference chain (desending starting at this).
{
    double v = 0.0; //This member variable is just the "value" of the ARD. It is named "v" to reduce clutter.
    ARD* reference = nullptr;

    //Returns the depth value given "depth." The depth value is essentially the value after its relativity has been removed a certain number of "levels" down the reference chain ladder. A depth of 1 = one step down, a depth of 2 = two steps down. If the depth exceeds the ladder length, it just stops at the end (essentially returning the same as GetUniValue()).
    double GetDepthValue(const size_t depth) const;
    //Returns the "objective" value of value, aka. a fully "deferenced" value. Essentially gets the max depth value.
    double GetUniValue() const;
    //IMPORTANT!!!: This method is NOT RECOMMENDED. Only use if you need to go more than 10,000 levels deep on the ARD ladder.
    double GetUniValueUnrestricted() const;

    //Sets the "value" member variable to match the given "depth_value" parameter. The depth value is essentially the value after its relativity has been removed a certain number of "levels" down the reference chain ladder. A depth of 1 = one step down, a depth of 2 = two steps down. If the depth exceeds the ladder length, it just stops at the end (essentially functioning the same as SetUniValue(...)).
    void SetDepthValue(const double depth_value, const size_t depth);
    //Sets the "value" member variable to match the given "uni_value" parameter.
    void SetUniValue(const double uni_value);
    //IMPORTANT!!!: This method is NOT RECOMMENDED. Only use if you need to go more than 10,000 levels deep on the ARD ladder.
    void SetUniValueUnrestricted(const double uni_value);
};

struct MRD //Stands for "multiplicative reference double." Because it is multiplicative, this.uni_value = the product(or multiplication result) of the whole reference chain (desending starting at this).
{
    double v = 0.0; //This member variable is just the "value" of the MRD. It is named "v" to reduce clutter.
    MRD* reference = nullptr;

    //Returns the depth value given "depth." The depth value is essentially the value after its relativity has been removed a certain number of "levels" down the reference chain ladder. A depth of 1 = one step down, a depth of 2 = two steps down. If the depth exceeds the ladder length, it just stops at the end (essentially returning the same as GetUniValue()).
    double GetDepthValue(const size_t depth) const;
    //Returns the "objective" value of value, aka. a fully "deferenced" value. Essentially gets the max depth value.
    double GetUniValue() const;
    //IMPORTANT!!!: This method is NOT RECOMMENDED. Only use if you need to go more than 10,000 levels deep on the MRD ladder.
    double GetUniValueUnrestricted() const;

    //Sets the "value" member variable to match the given "depth_value" parameter. The depth value is essentially the value after its relativity has been removed a certain number of "levels" down the reference chain ladder. A depth of 1 = one step down, a depth of 2 = two steps down. If the depth exceeds the ladder length, it just stops at the end (essentially functioning the same as SetUniValue(...)).
    void SetDepthValue(const double depth_value, const size_t depth);
    //Sets the "value" member variable to match the given "uni_value" parameter.
    void SetUniValue(const double uni_value);
    //IMPORTANT!!!: This method is NOT RECOMMENDED. Only use if you need to go more than 10,000 levels deep on the MRD ladder.
    void SetUniValueUnrestricted(const double uni_value);
};


struct V2 //Stands for "vector 2." Contains two doubles named x and y. In certain situations, x may represent width, y may represent height, x may represent x_scale, y may represent y_scale, etc.
{
    double x; //May represent x position, width, x scale, etc.
    double y; //May represent y position, height, y scale, etc.

    V2();
    V2(double x, double y);
};

struct Relativity
{
    double* x_reference = nullptr;
    double* y_reference = nullptr;

    double* scale_width_reference = nullptr;
    double* scale_height_reference = nullptr;

    double* rotation_reference = nullptr;
};

struct RectangleTwo
{
    V2 pos; //The x, y position of the rectangle. Yippee!!
    V2 unscaled_size = {100.0, 100.0}; //Scaled size (aka. real size) is equal to "unscaled_size" * "scale". To get scaled size, use GetScaledSize(), GetScaledWidth(), or GetScaledHeight().
    V2 scale; //"scale" partially defines scaled size (scaled size = "unscaled_size" * "scale"). Also, "scale" is a proportion, not a percentage.
    V2 centering = { 0.0, 0.0 }; //"centering" is a proportion that defines where the rectangle is relative to pos. For example, when "centering.x" == -1.0, the rectangle's right edge lines up with pos.x. When "centering.x" == 1.0, the rectangle's *left* edge lines up with pos.x. When "centering.y" == -1.0, pos.y == top_edge. When "centering.y" == 1.0, pos.y == bottom. {0.0, 0.0} means centered.
    double rotation = 0.0; //IMPORTANT: When a rectangle's uni_rotation is not a multiple of 90, overlap functions and collision functions are much more computationally expensive. Also, rotation is measured in degrees, but methods like GetRadians() or SetRadians() allow conversion to radians.

    Relativity relativity; // Contains a bunch of pointers to references that define this rectangle's universal proporties. These pointers are used whenever a "uni" method is called.






    // -----------------   SETTING RELATIVITY   -----------------

    void SetReferenceRectangle(RectangleTwo* const reference_rectangle);
    void SetReferencePoint(const Point2D reference_point);
    void SetReferenceScale(const Size2D reference_scale);
    void SetReferenceRotation(const double reference_rotation);






    // -----------------   GET UNI FUNCTIONS   -----------------

    Point2D GetUniPos() const;
    double GetUniX() const;
    double GetUniY() const;

    Point2D GetUniUnscaledOffset() const;
    double GetUniUnscaledOffsetX() const;
    double GetUniUnscaledOffsetY() const;

    Point2D GetUniScaledOffset() const;
    double GetUniScaledOffsetX() const;
    double GetUniScaledOffsetY() const;

    Size2D GetUniUnscaledSize() const;
    double GetUniUnscaledWidth() const;
    double GetUniUnscaledHeight() const;

    Size2D GetUniScaledSize() const;
    double GetUniScaledWidth() const;
    double GetUniScaledHeight() const;

    double GetUniRotation() const;






    // -----------------   SET UNI FUNCTIONS   -----------------

    //Changes pos
    void SetPosWithUniPos(Point2D param_uni_pos);
    //Changes pos.x
    void SetXWithUniX(double param_uni_x);
    //Changes pos.y
    void SetYWithUniY(double param_uni_y);

    //Changes size
    void SetSizeWithUniSize(Size2D param_uni_size);
    //Changes size.width
    void SetWidthWithUniWidth(double param_uni_width);
    //Changes size.height
    void SetHeightWithUniHeight(double param_uni_height);

    //Changes base_size
    void SetBaseSizeWithUniBaseSize(Size2D param_uni_base_size);
    //Changes base_size.width
    void SetBaseWidthWithUniBaseWidth(double param_uni_base_width);
    //Changes base_size.height
    void SetBaseHeightWithUniBaseHeight(double param_uni_base_height);

    //Changes offset
    void SetOffsetWithUniOffset(Point2D param_uni_offset);
    //Changes offset.x
    void SetXOffsetWithUniXOffset(Point2D param_uni_offset);
    //Changes offset.y
    void SetYOffsetWithUniYOffset(Point2D param_uni_offset);

    //Changes offset
    void SetOffsetWithUniScaledOffset(Point2D param_uni_offset);
    //Changes offset.x
    void SetXOffsetWithUniScaledXOffset(Point2D param_uni_offset);
    //Changes offset.y
    void SetYOffsetWithUniScaledYOffset(Point2D param_uni_offset);

    //Changes rotation
    void SetRotationWithUniRotation(double param_uni_rotation);






    // -----------------   OFFSET FUNCTIONS   -----------------

    Point2D GetScaledOffset() const;
    double GetScaledXOffset() const;
    double GetScaledYOffset() const;

    //Changes offset
    void SetOffsetWithScaledOffset(Point2D param_scaled_offset);
    //Changes offset.x
    void SetXOffsetWithScaledXOffset(double param_scaled_x_offset);
    //Changes offset.y
    void SetYOffsetWithScaledYOffset(double param_scaled_y_offset);


    Size2D GetCentering();
    double GetWidthCentering();
    double GetHeightCentering();

    //Changes offset
    void SetOffsetWithCentering(Size2D param_centering, bool adjust_pos_to_remain_stationary);
    //Changes offset.x
    void SetXOffsetWithWidthCentering(double param_width_centering, bool adjust_pos_to_remain_stationary);
    //Changes offset.y
    void SetYOffsetWithHeightCentering(double param_height_centering, bool adjust_pos_to_remain_stationary);






    // -----------------   EDGE FUNCTIONS   -----------------

    double GetScaledEdge(const Direction direction) const;
    //Changes offset
    void SetOffsetWithScaledEdge(double x_or_y_coordinate, Direction direction);

    double GetUnscaledEdge(Direction direction);
    //Changes offset
    void SetOffsetWithUnscaledEdge(double x_or_y_coordinate, Direction direction);

    double GetUniEdge(const Direction direction) const;
    //Changes pos
    void SetPosWithUniEdge(double x_or_y_coordinate, Direction direction);






    // -----------------   LOW-LEVEL FUNCTIONS   -----------------

    Size2D GetSizeScale() const;
    double GetWidthScale() const;
    double GetHeightScale() const;

    //Changes size
    void SetSizeWithSizeScale(Size2D param_size_scale);
    //Changes size.width
    void SetWidthWithWidthScale(double param_width_scale);
    //Changes size.height
    void SetHeightWithHeightScale(double param_height_scale);

    //Changes base_size
    void SetBaseSizeWithSizeScale(Size2D param_size_scale);
    //Changes base_size.width
    void SetBaseWidthWithWidthScale(double param_width_scale);
    //Changes base_size.height
    void SetBaseHeightWithHeightScale(double param_height_scale);


    Size2D GetUniSizeScale() const;
    double GetUniWidthScale() const;
    double GetUniHeightScale() const;

    //Changes size
    void SetSizeWithUniSizeScale(Size2D param_uni_size_scale);
    //Changes size.width
    void SetWidthWithUniWidthScale(double param_uni_width_scale);
    //Changes size.height
    void SetHeightWithUniHeightScale(double param_uni_height_scale);

    //Changes base_size
    void SetBaseSizeWithUniSizeScale(Size2D param_uni_size_scale);
    //Changes base_size.width
    void SetBaseWidthWithUniWidthScale(double param_uni_width_scale);
    //Changes base_size.height
    void SetBaseHeightWithUniHeightScale(double param_uni_height_scale);



    //Changes pos
    void SetScaledPointWithUniPoint(Point2D param_scaled_point, Point2D param_uni_point);
    //Changes pos.x
    void SetScaledXWithUniX(double param_scaled_x, double param_uni_x);
    //Changes pos.y
    void SetScaledYWithUniY(double param_scaled_y, double param_uni_y);


    //Changes pos
    void SetUnscaledPointWithUniPoint(Point2D param_unscaled_point, Point2D param_uni_point);
    //Changes pos.x
    void SetUnscaledXWithUniX(double param_unscaled_x, double param_uni_x);
    //Changes pos.y
    void SetUnscaledYWithUniY(double param_unscaled_y, double param_uni_y);



    Point2D GetScaledPointFromUniPoint(Point2D param_uni_point);
    double GetScaledXFromUniX(double param_uni_x);
    double GetScaledYFromUniY(double param_uni_y);

    Point2D GetUnscaledPointFromUniPoint(Point2D param_uni_point);
    double GetUnscaledXFromUniX(double param_uni_x);
    double GetUnscaledYFromUniY(double param_uni_y);


    Point2D GetUniPointFromScaledPoint(const Point2D param_scaled_point) const;
    double GetUniXFromScaledX(const double param_scaled_x) const;
    double GetUniYFromScaledY(const double param_scaled_y) const;

    Point2D GetUniPointFromUnscaledPoint(Point2D param_unscaled_point);
    double GetUniXFromUnscaledX(double param_unscaled_x);
    double GetUniYFromUnscaledY(double param_unscaled_y);


    Point2D GetScaledPointFromUnscaledPoint(Point2D param_unscaled_point);
    double GetScaledXFromUnscaledX(double param_unscaled_x);
    double GetScaledYFromUnscaledY(double param_unscaled_y);

    Point2D GetUnscaledPointFromScaledPoint(Point2D param_scaled_point);
    double GetUnscaledXFromScaledX(double param_scaled_x);
    double GetUnscaledYFromScaledY(double param_scaled_y);






    // -----------------   EXTRA FUNCTIONS   -----------------
};

*/






// -----------------   STUFF IM NOT USING   -----------------

struct Offset2DNew //Like Centering2DNew but does not scale with "size" or "scale"
{
    double x_offset = 0.0;
    double y_offset = 0.0;

    Offset2DNew();
    Offset2DNew(const double i_x_offset, const double i_y_offset);
};
struct Line2D
{
    Point2DNew v_1 = { 0.0, 0.0 };
    Point2DNew v_2 = { 100.0, 100.0 };

    Line2D();
    Line2D(const Point2DNew i_v_1, const Point2DNew i_v_2);
    Line2D(const double i_x_1, const double i_y_1, const double i_x_2, const double i_y_2);
};
struct DirectionOffset2DNew
{
    double x_axis = 0.0;
    double y_axis = 0.0;

    DirectionOffset2DNew();
    DirectionOffset2DNew(const double i_x_axis, const double i_y_axis);
};
struct SDL_RectWithRotation
{
    SDL_Rect rect;
    SDL_Point center;
    double radians = 0.0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    double GetDegrees() const;
    void SetWithDegrees(const double degrees);
};

















// ------------------------   LIST PROPERTIES FUNCTIONS   ------------------------

void Indent(const unsigned int indent_count);

void LongNotationStart(const unsigned int indentation);
void LongNotationEnd(const unsigned int indentation, const bool end_on_new_line);

void ListProperties(const CornerEnum& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const DirectionEnum& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const RotationEnum& obj, const bool in_degrees = false, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const Flip90& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const Scale90& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const Transformations90& obj, const bool rotations_in_degrees = false, const bool end_on_new_line = true, const bool long_notation = true, const unsigned int indentation = 1);
void ListProperties(const TotalFlip& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const Point2DNew& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
//IMPORTANT: If [direction_offsets_in_degrees] is passed as true, this function prints both [width_radians_offset] and [height_radians_offset] snapped to their nearest whole number degrees if they are within 1000 epsilon from it.
void ListProperties(const Scale2DNew& obj, const bool direction_offsets_in_degrees = false, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const Size2DNew& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const Centering2DNew& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
void ListProperties(const Offset2DNew& obj, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
//IMPORTANT: If [in_degrees] is passed as true, this function prints [radians] snapped to the nearest whole number degree if it is within 1000 epsilon from it.
void ListProperties(const Rotation2DNew& obj, const bool in_degrees = false, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);
//IMPORTANT: If [rotations_in_degrees] is passed as true, this function prints [rotation.radians], [scale.width_radian_offset] and [scale.height_radian_offset] snapped to their nearest whole number degrees if they are within 1000 epsilon from it.
void ListProperties(const Transformations& obj, const bool rotations_in_degrees = false, const bool end_on_new_line = true, const bool long_notation = true, const unsigned int indentation = 1);
void ListProperties(const Quad& obj, const bool end_on_new_line = true, const bool long_notation = true, const unsigned int indentation = 1);
void ListProperties(const RectangleNewest& obj, const bool rotations_in_degrees = false, const bool end_on_new_line = true, const bool long_notation = true, const unsigned int indentation = 1);
//void ListProperties(const CornerEnum& obj, const bool, const bool end_on_new_line = true, const bool long_notation = false, const unsigned int indentation = 1);