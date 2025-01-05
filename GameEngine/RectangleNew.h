#pragma once

#include "SDL.h"
//#include "SDL_opengl.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include <limits>
#include <vector>
#include "Rectangle.h"


using namespace std;

struct SDL_RectWithRotation
{
    SDL_Rect rect;
    SDL_Point center;
    double radians = 0.0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    double GetDegrees() const;
    void SetWithDegrees(const double degrees);
};



// -----------------   NON-REFERENCE STRUCTS   -----------------

/*
enum class TotalFlip : unsigned char
{
    FLIP_NONE,
    FLIP_HORIZONTAL,
    FLIP_VERTICAL,
    FLIP_BOTH
};
*/

struct TotalFlip
{
    bool flip_horizontally = 0;
    bool flip_vertically = 0;

    TotalFlip();
    TotalFlip(const bool i_flip_horizontally, const bool i_flip_vertically);

    //IMPORTANT!!!: If both flip_horizontally and flip_vertically are true, this function returns SDL_FLIP_NONE (SDL_RendererFlip does not support flipping in both directions). This case should be handled outside the function.
    SDL_RendererFlip GetSDLFlip() const;
};

struct Point2DNew
{
    double x = 0.0;
    double y = 0.0;

    Point2DNew();
    Point2DNew(const double i_x, const double i_y);
};
struct Scale2DNew
{
    double width_scale = 1.0;
    double height_scale = 1.0;

    Scale2DNew();
    Scale2DNew(const double i_width_scale, const double i_height_scale);
};
struct Size2DNew
{
    double width = 100.0;
    double height = 100.0;

    Size2DNew();
    Size2DNew(const double i_width, const double i_height);
};
struct Centering2DNew
{
    double x_centering = 0.0; //-1.0 = right edge of rectangle lines up with x pos; 0.0 = centered on the x axis; 1.0 = left edge of rectangle lines up with x pos
    double y_centering = 0.0; //-1.0 = top edge of rectangle lines up with y pos; 0.0 = centered on the y axis; 1.0 = bottom edge of rectangle lines up with y pos

    Centering2DNew();
    Centering2DNew(const double i_x_centering, const double i_y_centering);
};
struct Offset2DNew //Like Centering2DNew but does not scale with "size" or "scale"
{
    double x_offset = 0.0;
    double y_offset = 0.0;

    Offset2DNew();
    Offset2DNew(const double i_x_offset, const double i_y_offset);
};
struct Rotation2DNew
{
    double radians = 0.0;

    Rotation2DNew();
    Rotation2DNew(const double i_radians);

    double GetDegrees() const;
    void SetWithDegrees(const double degrees);
};
struct RectangleNew
{
    // -------- DATA --------

    Point2DNew pos;
    Size2DNew unscaled_size;
    Scale2DNew scale;
    Centering2DNew centering;
    Rotation2DNew rotation; //In radians
    TotalFlip total_flip;




    // -------- EDGE FUNCTIONS --------

    double GetEdge(const Direction direction) const;
    Point2DNew GetCorner(const Corner corner) const;

    //set edge, set corner, etc.




    // -------- SCALE FUNCTIONS --------

    Size2DNew GetScaledSize() const;
    double GetScaledWidth() const;
    double GetScaledHeight() const;




    // -------- CENTERING/OFFSET FUNCTIONS --------

    Offset2DNew GetUnscaledOffset() const;
    double GetUnscaledOffsetX() const;
    double GetUnscaledOffsetY() const;

    Offset2DNew GetScaledOffset() const;
    double GetScaledOffsetX() const;
    double GetScaledOffsetY() const;
};






// -----------------   REFERENCE STRUCTS   -----------------

struct RefTotalFlip //RefTotalFlip is the referenceable version of TotalFlip, which contains data about horizontal and vertical flips or the lack there of;      Ex: If, say, an instance of RefTotalFlip has a flip value of FLIP_HORIZONTAL, and its reference_total_flip also has a flip value of FLIP_HORIZONTAL (and a reference_total_flip of nullptr), then the uni flip value would be FLIP_NONE (they cancel each other out).
{
    TotalFlip v;
    
    RefTotalFlip* reference_total_flip = nullptr;

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

//WARNING: When RefScale2DNewNew has different width and height scales and there is a rotated rectangle (in a non-cardinal direction) referencing it, the rectangle would become a rhombus which is ILLEGAL (we have rhombuses). Idk how to solve this problem
struct RefScale2DNewNew
{
    double width_scale = 1.0;
    double height_scale = 1.0;

    RefScale2DNewNew* reference_scale = nullptr;



    RefScale2DNewNew();
    RefScale2DNewNew(const double i_width_scale, const double i_height_scale);
    RefScale2DNewNew(const double i_width_scale, const double i_height_scale, RefScale2DNewNew* const i_reference_scale);



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

    RefScale2DNewNew* reference_scale = nullptr;



    RefSize2DNewNew();
    RefSize2DNewNew(const double i_width, const double i_height);
    RefSize2DNewNew(const double i_width, const double i_height, RefScale2DNewNew* const i_reference_scale);



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

    RefRotation2DNewNew* reference_rotation = nullptr;
    RefTotalFlip* reference_total_flip = nullptr;


    RefRotation2DNewNew();
    RefRotation2DNewNew(const double i_radians);
    RefRotation2DNewNew(const double i_radians, RefRotation2DNewNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip);


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

    RefPoint2DNewNew* reference_point = nullptr;
    RefScale2DNewNew* reference_scale = nullptr;
    RefRotation2DNewNew* reference_rotation = nullptr;
    RefTotalFlip* reference_total_flip = nullptr;



    RefPoint2DNewNew();
    RefPoint2DNewNew(const double i_x, const double i_y);
    RefPoint2DNewNew(const double i_x, const double i_y, RefPoint2DNewNew* const i_reference_point, RefScale2DNewNew* const i_reference_scale, RefRotation2DNewNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip);



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

struct RefRectangleNewNew
{
    RefPoint2DNewNew pos;
    RefSize2DNewNew unscaled_size;
    RefScale2DNewNew scale;
    Centering2DNew centering;
    RefRotation2DNewNew rotation; //In radians
    RefTotalFlip total_flip;

    RectangleNew GetRectangleNew() const;

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