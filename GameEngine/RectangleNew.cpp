#include "RectangleNew.h"

double SDL_RectWithRotation::GetDegrees() const
{
    return (radians * 180.0 / M_PI);
}
void SDL_RectWithRotation::SetWithDegrees(const double degrees)
{
    radians = degrees * M_PI / 180.0;
}



// -----------------   NON-REFERENCE STRUCTS   -----------------

TotalFlip::TotalFlip() {}
TotalFlip::TotalFlip(const bool i_flip_horizontally, const bool i_flip_vertically) : flip_horizontally(i_flip_horizontally), flip_vertically(i_flip_vertically) {}
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

Point2DNew::Point2DNew() {}
Point2DNew::Point2DNew(const double i_x, const double i_y) : x(i_x), y(i_y) {}

Scale2DNew::Scale2DNew() {}
Scale2DNew::Scale2DNew(const double i_width_scale, const double i_height_scale) : width_scale(i_width_scale), height_scale(i_height_scale) {}

Size2DNew::Size2DNew() {}
Size2DNew::Size2DNew(const double i_width, const double i_height) : width(i_width), height(i_height) {}

Centering2DNew::Centering2DNew() {}
Centering2DNew::Centering2DNew(const double i_x_centering, const double i_y_centering) : x_centering(i_x_centering), y_centering(i_y_centering) {}

Offset2DNew::Offset2DNew() {}
Offset2DNew::Offset2DNew(const double i_x_offset, const double i_y_offset) : x_offset(i_x_offset), y_offset(i_y_offset) {}

Rotation2DNew::Rotation2DNew() {}
Rotation2DNew::Rotation2DNew(const double i_radians) : radians(i_radians) {}
double Rotation2DNew::GetDegrees() const
{
    return (radians * 180.0 / M_PI);
}
void Rotation2DNew::SetWithDegrees(const double degrees)
{
    radians = degrees * M_PI / 180.0;
}






// -----------------   REFERENCE STRUCTS   -----------------

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




// -------------  RefScale2DNewNew  -------------

RefScale2DNewNew::RefScale2DNewNew() {}
RefScale2DNewNew::RefScale2DNewNew(const double i_width_scale, const double i_height_scale) : width_scale(i_width_scale), height_scale(i_height_scale) {}
RefScale2DNewNew::RefScale2DNewNew(const double i_width_scale, const double i_height_scale, RefScale2DNewNew* const i_reference_scale) : width_scale(i_width_scale), height_scale(i_height_scale), reference_scale(i_reference_scale) {}



Scale2DNew RefScale2DNewNew::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return { width_scale, height_scale };
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
        return { width_scale * ref_scale.width_scale, height_scale * ref_scale.height_scale };
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
RefSize2DNewNew::RefSize2DNewNew(const double i_width, const double i_height, RefScale2DNewNew* const i_reference_scale) : width(i_width), height(i_height), reference_scale(i_reference_scale) {}



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
RefRotation2DNewNew::RefRotation2DNewNew(const double i_radians, RefRotation2DNewNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip) : radians(i_radians), reference_rotation(i_reference_rotation), reference_total_flip(i_reference_total_flip) {}


Rotation2DNew RefRotation2DNewNew::GetDepthValue(const unsigned int depth_index) const
{
    if (depth_index == 0)
    {
        return radians;
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
RefPoint2DNewNew::RefPoint2DNewNew(const double i_x, const double i_y, RefPoint2DNewNew* const i_reference_point, RefScale2DNewNew* const i_reference_scale, RefRotation2DNewNew* const i_reference_rotation, RefTotalFlip* const i_reference_total_flip) : x(i_x), y(i_y), reference_point(i_reference_point), reference_scale(i_reference_scale), reference_rotation(i_reference_rotation), reference_total_flip(i_reference_total_flip) {}



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






// -----------------   NON REFERENCE RECTANGLENEW METHODS   -----------------

// -------- EDGE FUNCTIONS --------

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




// -------- SCALE FUNCTIONS --------

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




// -------- CENTERING/OFFSET FUNCTIONS --------

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
    return (GetScaledOffsetX() * scale.width_scale);
}
double RectangleNew::GetScaledOffsetY() const
{
    return (GetScaledOffsetY() * scale.height_scale);
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