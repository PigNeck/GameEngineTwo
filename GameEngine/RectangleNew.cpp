#include "RectangleNew.h"

double EdgeData::GetSubtractOneDouble() const
{
    if (subtract_one)
    {
        return -1.0;
    }
    else
    {
        return 1.0;
    }
}
double EdgeData::GetFlipDouble() const
{
    if (flip)
    {
        return -1.0;
    }
    else
    {
        return 1.0;
    }
}

EdgeData GetEdgeData(const DirectionEnum edge, const RotationEnum this_rotation, const Flip90 this_flip)
{
    bool y_axis;
    bool subtract_one;
    bool flip;

    switch (edge)
    {
    case DirectionEnum::RIGHT:
        subtract_one = 0;
        switch (this_rotation)
        {
        case RotationEnum::DEGREES_0:
            flip = this_flip.flip_horizontally;
            y_axis = 0;
            break;
        case RotationEnum::DEGREES_90:
            flip = this_flip.flip_horizontally;
            y_axis = 1;
            break;
        case RotationEnum::DEGREES_180:
            flip = !this_flip.flip_horizontally;
            y_axis = 0;
            break;
        case RotationEnum::DEGREES_270:
            flip = !this_flip.flip_horizontally;
            y_axis = 1;
            break;
        }
        break;
    case DirectionEnum::BOTTOM:
        subtract_one = 1;
        switch (this_rotation)
        {
        case RotationEnum::DEGREES_0:
            flip = this_flip.flip_vertically;
            y_axis = 1;
            break;
        case RotationEnum::DEGREES_90:
            flip = !this_flip.flip_vertically;
            y_axis = 0;
            break;
        case RotationEnum::DEGREES_180:
            flip = !this_flip.flip_vertically;
            y_axis = 1;
            break;
        case RotationEnum::DEGREES_270:
            flip = this_flip.flip_vertically;
            y_axis = 0;
            break;
        }
        break;
    case DirectionEnum::LEFT:
        subtract_one = 1;
        switch (this_rotation)
        {
        case RotationEnum::DEGREES_0:
            flip = this_flip.flip_horizontally;
            y_axis = 0;
            break;
        case RotationEnum::DEGREES_90:
            flip = this_flip.flip_horizontally;
            y_axis = 1;
            break;
        case RotationEnum::DEGREES_180:
            flip = !this_flip.flip_horizontally;
            y_axis = 0;
            break;
        case RotationEnum::DEGREES_270:
            flip = !this_flip.flip_horizontally;
            y_axis = 1;
            break;
        }
        break;
    case DirectionEnum::TOP:
        subtract_one = 0;
        switch (this_rotation)
        {
        case RotationEnum::DEGREES_0:
            flip = this_flip.flip_vertically;
            y_axis = 1;
            break;
        case RotationEnum::DEGREES_90:
            flip = !this_flip.flip_vertically;
            y_axis = 0;
            break;
        case RotationEnum::DEGREES_180:
            flip = !this_flip.flip_vertically;
            y_axis = 1;
            break;
        case RotationEnum::DEGREES_270:
            flip = this_flip.flip_vertically;
            y_axis = 0;
            break;
        }
        break;
    }

    return {
        y_axis,
        subtract_one,
        flip
    };
}






// -----------------   IDEK WHAT TO CALL THIS. SNAP FUNCTIONS MAYBE?   -----------------

void SnapDouble(double* const double_pointer, double m, const double b, const unsigned int accepted_epsilon_difference)
{
    const double target_val = round(((*double_pointer) - b) / m) + b;
    const double difference = (*double_pointer) - target_val;

    if (abs(difference) <= (numeric_limits<double>::epsilon() * accepted_epsilon_difference))
    {
        *double_pointer = target_val;
    }
}
void SnapAwayDouble(double* const double_pointer, const double m, const double b, const unsigned int accepted_epsilon_difference)
{
    const double target_val = round(((*double_pointer) - b) / m) + b;
    const double difference = (*double_pointer) - target_val;

    const double total_epsilon = numeric_limits<double>::epsilon() * accepted_epsilon_difference;
    if (abs(difference) <= total_epsilon)
    {
        if (difference >= 0.0)
        {
            *double_pointer = target_val + total_epsilon;
        }
        else
        {
            *double_pointer = target_val - total_epsilon;
        }
    }
}

double SnapRadiansToDegrees(const double radians, const unsigned int degree_snap_factor, const unsigned int accepted_epsilon_difference)
{
    constexpr double epsilon = numeric_limits<double>::epsilon();

    double degrees = fmod((radians * (180.0 / M_PI)), 360.0);
    if (degrees < 0.0)
    {
        degrees += 360.0;
    }

    if ((degrees < (epsilon * (double)accepted_epsilon_difference)) || (degrees > (360.0 - (epsilon * (double)accepted_epsilon_difference))))
    {
        return 0.0;
    }

    const unsigned int repeat_count = (360 / degree_snap_factor) - 1;
    for (unsigned int i = 0; i < repeat_count; i++)
    {
        const double current_degree_check = (double)(degree_snap_factor * (i + 1));
        const double current_relative_degrees = degrees - current_degree_check;
        if ((current_relative_degrees > -(epsilon * (double)accepted_epsilon_difference)) && (current_relative_degrees < (epsilon * (double)accepted_epsilon_difference)))
        {
            return current_degree_check;
        }
    }

    return degrees;
}




double SDL_RectWithRotation::GetDegrees() const
{
    return (radians * 180.0 / M_PI);
}
void SDL_RectWithRotation::SetWithDegrees(const double degrees)
{
    radians = degrees * M_PI / 180.0;
}

double Rotation90ToRotation2D(const RotationEnum rotation_90)
{
    return (static_cast<double>(static_cast<unsigned char>(rotation_90)) * M_PI);
}





// ----------------------------------   9 0 - S T R U C T S   ----------------------------------

// -----------------   ROTATION90   -----------------
Rotation90::Rotation90() {}
Rotation90::Rotation90(const RotationEnum i_val) : val(i_val) {}
Rotation90::Rotation90(const Rotation2DNew& rotation_2d_new)
    : val(static_cast<RotationEnum>(static_cast<unsigned char>((((int)round((2.0 * rotation_2d_new.radians) / M_PI) % 4) + 4) % 4))) {}

double Rotation90::GetRadians() const
{
    return (static_cast<double>(static_cast<unsigned char>(val)) * M_PI);
}
double Rotation90::GetDegrees() const
{
    return (static_cast<double>(static_cast<unsigned char>(val)) * 90.0);
}




// -----------------   FLIP90   -----------------
Flip90::Flip90() {}
Flip90::Flip90(const bool i_flip_horizontally, const bool i_flip_vertically) : flip_horizontally(i_flip_horizontally), flip_vertically(i_flip_vertically) {}
Flip90::Flip90(const TotalFlip& total_flip) : flip_horizontally(total_flip.flip_horizontally), flip_vertically(total_flip.flip_vertically) {}




// -----------------   SCALE90   -----------------
Scale90::Scale90() {}
Scale90::Scale90(const double i_width_scale, const double i_height_scale) : width_scale(i_width_scale), height_scale(i_height_scale) {}
Scale90::Scale90(const Scale2DNew& scale_2d_new) : width_scale(scale_2d_new.width_scale), height_scale(scale_2d_new.height_scale) {}




// -----------------   TRANSFORMATIONS90   -----------------
Transformations90::Transformations90(const Rotation90 i_rotation, const Scale90 i_scale, const Flip90 i_flip) : rotation(i_rotation), scale(i_scale), flip(i_flip) {}
Transformations90::Transformations90(const Transformations& transformations) : rotation(transformations.rotation), scale(transformations.scale), flip(transformations.total_flip) {}

void Transformations90::RotateCounterclockwise(const unsigned char number_of_counterclockwise_90_degree_rotations)
{
    rotation.val = static_cast<RotationEnum>((static_cast<unsigned char>(rotation.val) + (number_of_counterclockwise_90_degree_rotations % 4)) % 4);
}
void Transformations90::RotateClockwise(const unsigned char number_of_clockwise_90_degree_rotations)
{
    rotation.val = static_cast<RotationEnum>(((static_cast<unsigned char>(rotation.val) + static_cast<unsigned char>(4)) - (number_of_clockwise_90_degree_rotations % 4)) % 4);
}












// ----------------------------------   F U L L   D A T A   S T R U C T S   ----------------------------------

// -----------------   POINT 2D   -----------------
Point2DNew::Point2DNew() {}
Point2DNew::Point2DNew(const double i_x, const double i_y) : x(i_x), y(i_y) {}


RefPoint2DNewest::RefPoint2DNewest() {}
RefPoint2DNewest::RefPoint2DNewest(const double i_x, const double i_y) : x(i_x), y(i_y) {}
RefPoint2DNewest::RefPoint2DNewest(const Point2DNew non_ref_point) : x(non_ref_point.x), y(non_ref_point.y) {}
RefPoint2DNewest::RefPoint2DNewest(const double i_x, const double i_y, const RefPoint2DNewest* const i_reference_point, const RefTransformations* const i_reference_transformations) : x(i_x), y(i_y), reference_point(i_reference_point), reference_transformations(i_reference_transformations) {}
RefPoint2DNewest::RefPoint2DNewest(const Point2DNew non_ref_point, const RefPoint2DNewest* const i_reference_point, const RefTransformations* const i_reference_transformations) : x(non_ref_point.x), y(non_ref_point.y), reference_point(i_reference_point), reference_transformations(i_reference_transformations) {}

Point2DNew RefPoint2DNewest::GetDepthValue(const unsigned int depth_index) const
{
    Point2DNew ref_point;
    if (reference_point)
    {
        ref_point = reference_point->GetDepthValue(depth_index - 1);
    }

    //Trans rights!
    Transformations ref_trans;
    if (reference_transformations)
    {
        ref_trans = reference_transformations->GetDepthValue(depth_index - 1);
    }


    const double flipped_x = x * ((-2.0 * ref_trans.total_flip.flip_horizontally) + 1.0);
    const double flipped_y = y * ((-2.0 * ref_trans.total_flip.flip_vertically) + 1.0);


    //Compute modulated total width and height directions.
    const double combined_width_direction = ref_trans.rotation.radians + ref_trans.scale.width_radian_offset;
    const double combined_height_direction = ref_trans.rotation.radians + ref_trans.scale.height_radian_offset;

    const double snapped_width_direction = SnapRadiansToDegrees(combined_width_direction, 90);
    const double snapped_height_direction = SnapRadiansToDegrees(combined_height_direction, 90);


    if (snapped_width_direction == snapped_height_direction)
    {
        if (snapped_width_direction == 0.0)
        {
            return Point2DNew(
                ref_point.x + (flipped_x * ref_trans.scale.width_scale),
                ref_point.y + (flipped_y * ref_trans.scale.height_scale)
            );
        }
        if (snapped_width_direction == 90.0)
        {
            return Point2DNew(
                ref_point.x - (flipped_y * ref_trans.scale.height_scale),
                ref_point.y + (flipped_x * ref_trans.scale.width_scale)
            );
        }
        if (snapped_width_direction == 180.0)
        {
            return Point2DNew(
                ref_point.x - (flipped_x * ref_trans.scale.width_scale),
                ref_point.y - (flipped_y * ref_trans.scale.height_scale)
            );
        }
        if (snapped_width_direction == 270.0)
        {
            return Point2DNew(
                ref_point.x + (flipped_y * ref_trans.scale.height_scale),
                ref_point.y - (flipped_x * ref_trans.scale.width_scale)
            );
        }
    }


    const double x_x_component = cos(combined_width_direction) * ref_trans.scale.width_scale;
    const double y_x_component = cos(combined_height_direction + (M_PI / 2.0)) * ref_trans.scale.height_scale;

    const double x_y_component = sin(combined_width_direction) * ref_trans.scale.width_scale;
    const double y_y_component = sin(combined_height_direction + (M_PI / 2.0)) * ref_trans.scale.height_scale;


    return Point2DNew(
        ref_point.x + (flipped_x * x_x_component) + (flipped_y * y_x_component),
        ref_point.y + (flipped_x * x_y_component) + (flipped_y * y_y_component)
    );
}
Point2DNew RefPoint2DNewest::GetUniValue() const
{
    return GetDepthValue(numeric_limits<unsigned int>::max());
}

unsigned int RefPoint2DNewest::GetDepthIndex(const RefPoint2DNewest* const depth_pointer) const
{
    const bool depth_pointer_nullptr = (depth_pointer == nullptr);

    unsigned int repeats = 0;
    const RefPoint2DNewest* temp_depth_pointer = this;
    while (true)
    {
        if (repeats == numeric_limits<unsigned int>::max())
        {
            cerr << "depth_pointer not found!! In this case, this is most likely due to a \"loop\" in the reference chain.\n";
            throw;
        }
        if ((temp_depth_pointer == nullptr) && !depth_pointer_nullptr)
        {
            cerr << "depth_pointer not found!! In this case, this is most likely because depth_pointer was simply not present in the reference chain provided.\n";
            throw;
        }

        if (temp_depth_pointer == depth_pointer)
        {
            return repeats;
        }

        temp_depth_pointer = temp_depth_pointer->reference_point;
        repeats++;
    }
}
Point2DNew RefPoint2DNewest::GetDepthValue(const RefPoint2DNewest* const depth_pointer) const
{
    return GetDepthValue(GetDepthIndex(depth_pointer));
}

void RefPoint2DNewest::SetValueToFitDepthValue(const unsigned int depth_index, const Point2DNew depth_value)
{
    Point2DNew ref_point;
    if (reference_point)
    {
        ref_point = reference_point->GetDepthValue(depth_index - 1);
    }

    Transformations ref_trans;
    if (reference_transformations)
    {
        ref_trans = reference_transformations->GetDepthValue(depth_index - 1);
    }


    const double flipped_x_old = x * ((-2.0 * ref_trans.total_flip.flip_horizontally) + 1.0);
    const double flipped_y_old = y * ((-2.0 * ref_trans.total_flip.flip_vertically) + 1.0);


    //Compute modulated total width and height directions.
    const double combined_width_direction = ref_trans.rotation.radians + ref_trans.scale.width_radian_offset;
    const double combined_height_direction = ref_trans.rotation.radians + ref_trans.scale.height_radian_offset;

    const double snapped_width_direction = SnapRadiansToDegrees(combined_width_direction, 90);
    const double snapped_height_direction = SnapRadiansToDegrees(combined_height_direction, 90);


    double flipped_x;
    double flipped_y;
    bool aligned_90 = 0;
    if (snapped_width_direction == snapped_height_direction)
    {
        if (snapped_width_direction == 0.0)
        {
            flipped_x = (depth_value.x - ref_point.x) / ref_trans.scale.width_scale;
            flipped_y = (depth_value.y - ref_point.y) / ref_trans.scale.height_scale;
            aligned_90 = 1;
        }
        if (snapped_width_direction == 90.0)
        {
            flipped_x = (depth_value.y - ref_point.y) / ref_trans.scale.width_scale;
            flipped_y = (ref_point.x - depth_value.x) / ref_trans.scale.height_scale;
            aligned_90 = 1;
        }
        if (snapped_width_direction == 180.0)
        {
            flipped_x = (ref_point.x - depth_value.x) / ref_trans.scale.width_scale;
            flipped_y = (ref_point.y - depth_value.y) / ref_trans.scale.height_scale;
            aligned_90 = 1;
        }
        if (snapped_width_direction == 270.0)
        {
            flipped_x = (ref_point.y - depth_value.y) / ref_trans.scale.width_scale;
            flipped_y = (depth_value.x - ref_point.x) / ref_trans.scale.height_scale;
            aligned_90 = 1;
        }

        const double flipped_x_old = x * ((-2.0 * ref_trans.total_flip.flip_horizontally) + 1.0);
        const double flipped_y_old = y * ((-2.0 * ref_trans.total_flip.flip_vertically) + 1.0);
    }

    if (!aligned_90)
    {
        const double x_x_component = cos(combined_width_direction) * ref_trans.scale.width_scale;
        const double y_x_component = cos(combined_height_direction + (M_PI / 2.0)) * ref_trans.scale.height_scale;

        const double x_y_component = sin(combined_width_direction) * ref_trans.scale.width_scale;
        const double y_y_component = sin(combined_height_direction + (M_PI / 2.0)) * ref_trans.scale.height_scale;


        flipped_y = (((depth_value.y - ref_point.y) / x_y_component) - ((depth_value.x - ref_point.x) / x_x_component)) / ((y_y_component / x_y_component) - (y_x_component / x_x_component));
        flipped_x = (depth_value.x - ref_point.x - (flipped_y * y_x_component)) / x_x_component;
    }

    x = flipped_x * ((-2.0 * ref_trans.total_flip.flip_horizontally) + 1.0);
    y = flipped_y * ((-2.0 * ref_trans.total_flip.flip_vertically) + 1.0);
}
void RefPoint2DNewest::SetValueToFitUniValue(const Point2DNew uni_value)
{
    SetValueToFitDepthValue(numeric_limits<unsigned int>::max(), uni_value);
}




// -----------------   SIZE 2D   -----------------
Size2DNew::Size2DNew() {}
Size2DNew::Size2DNew(const double i_width, const double i_height) : width(i_width), height(i_height) {}




// -----------------   CENTERING 2D   -----------------
Centering2DNew::Centering2DNew() {}
Centering2DNew::Centering2DNew(const double i_x_centering, const double i_y_centering) : x_centering(i_x_centering), y_centering(i_y_centering) {}




// -----------------   SCALE 2D   -----------------
Scale2DNew::Scale2DNew() {}
Scale2DNew::Scale2DNew(const double i_width_scale, const double i_height_scale) : width_scale(i_width_scale), height_scale(i_height_scale) {}
Scale2DNew::Scale2DNew(const double i_width_scale, const double i_width_direction_offset, const double i_height_scale, const double i_height_direction_offset) : width_scale(i_width_scale), width_radian_offset(i_width_direction_offset), height_scale(i_height_scale), height_radian_offset(i_height_direction_offset) {}
Scale2DNew::Scale2DNew(const Scale90 scale_90) : width_scale(scale_90.width_scale), height_scale(scale_90.height_scale) {}




// -----------------   ROTATION 2D   -----------------
Rotation2DNew::Rotation2DNew() {}
Rotation2DNew::Rotation2DNew(const double i_radians) : radians(i_radians) {}
Rotation2DNew::Rotation2DNew(const RotationEnum rotation_90) : radians(static_cast<double>(static_cast<unsigned char>(rotation_90))* M_PI) {}

double Rotation2DNew::GetDegrees() const
{
    return (radians * 180.0 / M_PI);
}
void Rotation2DNew::SetWithDegrees(const double degrees)
{
    radians = degrees * M_PI / 180.0;
}




// -----------------   TOTAL FLIP   -----------------
TotalFlip::TotalFlip(const bool i_flip_horizontally, const bool i_flip_vertically, const double i_horizontal_direction_offset, const double i_vertical_direction_offset) : flip_horizontally(i_flip_horizontally), horizontal_direction_offset(i_horizontal_direction_offset), flip_vertically(i_flip_vertically), vertical_direction_offset(i_vertical_direction_offset) {}
TotalFlip::TotalFlip(const Flip90& flip_90) : flip_horizontally(flip_90.flip_horizontally), flip_vertically(flip_90.flip_vertically) {}

SDL_RendererFlip TotalFlip::GetSDLFlip() const
{
    if (flip_horizontally && flip_vertically)
    {
        return SDL_FLIP_NONE;
    }
    else
    {
        return static_cast<SDL_RendererFlip>(flip_horizontally + (2 * flip_vertically));
    }
}




// -----------------   TRANSFORMATIONS 2D   -----------------
Transformations::Transformations() {}
Transformations::Transformations(const Rotation2DNew i_rotation, const Scale2DNew i_scale, const TotalFlip i_total_flip) : rotation(i_rotation), scale(i_scale), total_flip(i_total_flip) {}
Transformations::Transformations(const Transformations90 transformations_90) : rotation(transformations_90.rotation.val), scale(transformations_90.scale), total_flip(transformations_90.flip) {}


RefTransformations::RefTransformations() {}
RefTransformations::RefTransformations(const Transformations non_ref_transformations, const RefTransformations* const i_reference_transformations) : rotation(non_ref_transformations.rotation), scale(non_ref_transformations.scale), total_flip(non_ref_transformations.total_flip), reference_transformations(i_reference_transformations) {}
RefTransformations::RefTransformations(const Rotation2DNew i_rotation, const Scale2DNew i_scale, const TotalFlip i_total_flip) : rotation(i_rotation), scale(i_scale), total_flip(i_total_flip) {}
RefTransformations::RefTransformations(const Rotation2DNew i_rotation, const Scale2DNew i_scale, const TotalFlip i_total_flip, const RefTransformations* const i_reference_transformations) : rotation(i_rotation), scale(i_scale), total_flip(i_total_flip), reference_transformations(i_reference_transformations) {}

Transformations RefTransformations::GetDepthValue(const unsigned int depth_index) const
{
    if (reference_transformations && (depth_index != 0))
    {
        const Transformations ref = reference_transformations->GetDepthValue(depth_index - 1);

        const double half_pi = M_PI / 2.0;

        const double x1_x0_component = cos(ref.rotation.radians + ref.scale.width_radian_offset) * ref.scale.width_scale;
        const double x1_y0_component = sin(ref.rotation.radians + ref.scale.width_radian_offset) * ref.scale.width_scale;

        const double y1_x0_component = cos(ref.rotation.radians + ref.scale.height_radian_offset + half_pi) * ref.scale.height_scale;
        const double y1_y0_component = sin(ref.rotation.radians + ref.scale.height_radian_offset + half_pi) * ref.scale.height_scale;


        const double x2_x1_component = cos(rotation.radians + scale.width_radian_offset) * scale.width_scale;
        const double x2_y1_component = sin(rotation.radians + scale.width_radian_offset) * scale.width_scale;

        const double y2_x1_component = cos(rotation.radians + scale.height_radian_offset + half_pi) * scale.height_scale;
        const double y2_y1_component = sin(rotation.radians + scale.height_radian_offset + half_pi) * scale.height_scale;


        const double x2_x0_component = (x2_x1_component * x1_x0_component) + (x2_y1_component * y1_x0_component);
        const double x2_y0_component = (x2_x1_component * x1_y0_component) + (x2_y1_component * y1_y0_component);

        const double y2_x0_component = (y2_x1_component * x1_x0_component) + (y2_y1_component * y1_x0_component);
        const double y2_y0_component = (y2_x1_component * x1_y0_component) + (y2_y1_component * y1_y0_component);


        const double temp_rotation_radians = ref.rotation.radians + rotation.radians;

        return Transformations(
            Rotation2DNew(temp_rotation_radians),
            Scale2DNew(sqrt(pow(x2_x0_component, 2.0) + pow(x2_y0_component, 2.0)), atan2(x2_y0_component, x2_x0_component) - temp_rotation_radians, sqrt(pow(y2_x0_component, 2.0) + pow(y2_y0_component, 2.0)), atan2(y2_y0_component, y2_x0_component) - temp_rotation_radians - half_pi),
            TotalFlip(total_flip.flip_horizontally != ref.total_flip.flip_horizontally, total_flip.flip_vertically != ref.total_flip.flip_vertically)
        );
    }
    else
    {
        return Transformations(rotation, scale, total_flip);
    }
}
Transformations RefTransformations::GetUniValue() const
{
    return GetDepthValue(numeric_limits<unsigned int>::max());
}
unsigned int RefTransformations::GetDepthIndex(const RefTransformations* const depth_pointer) const
{
    //TO-DO
    return 0;
}
Transformations RefTransformations::GetDepthValue(const RefTransformations* const depth_pointer) const
{
    //TO-DO
    return Transformations();
}




// -----------------   QUAD   -----------------
Quad::Quad() {}
Quad::Quad(const double right_edge, const double bottom_edge, const double left_edge, const double top_edge) : top_right(right_edge, top_edge), bottom_right(right_edge, bottom_edge), bottom_left(left_edge, bottom_edge), top_left(left_edge, top_edge) {}
Quad::Quad(const Point2DNew i_top_right, const Point2DNew i_bottom_right, const Point2DNew i_bottom_left, const Point2DNew i_top_left) : top_right(i_top_right), bottom_right(i_bottom_right), bottom_left(i_bottom_left), top_left(i_top_left) {}

void Quad::Align90(const unsigned int WILL_BE_SCALED_accepted_epsilon_difference)
{
    const double total_epsilon = numeric_limits<double>::epsilon() * WILL_BE_SCALED_accepted_epsilon_difference;

    if (abs(top_right.x - bottom_right.x) < (total_epsilon * top_right.x))
    {
        SnapAwayDouble(&top_right.x, 1.0, 0.5, 10000);
        bottom_right.x = top_right.x;
    }
    if (abs(bottom_right.y - bottom_left.y) < (total_epsilon * bottom_right.y))
    {
        SnapAwayDouble(&bottom_right.y, 1.0, 0.5, 10000);
        bottom_left.y = bottom_right.y;
    }
    if (abs(bottom_left.x - top_left.x) < (total_epsilon * bottom_left.x))
    {
        SnapAwayDouble(&bottom_left.x, 1.0, 0.5, 10000);
        top_left.x = bottom_left.x;
    }
    if (abs(top_left.y - top_right.y) < (total_epsilon * top_left.y))
    {
        SnapAwayDouble(&top_left.y, 1.0, 0.5, 10000);
        top_right.y = top_left.y;
    }
}












// ----------------------------------   R E C T A N G L E   ----------------------------------

// -----------------   NON-REFERENCE   -----------------
Quad RectangleNewest::GetQuad() const
{
    if ((transformations.scale.width_radian_offset == 0.0) && (transformations.scale.height_radian_offset == 0.0) && (transformations.total_flip.horizontal_direction_offset == 0.0) && (transformations.total_flip.vertical_direction_offset == 0.0))
    {
        const double degrees = SnapRadiansToDegrees(transformations.rotation.radians, 90);

        if (degrees == 0.0)
        {
            const double flip_horizontally = (((double)transformations.total_flip.flip_horizontally * -2.0) + 1.0);
            const double flip_vertically = (((double)transformations.total_flip.flip_vertically * -2.0) + 1.0);

            return Quad(
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering + 1.0) / 2.0),
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering - 1.0) / 2.0),
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering - 1.0) / 2.0),
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering + 1.0) / 2.0)
            );
        }

        if (degrees == 90.0)
        {
            const double flip_horizontally = (((double)transformations.total_flip.flip_horizontally * -2.0) + 1.0);
            const double flip_vertically = (((double)transformations.total_flip.flip_vertically * -2.0) + 1.0);

            return Quad(
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering - 1.0) / 2.0),
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering - 1.0) / 2.0),
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering + 1.0) / 2.0),
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering + 1.0) / 2.0)
            );
        }

        if (degrees == 180.0)
        {
            const double flip_horizontally = (((double)transformations.total_flip.flip_horizontally * -2.0) + 1.0);
            const double flip_vertically = (((double)transformations.total_flip.flip_vertically * -2.0) + 1.0);

            return Quad(
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering - 1.0) / 2.0),
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering + 1.0) / 2.0),
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering + 1.0) / 2.0),
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering - 1.0) / 2.0)
            );
        }

        if (degrees == 270.0)
        {
            const double flip_horizontally = (((double)transformations.total_flip.flip_horizontally * -2.0) + 1.0);
            const double flip_vertically = (((double)transformations.total_flip.flip_vertically * -2.0) + 1.0);

            return Quad(
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering + 1.0) / 2.0),
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering + 1.0) / 2.0),
                pos.y + (unscaled_size.height * transformations.scale.height_scale * flip_vertically * (centering.y_centering - 1.0) / 2.0),
                pos.x + (unscaled_size.width * transformations.scale.width_scale * flip_horizontally * (centering.x_centering - 1.0) / 2.0)
            );
        }
    }

    return Quad(GetCorner(CornerEnum::TOP_RIGHT), GetCorner(CornerEnum::BOTTOM_RIGHT), GetCorner(CornerEnum::BOTTOM_LEFT), GetCorner(CornerEnum::TOP_LEFT));
}

Point2DNew RectangleNewest::GetCorner(const CornerEnum corner) const
{
    Point2DNew temp_point;
    switch (corner)
    {
    case CornerEnum::TOP_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::TOP_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    }

    const RefRectangleNewest temp_rect(*this);

    const RefPoint2DNewest temp_ref_point(temp_point.x, temp_point.y, &temp_rect.pos, &temp_rect.transformations);

    return temp_ref_point.GetUniValue();
}


//---- Edge Functions ----

Line2D RectangleNewest::GetEdge(const DirectionEnum edge) const
{
    switch (edge)
    {
    case DirectionEnum::RIGHT:
        return Line2D(GetCorner(CornerEnum::TOP_RIGHT), GetCorner(CornerEnum::BOTTOM_RIGHT));
    case DirectionEnum::BOTTOM:
        return Line2D(GetCorner(CornerEnum::BOTTOM_RIGHT), GetCorner(CornerEnum::BOTTOM_LEFT));
    case DirectionEnum::LEFT:
        return Line2D(GetCorner(CornerEnum::BOTTOM_LEFT), GetCorner(CornerEnum::TOP_LEFT));
    case DirectionEnum::TOP:
        return Line2D(GetCorner(CornerEnum::TOP_LEFT), GetCorner(CornerEnum::TOP_RIGHT));
    default:
        cerr << "[edge] was not a legal value!!!! You better recheck yo code;   Sent by Line2D RectangleNewest::GetEdge(const FourDirection edge) const";
        throw;
    }
}


//---- Scale Functions ----

Size2DNew RectangleNewest::GetScaledSize() const
{
    return Size2DNew(unscaled_size.width * transformations.scale.width_scale, unscaled_size.height * transformations.scale.height_scale);
}
double RectangleNewest::GetScaledWidth() const
{
    return (unscaled_size.width * transformations.scale.width_scale);
}
double RectangleNewest::GetScaledHeight() const
{
    return (unscaled_size.height * transformations.scale.height_scale);
}


//---- Centering/Offset Functions ----

Offset2DNew RectangleNewest::GetUnscaledOffset() const
{
    return Offset2DNew(centering.x_centering * unscaled_size.width, centering.y_centering * unscaled_size.height);
}
double RectangleNewest::GetUnscaledOffsetX() const
{
    return (centering.x_centering * unscaled_size.width);
}
double RectangleNewest::GetUnscaledOffsetY() const
{
    return (centering.y_centering * unscaled_size.height);
}

Offset2DNew RectangleNewest::GetScaledOffset() const
{
    return Offset2DNew(centering.x_centering * unscaled_size.width * transformations.scale.width_scale, centering.y_centering * unscaled_size.height * transformations.scale.height_scale);
}
double RectangleNewest::GetScaledOffsetX() const
{
    return (centering.x_centering * unscaled_size.width * transformations.scale.width_scale);
}
double RectangleNewest::GetScaledOffsetY() const
{
    return (centering.y_centering * unscaled_size.height * transformations.scale.height_scale);
}




// -----------------   REFERENCE   -----------------

// -------------  RefRectangleNewest  -------------

RefRectangleNewest::RefRectangleNewest() {}
RefRectangleNewest::RefRectangleNewest(const RefRectangleNewest* const reference_rectangle, const Point2DNew non_ref_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const Transformations non_ref_transformations)
    : pos(non_ref_pos, reference_rectangle ? &reference_rectangle->pos : nullptr, reference_rectangle ? &reference_rectangle->transformations : nullptr),
    unscaled_size(i_unscaled_size),
    centering(i_centering),
    transformations(non_ref_transformations, reference_rectangle ? &reference_rectangle->transformations : nullptr) {}
RefRectangleNewest::RefRectangleNewest(const RefPoint2DNewest* const reference_point, const RefTransformations* const reference_transformations, const Point2DNew non_ref_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const Transformations non_ref_transformations)
    : pos(non_ref_pos, reference_point, reference_transformations),
    unscaled_size(i_unscaled_size),
    centering(i_centering),
    transformations(non_ref_transformations, reference_transformations) {}
RefRectangleNewest::RefRectangleNewest(const RefPoint2DNewest i_pos, const RefTransformations i_transformations, const Size2DNew i_unscaled_size, const Centering2DNew i_centering) : pos(i_pos), transformations(i_transformations), unscaled_size(i_unscaled_size), centering(i_centering) {}

RefRectangleNewest::RefRectangleNewest(const RectangleNewest non_ref_rectangle) : pos(non_ref_rectangle.pos), transformations(non_ref_rectangle.transformations), unscaled_size(non_ref_rectangle.unscaled_size), centering(non_ref_rectangle.centering) {}


RectangleNewest RefRectangleNewest::GetUniValue() const
{
    return {
    pos.GetUniValue(),
    transformations.GetUniValue(),
    unscaled_size,
    centering
    };
}
RectangleNewest RefRectangleNewest::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return {
        { pos.x, pos.y },
        { transformations.rotation, transformations.scale, transformations.total_flip },
        unscaled_size,
        centering
        };
    }
    else
    {
        return {
        pos.GetDepthValue(depth_index),
        transformations.GetDepthValue(depth_index),
        unscaled_size,
        centering
        };
    }
}

Quad RefRectangleNewest::GetUniQuad() const
{
    return GetDepthQuad(numeric_limits<unsigned int>::max());
}
Quad RefRectangleNewest::GetDepthQuad(const unsigned int depth_index) const //TO-DO
{
    //TO-DO: create a condition for other cardinal rotations

    if ((((pos.reference_point == nullptr) && (!pos.reference_transformations) && (!transformations.reference_transformations)) || (depth_index == 0)) && (transformations.rotation.radians == 0.0) && (transformations.scale.width_radian_offset == 0.0) && (transformations.scale.height_radian_offset == 0.0))
    {
        return Quad(
            pos.x + (unscaled_size.width * transformations.scale.width_scale * (centering.x_centering + 1.0) / 2.0),
            pos.y + (unscaled_size.height * transformations.scale.height_scale * (centering.y_centering - 1.0) / 2.0),
            pos.x + (unscaled_size.width * transformations.scale.width_scale * (centering.x_centering - 1.0) / 2.0),
            pos.y + (unscaled_size.height * transformations.scale.height_scale * (centering.y_centering + 1.0) / 2.0)
        );
    }

    return Quad(GetDepthCorner(CornerEnum::TOP_RIGHT, depth_index), GetDepthCorner(CornerEnum::BOTTOM_RIGHT, depth_index), GetDepthCorner(CornerEnum::BOTTOM_LEFT, depth_index), GetDepthCorner(CornerEnum::TOP_LEFT, depth_index));
}

Point2DNew RefRectangleNewest::GetUniCorner(const CornerEnum corner) const
{
    return GetDepthCorner(corner, numeric_limits<unsigned int>::max());
}
Point2DNew RefRectangleNewest::GetDepthCorner(const CornerEnum corner, const unsigned int depth_index) const //TO-DO
{
    Point2DNew temp_point;
    switch (corner)
    {
    case CornerEnum::TOP_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::TOP_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    }

    const RefPoint2DNewest temp_ref_point(temp_point.x, temp_point.y, &pos, &transformations);

    return temp_ref_point.GetDepthValue(depth_index);
}

void RefRectangleNewest::SetPosToFitCurrentPlanePointToDepthPoint(const Point2DNew depth_point, const Point2DNew current_plane_point, const unsigned int depth_index)
{

}


void RefRectangleNewest::SetDepthCorner(const Point2DNew depth_corner, const CornerEnum corner_identity, const unsigned int depth_index)
{
    Point2DNew temp_point;
    switch (corner_identity)
    {
    case CornerEnum::TOP_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::TOP_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    }

    RefPoint2DNewest temp_corner(temp_point.x, temp_point.y, nullptr, &transformations);

    const Point2DNew temp_corner_offset = temp_corner.GetDepthValue(1);

    temp_corner.reference_point = &pos;
    temp_corner.SetValueToFitDepthValue(depth_index, depth_corner);

    pos.x = temp_corner.x - temp_corner_offset.x;
    pos.y = temp_corner.y - temp_corner_offset.y;
}
void RefRectangleNewest::SetUniCorner(const Point2DNew uni_corner, const CornerEnum corner_identity)
{
    SetDepthCorner(uni_corner, corner_identity, numeric_limits<unsigned int>::max());
}


Size2DNew RefRectangleNewest::GetScaledSize() const
{
    return { GetScaledWidth(), GetScaledHeight() };
}
double RefRectangleNewest::GetScaledWidth() const
{
    return (unscaled_size.width * transformations.scale.width_scale);
}
double RefRectangleNewest::GetScaledHeight() const
{
    return (unscaled_size.height * transformations.scale.height_scale);
}

void RefRectangleNewest::SetScaledSize(const Size2DNew scaled_size)
{
    SetScaledWidth(scaled_size.width);
    SetScaledHeight(scaled_size.height);
}
void RefRectangleNewest::SetScaledWidth(const double scaled_width)
{
    unscaled_size.width = (scaled_width / transformations.scale.width_scale);
}
void RefRectangleNewest::SetScaledHeight(const double scaled_height)
{
    unscaled_size.height = (scaled_height / transformations.scale.height_scale);
}


void RefRectangleNewest::SetReference(const RefRectangleNewest* const reference_rectangle)
{
    pos.reference_point = &reference_rectangle->pos;
    pos.reference_transformations = &reference_rectangle->transformations;

    transformations.reference_transformations = &reference_rectangle->transformations;
}






















// ----------------------------------   O L D   S T U F F   ----------------------------------

//---- Edge Functions ----

double RectangleNew::GetEdge(const Direction direction) const
{
    //WARNING: When rotating the rectangle, GetEdge(...) currently returns a value that is non-intuitive

    switch (direction.value)
    {
    case 0:
        return (pos.x + ((centering.x_centering + 1.0) * 0.5 * GetScaledWidth()));
    case 1:
        return (pos.y + ((centering.y_centering - 1.0) * 0.5 * GetScaledHeight()));
    case 2:
        return (pos.x + ((centering.x_centering - 1.0) * 0.5 * GetScaledWidth()));
    case 3:
        return (pos.y + ((centering.y_centering + 1.0) * 0.5 * GetScaledHeight()));
    default:
        return 0.0;
    }


    //Failsafe (should never be able to happen)
    return 0.0;
}
Point2DNew RectangleNew::GetCorner(const Corner corner) const
{
    return Point2DNew();
}

//set edge, set corner, etc.


//---- Scale Functions ----

Size2DNew RectangleNew::GetScaledSize() const
{
    return { GetScaledWidth(), GetScaledHeight() };
}
double RectangleNew::GetScaledWidth() const
{
    return (unscaled_size.width * scale.width_scale);
}
double RectangleNew::GetScaledHeight() const
{
    return (unscaled_size.height * scale.height_scale);
}


//---- Centering/Offset Functions ----

Offset2DNew RectangleNew::GetUnscaledOffset() const
{
    return { GetUnscaledOffsetX(), GetUnscaledOffsetY() };
}
double RectangleNew::GetUnscaledOffsetX() const
{
    return (centering.x_centering * unscaled_size.width / 2.0);
}
double RectangleNew::GetUnscaledOffsetY() const
{
    return (centering.y_centering * unscaled_size.height / 2.0);
}

Offset2DNew RectangleNew::GetScaledOffset() const
{
    return { GetScaledOffsetX(), GetScaledOffsetY() };
}
double RectangleNew::GetScaledOffsetX() const
{
    return (GetUnscaledOffsetX() * scale.width_scale);
}
double RectangleNew::GetScaledOffsetY() const
{
    return (GetUnscaledOffsetY() * scale.height_scale);
}














/*
Rectangle90::Rectangle90() {}
Rectangle90::Rectangle90(const Point2DNew i_pos) : pos(i_pos) {}
Rectangle90::Rectangle90(const Point2DNew i_pos, const Size2DNew i_unscaled_size) : pos(i_pos), unscaled_size(i_unscaled_size) {}
Rectangle90::Rectangle90(const Point2DNew i_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering) : pos(i_pos), unscaled_size(i_unscaled_size), centering(i_centering) {}
Rectangle90::Rectangle90(const Point2DNew i_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const Transformations90 i_transformations) : pos(i_pos), unscaled_size(i_unscaled_size), centering(i_centering), transformations(i_transformations) {}

double Rectangle90::GetEdge(const DirectionEnum edge) const
{
    const EdgeData edge_data = GetEdgeData(edge, transformations.rotation, transformations.flip);

    const double subtract_one_double = edge_data.GetSubtractOneDouble();

    const double flip_double = edge_data.GetFlipDouble();

    if (edge_data.y_axis)
    {
        return pos.y + ((unscaled_size.height * transformations.scale.height_scale) * ((centering.y_centering + subtract_one_double) / 2.0) * flip_double);
    }
    else
    {
        return pos.x + ((unscaled_size.width * transformations.scale.width_scale) * ((centering.x_centering + subtract_one_double) / 2.0) * flip_double);
    }
}
void Rectangle90::SetEdge(const DirectionEnum edge, const double target_coord)
{
    const EdgeData edge_data = GetEdgeData(edge, transformations.rotation, transformations.flip);

    double subtract_one_double = edge_data.GetSubtractOneDouble();

    double flip_double = edge_data.GetFlipDouble();

    if (edge_data.y_axis)
    {
        pos.y = target_coord - ((unscaled_size.height * transformations.scale.height_scale) * ((centering.y_centering + subtract_one_double) / 2.0) * flip_double);
    }
    else
    {
        pos.x = target_coord - ((unscaled_size.width * transformations.scale.width_scale) * ((centering.x_centering + subtract_one_double) / 2.0) * flip_double);
    }
}

Point2DNew Rectangle90::GetCorner(const CornerEnum corner) const
{
    double x_axis_edge = 0.0;
    double y_axis_edge = 0.0;

    switch (corner)
    {
    case CornerEnum::TOP_RIGHT:
        x_axis_edge = GetEdge(DirectionEnum::RIGHT);
        y_axis_edge = GetEdge(DirectionEnum::TOP);
        break;

    case CornerEnum::BOTTOM_RIGHT:
        x_axis_edge = GetEdge(DirectionEnum::RIGHT);
        y_axis_edge = GetEdge(DirectionEnum::BOTTOM);
        break;

    case CornerEnum::BOTTOM_LEFT:
        x_axis_edge = GetEdge(DirectionEnum::LEFT);
        y_axis_edge = GetEdge(DirectionEnum::BOTTOM);
        break;

    case CornerEnum::TOP_LEFT:
        x_axis_edge = GetEdge(DirectionEnum::LEFT);
        y_axis_edge = GetEdge(DirectionEnum::TOP);
        break;
    }

    if ((transformations.rotation == RotationEnum::DEGREES_90) || (transformations.rotation == RotationEnum::DEGREES_270))
    {
        return { y_axis_edge, x_axis_edge };
    }
    else
    {
        return { x_axis_edge, y_axis_edge };
    }
}
void Rectangle90::SetCorner(const CornerEnum corner, const Point2DNew target_point)
{
    switch (corner)
    {
    case CornerEnum::TOP_RIGHT:
        if ((transformations.rotation == RotationEnum::DEGREES_0) || (transformations.rotation == RotationEnum::DEGREES_180))
        {
            SetEdge(DirectionEnum::RIGHT, target_point.x);
            SetEdge(DirectionEnum::TOP, target_point.y);
        }
        else
        {
            SetEdge(DirectionEnum::RIGHT, target_point.y);
            SetEdge(DirectionEnum::TOP, target_point.x);
        }
        break;
    case CornerEnum::BOTTOM_RIGHT:
        if ((transformations.rotation == RotationEnum::DEGREES_0) || (transformations.rotation == RotationEnum::DEGREES_180))
        {
            SetEdge(DirectionEnum::RIGHT, target_point.x);
            SetEdge(DirectionEnum::BOTTOM, target_point.y);
        }
        else
        {
            SetEdge(DirectionEnum::RIGHT, target_point.y);
            SetEdge(DirectionEnum::BOTTOM, target_point.x);
        }
        break;
    case CornerEnum::BOTTOM_LEFT:
        if ((transformations.rotation == RotationEnum::DEGREES_0) || (transformations.rotation == RotationEnum::DEGREES_180))
        {
            SetEdge(DirectionEnum::LEFT, target_point.x);
            SetEdge(DirectionEnum::BOTTOM, target_point.y);
        }
        else
        {
            SetEdge(DirectionEnum::LEFT, target_point.y);
            SetEdge(DirectionEnum::BOTTOM, target_point.x);
        }
    break;    case CornerEnum::TOP_LEFT:
        if ((transformations.rotation == RotationEnum::DEGREES_0) || (transformations.rotation == RotationEnum::DEGREES_180))
        {
            SetEdge(DirectionEnum::LEFT, target_point.x);
            SetEdge(DirectionEnum::TOP, target_point.y);
        }
        else
        {
            SetEdge(DirectionEnum::LEFT, target_point.y);
            SetEdge(DirectionEnum::TOP, target_point.x);
        }
        break;
    }
}
*/



// ----------------------------     N O N - R E F E R E N C E   S T R U C T S     ----------------------------








Line2D::Line2D() {}
Line2D::Line2D(const Point2DNew i_v_1, const Point2DNew i_v_2) : v_1(i_v_1), v_2(i_v_2) {}
Line2D::Line2D(const double i_x_1, const double i_y_1, const double i_x_2, const double i_y_2) : v_1({ i_x_1, i_y_1 }), v_2({ i_x_2, i_y_2 }) {}











Offset2DNew::Offset2DNew() {}
Offset2DNew::Offset2DNew(const double i_x_offset, const double i_y_offset) : x_offset(i_x_offset), y_offset(i_y_offset) {}





DirectionOffset2DNew::DirectionOffset2DNew() {}
DirectionOffset2DNew::DirectionOffset2DNew(const double i_x_axis, const double i_y_axis) : x_axis(i_x_axis), y_axis(i_y_axis) {}



































// ----------------------------     R E F E R E N C E   S T R U C T S     ----------------------------


// -------------  TransformationsPointer  -------------
/*
TransformationsPointer::TransformationsPointer() {}
TransformationsPointer::TransformationsPointer(const RefTransformations* const i_transformations_pointer) : transformations_pointer(i_transformations_pointer) {}
TransformationsPointer::TransformationsPointer(const RefTransformations90* const i_transformations90_pointer) : transformations90_pointer(i_transformations90_pointer) {}

void TransformationsPointer::SetPointer(const RefTransformations* const new_transformations_pointer)
{
    transformations_pointer = new_transformations_pointer;
    transformations90_pointer = nullptr;
}
void TransformationsPointer::SetPointer(const RefTransformations90* const new_transformations90_pointer)
{
    transformations90_pointer = new_transformations90_pointer;
    transformations_pointer = nullptr;
}

TransformationsPointerState TransformationsPointer::GetState() const
{
    if (transformations_pointer)
    {
        return TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE;
    }
    if (transformations90_pointer)
    {
        return TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE;
    }
    return TransformationsPointerState::NEITHER_ARE_ACTIVE;
}
TransformationsPointerState TransformationsPointer::GetDepthState(const unsigned int depth_index) const
{
    const TransformationsPointerState t_state = GetState();

    switch (t_state)
    {
    case TransformationsPointerState::NEITHER_ARE_ACTIVE:
        return TransformationsPointerState::NEITHER_ARE_ACTIVE;

    case TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE:
        return TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE;

    case TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE:
        if (depth_index == 0)
        {
            return TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE;
        }
        else
        {
            const TransformationsPointerState ref_t_state = transformations90_pointer->reference_transformations.GetDepthState(depth_index - 1);

            if (ref_t_state == TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE)
            {
                return TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE;
            }
            else
            {
                return TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE;
            }
        }
    }
}
TransformationsPointerState TransformationsPointer::GetUniState() const
{
    return GetDepthState(numeric_limits<unsigned int>::max());
}

const RefTransformations* TransformationsPointer::GetTransformationsPointer() const
{
    return transformations_pointer;
}
const RefTransformations90* TransformationsPointer::GetTransformations90Pointer() const
{
    return transformations90_pointer;
}
*/




// -------------  RefTotalFlip  -------------

TotalFlip RefTotalFlip::GetDereferencedValue(const unsigned int depth_index, const RefTotalFlip* const depth_pointer) const
{
    if ((depth_index == 0) || (this == depth_pointer) || (reference_total_flip == nullptr))
    {
        return v;
    }
    else
    {
        const TotalFlip ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, depth_pointer);
        return { v.flip_horizontally != ref_total_flip.flip_horizontally, v.flip_vertically != ref_total_flip.flip_vertically };
    }
}
void RefTotalFlip::SetValueToFitDereferencedValue(const unsigned int depth_index, const RefTotalFlip* const depth_pointer, const TotalFlip dereferenced_value)
{
    if ((depth_index == 0) || (this == depth_pointer) || (reference_total_flip == nullptr))
    {
        v = dereferenced_value;
    }
    else
    {
        const TotalFlip ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, depth_pointer);
        v = { dereferenced_value.flip_horizontally != ref_total_flip.flip_horizontally, dereferenced_value.flip_vertically != ref_total_flip.flip_vertically };
    }
}

TotalFlip RefTotalFlip::GetUniValue() const
{
    return GetDereferencedValue(numeric_limits<unsigned int>::max(), nullptr);
}
TotalFlip RefTotalFlip::GetDepthValue(const unsigned int depth_index) const
{
    return GetDereferencedValue(depth_index, nullptr);
}
TotalFlip RefTotalFlip::GetDepthValue(const RefTotalFlip* const depth_pointer) const
{
    return GetDereferencedValue(numeric_limits<unsigned int>::max(), depth_pointer);
}

void RefTotalFlip::SetValueToFitUniValue(const TotalFlip uni_value)
{
    SetValueToFitDereferencedValue(numeric_limits<unsigned int>::max(), nullptr, uni_value);
}
void RefTotalFlip::SetValueToFitDepthValue(const unsigned int depth_index, const TotalFlip depth_value)
{
    SetValueToFitDereferencedValue(depth_index, nullptr, depth_value);
}
void RefTotalFlip::SetValueToFitDepthValue(const RefTotalFlip* const depth_pointer, const TotalFlip depth_value)
{
    SetValueToFitDereferencedValue(numeric_limits<unsigned int>::max(), depth_pointer, depth_value);
}








// -------------  RefTransformations90  -------------
/*
RefTransformations90::RefTransformations90() {}

RefTransformations90::RefTransformations90(const RotationEnum i_rotation) : rotation(i_rotation) {}
RefTransformations90::RefTransformations90(const Scale90 i_scale) : scale(i_scale) {}
RefTransformations90::RefTransformations90(const Flip90 i_flip) : flip(i_flip) {}

RefTransformations90::RefTransformations90(const RotationEnum i_rotation, const Scale90 i_scale) : rotation(i_rotation), scale(i_scale) {}
RefTransformations90::RefTransformations90(const RotationEnum i_rotation, const Flip90 i_flip) : rotation(i_rotation), flip(i_flip) {}
RefTransformations90::RefTransformations90(const Scale90 i_scale, const Flip90 i_flip) : scale(i_scale), flip(i_flip) {}

RefTransformations90::RefTransformations90(const RotationEnum i_rotation, const Scale90 i_scale, const Flip90 i_flip) : rotation(i_rotation), scale(i_scale), flip(i_flip) {}

RefTransformations90::RefTransformations90(const RotationEnum i_rotation, const Scale90 i_scale, const Flip90 i_flip, const TransformationsPointer i_reference_transformations) : rotation(i_rotation), scale(i_scale), flip(i_flip), reference_transformations(i_reference_transformations) {}

RefTransformations90::RefTransformations90(const Transformations90 i_non_ref_transformations, const TransformationsPointer i_reference_transformations) : rotation(i_non_ref_transformations.rotation), scale(i_non_ref_transformations.scale), flip(i_non_ref_transformations.flip), reference_transformations(i_reference_transformations) {}


void RefTransformations90::RotateCounterclockwise(const unsigned char number_of_counterclockwise_90_degree_rotations)
{
    rotation = static_cast<RotationEnum>((static_cast<unsigned char>(rotation) + (number_of_counterclockwise_90_degree_rotations % 4)) % 4);
}
void RefTransformations90::RotateClockwise(const unsigned char number_of_clockwise_90_degree_rotations)
{
    rotation = static_cast<RotationEnum>(((static_cast<unsigned char>(rotation) + static_cast<unsigned char>(4)) - (number_of_clockwise_90_degree_rotations % 4)) % 4);
}

RefTransformations RefTransformations90::GetRefTransformations() const
{
    return RefTransformations((double)static_cast<unsigned char>(rotation) * M_PI / 2.0, Scale2DNew(scale.width_scale, scale.height_scale), TotalFlip(flip.flip_horizontally, flip.flip_vertically));
}

Transformations90 RefTransformations90::GetDepthValue90(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return Transformations90(rotation, scale, flip); //Return "this" (without reference_transformations)
    }
    else
    {
        const TransformationsPointerState t_state = reference_transformations.GetState();

        Transformations90 ref_transformations;
        switch (t_state)
        {
        case TransformationsPointerState::NEITHER_ARE_ACTIVE:

            return Transformations90(rotation, scale, flip); //Return "this" (without reference_transformations)

        case TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE:
            ref_transformations = reference_transformations.GetTransformationsPointer()->GetDepthValue90(depth_index - 1);
            break;

        case TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE:
            ref_transformations = reference_transformations.GetTransformations90Pointer()->GetDepthValue90(depth_index - 1);
            break;
        }

        const RotationEnum return_rotation = static_cast<RotationEnum>((static_cast<unsigned char>(rotation) + static_cast<unsigned char>(ref_transformations.rotation)) % static_cast<unsigned char>(4));
        Scale90 return_scale;
        Flip90 return_flip;
        if ((rotation == RotationEnum::DEGREES_0) || (rotation == RotationEnum::DEGREES_180))
        {
            return_scale = { scale.width_scale * ref_transformations.scale.width_scale, scale.height_scale * ref_transformations.scale.height_scale };
            return_flip = { flip.flip_horizontally != ref_transformations.flip.flip_horizontally, flip.flip_vertically != ref_transformations.flip.flip_vertically };
        }
        else
        {
            return_scale = { scale.width_scale * ref_transformations.scale.height_scale, scale.height_scale * ref_transformations.scale.width_scale };
            return_flip = { flip.flip_horizontally != ref_transformations.flip.flip_vertically, flip.flip_vertically != ref_transformations.flip.flip_horizontally };
        }

        return Transformations90(
            return_rotation,
            return_scale,
            return_flip
        );
    }
}
Transformations RefTransformations90::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        const RefTransformations temp_transformations = GetRefTransformations();
        return Transformations(temp_transformations.rotation, temp_transformations.scale, temp_transformations.total_flip); //Return "this" (as an instance of Transformations)
    }
    else
    {
        const TransformationsPointerState t_state = reference_transformations.GetState();

        if (t_state == TransformationsPointerState::NEITHER_ARE_ACTIVE)
        {
            const RefTransformations temp_transformations = GetRefTransformations();
            return Transformations(temp_transformations.rotation, temp_transformations.scale, temp_transformations.total_flip); //Return "this" (as an instance of Transformations)
        }
        else
        {
            const RefTransformations temp_transformations = GetRefTransformations();
            return temp_transformations.GetDepthValue(depth_index);
        }
    }
}

Transformations90 RefTransformations90::GetUniValue90() const
{
    return GetDepthValue90(numeric_limits<unsigned int>::max());
}
Transformations RefTransformations90::GetUniValue() const
{
    return GetDepthValue(numeric_limits<unsigned int>::max());
}
*/




// -------------  RefScale2DNewNew  -------------

RefScale2DNewNew::RefScale2DNewNew() {}
RefScale2DNewNew::RefScale2DNewNew(const double i_width_scale, const double i_height_scale) : width_scale(i_width_scale), height_scale(i_height_scale) {}
RefScale2DNewNew::RefScale2DNewNew(const double i_width_scale, const double i_height_scale, const RefScale2DNewNew* const i_reference_scale) : width_scale(i_width_scale), height_scale(i_height_scale), reference_scale(i_reference_scale) {}



Scale2DNew RefScale2DNewNew::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return Scale2DNew(width_scale, width_radian_offset, height_scale, height_radian_offset);
    }
    else
    {
        //Deal with nullptr reference_scale
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }


        //Calculate and return dereferenced value
        return Scale2DNew(
            width_scale * ref_scale.width_scale,
            height_scale * ref_scale.height_scale
        );
    }
}
double RefScale2DNewNew::GetDepthWidthScale(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return width_scale;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_width_scale;
        if (reference_scale)
        {
            ref_width_scale = reference_scale->GetDepthWidthScale(depth_index - 1);
        }
        else
        {
            ref_width_scale = 1.0;
        }


        //Calculate and return dereferenced value
        return (width_scale * ref_width_scale);
    }
}
double RefScale2DNewNew::GetDepthHeightScale(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return height_scale;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_height_scale;
        if (reference_scale)
        {
            ref_height_scale = reference_scale->GetDepthHeightScale(depth_index - 1);
        }
        else
        {
            ref_height_scale = 1.0;
        }


        //Calculate and return dereferenced value
        return (height_scale * ref_height_scale);
    }
}

void RefScale2DNewNew::SetValueToFitDepthValue(const unsigned int depth_index, const Scale2DNew depth_value)
{
    if (depth_index == 0)
    {
        width_scale = depth_value.width_scale;
        height_scale = depth_value.height_scale;
    }
    else
    {
        //Deal with nullptr reference_scale
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }


        //Calculate and set width_scale and height_scale to fit depth_value
        width_scale = depth_value.width_scale / ref_scale.width_scale;
        height_scale = depth_value.height_scale / ref_scale.height_scale;
    }
}
void RefScale2DNewNew::SetValueToFitDepthWidthScale(const unsigned int depth_index, const double depth_width_scale)
{
    if (depth_index == 0)
    {
        width_scale = depth_width_scale;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_width_scale;
        if (reference_scale)
        {
            ref_width_scale = reference_scale->GetDepthWidthScale(depth_index - 1);
        }
        else
        {
            ref_width_scale = 1.0;
        }


        //Calculate and set width_scale to fit depth_width_scale
        width_scale = depth_width_scale / ref_width_scale;
    }
}
void RefScale2DNewNew::SetValueToFitDepthHeightScale(const unsigned int depth_index, const double depth_height_scale)
{
    if (depth_index == 0)
    {
        height_scale = depth_height_scale;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_height_scale;
        if (reference_scale)
        {
            ref_height_scale = reference_scale->GetDepthHeightScale(depth_index - 1);
        }
        else
        {
            ref_height_scale = 1.0;
        }


        //Calculate and set height_scale to fit depth_height_scale
        height_scale = depth_height_scale / ref_height_scale;
    }
}


Scale2DNew RefScale2DNewNew::GetUniValue() const
{
    return GetDepthValue(numeric_limits<unsigned int>::max());
}
double RefScale2DNewNew::GetUniWidthScale() const
{
    return GetDepthWidthScale(numeric_limits<unsigned int>::max());
}
double RefScale2DNewNew::GetUniHeightScale() const
{
    return GetDepthHeightScale(numeric_limits<unsigned int>::max());
}

void RefScale2DNewNew::SetValueToFitUniValue(const Scale2DNew uni_value)
{
    SetValueToFitDepthValue(numeric_limits<unsigned int>::max(), uni_value);
}
void RefScale2DNewNew::SetValueToFitUniWidthScale(const double uni_width_scale)
{
    SetValueToFitDepthWidthScale(numeric_limits<unsigned int>::max(), uni_width_scale);
}
void RefScale2DNewNew::SetValueToFitUniHeightScale(const double uni_height_scale)
{
    SetValueToFitDepthHeightScale(numeric_limits<unsigned int>::max(), uni_height_scale);
}


unsigned int RefScale2DNewNew::GetDepthIndex(const RefScale2DNewNew* const depth_pointer) const
{
    const bool depth_pointer_nullptr = (depth_pointer == nullptr);

    unsigned int repeats = 0;
    const RefScale2DNewNew* temp_depth_pointer = this;
    while (true)
    {
        if (repeats == numeric_limits<unsigned int>::max())
        {
            cerr << "depth_pointer not found!! In this case, this is most likely due to a \"loop\" in the reference chain.\n";
            throw;
        }
        if ((temp_depth_pointer == nullptr) && !depth_pointer_nullptr)
        {
            cerr << "depth_pointer not found!! In this case, this is most likely because depth_pointer was simply not present in the reference chain provided.\n";
            throw;
        }

        if (temp_depth_pointer == depth_pointer)
        {
            return repeats;
        }

        temp_depth_pointer = temp_depth_pointer->reference_scale;
        repeats++;
    }
}

Scale2DNew RefScale2DNewNew::GetDepthValue(const RefScale2DNewNew* const depth_pointer) const
{
    return GetDepthValue(GetDepthIndex(depth_pointer));
}
double RefScale2DNewNew::GetDepthWidthScale(const RefScale2DNewNew* const depth_pointer) const
{
    return GetDepthWidthScale(GetDepthIndex(depth_pointer));
}
double RefScale2DNewNew::GetDepthHeightScale(const RefScale2DNewNew* const depth_pointer) const
{
    return GetDepthHeightScale(GetDepthIndex(depth_pointer));
}

void RefScale2DNewNew::SetValueToFitDepthValue(const RefScale2DNewNew* const depth_pointer, const Scale2DNew depth_value)
{
    SetValueToFitDepthValue(GetDepthIndex(depth_pointer), depth_value);
}
void RefScale2DNewNew::SetValueToFitDepthWidthScale(const RefScale2DNewNew* const depth_pointer, const double depth_width_scale)
{
    SetValueToFitDepthWidthScale(GetDepthIndex(depth_pointer), depth_width_scale);
}
void RefScale2DNewNew::SetValueToFitDepthHeightScale(const RefScale2DNewNew* const depth_pointer, const double depth_height_scale)
{
    SetValueToFitDepthHeightScale(GetDepthIndex(depth_pointer), depth_height_scale);
}




// -------------  RefSize2DNewNew  -------------

RefSize2DNewNew::RefSize2DNewNew() {}
RefSize2DNewNew::RefSize2DNewNew(const double i_width, const double i_height) : width(i_width), height(i_height) {}
RefSize2DNewNew::RefSize2DNewNew(const double i_width, const double i_height, const RefScale2DNewNew* const i_reference_scale) : width(i_width), height(i_height), reference_scale(i_reference_scale) {}



Size2DNew RefSize2DNewNew::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return { width, height };
    }
    else
    {
        //Deal with nullptr reference_scale
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }

        //Calculate and return depth value
        return { width * ref_scale.width_scale, height * ref_scale.height_scale };
    }
}
double RefSize2DNewNew::GetDepthWidth(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return width;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_width_scale;
        if (reference_scale)
        {
            ref_width_scale = reference_scale->GetDepthWidthScale(depth_index - 1);
        }
        else
        {
            ref_width_scale = 1.0;
        }

        //Calculate and return depth width
        return (width * ref_width_scale);
    }
}
double RefSize2DNewNew::GetDepthHeight(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return height;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_height_scale;
        if (reference_scale)
        {
            ref_height_scale = reference_scale->GetDepthHeightScale(depth_index - 1);
        }
        else
        {
            ref_height_scale = 1.0;
        }

        //Calculate and return depth height
        return (height * ref_height_scale);
    }
}

void RefSize2DNewNew::SetValueToFitDepthValue(const unsigned int depth_index, const Size2DNew depth_value)
{
    if (depth_index == 0)
    {
        width = depth_value.width;
        height = depth_value.height;
    }
    else
    {
        //Deal with nullptr reference_scale
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }

        //Calculate and set value to fit depth_value
        width = depth_value.width / ref_scale.width_scale;
        height = depth_value.height / ref_scale.height_scale;
    }
}
void RefSize2DNewNew::SetValueToFitDepthWidth(const unsigned int depth_index, const double depth_width)
{
    if (depth_index == 0)
    {
        width = depth_width;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_width_scale;
        if (reference_scale)
        {
            ref_width_scale = reference_scale->GetDepthWidthScale(depth_index - 1);
        }
        else
        {
            ref_width_scale = 1.0;
        }

        //Calculate and set width to fit depth_width
        width = depth_width / ref_width_scale;
    }
}
void RefSize2DNewNew::SetValueToFitDepthHeight(const unsigned int depth_index, const double depth_height)
{
    if (depth_index == 0)
    {
        height = depth_height;
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_height_scale;
        if (reference_scale)
        {
            ref_height_scale = reference_scale->GetDepthHeightScale(depth_index - 1);
        }
        else
        {
            ref_height_scale = 1.0;
        }

        //Calculate and set height to fit depth_height
        height = depth_height / ref_height_scale;
    }
}


Size2DNew RefSize2DNewNew::GetUniValue() const
{
    return GetDepthValue(numeric_limits<unsigned int>::max());
}
double RefSize2DNewNew::GetUniWidth() const
{
    return GetDepthWidth(numeric_limits<unsigned int>::max());
}
double RefSize2DNewNew::GetUniHeight() const
{
    return GetDepthHeight(numeric_limits<unsigned int>::max());
}

void RefSize2DNewNew::SetValueToFitUniValue(const Size2DNew uni_value)
{
    SetValueToFitDepthValue(numeric_limits<unsigned int>::max(), uni_value);
}
void RefSize2DNewNew::SetValueToFitUniWidth(const double uni_width)
{
    SetValueToFitDepthWidth(numeric_limits<unsigned int>::max(), uni_width);
}
void RefSize2DNewNew::SetValueToFitUniHeight(const double uni_height)
{
    SetValueToFitDepthHeight(numeric_limits<unsigned int>::max(), uni_height);
}


unsigned int RefSize2DNewNew::GetDepthIndex(const RefScale2DNewNew* const depth_pointer) const
{
    const bool depth_pointer_nullptr = (depth_pointer == nullptr);

    unsigned int repeats = 1;
    const RefScale2DNewNew* temp_depth_pointer = reference_scale;
    while (true)
    {
        if (repeats == numeric_limits<unsigned int>::max())
        {
            cerr << "depth_pointer not found!! In this case, this is most likely due to a \"loop\" in the reference chain.\n";
            throw;
        }
        if ((temp_depth_pointer == nullptr) && !depth_pointer_nullptr)
        {
            cerr << "depth_pointer not found!! In this case, this is most likely because depth_pointer was simply not present in the reference chain provided.\n";
            throw;
        }

        if (temp_depth_pointer == depth_pointer)
        {
            return repeats;
        }

        temp_depth_pointer = temp_depth_pointer->reference_scale;
        repeats++;
    }
}

Size2DNew RefSize2DNewNew::GetDepthValue(const RefScale2DNewNew* const depth_pointer) const
{
    return GetDepthValue(GetDepthIndex(depth_pointer));
}
double RefSize2DNewNew::GetDepthWidth(const RefScale2DNewNew* const depth_pointer) const
{
    return GetDepthWidth(GetDepthIndex(depth_pointer));
}
double RefSize2DNewNew::GetDepthHeight(const RefScale2DNewNew* const depth_pointer) const
{
    return GetDepthHeight(GetDepthIndex(depth_pointer));
}

void RefSize2DNewNew::SetValueToFitDepthValue(const RefScale2DNewNew* const depth_pointer, const Size2DNew depth_value)
{
    SetValueToFitDepthValue(GetDepthIndex(depth_pointer), depth_value);
}
void RefSize2DNewNew::SetValueToFitDepthWidth(const RefScale2DNewNew* const depth_pointer, const double depth_width)
{
    SetValueToFitDepthWidth(GetDepthIndex(depth_pointer), depth_width);
}
void RefSize2DNewNew::SetValueToFitDepthHeight(const RefScale2DNewNew* const depth_pointer, const double depth_height)
{
    SetValueToFitDepthHeight(GetDepthIndex(depth_pointer), depth_height);
}




// -------------  RefRotation2DNewNew  -------------

RefRotation2DNewNew::RefRotation2DNewNew() {}
RefRotation2DNewNew::RefRotation2DNewNew(const double i_radians) : radians(i_radians) {}
RefRotation2DNewNew::RefRotation2DNewNew(const double i_radians, const RefRotation2DNewNew* const i_reference_rotation, const RefTotalFlip* const i_reference_total_flip) : radians(i_radians), reference_rotation(i_reference_rotation), reference_total_flip(i_reference_total_flip) {}


Rotation2DNew RefRotation2DNewNew::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return { radians };
    }
    else
    {
        //Deal with nullptr reference_rotation
        double ref_radians;
        if (reference_rotation)
        {
            ref_radians = reference_rotation->GetDepthValue(depth_index - 1).radians;
        }
        else
        {
            ref_radians = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and return dereferenced value
        if (ref_total_flip.flip_horizontally == ref_total_flip.flip_vertically)
        {
            return { radians + ref_radians };
        }
        else
        {
            return { -radians + ref_radians };
        }
    }
}
void RefRotation2DNewNew::SetValueToFitDepthValue(const unsigned int depth_index, const Rotation2DNew depth_value)
{
    if (depth_index == 0)
    {
        radians = depth_value.radians;
    }
    else
    {
        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDepthValue(depth_index - 1).radians;
        }
        else
        {
            ref_rotation = 1.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate the new value of v
        if (ref_total_flip.flip_horizontally == ref_total_flip.flip_vertically)
        {
            radians = -depth_value.radians + ref_rotation;
        }
        else
        {
            radians = depth_value.radians + ref_rotation;
        }
    }
}

Rotation2DNew RefRotation2DNewNew::GetUniValue() const
{
    return GetDepthValue(numeric_limits<unsigned int>::max());
}
void RefRotation2DNewNew::SetValueToFitUniValue(const Rotation2DNew uni_value)
{
    SetValueToFitDepthValue(numeric_limits<unsigned int>::max(), uni_value);
}

unsigned int RefRotation2DNewNew::GetDepthIndex(const RefRotation2DNewNew* const depth_pointer) const
{
    const bool depth_pointer_nullptr = (depth_pointer == nullptr);

    unsigned int repeats = 0;
    const RefRotation2DNewNew* temp_depth_pointer = this;
    while (true)
    {
        if (repeats == numeric_limits<unsigned int>::max())
        {
            cerr << "depth_pointer not found!! In this case, this is most likely due to a \"loop\" in the reference chain.\n";
            throw;
        }
        if ((temp_depth_pointer == nullptr) && !depth_pointer_nullptr)
        {
            cerr << "depth_pointer not found!! In this case, this is most likely because depth_pointer was simply not present in the reference chain provided.\n";
            throw;
        }

        if (temp_depth_pointer == depth_pointer)
        {
            return repeats;
        }

        temp_depth_pointer = temp_depth_pointer->reference_rotation;
        repeats++;
    }
}
Rotation2DNew RefRotation2DNewNew::GetDepthValue(const RefRotation2DNewNew* const depth_pointer) const
{
    return GetDepthValue(GetDepthIndex(depth_pointer));
}
void RefRotation2DNewNew::SetValueToFitDepthValue(const RefRotation2DNewNew* const depth_pointer, const Rotation2DNew depth_value)
{
    SetValueToFitDepthValue(GetDepthIndex(depth_pointer), depth_value);
}




// -------------  RefPoint2DNewNew  -------------

RefPoint2DNewNew::RefPoint2DNewNew() {}
RefPoint2DNewNew::RefPoint2DNewNew(const double i_x, const double i_y) : x(i_x), y(i_y) {}
RefPoint2DNewNew::RefPoint2DNewNew(const double i_x, const double i_y, const RefPoint2DNewNew* const i_reference_point, const RefScale2DNewNew* const i_reference_scale, const RefRotation2DNewNew* const i_reference_rotation, const RefTotalFlip* const i_reference_total_flip) : x(i_x), y(i_y), reference_point(i_reference_point), reference_scale(i_reference_scale), reference_rotation(i_reference_rotation), reference_total_flip(i_reference_total_flip) {}



Point2DNew RefPoint2DNewNew::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return { x, y };
    }
    else
    {
        //Deal with nullptr reference_point
        Point2DNew ref_point;
        if (reference_point)
        {
            ref_point = reference_point->GetDepthValue(depth_index - 1);
        }

        //Deal with nullptr reference_scale and depth_rd_contdition (stops dereferencing 
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }

        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDepthValue(depth_index - 1).radians;
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and return dereferenced value
        const double flipped_x = x * ((-2.0 * ref_total_flip.flip_horizontally) + 1.0);
        const double flipped_y = y * ((-2.0 * ref_total_flip.flip_vertically) + 1.0);

        if (ref_rotation == 0.0)
        {
            return { (flipped_x * ref_scale.width_scale) + ref_point.x, (flipped_y * ref_scale.height_scale) + ref_point.y };
        }
        else
        {
            const double scaled_x_distance = flipped_x * ref_scale.width_scale;
            const double scaled_y_distance = flipped_y * ref_scale.height_scale;

            const double scaled_distance = sqrt((scaled_x_distance * scaled_x_distance) + (scaled_y_distance * scaled_y_distance));

            if (scaled_distance == 0.0)
            {
                return { ref_point.x, ref_point.y };
            }
            else
            {
                //If flipped_y is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is
                double ref_rotation_sign;
                if (flipped_y >= 0.0)
                {
                    ref_rotation_sign = 1.0;
                }
                else
                {
                    ref_rotation_sign = -1.0;
                }
                const double uni_non_added_x = cos(acos(scaled_x_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;

                //If flipped_x is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is.
                if (flipped_x >= 0.0)
                {
                    ref_rotation_sign = 1.0;
                }
                else
                {
                    ref_rotation_sign = -1.0;
                }
                const double uni_non_added_y = sin(asin(scaled_y_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;

                return { uni_non_added_x + ref_point.x, uni_non_added_y + ref_point.y };
            }
        }
    }
}
double RefPoint2DNewNew::GetDepthX(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return x;
    }
    else
    {
        //Deal with nullptr reference_point
        double ref_point;
        if (reference_point)
        {
            ref_point = reference_point->GetDepthX(depth_index - 1);
        }
        else
        {
            ref_point = 0.0;
        }

        //Deal with nullptr reference_scale
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }

        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDepthValue(depth_index - 1).radians;
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and return dereferenced value
        const Point2DNew flipped_v = { x * ((-2.0 * ref_total_flip.flip_horizontally) + 1.0), y * ((-2.0 * ref_total_flip.flip_vertically) + 1.0) };

        if (ref_rotation == 0.0)
        {
            return (flipped_v.x * ref_scale.width_scale) + ref_point;
        }
        else
        {
            const double scaled_x_distance = flipped_v.x * ref_scale.width_scale;
            const double scaled_y_distance = flipped_v.y * ref_scale.height_scale;

            const double scaled_distance = sqrt((scaled_x_distance * scaled_x_distance) + (scaled_y_distance * scaled_y_distance));

            if (scaled_distance == 0.0)
            {
                return ref_point;
            }
            else
            {
                double ref_rotation_sign;
                //If flipped_v.y is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is
                if (flipped_v.y >= 0.0)
                {
                    ref_rotation_sign = 1.0;
                }
                else
                {
                    ref_rotation_sign = -1.0;
                }
                const double uni_non_added_x = cos(acos(scaled_x_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;
                return uni_non_added_x + ref_point;
            }
        }
    }
}
double RefPoint2DNewNew::GetDepthY(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return x;
    }
    else
    {
        //Deal with nullptr reference_point
        double ref_point;
        if (reference_point)
        {
            ref_point = reference_point->GetDepthY(depth_index - 1);
        }
        else
        {
            ref_point = 0.0;
        }

        //Deal with nullptr reference_scale
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }

        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDepthValue(depth_index - 1).radians;
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and return dereferenced value
        const Point2DNew flipped_v = { x * ((-2.0 * ref_total_flip.flip_horizontally) + 1.0), y * ((-2.0 * ref_total_flip.flip_vertically) + 1.0) };

        if (ref_rotation == 0.0)
        {
            return (flipped_v.y * ref_scale.height_scale) + ref_point;
        }
        else
        {
            const double scaled_x_distance = flipped_v.x * ref_scale.width_scale;
            const double scaled_y_distance = flipped_v.y * ref_scale.height_scale;

            const double scaled_distance = sqrt((scaled_x_distance * scaled_x_distance) + (scaled_y_distance * scaled_y_distance));

            if (scaled_distance == 0.0)
            {
                return ref_point;
            }
            else
            {
                double ref_rotation_sign;
                //If flipped_v.x is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is
                if (flipped_v.x >= 0.0)
                {
                    ref_rotation_sign = 1.0;
                }
                else
                {
                    ref_rotation_sign = -1.0;
                }
                const double uni_non_added_y = sin(asin(scaled_y_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;
                return uni_non_added_y + ref_point;
            }
        }
    }
}

void RefPoint2DNewNew::SetValueToFitDepthValue(const unsigned int depth_index, const Point2DNew depth_value)
{
    if (depth_index == 0)
    {
        x = depth_value.x;
        y = depth_value.y;
    }
    else
    {
        //Deal with nullptr reference_point
        Point2DNew ref_point;
        if (reference_point)
        {
            ref_point = reference_point->GetDepthValue(depth_index - 1);
        }

        //Deal with nullptr reference_scale
        Scale2DNew ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDepthValue(depth_index - 1);
        }

        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDepthValue(depth_index - 1).radians;
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and set dereferenced value
        const double flipped_x = (-2.0 * ref_total_flip.flip_horizontally) + 1.0;
        const double flipped_y = (-2.0 * ref_total_flip.flip_vertically) + 1.0;

        if (ref_rotation == 0.0)
        {
            x = ((depth_value.x - ref_point.x) / ref_scale.width_scale) * flipped_x;
            y = ((depth_value.y - ref_point.y) / ref_scale.height_scale) * flipped_y;
        }
        else
        {
            const double R = sqrt(pow(depth_value.x - ref_point.x, 2.0) + pow(depth_value.y - ref_point.y, 2.0));
            const double theta = atan2(depth_value.y - ref_point.y, depth_value.x - ref_point.x);

            x = (R * cos(theta + ref_rotation) / ref_scale.width_scale) * flipped_x;
            y = (R * sin(theta + ref_rotation) / ref_scale.height_scale) * flipped_y;
        }
    }
}
//Moves point HORIZONTALLY (on the plane defined by depth_index) to fit depth_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
void RefPoint2DNewNew::SetValueToFitDepthX(const unsigned int depth_index, const double depth_x)
{
    cerr << "This function is not defined yet, sorry :( (void RefPoint2DNewNew::SetValueToFitDepthX(const unsigned int depth_index, const double depth_x))";
    throw;
}
//Moves point VERTICALLY (on the plane defined by depth_index) to fit depth_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
void RefPoint2DNewNew::SetValueToFitDepthY(const unsigned int depth_index, const double depth_x)
{
    cerr << "This function is not defined yet, sorry :( (void RefPoint2DNewNew::SetValueToFitDepthY(const unsigned int depth_index, const double depth_x))";
    throw;
}


Point2DNew RefPoint2DNewNew::GetUniValue() const
{
    return GetDepthValue(numeric_limits<unsigned int>::max());
}
double RefPoint2DNewNew::GetUniX() const
{
    return GetDepthX(numeric_limits<unsigned int>::max());
}
double RefPoint2DNewNew::GetUniY() const
{
    return GetDepthY(numeric_limits<unsigned int>::max());
}

void RefPoint2DNewNew::SetValueToFitUniValue(const Point2DNew uni_value)
{
    SetValueToFitDepthValue(numeric_limits<unsigned int>::max(), uni_value);
}
//Moves point HORIZONTALLY to fit uni_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
void RefPoint2DNewNew::SetValueToFitUniX(const double uni_x)
{
    SetValueToFitDepthX(numeric_limits<unsigned int>::max(), uni_x);
}
//Moves point VERTICALLY to fit uni_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
void RefPoint2DNewNew::SetValueToFitUniY(const double uni_y)
{
    SetValueToFitDepthY(numeric_limits<unsigned int>::max(), uni_y);
}


unsigned int RefPoint2DNewNew::GetDepthIndex(const RefPoint2DNewNew* const depth_pointer) const
{
    const bool depth_pointer_nullptr = (depth_pointer == nullptr);

    unsigned int repeats = 0;
    const RefPoint2DNewNew* temp_depth_pointer = this;
    while (true)
    {
        if (repeats == numeric_limits<unsigned int>::max())
        {
            cerr << "depth_pointer not found!! In this case, this is most likely due to a \"loop\" in the reference chain.\n";
            throw;
        }
        if ((temp_depth_pointer == nullptr) && !depth_pointer_nullptr)
        {
            cerr << "depth_pointer not found!! In this case, this is most likely because depth_pointer was simply not present in the reference chain provided.\n";
            throw;
        }

        if (temp_depth_pointer == depth_pointer)
        {
            return repeats;
        }

        temp_depth_pointer = temp_depth_pointer->reference_point;
        repeats++;
    }
}

Point2DNew RefPoint2DNewNew::GetDepthValue(const RefPoint2DNewNew* const depth_pointer) const
{
    return GetDepthValue(GetDepthIndex(depth_pointer));
}
double RefPoint2DNewNew::GetDepthX(const RefPoint2DNewNew* const depth_pointer) const
{
    return GetDepthX(GetDepthIndex(depth_pointer));
}
double RefPoint2DNewNew::GetDepthY(const RefPoint2DNewNew* const depth_pointer) const
{
    return GetDepthY(GetDepthIndex(depth_pointer));
}

void RefPoint2DNewNew::SetValueToFitDepthValue(const RefPoint2DNewNew* const depth_pointer, const Point2DNew depth_value)
{
    SetValueToFitDepthValue(GetDepthIndex(depth_pointer), depth_value);
}
//Moves point HORIZONTALLY (on the plane defined by depth_pointer) to fit depth_x. If rotation is not 0 or pi, this function WILL ALSO CHANGE Y (very spooky). Also if rotation is pi/2 or 3pi/2, x won't change.
void RefPoint2DNewNew::SetValueToFitDepthX(const RefPoint2DNewNew* const depth_pointer, const double depth_x)
{
    SetValueToFitDepthX(GetDepthIndex(depth_pointer), depth_x);
}
//Moves point VERTICALLY (on the plane defined by depth_pointer) to fit depth_y. If rotation is not 0 or pi, this function WILL ALSO CHANGE X (very spooky). Also if rotation is pi/2 or 3pi/2, y won't change.
void RefPoint2DNewNew::SetValueToFitDepthY(const RefPoint2DNewNew* const depth_pointer, const double depth_y)
{
    SetValueToFitDepthY(GetDepthIndex(depth_pointer), depth_y);
}









// -------------  RefRectangle90  -------------
/*
RefRectangle90::RefRectangle90() {}
RefRectangle90::RefRectangle90(const RefPoint2DNewest i_pos) : pos(i_pos) {}
RefRectangle90::RefRectangle90(const RefPoint2DNewest i_pos, const Size2DNew i_unscaled_size) : pos(i_pos), unscaled_size(i_unscaled_size) {}
RefRectangle90::RefRectangle90(const RefPoint2DNewest i_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering) : pos(i_pos), unscaled_size(i_unscaled_size), centering(i_centering) {}
RefRectangle90::RefRectangle90(const RefPoint2DNewest i_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const RefTransformations90 i_transformations) : pos(i_pos), unscaled_size(i_unscaled_size), centering(i_centering), transformations(i_transformations) {}
RefRectangle90::RefRectangle90(const RefRectangle90* const reference_rectangle, const Point2DNew i_non_ref_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const Transformations90 i_non_ref_transformations) : pos(i_non_ref_pos, &reference_rectangle->pos, TransformationsPointer(&reference_rectangle->transformations)), unscaled_size(i_unscaled_size), centering(i_centering), transformations(i_non_ref_transformations, TransformationsPointer(&reference_rectangle->transformations)) {}
RefRectangle90::RefRectangle90(const RefRectangleNewest* const reference_rectangle, const Point2DNew i_non_ref_pos, const Size2DNew i_unscaled_size, const Centering2DNew i_centering, const Transformations90 i_non_ref_transformations) : pos(i_non_ref_pos, &reference_rectangle->pos, TransformationsPointer(&reference_rectangle->transformations)), unscaled_size(i_unscaled_size), centering(i_centering), transformations(i_non_ref_transformations, TransformationsPointer(&reference_rectangle->transformations)) {}



Rectangle90 RefRectangle90::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return Rectangle90(Point2DNew(pos.x, pos.y), unscaled_size, centering, Transformations90(transformations.rotation, transformations.scale, transformations.flip));
    }
    else
    {
        return Rectangle90(pos.GetDepthValue(depth_index), unscaled_size, centering, transformations.GetDepthValue90(depth_index));
    }
}
Rectangle90 RefRectangle90::GetUniValue() const
{
    return Rectangle90(pos.GetUniValue(), unscaled_size, centering, transformations.GetUniValue90());
}

Quad RefRectangle90::GetUniQuad() const
{
    return GetDepthQuad(numeric_limits<unsigned int>::max());
}
Quad RefRectangle90::GetDepthQuad(const unsigned int depth_index) const
{
    return Quad(GetDepthCorner(CornerEnum::TOP_RIGHT, depth_index), GetDepthCorner(CornerEnum::BOTTOM_RIGHT, depth_index), GetDepthCorner(CornerEnum::BOTTOM_LEFT, depth_index), GetDepthCorner(CornerEnum::TOP_LEFT, depth_index));
}

double RefRectangle90::GetDepthEdge(const DirectionEnum edge, const unsigned int depth_index) const
{
    switch (transformations.reference_transformations.GetDepthState(depth_index))
    {
    case TransformationsPointerState::NEITHER_ARE_ACTIVE:
        return GetDepthValue(0).GetEdge(edge);

    case TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE:
        return GetDepthValue(depth_index).GetEdge(edge);

    case TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE:
        cout << "WARNING: depth_rectangle_90 may have RectangleNewest references, leading to unexpected results. Sent by double RefRectangle90::GetDepthEdge(const DirectionEnum edge, const unsigned int depth_index) const.\n";
        return GetDepthValue(depth_index).GetEdge(edge);
    }
}
void RefRectangle90::SetDepthEdge(const DirectionEnum edge, const double target_depth_coord, const unsigned int depth_index)
{
    Rectangle90 depth_rectangle_90;


    switch (transformations.reference_transformations.GetDepthState(depth_index))
    {
    case TransformationsPointerState::NEITHER_ARE_ACTIVE:
        depth_rectangle_90 = GetDepthValue(0);
        break;

    case TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE:
        depth_rectangle_90 = GetDepthValue(depth_index);
        break;

    case TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE:
        cout << "WARNING: depth_rectangle_90 may have RectangleNewest references, leading to unexpected results. Sent by void RefRectangle90::SetDepthEdge(const DirectionEnum edge, const double target_depth_coord, const unsigned int depth_index).\n";
        depth_rectangle_90 = GetDepthValue(depth_index);
        break;
    }



    const EdgeData edge_data = GetEdgeData(edge, depth_rectangle_90.transformations.rotation, depth_rectangle_90.transformations.flip);

    double subtract_one_double = edge_data.GetSubtractOneDouble();

    double flip_double = edge_data.GetFlipDouble();

    if (edge_data.y_axis)
    {
        pos.y = target_depth_coord - ((unscaled_size.height * depth_rectangle_90.transformations.scale.height_scale) * ((centering.y_centering + subtract_one_double) / 2.0) * flip_double);
    }
    else
    {
        pos.x = target_depth_coord - ((unscaled_size.width * depth_rectangle_90.transformations.scale.width_scale) * ((centering.x_centering + subtract_one_double) / 2.0) * flip_double);
    }
}

Point2DNew RefRectangle90::GetDepthCorner(const CornerEnum corner, const unsigned int depth_index) const
{
    switch (transformations.reference_transformations.GetDepthState(depth_index))
    {
    case TransformationsPointerState::NEITHER_ARE_ACTIVE:
        return GetDepthValue(0).GetCorner(corner);

    case TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE:
        return GetDepthValue(depth_index).GetCorner(corner);

    case TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE:
        cout << "WARNING: depth_rectangle_90 may have RectangleNewest references, leading to unexpected results. Sent by Point2D RefRectangle90::GetDepthCorner(const CornerEnum corner, const unsigned int depth_index) const.\n";
        return GetDepthValue(depth_index).GetCorner(corner);
    }
}
void RefRectangle90::SetDepthCorner(const CornerEnum corner, const Point2DNew target_depth_point, const unsigned int depth_index)
{
    Rectangle90 depth_rectangle_90;
    switch (transformations.reference_transformations.GetDepthState(depth_index))
    {
    case TransformationsPointerState::NEITHER_ARE_ACTIVE:
        depth_rectangle_90 = GetDepthValue(0);
        break;

    case TransformationsPointerState::TRANSFORMATIONS90_POINTER_IS_ACTIVE:
        depth_rectangle_90 = GetDepthValue(depth_index);
        break;

    case TransformationsPointerState::TRANSFORMATIONS_POINTER_IS_ACTIVE:
        cout << "WARNING: depth_rectangle_90 may have RectangleNewest references, leading to unexpected results. Sent by void RefRectangle90::SetDepthEdge(const DirectionEnum edge, const double target_depth_coord, const unsigned int depth_index).\n";
        depth_rectangle_90 = GetDepthValue(depth_index);
        break;
    }


    DirectionEnum x_dir;
    DirectionEnum y_dir;
    switch (corner)
    {
    case CornerEnum::TOP_RIGHT:
        x_dir = DirectionEnum::RIGHT;
        y_dir = DirectionEnum::TOP;
        break;
    case CornerEnum::BOTTOM_RIGHT:
        x_dir = DirectionEnum::RIGHT;
        y_dir = DirectionEnum::BOTTOM;
        break;
    case CornerEnum::BOTTOM_LEFT:
        x_dir = DirectionEnum::LEFT;
        y_dir = DirectionEnum::BOTTOM;
        break;
    case CornerEnum::TOP_LEFT:
        x_dir = DirectionEnum::LEFT;
        y_dir = DirectionEnum::TOP;
        break;
    }

    //Set x_dir edge
    {
        const EdgeData edge_data = GetEdgeData(x_dir, depth_rectangle_90.transformations.rotation, depth_rectangle_90.transformations.flip);
        double subtract_one_double = edge_data.GetSubtractOneDouble();
        double flip_double = edge_data.GetFlipDouble();

        if (edge_data.y_axis)
        {
            pos.y = target_depth_point.y - ((unscaled_size.height * depth_rectangle_90.transformations.scale.height_scale) * ((centering.y_centering + subtract_one_double) / 2.0) * flip_double);
        }
        else
        {
            pos.x = target_depth_point.x - ((unscaled_size.width * depth_rectangle_90.transformations.scale.width_scale) * ((centering.x_centering + subtract_one_double) / 2.0) * flip_double);
        }
    }


    //Set y_dir edge
    {
        const EdgeData edge_data = GetEdgeData(y_dir, depth_rectangle_90.transformations.rotation, depth_rectangle_90.transformations.flip);
        double subtract_one_double = edge_data.GetSubtractOneDouble();
        double flip_double = edge_data.GetFlipDouble();

        if (edge_data.y_axis)
        {
            pos.y = target_depth_point.y - ((unscaled_size.height * depth_rectangle_90.transformations.scale.height_scale) * ((centering.y_centering + subtract_one_double) / 2.0) * flip_double);
        }
        else
        {
            pos.x = target_depth_point.x - ((unscaled_size.width * depth_rectangle_90.transformations.scale.width_scale) * ((centering.x_centering + subtract_one_double) / 2.0) * flip_double);
        }
    }
}


Size2DNew RefRectangle90::GetScaledSize() const
{
    return { GetScaledWidth(), GetScaledHeight() };
}
double RefRectangle90::GetScaledWidth() const
{
    return (unscaled_size.width * transformations.scale.width_scale);
}
double RefRectangle90::GetScaledHeight() const
{
    return (unscaled_size.height * transformations.scale.height_scale);
}

void RefRectangle90::SetScaledSize(const Size2DNew scaled_size)
{
    SetScaledWidth(scaled_size.width);
    SetScaledHeight(scaled_size.height);
}
void RefRectangle90::SetScaledWidth(const double scaled_width)
{
    unscaled_size.width = (scaled_width / transformations.scale.width_scale);
}
void RefRectangle90::SetScaledHeight(const double scaled_height)
{
    unscaled_size.height = (scaled_height / transformations.scale.height_scale);
}


void RefRectangle90::SetReference(const RefRectangle90* const reference_rectangle)
{
    pos.reference_point = &reference_rectangle->pos;
    pos.reference_transformations.SetPointer(&reference_rectangle->transformations);

    transformations.reference_transformations.SetPointer(&reference_rectangle->transformations);
}
void RefRectangle90::SetReference(const RefRectangleNewest* const reference_rectangle)
{
    pos.reference_point = &reference_rectangle->pos;
    pos.reference_transformations.SetPointer(&reference_rectangle->transformations);

    transformations.reference_transformations.SetPointer(&reference_rectangle->transformations);
}
*/




// -------------  RefRectangleNewNew  -------------

RectangleNew RefRectangleNewNew::GetRectangleNew() const
{
    return {
        pos.GetUniValue(),
        { unscaled_size.width, unscaled_size.height },
        scale.GetUniValue(),
        centering,
        rotation.GetUniValue(),
        total_flip.GetUniValue()
    };
}

Point2DNew RefRectangleNewNew::GetUniCorner(const CornerEnum corner) const
{
    Point2DNew temp_point;
    switch (corner)
    {
    case CornerEnum::TOP_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_RIGHT:
        temp_point.x = unscaled_size.width * ((centering.x_centering + 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::BOTTOM_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering - 1.0) / 2.0);
        break;
    case CornerEnum::TOP_LEFT:
        temp_point.x = unscaled_size.width * ((centering.x_centering - 1.0) / 2.0);
        temp_point.y = unscaled_size.height * ((centering.y_centering + 1.0) / 2.0);
        break;
    }

    const RefPoint2DNewNew temp_ref_point(temp_point.x, temp_point.y, &pos, &scale, &rotation, &total_flip);

    return temp_ref_point.GetUniValue();
}
Point2DNew RefRectangleNewNew::GetDepthCorner(const unsigned int depth_index, const CornerEnum corner) const
{
    return Point2DNew();
}

void RefRectangleNewNew::SetReference(RefRectangleNewNew* const reference_rectangle)
{
    pos.reference_point = &reference_rectangle->pos;
    pos.reference_scale = &reference_rectangle->scale;
    pos.reference_rotation = &reference_rectangle->rotation;
    pos.reference_total_flip = &reference_rectangle->total_flip;

    unscaled_size.reference_scale = &reference_rectangle->scale;

    scale.reference_scale = &reference_rectangle->scale;
    
    rotation.reference_rotation = &reference_rectangle->rotation;
    rotation.reference_total_flip = &reference_rectangle->total_flip;

    total_flip.reference_total_flip = &reference_rectangle->total_flip;
}





























// -------------  RefDoubleNew  -------------

RefDoubleNew::RefDoubleNew() : v{ 0.0 } {}
RefDoubleNew::RefDoubleNew(vector<double> param_v) : v(param_v) {}
RefDoubleNew::~RefDoubleNew()
{
    //Nothin
}




// ------------- VIRTUAL FUNCTIONS -------------

vector<double> RefDoubleNew::GetDereferencedValue(const unsigned int depth_index) const
{
    return v;
}
double RefDoubleNew::GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const
{
    return v[v_index];
}
void RefDoubleNew::SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value)
{
    v = new_value;
}
void RefDoubleNew::SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value)
{
    v[v_index] = new_indexed_value;
}




// ---------- IMPORTANT FUNCTIONS ----------

vector<double> RefDoubleNew::GetUniValue() const
{
    return GetDereferencedValue(numeric_limits<unsigned int>::max());
}
void RefDoubleNew::SetUniValue(const vector<double> uni_value)
{
    SetDereferencedValue(numeric_limits<unsigned int>::max(), uni_value);
}

double RefDoubleNew::GetUniIndexedValue(const size_t v_index) const
{
    return GetDereferencedIndexedValue(numeric_limits<unsigned int>::max(), v_index);
}
void RefDoubleNew::SetUniIndexedValue(const size_t v_index, const double uni_indexed_value)
{
    SetDereferencedIndexedValue(numeric_limits<unsigned int>::max(), v_index, uni_indexed_value);
}




// ---------- SIGNIFICANTLY LESS IMPORTANT FUNCTIONS ----------

vector<double> RefDoubleNew::GetDepthValue(const unsigned int depth_index) const
{
    return GetDereferencedValue(depth_index);
}
double RefDoubleNew::GetDepthIndexedValue(const unsigned int depth_index, const size_t v_index) const
{
    return GetDereferencedIndexedValue(depth_index, v_index);
}
void RefDoubleNew::SetDepthValue(const unsigned int depth_index, const vector<double> depth_value)
{
    SetDereferencedValue(depth_index, depth_value);
}
void RefDoubleNew::SetDepthIndexedValue(const unsigned int depth_index, const size_t v_index, const double depth_indexed_value)
{
    SetDereferencedIndexedValue(depth_index, v_index, depth_indexed_value);
}

/*
vector<double> RefDoubleNew::GetReverseDepthValue(const unsigned int reverse_depth_index) const
{
    unsigned int ladder_length = 0;

    while (true)
    {
        
    }
}
double RefDoubleNew::GetReverseDepthIndexedValue(const unsigned int reverse_depth_index, const size_t v_index) const
{

}
void RefDoubleNew::SetReverseDepthValue(const unsigned int depth_index, const vector<double> depth_value)
{

}
void RefDoubleNew::SetReverseDepthIndexedValue(const unsigned int depth_index, const size_t v_index, const double depth_indexed_value)
{

}
*/

/*
vector<double> RefDoubleNew::GetDepthValue(const RefDoubleNew* const depth_rd) const
{
    return GetDereferencedValue(numeric_limits<unsigned int>::max(), depth_rd);
}
double RefDoubleNew::GetDepthIndexedValue(const RefDoubleNew* const depth_rd, const size_t v_index) const
{
    return GetDereferencedIndexedValue(numeric_limits<unsigned int>::max(), depth_rd, v_index);
}
void RefDoubleNew::SetDepthValue(const RefDoubleNew* const depth_rd, const vector<double> depth_value)
{
    SetDereferencedValue(numeric_limits<unsigned int>::max(), depth_rd, depth_value);
}
void RefDoubleNew::SetDepthIndexedValue(const RefDoubleNew* const depth_rd, const size_t v_index, const double depth_value)
{
    SetDereferencedIndexedValue(numeric_limits<unsigned int>::max(), depth_rd, v_index, depth_value);
}
*/






// -------------  RefPoint2DNew  -------------

RefPoint2DNew::RefPoint2DNew() : RefDoubleNew({ 0.0, 0.0 }) {}
RefPoint2DNew::RefPoint2DNew(const double x, const double y) : RefDoubleNew({ x, y }) {}
RefPoint2DNew::RefPoint2DNew(const double x, const double y, RefDoubleNew* const i_reference_point, RefDoubleNew* const i_reference_scale, RefDoubleNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip) : RefDoubleNew({ x, y }), reference_point(i_reference_point), reference_scale(i_reference_scale), reference_rotation(i_reference_rotation), reference_total_flip(i_reference_total_flip) {}

vector<double> RefPoint2DNew::GetDereferencedValue(const unsigned int depth_index) const
{
    //Deal with invalid v
    if (v.size() != size_t(2))
    {
        cerr << "v.size() was not 2!! v of an instance of RefPoint2DNew should have 2 values (x and y)\n";
        throw;
    }

    if (depth_index == 0)
    {
        return v;
    }
    else
    {
        //Deal with nullptr reference_point
        vector<double> ref_point;
        if (reference_point)
        {
            ref_point = reference_point->GetDereferencedValue(depth_index - 1);
        }
        else
        {
            ref_point = { 0.0, 0.0 };
        }

        //Deal with nullptr reference_scale and depth_rd_contdition (stops dereferencing 
        vector<double> ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDereferencedValue(depth_index - 1);
        }
        else
        {
            ref_scale = { 1.0, 1.0 };
        }

        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDereferencedIndexedValue(depth_index - 1, 0);
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }
        

        //Calculate and return dereferenced value
        const double flipped_v_0 = v[0] * ((-2.0 * ref_total_flip.flip_horizontally) + 1.0);
        const double flipped_v_1 = v[1] * ((-2.0 * ref_total_flip.flip_vertically) + 1.0);

        if (ref_rotation == 0.0)
        {
            return { (flipped_v_0 * ref_scale[0]) + ref_point[0], (flipped_v_1 * ref_scale[1]) + ref_point[1] };
        }
        else
        {
            const double scaled_x_distance = flipped_v_0 * ref_scale[0];
            const double scaled_y_distance = flipped_v_1 * ref_scale[1];

            const double scaled_distance = sqrt((scaled_x_distance * scaled_x_distance) + (scaled_y_distance * scaled_y_distance));

            if (scaled_distance == 0.0)
            {
                return { ref_point[0], ref_point[1] };
            }
            else
            {
                //If v[1] is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is
                double ref_rotation_sign;
                if (flipped_v_1 >= 0.0)
                {
                    ref_rotation_sign = 1.0;
                }
                else
                {
                    ref_rotation_sign = -1.0;
                }
                const double uni_non_added_x = cos(acos(scaled_x_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;
                
                //If v[0] is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is.
                if (flipped_v_0 >= 0.0)
                {
                    ref_rotation_sign = 1.0;
                }
                else
                {
                    ref_rotation_sign = -1.0;
                }
                const double uni_non_added_y = sin(asin(scaled_y_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;

                return { uni_non_added_x + ref_point[0], uni_non_added_y + ref_point[1] };
            }
        }
    }
}
double RefPoint2DNew::GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const
{
    //Deal with invalid v_index
    if (v_index >= size_t(2))
    {
        cerr << "v_index was too high!! The v_index passed for an instance of RefPoint2DNew cannot be higher than 1. v[0] = x;  v[1] = y\n";
        throw;
    }

    //Deal with invalid v
    if (v.size() != size_t(2))
    {
        cerr << "v.size() was not 2!! v of an instance of RefPoint2DNew should have 2 values (x and y)\n";
        throw;
    }

    if (depth_index == 0)
    {
        return v[v_index];
    }
    else
    {
        //Deal with nullptr reference_point
        double ref_point;
        if (reference_point)
        {
            ref_point = reference_point->GetDereferencedIndexedValue(depth_index - 1, v_index);
        }
        else
        {
            ref_point = 0.0;
        }

        //Deal with nullptr reference_scale
        vector<double> ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDereferencedValue(depth_index - 1);
        }
        else
        {
            ref_scale = { 1.0, 1.0 };
        }

        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDereferencedIndexedValue(depth_index - 1, 0);
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and return dereferenced value
        const vector<double> flipped_v = { v[0] * ((-2.0 * ref_total_flip.flip_horizontally) + 1.0), v[1] * ((-2.0 * ref_total_flip.flip_vertically) + 1.0) };

        if (ref_rotation == 0.0)
        {
            return (flipped_v[v_index] * ref_scale[v_index]) + ref_point;
        }
        else
        {
            const double scaled_x_distance = flipped_v[v_index] * ref_scale[0];
            const double scaled_y_distance = flipped_v[v_index] * ref_scale[1];

            const double scaled_distance = sqrt((scaled_x_distance * scaled_x_distance) + (scaled_y_distance * scaled_y_distance));

            if (scaled_distance == 0.0)
            {
                return ref_point;
            }
            else
            {
                double ref_rotation_sign;
                if (v_index == 0)
                {
                    //If flipped_v[1] is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is
                    if (flipped_v[1] >= 0.0)
                    {
                        ref_rotation_sign = 1.0;
                    }
                    else
                    {
                        ref_rotation_sign = -1.0;
                    }
                    const double uni_non_added_x = cos(acos(scaled_x_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;
                    return uni_non_added_x + ref_point;
                }
                else
                {
                    //If flipped_v[0] is positive, subtract ref_rotation, otherwise, add. I'm not exactly sure why it is needed (I didn't bother to figure it out), but it is
                    if (flipped_v[0] >= 0.0)
                    {
                        ref_rotation_sign = 1.0;
                    }
                    else
                    {
                        ref_rotation_sign = -1.0;
                    }
                    const double uni_non_added_y = sin(asin(scaled_y_distance / scaled_distance) - (ref_rotation * ref_rotation_sign)) * scaled_distance;
                    return uni_non_added_y + ref_point;
                }
            }
        }
    }
}
void RefPoint2DNew::SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value)
{
    //Deal with invalid new_value
    if (new_value.size() != size_t(2))
    {
        cerr << "new_value.size() was not 2!! The new_value passed for an instance of RefPoint2DNew must have 2 elements (x and y)\n";
        throw;
    }

    if (depth_index == 0)
    {
        v = new_value;
    }
    else
    {
        //Deal with nullptr reference_point
        vector<double> ref_point;
        if (reference_point)
        {
            ref_point = reference_point->GetDereferencedValue(depth_index - 1);
        }
        else
        {
            ref_point = { 0.0, 0.0 };
        }

        //Deal with nullptr reference_scale
        vector<double> ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDereferencedValue(depth_index - 1);
        }
        else
        {
            ref_scale = { 1.0, 1.0 };
        }

        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDereferencedIndexedValue(depth_index - 1, 0);
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and set dereferenced value
        const double flipped_0 = (-2.0 * ref_total_flip.flip_horizontally) + 1.0;
        const double flipped_1 = (-2.0 * ref_total_flip.flip_vertically) + 1.0;

        if (ref_rotation == 0.0)
        {
            v = {
                ((new_value[0] - ref_point[0]) / ref_scale[0]) * flipped_0,
                ((new_value[1] - ref_point[1]) / ref_scale[1]) * flipped_1
            };
        }
        else
        {
            const double R = sqrt(pow(new_value[0] - ref_point[0], 2.0) + pow(new_value[1] - ref_point[1], 2.0));
            const double theta = atan2(new_value[1] - ref_point[1], new_value[0] - ref_point[0]);

            v = {
                (R * cos(theta + ref_rotation) / ref_scale[0]) * flipped_0,
                (R * sin(theta + ref_rotation) / ref_scale[1]) * flipped_1
            };
        }
    }
}
void RefPoint2DNew::SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value)
{

}

Point2DNew RefPoint2DNew::GetPoint2DNew() const
{
    const vector<double> temp_ref_point = GetUniValue();
    return { temp_ref_point[0], temp_ref_point[1] };
}

/*
// ----- RefSize2DNew -----

RefSize2DNew::RefSize2DNew() : RefDoubleNew({ 100.0, 100.0 }) {}
RefSize2DNew::RefSize2DNew(const double width, const double height) : RefDoubleNew({ width, height}) {}
RefSize2DNew::RefSize2DNew(const double width, const double height, RefDoubleNew* const i_reference_scale) : RefDoubleNew({ width, height }), reference_scale(i_reference_scale) {}

vector<double> RefSize2DNew::GetDerefencedValue() const
{
    //Deal with invalid v
    if (v.size() != size_t(2))
    {
        cerr << "v.size() was not 2!! v of an instance of RefSize2DNew should have 2 values (width and height)\n";
        throw;
    }

    //Deal with invalid or nullptr reference_scale
    vector<double> ref_scale;
    if (reference_scale)
    {
        ref_scale = reference_scale->GetDerefencedValue();

        if (ref_scale.size() != size_t(2))
        {
            cerr << "ref_scale.size() was not 2!! ref_scale should have 2 values (width_scale and height_scale)\n";
            throw;
        }
    }
    else
    {
        ref_scale = { 1.0, 1.0 };
    }


    //Calculate and return dereferenced value
    return { v[0] * ref_scale[0], v[1] * ref_scale[1] };
}
void RefSize2DNew::SetReferencedValue(const vector<double> uni_v)
{

}

Size2DNew RefSize2DNew::GetSize2DNew() const
{
    const vector<double> temp_ref_size = GetDerefencedValue();
    return { temp_ref_size[0], temp_ref_size[1] };
}
*/



// -------------  RefScale2DNew  -------------

RefScale2DNew::RefScale2DNew() : RefDoubleNew({ 1.0, 1.0 }) {}
RefScale2DNew::RefScale2DNew(const double width_scale, const double height_scale) : RefDoubleNew({ width_scale, height_scale }) {}
RefScale2DNew::RefScale2DNew(const double width_scale, const double height_scale, RefDoubleNew* const i_reference_scale) : RefDoubleNew({ width_scale, height_scale }), reference_scale(i_reference_scale) {}

vector<double> RefScale2DNew::GetDereferencedValue(const unsigned int depth_index) const
{
    //Deal with invalid v
    if (v.size() != size_t(2))
    {
        cerr << "v.size() was not 2!! v of an instance of RefScale2DNew should have 2 values (width_scale and height_scale)\n";
        throw;
    }

    if (depth_index == 0)
    {
        return v;
    }
    else
    {
        //Deal with nullptr reference_scale
        vector<double> ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDereferencedValue(depth_index - 1);
        }
        else
        {
            ref_scale = { 1.0, 1.0 };
        }


        //Calculate and return dereferenced value
        return { v[0] * ref_scale[0], v[1] * ref_scale[1] };
    }
}
double RefScale2DNew::GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const
{
    //Deal with invalid v_index
    if (v_index >= size_t(2))
    {
        cerr << "v_index was too high!! The v_index passed for an instance of RefScale2DNew cannot be higher than 1. v[0] = width_scale;  v[1] = height_scale\n";
        throw;
    }

    //Deal with invalid v
    if (v.size() != size_t(2))
    {
        cerr << "v.size() was not 2!! v of an instance of RefScale2DNew should have 2 values (width_scale and height_scale)\n";
        throw;
    }

    if (depth_index == 0)
    {
        return v[v_index];
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDereferencedIndexedValue(depth_index - 1, v_index);
        }
        else
        {
            ref_scale = 1.0;
        }


        //Calculate and return dereferenced value
        return v[v_index] * ref_scale;
    }
}
void RefScale2DNew::SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value)
{
    //Deal with invalid new_value
    if (new_value.size() != size_t(2))
    {
        cerr << "new_value.size() was not 2!! The new_value passed for an instance of RefScale2DNew must have 2 elements (width_scale and height_scale)\n";
        throw;
    }

    if (depth_index == 0)
    {
        v = new_value;
    }
    else
    {
        //Deal with nullptr reference_scale
        vector<double> ref_scale;
        if (reference_scale)
        {
            ref_scale = reference_scale->GetDereferencedValue(depth_index - 1);
        }
        else
        {
            ref_scale = { 1.0, 1.0 };
        }

        v = { new_value[0] / ref_scale[0], new_value[1] / ref_scale[1] };
    }
}
void RefScale2DNew::SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value)
{

}

Scale2DNew RefScale2DNew::GetScale2DNew() const
{
    const vector<double> temp_ref_scale = GetUniValue();
    return { temp_ref_scale[0], temp_ref_scale[1] };
}




// -------------  RefRotation2DNew  -------------

RefRotation2DNew::RefRotation2DNew() : RefDoubleNew({ 0.0 }) {}
RefRotation2DNew::RefRotation2DNew(const double rotation) : RefDoubleNew({ rotation }) {}
RefRotation2DNew::RefRotation2DNew(const double rotation, RefDoubleNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip) : RefDoubleNew({ rotation }), reference_rotation(i_reference_rotation), reference_total_flip(i_reference_total_flip) {}

vector<double> RefRotation2DNew::GetDereferencedValue(const unsigned int depth_index) const
{
    //Deal with invalid v
    if (v.size() != size_t(1))
    {
        cerr << "v.size() was not 1!! v of an instance of RefRotation2DNew should have 1 value (rotation in radians)\n";
        throw;
    }

    if (depth_index == 0)
    {
        return v;
    }
    else
    {
        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDereferencedValue(depth_index - 1)[0];
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and return dereferenced value
        if (ref_total_flip.flip_horizontally == ref_total_flip.flip_vertically)
        {
            return { v[0] + ref_rotation };
        }
        else
        {
            return { -v[0] + ref_rotation };
        }
    }
}
double RefRotation2DNew::GetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index) const
{
    //Deal with invalid v_index
    if (v_index != size_t(0))
    {
        cerr << "v_index was too high!! The v_index passed for an instance of RefRotation2DNew MUST be 0. v[0] = rotation (in radians)\n";
        throw;
    }

    //Deal with invalid v
    if (v.size() != size_t(1))
    {
        cerr << "v.size() was not 1!! v of an instance of RefRotation2DNew should have 1 value (rotation in radians)\n";
        throw;
    }

    if (depth_index == 0)
    {
        return v[0];
    }
    else
    {
        //Deal with nullptr reference_scale
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDereferencedIndexedValue(depth_index - 1, 0);
        }
        else
        {
            ref_rotation = 0.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate and return dereferenced value
        if (ref_total_flip.flip_horizontally == ref_total_flip.flip_vertically)
        {
            return (v[0] + ref_rotation);
        }
        else
        {
            return (-v[0] + ref_rotation);
        }
    }
}
void RefRotation2DNew::SetDereferencedValue(const unsigned int depth_index, const vector<double> new_value)
{
    //Deal with invalid new_value
    if (new_value.size() != size_t(1))
    {
        cerr << "new_value.size() was not 1!! The new_value passed for an instance of RefRotation2DNew must have 1 element (rotation in radians)\n";
        throw;
    }

    if (depth_index == 0)
    {
        v = new_value;
    }
    else
    {
        //Deal with nullptr reference_rotation
        double ref_rotation;
        if (reference_rotation)
        {
            ref_rotation = reference_rotation->GetDereferencedIndexedValue(depth_index - 1, 0);
        }
        else
        {
            ref_rotation = 1.0;
        }

        //Deal with nullptr reference_total_flip
        TotalFlip ref_total_flip;
        if (reference_total_flip)
        {
            ref_total_flip = reference_total_flip->GetDereferencedValue(depth_index - 1, nullptr);
        }


        //Calculate the new value of v
        if (ref_total_flip.flip_horizontally == ref_total_flip.flip_vertically)
        {
            v = { -new_value[0] + ref_rotation };
        }
        else
        {
            v = { new_value[0] - ref_rotation };
        }
    }
}
void RefRotation2DNew::SetDereferencedIndexedValue(const unsigned int depth_index, const size_t v_index, const double new_indexed_value)
{

}

Rotation2DNew RefRotation2DNew::GetRotation2DNew() const
{
    const vector<double> temp_ref_rotation = GetUniValue();
    return { temp_ref_rotation[0] };
}




// -------------  RefRectangleNew  -------------

RectangleNew RefRectangleNew::GetRectangleNew() const
{
    return { pos.GetPoint2DNew(), unscaled_size, scale.GetScale2DNew(), centering, rotation.GetRotation2DNew(), total_flip.GetUniValue() };
}

void RefRectangleNew::SetReference(RefRectangleNew* const reference_rectangle)
{
    pos.reference_point = &reference_rectangle->pos;
    pos.reference_scale = &reference_rectangle->scale;
    pos.reference_rotation = &reference_rectangle->rotation;

    scale.reference_scale = &reference_rectangle->scale;

    rotation.reference_rotation = &reference_rectangle->rotation;

    total_flip.reference_total_flip = &reference_rectangle->total_flip;
    pos.reference_total_flip = &reference_rectangle->total_flip;
    rotation.reference_total_flip = &reference_rectangle->total_flip;
}
















double RD::Other(const double temp_depth_value, const double pathi) const
{
    return 0.0;
}
double RD::InverseOther(const double temp_depth_value, const double depth_value) const
{
    return 0.0;
}

double RD::GetDepthValue(const size_t depth) const
{
    if (depth != 0)
    {
        vector<const RD*> path;
        const RD* current_rd = this;
        for (size_t i = 0; (i < depth) && (current_rd->reference_type != unsigned char(0)) && (current_rd->reference); i++)
        {
            path.push_back(current_rd);
            current_rd = current_rd->reference;
        }

        double temp_depth_value = current_rd->v;
        for (size_t i = path.size() - size_t(1); i != numeric_limits<size_t>::max(); i--)
        {
            switch (path[i]->reference_type)
            {
            case 0:
                temp_depth_value = path[i]->v;
                break;
            case 1:
                temp_depth_value += path[i]->v;
                break;
            case 2:
                temp_depth_value -= path[i]->v;
                break;
            case 3:
                temp_depth_value *= path[i]->v;
                break;
            case 4:
                temp_depth_value /= path[i]->v;
                break;
            case 5:
                temp_depth_value = pow(temp_depth_value, path[i]->v);
                break;
            case 6:
                temp_depth_value = log(temp_depth_value) / log(path[i]->v);
                break;
            case 7:
                temp_depth_value = Other(temp_depth_value, path[i]->v);
                break;
            default:
                throw std::runtime_error("reference_type out of range! (accepted values are 0-4)");
                break;
            }
        }

        return temp_depth_value;
    }
    else
    {
        return v;
    }
}
double RD::GetUniValue() const
{
    return GetDepthValue(numeric_limits<size_t>::max());
}

void RD::SetDepthValue(const double depth_value, const size_t depth)
{
    if (reference && (reference_type != unsigned char(0)) && (depth != size_t(0)))
    {
        const double temp_depth_value = reference->GetDepthValue(depth - size_t(1));

        switch (reference_type)
        {
        case 0:
            v = depth_value;
            break;
        case 1:
            v = depth_value - temp_depth_value;
            break;
        case 2:
            v = depth_value + temp_depth_value;
            break;
        case 3:
            v = depth_value / temp_depth_value;
            break;
        case 4:
            v = depth_value * temp_depth_value;
            break;
        case 5:
            v = log(depth_value) / log(temp_depth_value);
            break;
        case 6:
            v = pow(temp_depth_value, 1.0 / depth_value);
            break;
        case 7:
            v = InverseOther(temp_depth_value, depth_value);
            break;
        }
    }
    else
    {
        v = depth_value;
    }
}
void RD::SetUniValue(const double uni_value)
{
    SetDepthValue(uni_value, numeric_limits<size_t>::max());
}



/*

double ARD::GetDepthValue(const size_t depth) const
{
    double temp_depth_value = v;
    const ARD* current_ard = this;
    for (size_t i = 0; i < depth; i++)
    {
        current_ard = current_ard->reference;
        if (current_ard)
        {
            temp_depth_value += current_ard->v;
        }
        else
        {
            break;
        }
    }

    return temp_depth_value;
}
double ARD::GetUniValue() const
{
    double temp_uni_value = v;
    const ARD* current_ard = this;

    for (size_t i = 0; true; i++)
    {
        if (i >= 10000)
        {
            cout << "Exceeded ARD reference limit (10000). To ignore this failsafe, use ARD::GetUniValueUnrestricted(), however, there's like a 99.9% chance this is a bug in which an ARD ladder loops in on itself. Sent by ARD::GetUniValue()." << endl;
            break;
        }

        current_ard = current_ard->reference;
        if (current_ard)
        {
            temp_uni_value += current_ard->v;
        }
        else
        {
            break;
        }
    }

    return temp_uni_value;
}
double ARD::GetUniValueUnrestricted() const
{
    double temp_uni_value = v;
    const ARD* current_ard = this;

    for (size_t i = 0; true; i++)
    {
        current_ard = current_ard->reference;
        if (current_ard)
        {
            temp_uni_value += current_ard->v;
        }
        else
        {
            break;
        }
    }

    return temp_uni_value;
}
void ARD::SetDepthValue(const double depth_value, const size_t depth)
{
    double temp_value = depth_value;
    const ARD* current_ard = this;
    for (size_t i = 0; i < depth; i++)
    {
        current_ard = current_ard->reference;
        if (current_ard)
        {
            temp_value -= current_ard->v;
        }
        else
        {
            break;
        }
    }

    v = temp_value;
}
void ARD::SetUniValue(const double uni_value)
{
    double temp_value = uni_value;
    const ARD* current_ard = this;

    for (size_t i = 0; true; i++)
    {
        if (i >= 10000)
        {
            cout << "Exceeded ARD reference limit (10000). To ignore this failsafe, use ARD::SetUniValueUnrestricted(), however, there's like a 99.9% chance this is a bug in which an ARD ladder loops in on itself. Sent by ARD::SetUniValue()." << endl;
            break;
        }

        current_ard = current_ard->reference;
        if (current_ard)
        {
            temp_value -= current_ard->v;
        }
        else
        {
            break;
        }
    }

    v = temp_value;
}
void ARD::SetUniValueUnrestricted(const double uni_value)
{
    double temp_value = uni_value;
    const ARD* current_ard = this;

    for (size_t i = 0; true; i++)
    {
        current_ard = current_ard->reference;
        if (current_ard)
        {
            temp_value -= current_ard->v;
        }
        else
        {
            break;
        }
    }

    v = temp_value;
}

double MRD::GetDepthValue(const size_t depth) const
{
    double temp_depth_value = v;
    const MRD* current_mrd = this;
    for (size_t i = 0; i < depth; i++)
    {
        current_mrd = current_mrd->reference;
        if (current_mrd)
        {
            temp_depth_value *= current_mrd->v;
        }
        else
        {
            break;
        }
    }

    return temp_depth_value;
}
double MRD::GetUniValue() const
{
    double temp_uni_value = v;
    const MRD* current_mrd = this;

    for (size_t i = 0; true; i++)
    {
        if (i >= 10000)
        {
            cout << "Exceeded MRD reference limit (10000). To ignore this failsafe, use MRD::GetUniValueUnrestricted(), however, there's like a 99.9% chance this is a bug in which an MRD ladder loops in on itself. Sent by MRD::GetUniValue()." << endl;
            break;
        }

        current_mrd = current_mrd->reference;
        if (current_mrd)
        {
            temp_uni_value *= current_mrd->v;
        }
        else
        {
            break;
        }
    }

    return temp_uni_value;
}
double MRD::GetUniValueUnrestricted() const
{
    double temp_uni_value = v;
    const MRD* current_mrd = this;

    for (size_t i = 0; true; i++)
    {
        current_mrd = current_mrd->reference;
        if (current_mrd)
        {
            temp_uni_value *= current_mrd->v;
        }
        else
        {
            break;
        }
    }

    return temp_uni_value;
}
void MRD::SetDepthValue(const double depth_value, const size_t depth)
{
    double temp_value = depth_value;
    const MRD* current_mrd = this;
    for (size_t i = 0; i < depth; i++)
    {
        current_mrd = current_mrd->reference;
        if (current_mrd)
        {
            temp_value /= current_mrd->v;
        }
        else
        {
            break;
        }
    }

    v = temp_value;
}
void MRD::SetUniValue(const double uni_value)
{
    double temp_value = uni_value;
    const MRD* current_mrd = this;

    for (size_t i = 0; true; i++)
    {
        if (i >= 10000)
        {
            cout << "Exceeded MRD reference limit (10000). To ignore this failsafe, use MRD::SetUniValueUnrestricted(), however, there's like a 99.9% chance this is a bug in which an MRD ladder loops in on itself. Sent by MRD::SetUniValue()." << endl;
            break;
        }

        current_mrd = current_mrd->reference;
        if (current_mrd)
        {
            temp_value -= current_mrd->v;
        }
        else
        {
            break;
        }
    }

    v = temp_value;
}
void MRD::SetUniValueUnrestricted(const double uni_value)
{
    double temp_value = uni_value;
    const MRD* current_mrd = this;

    for (size_t i = 0; true; i++)
    {
        current_mrd = current_mrd->reference;
        if (current_mrd)
        {
            temp_value -= current_mrd->v;
        }
        else
        {
            break;
        }
    }

    v = temp_value;
}







V2::V2() : x(0.0), y(0.0) {}
V2::V2(double x, double y) : x(x), y(y) {}

*/









// ------------------------   LIST PROPERTIES FUNCTIONS   ------------------------

void Indent(const unsigned int indent_count)
{
    for (unsigned int i = 0; i < indent_count; i++)
    {
        cout << "    ";
    }
}

void LongNotationStart(const unsigned int indentation)
{
    cout << "{\n";
    Indent(indentation);
}
void LongNotationEnd(const unsigned int indentation, const bool end_on_new_line)
{
    cout << "\n";
    if (indentation > 1)
    {
        Indent(indentation - 1);
    }
    cout << "}";
    if (end_on_new_line)
    {
        cout << "\n";
    }
}

void ListProperties(const CornerEnum& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "*this: ";
        switch (obj)
        {
        case CornerEnum::TOP_RIGHT:
            cout << "top-right (0)";
            break;
        case CornerEnum::BOTTOM_RIGHT:
            cout << "bottom-right (1)";
            break;
        case CornerEnum::BOTTOM_LEFT:
            cout << "bottom-left (2)";
            break;
        case CornerEnum::TOP_LEFT:
            cout << "top-left (3)";
            break;
        default:
            cout << "[ERROR: corner_enum is INVALID] :( ";
            break;
        }

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{*this: ";
        switch (obj)
        {
        case CornerEnum::TOP_RIGHT:
            cout << "top-right (0)";
            break;
        case CornerEnum::BOTTOM_RIGHT:
            cout << "bottom-right (1)";
            break;
        case CornerEnum::BOTTOM_LEFT:
            cout << "bottom-left (2)";
            break;
        case CornerEnum::TOP_LEFT:
            cout << "top-left (3)";
            break;
        default:
            cout << "[ERROR: corner_enum is INVALID] :( ";
            break;
        }
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const DirectionEnum& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "*this: ";
        switch (obj)
        {
        case DirectionEnum::RIGHT:
            cout << "right (0)";
            break;
        case DirectionEnum::BOTTOM:
            cout << "bottom (1)";
            break;
        case DirectionEnum::LEFT:
            cout << "left (2)";
            break;
        case DirectionEnum::TOP:
            cout << "top (3)";
            break;
        default:
            cout << "[ERROR: direction_90 is INVALID] :( ";
            break;
        }

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{*this: ";
        switch (obj)
        {
        case DirectionEnum::RIGHT:
            cout << "right (0)";
            break;
        case DirectionEnum::BOTTOM:
            cout << "bottom (1)";
            break;
        case DirectionEnum::LEFT:
            cout << "left (2)";
            break;
        case DirectionEnum::TOP:
            cout << "top (3)";
            break;
        default:
            cout << "[ERROR: direction_90 is INVALID] :( ";
            break;
        }
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const RotationEnum& obj, const bool in_degrees, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "*this: ";
        switch (obj)
        {
        case RotationEnum::DEGREES_0:
            cout << (in_degrees ? "0 degrees (0)" : "ZERO_HALF_PI (0)");
            break;
        case RotationEnum::DEGREES_90:
            cout << (in_degrees ? "90 degrees (1)" : "ONE_HALF_PI (1)");
            break;
        case RotationEnum::DEGREES_180:
            cout << (in_degrees ? "180 degrees (2)" : "TWO_HALF_PI (2)");
            break;
        case RotationEnum::DEGREES_270:
            cout << (in_degrees ? "270 degrees (3)" : "THREE_HALF_PI (3)");
            break;
        default:
            cout << "[ERROR: rotation_90 is INVALID] :( ";
            break;
        }
        
        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{*this: ";
        switch (obj)
        {
        case RotationEnum::DEGREES_0:
            cout << (in_degrees ? "0 degrees (0)" : "ZERO_HALF_PI (0)");
            break;
        case RotationEnum::DEGREES_90:
            cout << (in_degrees ? "90 degrees (1)" : "ONE_HALF_PI (1)");
            break;
        case RotationEnum::DEGREES_180:
            cout << (in_degrees ? "180 degrees (2)" : "TWO_HALF_PI (2)");
            break;
        case RotationEnum::DEGREES_270:
            cout << (in_degrees ? "270 degrees (3)" : "THREE_HALF_PI (3)");
            break;
        default:
            cout << "[ERROR: rotation_90 is INVALID] :( ";
            break;
        }
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Flip90& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "flip_horizontally: " << (obj.flip_horizontally ? "true" : "false") << "\n";
        Indent(indentation);
        cout << "flip_vertically: " << (obj.flip_vertically ? "true" : "false");

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{flip_horizontally: " << (obj.flip_horizontally ? "true" : "false") << ", flip_vertically: " << (obj.flip_vertically ? "true" : "false") << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Scale90& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "width_scale: " << obj.width_scale << "\n";
        Indent(indentation);
        cout << "height_scale: " << obj.height_scale;

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{width_scale: " << obj.width_scale << ", height_scale: " << obj.height_scale << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Transformations90& obj, const bool rotations_in_degrees, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "rotation: ";
        ListProperties(obj.rotation, rotations_in_degrees, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "scale: ";
        ListProperties(obj.scale, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "flip: ";
        ListProperties(obj.flip, false, false); //Not long-notation, so indentation doesn't matter.

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{rotation: ";
        ListProperties(obj.rotation, rotations_in_degrees, false, false);
        cout << ",    scale: ";
        ListProperties(obj.scale, false, false);
        cout << ",    flip: ";
        ListProperties(obj.flip, false, false);
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const TotalFlip& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "flip_horizontally: " << obj.flip_horizontally << "\n";
        Indent(indentation);
        cout << "flip_vertically: " << obj.flip_vertically;

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{flip_horizontally: " << obj.flip_horizontally << ", flip_vertically: " << obj.flip_vertically << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Point2DNew& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "x: " << obj.x << "\n";
        Indent(indentation);
        cout << "y: " << obj.y;

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{x: " << obj.x << ", y: " << obj.y << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Scale2DNew& obj, const bool direction_offsets_in_degrees, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "width_scale: " << obj.width_scale << "\n";
        Indent(indentation);
        cout << "height_scale: " << obj.height_scale << "\n";
        Indent(indentation);
        direction_offsets_in_degrees ? (cout << "width_degree_offset (converted): " << SnapRadiansToDegrees(obj.width_radian_offset, 1) << "\n") : (cout << "width_radian_offset: " << obj.width_radian_offset << "\n");
        Indent(indentation);
        direction_offsets_in_degrees ? (cout << "height_degree_offset (converted): " << SnapRadiansToDegrees(obj.height_radian_offset, 1) << "\n") : (cout << "height_radian_offset: " << obj.height_radian_offset << "\n");

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{width_scale: " << obj.width_scale;
        cout << ", height_scale: " << obj.height_scale;
        direction_offsets_in_degrees ? (cout << ", width_degree_offset (converted): " << SnapRadiansToDegrees(obj.width_radian_offset, 1)) : (cout << ", width_radian_offset: " << obj.width_radian_offset);
        direction_offsets_in_degrees ? (cout << ", height_degree_offset (converted): " << SnapRadiansToDegrees(obj.height_radian_offset, 1)) : (cout << ", height_radian_offset: " << obj.height_radian_offset);
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Size2DNew& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "width: " << obj.width << "\n";
        Indent(indentation);
        cout << "height: " << obj.height;

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{width: " << obj.width << ", height: " << obj.height << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Centering2DNew& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "x_centering: " << obj.x_centering << "\n";
        Indent(indentation);
        cout << "y_centering: " << obj.y_centering;

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{x_centering: " << obj.x_centering << ", y_centering: " << obj.y_centering << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Offset2DNew& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "x_offset: " << obj.x_offset << "\n";
        Indent(indentation);
        cout << "y_offset: " << obj.y_offset;

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{x_offset: " << obj.x_offset << ", y_offset: " << obj.y_offset << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Rotation2DNew& obj, const bool in_degrees, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        in_degrees ? (cout << "degrees (converted): " << SnapRadiansToDegrees(obj.radians, 1)) : (cout << "radians: " << obj.radians);

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        in_degrees ? (cout << "{degrees (converted): " << SnapRadiansToDegrees(obj.radians, 1)) : (cout << "{radians: " << obj.radians);
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Transformations& obj, const bool rotations_in_degrees, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "rotation: ";
        ListProperties(obj.rotation, rotations_in_degrees, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "scale: ";
        ListProperties(obj.scale, rotations_in_degrees, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "total_flip: ";
        ListProperties(obj.total_flip, false, false); //Not long-notation, so indentation doesn't matter.

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{rotation: ";
        ListProperties(obj.rotation, rotations_in_degrees, false, false);
        cout << ", scale: ";
        ListProperties(obj.scale, rotations_in_degrees, false, false);
        cout << ", total_flip: ";
        ListProperties(obj.total_flip, false, false);
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const Quad& obj, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "top_right: ";
        ListProperties(obj.top_right, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "bottom_right: ";
        ListProperties(obj.bottom_right, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "bottom_left: ";
        ListProperties(obj.bottom_left, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "top_left: ";
        ListProperties(obj.top_left, false, false); //Not long-notation, so indentation doesn't matter.

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{top_right: ";
        ListProperties(obj.top_right, false, false);
        cout << ", bottom_right: ";
        ListProperties(obj.bottom_right, false, false);
        cout << ", bottom_left: ";
        ListProperties(obj.bottom_left, false, false);
        cout << ", top_left: ";
        ListProperties(obj.top_left, false, false);
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}
void ListProperties(const RectangleNewest& obj, const bool rotations_in_degrees, const bool end_on_new_line, const bool long_notation, const unsigned int indentation)
{
    if (long_notation)
    {
        LongNotationStart(indentation);

        cout << "pos: ";
        ListProperties(obj.pos, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "unscaled_size: ";
        ListProperties(obj.unscaled_size, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "centering: ";
        ListProperties(obj.centering, true, false); //Not long-notation, so indentation doesn't matter.

        Indent(indentation);
        cout << "transformations: ";
        ListProperties(obj.transformations, rotations_in_degrees, false, true, indentation + 1);

        LongNotationEnd(indentation, end_on_new_line);
    }
    else
    {
        cout << "{pos: ";
        ListProperties(obj.pos, false, false);
        cout << ", unscaled_size: ";
        ListProperties(obj.unscaled_size, false, false);
        cout << ", centering: ";
        ListProperties(obj.centering, false, false);
        cout << ", transformations: ";
        ListProperties(obj.transformations, rotations_in_degrees, false, false);
        cout << "}" << (end_on_new_line ? "\n" : "");
    }
}