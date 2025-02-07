#include "Rectangle.h"
#include <cstddef>

#define RECT_RIGHT Direction(0)
#define RECT_BOTTOM Direction(1)
#define RECT_LEFT Direction(2)
#define RECT_TOP Direction(3)






// -----------------   DATA CHUNCK CONSTRUCTORS   -----------------

Point2D::Point2D() {}
Point2D::Point2D(double param_x, double param_y) : x(param_x), y(param_y) {}
void Point2D::PrintProperties()
{
    cout << "x: " << x << "   y: " << y;
}

Size2D::Size2D() {}
Size2D::Size2D(double param_width, double param_height) : width(param_width), height(param_height) {}
void Size2D::PrintProperties()
{
    cout << "width: " << width << "   height: " << height;
}

Flip::Flip() : value(0) {}
Flip::Flip(unsigned int param_value) : value(param_value) {}
void Flip::PrintProperties(const bool display_as_int)
{
    if (display_as_int)
    {
        cout << "value: " << value;
    }
    else
    {
        switch (value)
        {
        case 0:
            cout << "value: NO_FLIP";
            break;
        case 1:
            cout << "value: HORIZONTAL_FLIP";
            break;
        case 2:
            cout << "value: VERTICAL_FLIP";
            break;
        case 3:
            cout << "value: BOTH_FLIP";
            break;
        }
    }
}
RigidCentering::RigidCentering() : value(0) {}
RigidCentering::RigidCentering(unsigned int param_value) : value(param_value) {}
void RigidCentering::PrintProperties(const bool display_as_int)
{
    if (display_as_int)
    {
        cout << "value: " << value;
    }
    else
    {
        switch (value)
        {
        case 0:
            cout << "value: LEFT_OR_DOWN";
            break;
        case 1:
            cout << "value: MIDDLE";
            break;
        case 2:
            cout << "value: RIGHT_OR_UP";
            break;
        case 3:
            cout << "value: UNDEFINED (you should probably go and fix this)";
            break;
        }
    }
}
Direction::Direction() : value(0) {}
Direction::Direction(unsigned int param_value) : value(param_value) {}
void Direction::PrintProperties(const bool display_as_int)
{
    if (display_as_int)
    {
        cout << "value: " << value;
    }
    else
    {
        switch (value)
        {
        case 0:
            cout << "value: RIGHT";
            break;
        case 1:
            cout << "value: DOWN";
            break;
        case 2:
            cout << "value: LEFT";
            break;
        case 3:
            cout << "value: UP";
            break;
        }
    }
}
Corner::Corner() : value(0) {}
Corner::Corner(unsigned int param_value) : value(param_value) {};
void Corner::PrintProperties(const bool display_as_int)
{
    if (display_as_int)
    {
        cout << "value: " << value;
    }
    else
    {
        switch (value)
        {
        case 0:
            cout << "value: TOP-RIGHT";
            break;
        case 1:
            cout << "value: BOTTOM-RIGHT";
            break;
        case 2:
            cout << "value: BOTTOM-LEFT";
            break;
        case 3:
            cout << "value: TOP-LEFT";
            break;
        }
    }
}

RectStructOne::RectStructOne() {}
RectStructOne::RectStructOne(const double param_uni_left_edge, const double param_uni_right_edge, const double param_uni_bottom_edge, const double param_uni_top_edge) : uni_left_edge(param_uni_left_edge), uni_right_edge(param_uni_right_edge), uni_bottom_edge(param_uni_bottom_edge), uni_top_edge(param_uni_top_edge) {}
void RectStructOne::PrintProperties()
{
    cout << "uni_left_edge: " << uni_left_edge << "   uni_right_edge: " << uni_right_edge << "   uni_bottom_edge: " << uni_bottom_edge << "   uni_top_edge: " << uni_top_edge;
}





// -----------------   CONSTRUCTORS   -----------------

RectangleOld::RectangleOld() {}

RectangleOld::RectangleOld(RectangleOld* param_reference_rectangle_data) : reference_rectangle(param_reference_rectangle_data) {}






// -----------------   BASIC UNI-FUNCTIONS   -----------------

Point2D RectangleOld::GetUniPos() const
{
    return { GetUniX(), GetUniY() };
}
double RectangleOld::GetUniX() const
{
    double ref_uni_x;
    if (reference_rectangle && relativity_rules.relative_x)
    {
        ref_uni_x = reference_rectangle->GetUniX();
    }
    else
    {
        ref_uni_x = 0.0;
    }

    double ref_center_offset_x;
    if (reference_rectangle && relativity_rules.origin_at_ref_rect_center_x)
    {
        ref_center_offset_x = reference_rectangle->offset.x;
    }
    else
    {
        ref_center_offset_x = 0.0;
    }

    double ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_x && relativity_rules.scale_x)
    {
        ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        ref_uni_width_scale = 1.0;
    }

    return (ref_uni_x + ((pos.x + ref_center_offset_x) * ref_uni_width_scale));
}
double RectangleOld::GetUniY() const
{
    double ref_uni_y;
    if (reference_rectangle && relativity_rules.relative_y)
    {
        ref_uni_y = reference_rectangle->GetUniY();
    }
    else
    {
        ref_uni_y = 0.0;
    }

    double ref_center_offset_y;
    if (reference_rectangle && relativity_rules.origin_at_ref_rect_center_y)
    {
        ref_center_offset_y = reference_rectangle->offset.y;
    }
    else
    {
        ref_center_offset_y = 0.0;
    }

    double ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_y && relativity_rules.scale_y)
    {
        ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        ref_uni_height_scale = 1.0;
    }

    return (ref_uni_y + ((pos.y + ref_center_offset_y) * ref_uni_height_scale));
}

//Changes pos
void RectangleOld::SetPosWithUniPos(Point2D param_uni_pos)
{
    SetXWithUniX(param_uni_pos.x);
    SetYWithUniY(param_uni_pos.y);
}
//Changes pos.x
void RectangleOld::SetXWithUniX(double param_uni_x)
{
    double ref_uni_x;
    if (reference_rectangle && relativity_rules.relative_x)
    {
        ref_uni_x = reference_rectangle->GetUniX();
    }
    else
    {
        ref_uni_x = 0.0;
    }

    double ref_center_offset_x;
    if (reference_rectangle && relativity_rules.origin_at_ref_rect_center_x)
    {
        ref_center_offset_x = reference_rectangle->offset.x;
    }
    else
    {
        ref_center_offset_x = 0.0;
    }

    double ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_x && relativity_rules.scale_x)
    {
        ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        ref_uni_width_scale = 1.0;
    }

    pos.x = ((param_uni_x - ref_uni_x) / ref_uni_width_scale) - ref_center_offset_x;
}
//Changes pos.y
void RectangleOld::SetYWithUniY(double param_uni_y)
{
    double temp_ref_y;
    if (reference_rectangle && relativity_rules.relative_y)
    {
        temp_ref_y = reference_rectangle->GetUniY();
    }
    else
    {
        temp_ref_y = 0.0;
    }

    double ref_center_offset_y;
    if (reference_rectangle && relativity_rules.origin_at_ref_rect_center_y)
    {
        ref_center_offset_y = reference_rectangle->offset.y;
    }
    else
    {
        ref_center_offset_y = 0.0;
    }

    double temp_ref_height_scale;
    if (reference_rectangle && relativity_rules.relative_y && relativity_rules.scale_y)
    {
        temp_ref_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_height_scale = 1.0;
    }

    pos.y = ((param_uni_y - temp_ref_y) / temp_ref_height_scale) - ref_center_offset_y;
}

Point2D RectangleOld::GetUniCenter()
{
    return { GetUniCenterX(), GetUniCenterY() };
}
double RectangleOld::GetUniCenterX()
{
    return GetUniXFromUnscaledX(offset.x);
}
double RectangleOld::GetUniCenterY()
{
    return GetUniYFromUnscaledY(offset.y);
}

Size2D RectangleOld::GetUniSize() const
{
    return { GetUniWidth(), GetUniHeight() };
}
double RectangleOld::GetUniWidth() const
{
    double temp_ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
    }

    return (size.width * temp_ref_uni_width_scale);
}
double RectangleOld::GetUniHeight() const
{
    double temp_ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_height_scale = 1.0;
    }

    return (size.height * temp_ref_uni_height_scale);
}

//Changes size
void RectangleOld::SetSizeWithUniSize(Size2D param_uni_size)
{
    SetWidthWithUniWidth(param_uni_size.width);
    SetHeightWithUniHeight(param_uni_size.height);
}
//Changes size.width
void RectangleOld::SetWidthWithUniWidth(double param_uni_width)
{
    double temp_ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
    }

    size.width = param_uni_width / temp_ref_uni_width_scale;
}
//Changes size.height
void RectangleOld::SetHeightWithUniHeight(double param_uni_height)
{
    double temp_ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_height_scale = 1.0;
    }

    size.height = param_uni_height / temp_ref_uni_height_scale;
}


Size2D RectangleOld::GetUniBaseSize()
{
    return { GetUniBaseWidth(), GetUniBaseHeight() };
}
double RectangleOld::GetUniBaseWidth()
{
    double temp_ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
    }

    return (base_size.width * temp_ref_uni_width_scale);
}
double RectangleOld::GetUniBaseHeight()
{
    double temp_ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_height_scale = 1.0;
    }

    return (base_size.height * temp_ref_uni_height_scale);
}

//Changes base_size
void RectangleOld::SetBaseSizeWithUniBaseSize(Size2D param_uni_base_size)
{
    SetBaseWidthWithUniBaseWidth(param_uni_base_size.width);
    SetBaseHeightWithUniBaseHeight(param_uni_base_size.height);
}
//Changes base_size.width
void RectangleOld::SetBaseWidthWithUniBaseWidth(double param_uni_base_width)
{
    double temp_ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
    }

    base_size.width = param_uni_base_width / temp_ref_uni_width_scale;
}
//Changes base_size.height
void RectangleOld::SetBaseHeightWithUniBaseHeight(double param_uni_base_height)
{
    double temp_ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_height_scale = 1.0;
    }

    base_size.height = param_uni_base_height / temp_ref_uni_height_scale;
}


Point2D RectangleOld::GetUniOffset()
{
    return { GetUniXOffset(), GetUniYOffset() };
}
double RectangleOld::GetUniXOffset()
{
    double temp_reference_uni_width_scale;

    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_reference_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_reference_uni_width_scale = 1.0;
    }

    return offset.x * temp_reference_uni_width_scale;
}
double RectangleOld::GetUniYOffset()
{
    double temp_reference_uni_height_scale;

    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_reference_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_reference_uni_height_scale = 1.0;
    }

    return offset.y * temp_reference_uni_height_scale;
}

//Changes offset
void RectangleOld::SetOffsetWithUniOffset(Point2D param_uni_offset)
{
    //I dunno
}
//Changes offset.x
void RectangleOld::SetXOffsetWithUniXOffset(Point2D param_uni_offset)
{
    //I dunno
}
//Changes offset.y
void RectangleOld::SetYOffsetWithUniYOffset(Point2D param_uni_offset)
{
    //I dunno
}


Point2D RectangleOld::GetUniScaledOffset() const
{
    return { GetUniScaledXOffset(), GetUniScaledYOffset() };
}
double RectangleOld::GetUniScaledXOffset() const
{
    return offset.x * GetUniWidthScale();
}
double RectangleOld::GetUniScaledYOffset() const
{
    return offset.y * GetUniHeightScale();
}

//Changes offset
void RectangleOld::SetOffsetWithUniScaledOffset(Point2D param_uni_offset)
{
    //I dunno
}
//Changes offset.x
void RectangleOld::SetXOffsetWithUniScaledXOffset(Point2D param_uni_offset)
{
    //I dunno
}
//Changes offset.y
void RectangleOld::SetYOffsetWithUniScaledYOffset(Point2D param_uni_offset)
{
    //I dunno
}


double RectangleOld::GetUniRotation() const
{
    return rotation;
}

//Changes rotation
void RectangleOld::SetRotationWithUniRotation(double param_uni_rotation)
{
    //I dunno
}






// -----------------   OFFSET FUNCTIONS   -----------------

Point2D RectangleOld::GetScaledOffset() const
{
    return { GetScaledXOffset(), GetScaledYOffset() };
}
double RectangleOld::GetScaledXOffset() const
{
    return (offset.x * GetWidthScale());
}
double RectangleOld::GetScaledYOffset() const
{
    return (offset.y * GetHeightScale());
}

//Changes offset
void RectangleOld::SetOffsetWithScaledOffset(Point2D param_scaled_offset)
{
    SetXOffsetWithScaledXOffset(param_scaled_offset.x);
    SetYOffsetWithScaledYOffset(param_scaled_offset.y);
}
//Changes offset.x
void RectangleOld::SetXOffsetWithScaledXOffset(double param_scaled_x_offset)
{
    offset.x = param_scaled_x_offset / GetWidthScale();
}
//Changes offset.y
void RectangleOld::SetYOffsetWithScaledYOffset(double param_scaled_y_offset)
{
    offset.y = param_scaled_y_offset / GetHeightScale();
}


Size2D RectangleOld::GetCentering()
{
    return { GetWidthCentering(), GetHeightCentering() };
}
double RectangleOld::GetWidthCentering()
{
    return ((offset.x / base_size.width) * 2.0);
}
double RectangleOld::GetHeightCentering()
{
    return ((offset.y / base_size.height) * 2.0);
}

//Changes offset
void RectangleOld::SetOffsetWithCentering(Size2D param_centering, bool adjust_pos_to_remain_stationary)
{
    SetXOffsetWithWidthCentering(param_centering.width, adjust_pos_to_remain_stationary);
    SetYOffsetWithHeightCentering(param_centering.height, adjust_pos_to_remain_stationary);
}
//Changes offset.x
void RectangleOld::SetXOffsetWithWidthCentering(double param_width_centering, bool adjust_pos_to_remain_stationary)
{
    if (adjust_pos_to_remain_stationary)
    {
        double delta_x_offset = -offset.x;
        offset.x = (param_width_centering / 2.0) * base_size.width;
        delta_x_offset += offset.x;

        pos.x -= delta_x_offset * GetWidthScale();
    }
    else
    {
        offset.x = (param_width_centering / 2.0) * base_size.width;
    }
}
//Changes offset.y
void RectangleOld::SetYOffsetWithHeightCentering(double param_height_centering, bool adjust_pos_to_remain_stationary)
{
    if (adjust_pos_to_remain_stationary)
    {
        double delta_y_offset = -offset.y;
        offset.y = (param_height_centering / 2.0) * base_size.height;
        delta_y_offset += offset.y;

        pos.y -= delta_y_offset * GetHeightScale();
    }
    else
    {
        offset.y = (param_height_centering / 2.0) * base_size.height;
    }
}






// -----------------   EDGE FUNCTIONS   -----------------

double RectangleOld::GetScaledEdge(const Direction direction) const
{
    switch (direction.value)
    {
    case 0:
        return (GetScaledXOffset() + (size.width / 2.0));
        break;
    case 1:
        return (GetScaledYOffset() - (size.height / 2.0));
        break;
    case 2:
        return (GetScaledXOffset() - (size.width / 2.0));
        break;
    case 3:
        return (GetScaledYOffset() + (size.height / 2.0));
        break;
    }

    return NULL;
}
//Changes offset
void RectangleOld::SetOffsetWithScaledEdge(double x_or_y_coordinate, Direction direction)
{
    switch (direction.value)
    {
    case 0:
        SetXOffsetWithScaledXOffset(x_or_y_coordinate - (size.width / 2.0));
        break;
    case 1:
        SetYOffsetWithScaledYOffset(x_or_y_coordinate + (size.height / 2.0));
        break;
    case 2:
        SetXOffsetWithScaledXOffset(x_or_y_coordinate + (size.width / 2.0));
        break;
    case 3:
        SetYOffsetWithScaledYOffset(x_or_y_coordinate - (size.height / 2.0));
        break;
    }
}

double RectangleOld::GetUnscaledEdge(Direction direction)
{
    switch (direction.value)
    {
    case 0:
        return (offset.x + (base_size.width / 2.0));
        break;
    case 1:
        return (offset.y - (base_size.height / 2.0));
        break;
    case 2:
        return (offset.x - (base_size.width / 2.0));
        break;
    case 3:
        return (offset.y + (base_size.height / 2.0));
        break;
    }

    return NULL;
}
//Changes offset
void RectangleOld::SetOffsetWithUnscaledEdge(double x_or_y_coordinate, Direction direction)
{
    switch (direction.value)
    {
    case 0:
        offset.x = x_or_y_coordinate - (base_size.width / 2.0);
        break;
    case 1:
        offset.y = x_or_y_coordinate + (base_size.height / 2.0);
        break;
    case 2:
        offset.x = x_or_y_coordinate + (base_size.width / 2.0);
        break;
    case 3:
        offset.y = x_or_y_coordinate - (base_size.height / 2.0);
        break;
    }
}

double RectangleOld::GetUniEdge(const Direction direction) const
{
    switch (direction.value)
    {
    case 0:
        return GetUniXFromScaledX(GetScaledEdge(direction));
        break;
    case 1:
        return GetUniYFromScaledY(GetScaledEdge(direction));
        break;
    case 2:
        return GetUniXFromScaledX(GetScaledEdge(direction));
        break;
    case 3:
        return GetUniYFromScaledY(GetScaledEdge(direction));
        break;
    }

    return NULL;
}
//Changes pos
void RectangleOld::SetPosWithUniEdge(double x_or_y_coordinate, Direction direction)
{
    double temp_uni_x_or_y_diff = x_or_y_coordinate - GetUniEdge(direction);

    switch (direction.value)
    {
    case 0:
        SetXWithUniX(GetUniX() + temp_uni_x_or_y_diff);
        break;
    case 1:
        SetYWithUniY(GetUniY() + temp_uni_x_or_y_diff);
        break;
    case 2:
        SetXWithUniX(GetUniX() + temp_uni_x_or_y_diff);
        break;
    case 3:
        SetYWithUniY(GetUniY() + temp_uni_x_or_y_diff);
        break;
    }
}






// -----------------   LOW-LEVEL FUNCTIONS   -----------------

Size2D RectangleOld::GetSizeScale() const
{
    return { GetWidthScale(), GetHeightScale() };
}
double RectangleOld::GetWidthScale() const
{
    return (size.width / base_size.width);
}
double RectangleOld::GetHeightScale() const
{
    return (size.height / base_size.height);
}

//Changes size
void RectangleOld::SetSizeWithSizeScale(Size2D param_size_scale)
{
    SetWidthWithWidthScale(param_size_scale.width);
    SetHeightWithHeightScale(param_size_scale.height);
}
//Changes size.width
void RectangleOld::SetWidthWithWidthScale(double param_width_scale)
{
    size.width = base_size.width * param_width_scale;
}
//Changes size.height
void RectangleOld::SetHeightWithHeightScale(double param_height_scale)
{
    size.height = base_size.height * param_height_scale;
}

//Changes base_size
void RectangleOld::SetBaseSizeWithSizeScale(Size2D param_size_scale)
{
    SetBaseWidthWithWidthScale(param_size_scale.width);
    SetBaseHeightWithHeightScale(param_size_scale.height);
}
//Changes base_size.width
void RectangleOld::SetBaseWidthWithWidthScale(double param_width_scale)
{
    base_size.width = size.width / param_width_scale;
}
//Changes base_size.height
void RectangleOld::SetBaseHeightWithHeightScale(double param_height_scale)
{
    base_size.height = size.height / param_height_scale;
}


Size2D RectangleOld::GetUniSizeScale() const
{
    return { GetUniWidthScale(), GetUniHeightScale() };
}
double RectangleOld::GetUniWidthScale() const
{
    double temp_ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
    }

    return (GetWidthScale() * temp_ref_uni_width_scale);
}
double RectangleOld::GetUniHeightScale() const
{
    double temp_ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_height_scale = 1.0;
    }

    return (GetHeightScale() * temp_ref_uni_height_scale);
}

//Changes size
void RectangleOld::SetSizeWithUniSizeScale(Size2D param_uni_size_scale)
{
    SetWidthWithUniWidthScale(param_uni_size_scale.width);
    SetHeightWithUniHeightScale(param_uni_size_scale.height);
}
//Changes size.width
void RectangleOld::SetWidthWithUniWidthScale(double param_uni_width_scale)
{
    double temp_ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
    }

    SetWidthWithWidthScale(param_uni_width_scale / temp_ref_uni_width_scale);
}
//Changes size.height
void RectangleOld::SetHeightWithUniHeightScale(double param_uni_height_scale)
{
    double temp_ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_height_scale = 1.0;
    }

    SetHeightWithHeightScale(param_uni_height_scale / temp_ref_uni_height_scale);
}

//Changes base_size
void RectangleOld::SetBaseSizeWithUniSizeScale(Size2D param_uni_size_scale)
{
    SetBaseWidthWithUniWidthScale(param_uni_size_scale.width);
    SetBaseHeightWithUniHeightScale(param_uni_size_scale.height);
}
//Changes base_size.width
void RectangleOld::SetBaseWidthWithUniWidthScale(double param_uni_width_scale)
{
    double temp_ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        temp_ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
    }

    SetBaseWidthWithWidthScale(param_uni_width_scale / temp_ref_uni_width_scale);
}
//Changes base_size.height
void RectangleOld::SetBaseHeightWithUniHeightScale(double param_uni_height_scale)
{
    double temp_ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        temp_ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_height_scale = 1.0;
    }

    SetBaseHeightWithHeightScale(param_uni_height_scale / temp_ref_uni_height_scale);
}



//Changes pos
void RectangleOld::SetScaledPointWithUniPoint(Point2D param_scaled_point, Point2D param_uni_point)
{
    SetScaledXWithUniX(param_scaled_point.x, param_uni_point.x);
    SetScaledYWithUniY(param_scaled_point.y, param_uni_point.y);
}
//Changes pos.x
void RectangleOld::SetScaledXWithUniX(double param_scaled_x, double param_uni_x)
{
    pos.x += GetScaledXFromUniX(param_uni_x) - param_scaled_x;
}
//Changes pos.y
void RectangleOld::SetScaledYWithUniY(double param_scaled_y, double param_uni_y)
{
    pos.y += GetScaledYFromUniY(param_uni_y) - param_scaled_y;
}


//Changes pos
void RectangleOld::SetUnscaledPointWithUniPoint(Point2D param_unscaled_point, Point2D param_uni_point)
{
    SetUnscaledXWithUniX(param_unscaled_point.x, param_uni_point.x);
    SetUnscaledYWithUniY(param_unscaled_point.y, param_uni_point.y);
}
//Changes pos.x
void RectangleOld::SetUnscaledXWithUniX(double param_unscaled_x, double param_uni_x)
{
    pos.x += GetUnscaledXFromUniX(param_uni_x) - param_unscaled_x;
}
//Changes pos.y
void RectangleOld::SetUnscaledYWithUniY(double param_unscaled_y, double param_uni_y)
{
    pos.y += GetUnscaledYFromUniY(param_uni_y) - param_unscaled_y;
}



Point2D RectangleOld::GetScaledPointFromUniPoint(Point2D param_uni_point)
{
    return { GetScaledXFromUniX(param_uni_point.x), GetScaledYFromUniY(param_uni_point.y) };
}
double RectangleOld::GetScaledXFromUniX(double param_uni_x)
{
    double ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        ref_uni_width_scale = 1.0;
    }

    return ((param_uni_x - GetUniX()) / ref_uni_width_scale);
}
double RectangleOld::GetScaledYFromUniY(double param_uni_y)
{
    double ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        ref_uni_height_scale = 1.0;
    }

    return ((param_uni_y - GetUniY()) / ref_uni_height_scale);
}

Point2D RectangleOld::GetUnscaledPointFromUniPoint(Point2D param_uni_point)
{
    return { GetUnscaledXFromUniX(param_uni_point.x), GetUnscaledYFromUniY(param_uni_point.y) };
}
double RectangleOld::GetUnscaledXFromUniX(double param_uni_x)
{
    return ((param_uni_x - GetUniX()) / GetUniWidthScale());
}
double RectangleOld::GetUnscaledYFromUniY(double param_uni_y)
{
    return ((param_uni_y - GetUniY()) / GetUniHeightScale());
}


Point2D RectangleOld::GetUniPointFromScaledPoint(const Point2D param_scaled_point) const
{
    return { GetUniXFromScaledX(param_scaled_point.x), GetUniYFromScaledY(param_scaled_point.y) };
}
double RectangleOld::GetUniXFromScaledX(const double param_scaled_x) const
{
    double ref_uni_width_scale;
    if (reference_rectangle && relativity_rules.relative_width)
    {
        ref_uni_width_scale = reference_rectangle->GetUniWidthScale();
    }
    else
    {
        ref_uni_width_scale = 1.0;
    }

    return (GetUniX() + (ref_uni_width_scale * param_scaled_x));
}
double RectangleOld::GetUniYFromScaledY(const double param_scaled_y) const
{
    double ref_uni_height_scale;
    if (reference_rectangle && relativity_rules.relative_height)
    {
        ref_uni_height_scale = reference_rectangle->GetUniHeightScale();
    }
    else
    {
        ref_uni_height_scale = 1.0;
    }

    return (GetUniY() + (ref_uni_height_scale * param_scaled_y));
}

Point2D RectangleOld::GetUniPointFromUnscaledPoint(Point2D param_unscaled_point)
{
    return { GetUniXFromUnscaledX(param_unscaled_point.x), GetUniYFromUnscaledY(param_unscaled_point.y) };
}
double RectangleOld::GetUniXFromUnscaledX(double param_unscaled_x)
{
    return (GetUniX() + (GetUniWidthScale() * param_unscaled_x));
}
double RectangleOld::GetUniYFromUnscaledY(double param_unscaled_y)
{
    return (GetUniY() + (GetUniHeightScale() * param_unscaled_y));
}


Point2D RectangleOld::GetScaledPointFromUnscaledPoint(Point2D param_unscaled_point)
{
    //return { GetScaledXFromUnscaledX(param_unscaled_point.x), GetScaledYFromUnscaledY(param_unscaled_point.y) };
    return { NULL, NULL };
}
double RectangleOld::GetScaledXFromUnscaledX(double param_unscaled_x)
{
    return (param_unscaled_x * GetWidthScale());
}
double RectangleOld::GetScaledYFromUnscaledY(double param_unscaled_y)
{
    return (param_unscaled_y * GetHeightScale());
}

Point2D RectangleOld::GetUnscaledPointFromScaledPoint(Point2D param_scaled_point)
{
    //return { GetUnscaledXFromScaledX(param_scaled_point.x), GetUnscaledYFromScaledY(param_scaled_point.y) };
    return { NULL, NULL };
}
double RectangleOld::GetUnscaledXFromScaledX(double param_scaled_x)
{
    return (param_scaled_x / GetWidthScale());
}
double RectangleOld::GetUnscaledYFromScaledY(double param_scaled_y)
{
    return (param_scaled_y / GetHeightScale());
}






// -----------------   EXTRA FUNCTIONS   -----------------

Point2D RectangleOld::GetUniCorner(const Corner param_corner) const
{
    switch (param_corner.value)
    {
    case 0:
        return { GetUniEdge({ 0 }), GetUniEdge({ 3 }) };
        break;
    case 1:
        return { GetUniEdge({ 0 }), GetUniEdge({ 1 }) };
        break;
    case 2:
        return { GetUniEdge({ 2 }), GetUniEdge({ 1 }) };
        break;
    case 3:
        return { GetUniEdge({ 2 }), GetUniEdge({ 3 }) };
        break;
    default:
        cerr << "ILLEGAL CORNER VALUE!!! Sent from Point2D RectangleOld::GetUniCorner(const Corner param_corner) const\n";
        throw;
    }
}