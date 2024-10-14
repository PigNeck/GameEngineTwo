#pragma once
#include <iostream>

using namespace std;


// -----------------   LITTLE GOOFY DATA CHUNKS   -----------------

struct Point2D
{
    double x = 0.0;
    double y = 0.0;

    Point2D();
    Point2D(double param_x, double param_y);

    void PrintProperties();
};

struct Size2D
{
    double width = 1.0;
    double height = 1.0;

    Size2D();
    Size2D(double param_width, double param_height);

    void PrintProperties();
};

struct Flip
{
    //0: no flip -- 1: horizontal flip -- 2: vertical flip -- 3: both flip
    unsigned int value : 2;

    Flip();
    Flip(unsigned int param_value);

    void PrintProperties(const bool display_as_int);
};

struct RigidCentering
{
    //0: left/down -- 1: middle -- 2: right/up -- 3: UNDEFINED
    unsigned int value : 2;

    RigidCentering();
    RigidCentering(unsigned int param_value);

    void PrintProperties(const bool display_as_int);
};
struct Direction
{
    //0: right -- 1: down -- 2: left -- 3: up
    unsigned int value : 2;

    Direction();
    Direction(unsigned int param_value);

    void PrintProperties(const bool display_as_int);
};

struct RelativityRules
{
    bool relative_x = 1;
    bool relative_y = 1;

    bool scale_x = 1;
    bool scale_y = 1;

    bool relative_width = 1;
    bool relative_height = 1;

    bool origin_at_ref_rect_center_x = 1;
    bool origin_at_ref_rect_center_y = 1;

    void PrintProperties();
};

struct RectStructOne
{
    double uni_left_edge = 0.0;
    double uni_right_edge = 0.0;
    double uni_bottom_edge = 0.0;
    double uni_top_edge = 0.0;

    RectStructOne();
    RectStructOne(const double param_uni_left_edge, const double param_uni_right_edge, const double param_uni_bottom_edge, const double param_uni_top_edge);

    void PrintProperties();
};

//The origin of RectStructTwos is assumed to at the top left
struct RectStructTwo
{
    Point2D pos;
    Size2D size;
};

/*
ostream& operator<<(ostream& os, const RectStructOne& obj)
{
    os << "uni_left_edge: " << obj.uni_left_edge << "   uni_right_edge: " << obj.uni_right_edge << "   uni_bottom_edge: " << obj.uni_bottom_edge << "   uni_top_edge: " << obj.uni_top_edge;
    return os;
}
*/






// -----------------   RECTANGLE   -----------------

struct Rectangle
{
    Point2D pos;
    Size2D base_size;
    Size2D size;
    Point2D offset;
    Flip flip;
    double rotation = 0.0;

    RelativityRules relativity_rules;
    Rectangle* reference_rectangle_data = nullptr;






    // -----------------   CONSTRUCTORS   -----------------

    Rectangle();
    Rectangle(Rectangle* param_reference_rectangle_data);






    // -----------------   BASIC UNI-FUNCTIONS   -----------------

    Point2D GetUniPos() const;
    double GetUniX() const;
    double GetUniY() const;

    //Changes pos
    void SetPosWithUniPos(Point2D param_uni_pos);
    //Changes pos.x
    void SetXWithUniX(double param_uni_x);
    //Changes pos.y
    void SetYWithUniY(double param_uni_y);

    Point2D GetUniCenter();
    double GetUniCenterX();
    double GetUniCenterY();


    Size2D GetUniSize() const;
    double GetUniWidth() const;
    double GetUniHeight() const;

    //Changes size
    void SetSizeWithUniSize(Size2D param_uni_size);
    //Changes size.width
    void SetWidthWithUniWidth(double param_uni_width);
    //Changes size.height
    void SetHeightWithUniHeight(double param_uni_height);


    Size2D GetUniBaseSize();
    double GetUniBaseWidth();
    double GetUniBaseHeight();

    //Changes base_size
    void SetBaseSizeWithUniBaseSize(Size2D param_uni_base_size);
    //Changes base_size.width
    void SetBaseWidthWithUniBaseWidth(double param_uni_base_width);
    //Changes base_size.height
    void SetBaseHeightWithUniBaseHeight(double param_uni_base_height);


    Point2D GetUniOffset();
    double GetUniXOffset();
    double GetUniYOffset();

    //Changes offset
    void SetOffsetWithUniOffset(Point2D param_uni_offset);
    //Changes offset.x
    void SetXOffsetWithUniXOffset(Point2D param_uni_offset);
    //Changes offset.y
    void SetYOffsetWithUniYOffset(Point2D param_uni_offset);


    Point2D GetUniScaledOffset() const;
    double GetUniScaledXOffset() const;
    double GetUniScaledYOffset() const;

    //Changes offset
    void SetOffsetWithUniScaledOffset(Point2D param_uni_offset);
    //Changes offset.x
    void SetXOffsetWithUniScaledXOffset(Point2D param_uni_offset);
    //Changes offset.y
    void SetYOffsetWithUniScaledYOffset(Point2D param_uni_offset);


    double GetUniRotation() const;

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
