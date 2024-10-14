#include "Engine.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <limits>

#define DEBUG_DATA_TEXT_BOX_MARGIN blank_camera->rect.base_size.width / 80.0

#define DEBUG_DATA_TEXT_COLOR_NAME 0, 0, 0, 255
#define DEBUG_DATA_TEXT_COLOR_SUB_NAME 100, 100, 100, 255

#define DEBUG_DATA_TEXT_COLOR_RIGID_CENTERING 44, 0, 190, 255
#define DEBUG_DATA_TEXT_COLOR_OTHER 149, 0, 190, 255
#define DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE 0, 181, 190, 255
#define DEBUG_DATA_TEXT_COLOR_POINT2D 10, 190, 0, 255
#define DEBUG_DATA_TEXT_COLOR_SIZE2D 190, 38, 0, 255

using namespace std;

std::string DoubleToString(double value, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    std::string str = ss.str();

    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') {
        str.pop_back();
    }

    return str;
}

std::string FloatToString(float value, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    std::string str = ss.str();

    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') {
        str.pop_back();
    }

    return str;
}

void Engine::MoveDebugCamera()
{
    if (input.w.pressed)
    {
        debug_camera->rect.pos.y += 10.0 * frame_factor * debug_camera->rect.GetUniHeightScale();
    }
    if (input.a.pressed)
    {
        debug_camera->rect.pos.x -= 10.0 * frame_factor * debug_camera->rect.GetUniWidthScale();
    }
    if (input.s.pressed)
    {
        debug_camera->rect.pos.y -= 10.0 * frame_factor * debug_camera->rect.GetUniHeightScale();
    }
    if (input.d.pressed)
    {
        debug_camera->rect.pos.x += 10.0 * frame_factor * debug_camera->rect.GetUniWidthScale();
    }

    if (debug_data_container_layer.active)
    {
        Size2D temp_size_scale = debug_camera->rect.GetUniSizeScale();
        debug_camera->rect.SetSizeWithUniSizeScale(Size2D{ temp_size_scale.width * pow(0.85, input.mouse_scroll_y), temp_size_scale.height * pow(0.85, input.mouse_scroll_y) });

        DeactivateMouseLayers(0, { &debug_data_container_layer });
    }
}

void Engine::BasicBasicDrawRectangle(Rectangle* param_rectangle, SDL_Color color, Camera* camera)
{
    SDL_Rect rect = RectangleToSDLRect(param_rectangle, camera);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
void Engine::BasicDrawRectangle(Rectangle* param_rectangle, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera)
{
    // -----------------   INITILIZE NECESSARY LOCAL VARIABLES   -----------------

    SDL_Rect sdl_rect;
    Rectangle temp_rectangle_data = *param_rectangle;






    // -----------------   INITIALIZE OPTIMIZING INFORMATION   -----------------

    const bool has_border = !(((right_border_scaled_size == 0.0) && (bottom_border_scaled_size == 0.0) && (left_border_scaled_size == 0.0) && (top_border_scaled_size == 0.0)));
    const bool has_invisible_border = (has_border && (border_color.a == 0));

    const bool has_shadow = !(((shadow_scaled_offset.x == 0.0) && (shadow_scaled_offset.y == 0.0)) || (shadow_color.a == 0));

    const bool has_fill = !((param_rectangle->size.width == 0.0) || (param_rectangle->size.height == 0.0) || (filling_color.a == 0));






    // -----------------   GENERATE BORDER_DELTA_SCALED_SIZE DATA IF APPLICABLE   -----------------

    double right_border_delta_scaled_size = 0.0;
    double left_border_delta_scaled_size = 0.0;
    double top_border_delta_scaled_size = 0.0;
    double bottom_border_delta_scaled_size = 0.0;

    double right_border_reverse_delta_scaled_size = 0.0;
    double left_border_reverse_delta_scaled_size = 0.0;
    double top_border_reverse_delta_scaled_size = 0.0;
    double bottom_border_reverse_delta_scaled_size = 0.0;

    if (has_border)
    {
        right_border_delta_scaled_size = right_border_scaled_size * ((double)right_border_centering.value / 2.0);
        left_border_delta_scaled_size = left_border_scaled_size * ((double)left_border_centering.value / 2.0);
        top_border_delta_scaled_size = top_border_scaled_size * ((double)top_border_centering.value / 2.0);
        bottom_border_delta_scaled_size = bottom_border_scaled_size * ((double)bottom_border_centering.value / 2.0);

        right_border_reverse_delta_scaled_size = right_border_delta_scaled_size - right_border_scaled_size;
        left_border_reverse_delta_scaled_size = left_border_delta_scaled_size - left_border_scaled_size;
        top_border_reverse_delta_scaled_size = top_border_delta_scaled_size - top_border_scaled_size;
        bottom_border_reverse_delta_scaled_size = bottom_border_delta_scaled_size - bottom_border_scaled_size;
    }






    // -----------------   GENERATE FILL DATA   -----------------

    const double temp_rect_uni_right = temp_rectangle_data.GetUniEdge({ 0 });
    const double temp_rect_uni_bottom = temp_rectangle_data.GetUniEdge({ 1 });
    const double temp_rect_uni_left = temp_rectangle_data.GetUniEdge({ 2 });
    const double temp_rect_uni_top = temp_rectangle_data.GetUniEdge({ 3 });

    double temp_ref_uni_width_scale;
    double temp_ref_uni_height_scale;

    if (temp_rectangle_data.reference_rectangle_data)
    {
        temp_ref_uni_width_scale = temp_rectangle_data.reference_rectangle_data->GetUniWidthScale();
        temp_ref_uni_height_scale = temp_rectangle_data.reference_rectangle_data->GetUniHeightScale();
    }
    else
    {
        temp_ref_uni_width_scale = 1.0;
        temp_ref_uni_height_scale = 1.0;
    }

    const double uni_fill_right = temp_rect_uni_right + (right_border_reverse_delta_scaled_size * temp_ref_uni_width_scale);
    const double uni_fill_bottom = temp_rect_uni_bottom - (bottom_border_reverse_delta_scaled_size * temp_ref_uni_height_scale);
    const double uni_fill_left = temp_rect_uni_left - (left_border_reverse_delta_scaled_size * temp_ref_uni_width_scale);
    const double uni_fill_top = temp_rect_uni_top + (top_border_reverse_delta_scaled_size * temp_ref_uni_height_scale);

    const int sdl_fill_right = UniXToSDLX(uni_fill_right, { 2 }, camera);
    const int sdl_fill_bottom = UniYToSDLY(uni_fill_bottom, { 0 }, camera);
    const int sdl_fill_left = UniXToSDLX(uni_fill_left, { 0 }, camera);
    const int sdl_fill_top = UniYToSDLY(uni_fill_top, { 2 }, camera);






    // -----------------   DRAW FILL IF APPLICABLE   -----------------

    if (has_fill)
    {
        sdl_rect = GetSDLRectWithEdges(sdl_fill_right, sdl_fill_bottom, sdl_fill_left, sdl_fill_top);

        SDL_SetRenderDrawColor(renderer, filling_color.r, filling_color.g, filling_color.b, filling_color.a);
        SDL_RenderFillRect(renderer, &sdl_rect);
    }






    // -----------------   GENERATE BORDER DATA IF APPLICABLE   -----------------

    if (has_border)
    {
        const double uni_border_right = temp_rect_uni_right + (right_border_delta_scaled_size * temp_ref_uni_width_scale);
        const double uni_border_bottom = temp_rect_uni_bottom - (bottom_border_delta_scaled_size * temp_ref_uni_height_scale);
        const double uni_border_left = temp_rect_uni_left - (left_border_delta_scaled_size * temp_ref_uni_width_scale);
        const double uni_border_top = temp_rect_uni_top + (top_border_delta_scaled_size * temp_ref_uni_height_scale);



        const int sdl_border_top_right = UniXToSDLX(uni_border_right, { 2 }, camera);
        const int sdl_border_top_bottom = sdl_fill_top - 1;
        const int sdl_border_top_left = UniXToSDLX(uni_border_left, { 0 }, camera);
        const int sdl_border_top_top = UniYToSDLY(uni_border_top, { 2 }, camera);

        const int sdl_border_bottom_right = UniXToSDLX(uni_border_right, { 2 }, camera);
        const int sdl_border_bottom_bottom = UniYToSDLY(uni_border_bottom, { 0 }, camera);
        const int sdl_border_bottom_left = UniXToSDLX(uni_border_left, { 0 }, camera);
        const int sdl_border_bottom_top = sdl_fill_bottom + 1;

        const int sdl_border_right_right = sdl_border_top_right;
        const int sdl_border_right_bottom = sdl_fill_bottom;
        const int sdl_border_right_left = sdl_fill_right + 1;
        const int sdl_border_right_top = sdl_fill_top;

        const int sdl_border_left_right = sdl_fill_left - 1;
        const int sdl_border_left_bottom = sdl_fill_bottom;
        const int sdl_border_left_left = sdl_border_top_left;
        const int sdl_border_left_top = sdl_fill_top;






        // -----------------   DRAW BORDER IF APPLICABLE   -----------------

        if (!has_invisible_border)
        {
            sdl_rect = GetSDLRectWithEdges(sdl_border_top_right, sdl_border_top_bottom, sdl_border_top_left, sdl_border_top_top);
            SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_border_bottom_right, sdl_border_bottom_bottom, sdl_border_bottom_left, sdl_border_bottom_top);
            SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_border_right_right, sdl_border_right_bottom, sdl_border_right_left, sdl_border_right_top);
            SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_border_left_right, sdl_border_left_bottom, sdl_border_left_left, sdl_border_left_top);
            SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);
        }






        // -----------------   GENERATE SHADOW DATA IF APPLICABLE   -----------------

        if (has_shadow)
        {
            const double uni_shadow_right = uni_border_right + (shadow_scaled_offset.x * temp_ref_uni_width_scale);
            const double uni_shadow_bottom = uni_border_bottom + (shadow_scaled_offset.y * temp_ref_uni_height_scale);
            const double uni_shadow_left = uni_border_left + (shadow_scaled_offset.x * temp_ref_uni_width_scale);
            const double uni_shadow_top = uni_border_top + (shadow_scaled_offset.y * temp_ref_uni_height_scale);



            const int sdl_shadow_top_right = UniXToSDLX(uni_shadow_right, { 2 }, camera);
            const int sdl_shadow_top_bottom = sdl_border_top_top - 1;
            const int sdl_shadow_top_left = UniXToSDLX(uni_shadow_left, { 0 }, camera);
            const int sdl_shadow_top_top = UniYToSDLY(uni_shadow_top, { 2 }, camera);

            const int sdl_shadow_bottom_right = UniXToSDLX(uni_shadow_right, { 2 }, camera);
            const int sdl_shadow_bottom_bottom = UniYToSDLY(uni_shadow_bottom, { 0 }, camera);
            const int sdl_shadow_bottom_left = UniXToSDLX(uni_shadow_left, { 0 }, camera);
            const int sdl_shadow_bottom_top = sdl_border_bottom_bottom + 1;

            const int sdl_shadow_right_right = UniXToSDLX(uni_shadow_right, { 2 }, camera);
            int sdl_shadow_right_bottom;
            if ((sdl_shadow_bottom_bottom - 1) <= sdl_border_bottom_bottom)
            {
                sdl_shadow_right_bottom = sdl_shadow_bottom_bottom - 1;
            }
            else
            {
                sdl_shadow_right_bottom = sdl_border_bottom_bottom;
            }
            const int sdl_shadow_right_left = sdl_border_right_right + 1;
            int sdl_shadow_right_top;
            if ((sdl_shadow_top_top + 1) >= sdl_border_top_top)
            {
                sdl_shadow_right_top = sdl_shadow_top_top + 1;
            }
            else
            {
                sdl_shadow_right_top = sdl_border_top_top;
            }

            const int sdl_shadow_left_right = sdl_border_left_left - 1;
            const int sdl_shadow_left_bottom = sdl_shadow_right_bottom;
            const int sdl_shadow_left_left = UniXToSDLX(uni_shadow_left, { 0 }, camera);
            const int sdl_shadow_left_top = sdl_shadow_right_top;






            // -----------------   DRAW SHADOW   -----------------

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_top_right, sdl_shadow_top_bottom, sdl_shadow_top_left, sdl_shadow_top_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_bottom_right, sdl_shadow_bottom_bottom, sdl_shadow_bottom_left, sdl_shadow_bottom_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_right_right, sdl_shadow_right_bottom, sdl_shadow_right_left, sdl_shadow_right_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_left_right, sdl_shadow_left_bottom, sdl_shadow_left_left, sdl_shadow_left_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);
        }
    }
    else
    {
        //(Uses the fill_rect data instead of border_rect data because there is no border in this case)
        // -----------------   GENERATE SHADOW DATA IF APPLICABLE   -----------------

        if (has_shadow)
        {
            const double uni_shadow_right = uni_fill_right + (shadow_scaled_offset.x * temp_ref_uni_width_scale);
            const double uni_shadow_bottom = uni_fill_bottom + (shadow_scaled_offset.y * temp_ref_uni_height_scale);
            const double uni_shadow_left = uni_fill_left + (shadow_scaled_offset.x * temp_ref_uni_width_scale);
            const double uni_shadow_top = uni_fill_top + (shadow_scaled_offset.y * temp_ref_uni_height_scale);



            const int sdl_shadow_top_right = UniXToSDLX(uni_shadow_right, { 2 }, camera);
            const int sdl_shadow_top_bottom = sdl_fill_top - 1;
            const int sdl_shadow_top_left = UniXToSDLX(uni_shadow_left, { 0 }, camera);
            const int sdl_shadow_top_top = UniYToSDLY(uni_shadow_top, { 2 }, camera);

            const int sdl_shadow_bottom_right = UniXToSDLX(uni_shadow_right, { 2 }, camera);
            const int sdl_shadow_bottom_bottom = UniYToSDLY(uni_shadow_bottom, { 0 }, camera);
            const int sdl_shadow_bottom_left = UniXToSDLX(uni_shadow_left, { 0 }, camera);
            const int sdl_shadow_bottom_top = sdl_fill_bottom + 1;

            const int sdl_shadow_right_right = UniXToSDLX(uni_shadow_right, { 2 }, camera);
            int sdl_shadow_right_bottom;
            if ((sdl_shadow_bottom_bottom - 1) <= sdl_fill_bottom)
            {
                sdl_shadow_right_bottom = sdl_shadow_bottom_bottom - 1;
            }
            else
            {
                sdl_shadow_right_bottom = sdl_fill_bottom;
            }
            const int sdl_shadow_right_left = sdl_fill_right + 1;
            int sdl_shadow_right_top;
            if ((sdl_shadow_top_top + 1) >= sdl_fill_top)
            {
                sdl_shadow_right_top = sdl_shadow_top_top + 1;
            }
            else
            {
                sdl_shadow_right_top = sdl_fill_top;
            }

            const int sdl_shadow_left_right = sdl_fill_left - 1;
            const int sdl_shadow_left_bottom = sdl_shadow_right_bottom;
            const int sdl_shadow_left_left = UniXToSDLX(uni_shadow_left, { 0 }, camera);
            const int sdl_shadow_left_top = sdl_shadow_right_top;






            // -----------------   DRAW SHADOW   -----------------

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_top_right, sdl_shadow_top_bottom, sdl_shadow_top_left, sdl_shadow_top_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_bottom_right, sdl_shadow_bottom_bottom, sdl_shadow_bottom_left, sdl_shadow_bottom_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_right_right, sdl_shadow_right_bottom, sdl_shadow_right_left, sdl_shadow_right_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);

            sdl_rect = GetSDLRectWithEdges(sdl_shadow_left_right, sdl_shadow_left_bottom, sdl_shadow_left_left, sdl_shadow_left_top);
            SDL_SetRenderDrawColor(renderer, shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);
            SDL_RenderFillRect(renderer, &sdl_rect);
        }
    }

    //All done :) (phew)
}
void Engine::BasicDrawRectangleScaledBorder(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera)
{
    BasicDrawRectangle(param_rectangle, filling_color, border_scaled_size, border_centering, border_scaled_size, border_centering, border_scaled_size, border_centering, border_scaled_size, border_centering, border_color, { 0.0, 0.0 }, { 0, 0, 0, 0 }, camera);
}
void Engine::BasicDrawRectangleScaledBorderScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera)
{
    BasicDrawRectangle(param_rectangle, filling_color, border_scaled_size, border_centering, border_scaled_size, border_centering, border_scaled_size, border_centering, border_scaled_size, border_centering, border_color, shadow_scaled_offset, shadow_color, camera);
}
void Engine::BasicDrawRectangleScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera)
{
    BasicDrawRectangle(param_rectangle, filling_color, 0.0, { 0 }, 0.0, { 0 }, 0.0, { 0 }, 0.0, { 0 }, { 0, 0, 0, 0 }, shadow_scaled_offset, shadow_color, camera);
}
void Engine::BasicDrawRectangleOutline(Rectangle* param_rectangle, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera)
{
    BasicDrawRectangle(param_rectangle, { 0, 0, 0, 0 }, border_scaled_size, border_centering, border_scaled_size, border_centering, border_scaled_size, border_centering, border_scaled_size, border_centering, border_color, { 0.0, 0.0 }, { 0, 0, 0, 0 }, camera);
}

void Engine::BasicDrawRectStructOne(RectStructOne* param_rect_struct_one, SDL_Color color, Camera* camera)
{
    SDL_Rect rect = RectStructOneToSDLRect(param_rect_struct_one, camera);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}


void Engine::ScaleDebugLabel(DebugLabel* const param_debug_label)
{
    //Create camera scale const doubles
    const double cam_width_scale = debug_camera->rect.GetWidthScale();
    const double cam_height_scale = debug_camera->rect.GetHeightScale();


    //Set size scale of text_box_data
    param_debug_label->text_box_data.parent_rectangle.SetSizeWithSizeScale({ param_debug_label->text_scale * cam_width_scale, param_debug_label->text_scale * cam_height_scale });

    //Create the label_rectangle_data (serves as the backdrop of the label. It includes margin)
    param_debug_label->rectangle.size.width = (param_debug_label->text_box_data.parent_rectangle.size.width) + (param_debug_label->scaled_margin_size * 2.0 * cam_width_scale);
    param_debug_label->rectangle.size.height = (param_debug_label->text_box_data.parent_rectangle.size.height) + (param_debug_label->scaled_margin_size * 2.0 * cam_height_scale);
    param_debug_label->rectangle.SetOffsetWithCentering({ 1.0, 1.0 }, 0);
}
void Engine::AlignDebugLabelAndPushbackToSavedLabelRects(DebugLabel* const param_debug_label)
{
    //Create camera scale const doubles
    const double cam_width_scale = debug_camera->rect.GetWidthScale();
    const double cam_height_scale = debug_camera->rect.GetHeightScale();

    //Generate rect_struct_one
    RectStructOne temp_label_rect_struct_one = RectangleToRectStructOne(&param_debug_label->rectangle);

    bool aligned_first_rect_struct_one_to_right = 0;
    bool aligned_first_rect_struct_one_to_bottom = 0;
    bool aligned_first_rect_struct_one_to_left = 0;
    bool aligned_first_rect_struct_one_to_top = 0;

    //Generate vector of every label not yet collided with
    vector<RectStructOne> temp_saved_label_rects = saved_label_rects;

    for (int j = 0; j < temp_saved_label_rects.size(); j++)
    {
        if (OverlapRectStructOneWithRectStructOne(&temp_label_rect_struct_one, &temp_saved_label_rects[j], 0))
        {
            //Initialize all diff values as the max
            double first_rect_struct_one_to_right_diff = DBL_MAX;
            double first_rect_struct_one_to_bottom_diff = DBL_MAX;
            double first_rect_struct_one_to_left_diff = DBL_MAX;
            double first_rect_struct_one_to_top_diff = DBL_MAX;

            //Defining all the diff values if applicable
            if (!aligned_first_rect_struct_one_to_left)
            {
                first_rect_struct_one_to_right_diff = (temp_saved_label_rects[j].uni_right_edge - temp_label_rect_struct_one.uni_left_edge);
            }
            if (!aligned_first_rect_struct_one_to_top)
            {
                first_rect_struct_one_to_bottom_diff = (temp_label_rect_struct_one.uni_top_edge - temp_saved_label_rects[j].uni_bottom_edge);
            }
            if (!aligned_first_rect_struct_one_to_right)
            {
                first_rect_struct_one_to_left_diff = (temp_label_rect_struct_one.uni_right_edge - temp_saved_label_rects[j].uni_left_edge);
            }
            if (!aligned_first_rect_struct_one_to_bottom)
            {
                first_rect_struct_one_to_top_diff = (temp_saved_label_rects[j].uni_top_edge - temp_label_rect_struct_one.uni_bottom_edge);
            }

            bool finished = 0;
            //Compares with all other diff variables to return whether or not first_rect_struct_one_to_right_diff is the highest value
            if (!(aligned_first_rect_struct_one_to_left || finished))
            {
                if ((first_rect_struct_one_to_right_diff <= first_rect_struct_one_to_bottom_diff) && (first_rect_struct_one_to_right_diff <= first_rect_struct_one_to_left_diff) && (first_rect_struct_one_to_right_diff <= first_rect_struct_one_to_top_diff))
                {
                    param_debug_label->rectangle.SetPosWithUniEdge(temp_saved_label_rects[j].uni_right_edge, { 2 });
                    aligned_first_rect_struct_one_to_right = 1;

                    finished = 1;
                }
            }
            if (!(aligned_first_rect_struct_one_to_top || finished))
            {
                if ((first_rect_struct_one_to_bottom_diff <= first_rect_struct_one_to_right_diff) && (first_rect_struct_one_to_bottom_diff <= first_rect_struct_one_to_left_diff) && (first_rect_struct_one_to_bottom_diff <= first_rect_struct_one_to_top_diff))
                {
                    param_debug_label->rectangle.SetPosWithUniEdge(temp_saved_label_rects[j].uni_bottom_edge, { 3 });
                    aligned_first_rect_struct_one_to_bottom = 1;

                    finished = 1;
                }
            }
            if (!(aligned_first_rect_struct_one_to_right || finished))
            {
                if ((first_rect_struct_one_to_left_diff <= first_rect_struct_one_to_right_diff) && (first_rect_struct_one_to_left_diff <= first_rect_struct_one_to_bottom_diff) && (first_rect_struct_one_to_left_diff <= first_rect_struct_one_to_top_diff))
                {
                    param_debug_label->rectangle.SetPosWithUniEdge(temp_saved_label_rects[j].uni_left_edge, { 0 });
                    aligned_first_rect_struct_one_to_left = 1;

                    finished = 1;
                }
            }
            if (!(aligned_first_rect_struct_one_to_bottom || finished))
            {
                param_debug_label->rectangle.SetPosWithUniEdge(temp_saved_label_rects[j].uni_top_edge, { 1 });
                aligned_first_rect_struct_one_to_top = 1;

                finished = 1;
            }

            temp_label_rect_struct_one = RectangleToRectStructOne(&param_debug_label->rectangle);

            temp_saved_label_rects.erase(temp_saved_label_rects.begin() + j);
            j = -1;
        }
    }

    param_debug_label->text_box_data.parent_rectangle.pos.x = param_debug_label->rectangle.pos.x + (param_debug_label->scaled_margin_size * cam_width_scale);
    param_debug_label->text_box_data.parent_rectangle.pos.y = param_debug_label->rectangle.pos.y + (param_debug_label->scaled_margin_size * cam_height_scale);

    //Add the current rect_struct_one to the saved_label_rects vector
    saved_label_rects.push_back(temp_label_rect_struct_one);
}

void Engine::UpdateDebugLabelPos(DebugLabel* const param_debug_label)
{
    ScaleDebugLabel(param_debug_label);

    param_debug_label->rectangle.pos.x = param_debug_label->describing_rectangle->GetUniEdge({ 2 });
    param_debug_label->rectangle.pos.y = param_debug_label->describing_rectangle->GetUniEdge({ 3 });

    AlignDebugLabelAndPushbackToSavedLabelRects(param_debug_label);
}
void Engine::UpdateDebugLabelPosWithTargetPos(DebugLabel* const param_debug_label, const Point2D param_bottom_left_point)
{
    ScaleDebugLabel(param_debug_label);

    param_debug_label->rectangle.pos.x = param_bottom_left_point.x;
    param_debug_label->rectangle.pos.y = param_bottom_left_point.y;

    AlignDebugLabelAndPushbackToSavedLabelRects(param_debug_label);
}
void Engine::BasicDrawDebugLabel(DebugLabel* const param_debug_label)
{
    BasicBasicDrawRectangle(&param_debug_label->rectangle, { 255, 255, 255, 180 }, debug_camera);
    BasicDrawTextBoxData(&param_debug_label->text_box_data, debug_camera);
}


void Engine::BasicDrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera)
{
    Rectangle temp_rectangle;

    temp_rectangle.base_size = param_size;
    temp_rectangle.SetSizeWithSizeScale({ 1.0, 1.0 });

    SDL_Rect rect = RectangleToSDLRect(&temp_rectangle, camera);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
void Engine::BasicDrawTexture(const Texture* const texture, const Camera* const camera, const Rectangle* const param_rectangle)
{
    SDL_Rect temp_rect = RectangleToSDLRect(param_rectangle, camera);

    if ((param_rectangle->flip.value == 0) && (param_rectangle->rotation == 0.0))
    {
        SDL_RenderCopy(renderer, texture->sdl_texture, NULL, &temp_rect);
    }
    else
    {
        SDL_Point sdl_center = RectangleToSDLCenterOfRotation(param_rectangle, camera);

        switch (param_rectangle->flip.value)
        {
        case 0:
            SDL_RenderCopyEx(renderer, texture->sdl_texture, NULL, &temp_rect, param_rectangle->GetUniRotation(), &sdl_center, SDL_FLIP_NONE);
            break;
        case 1:
            SDL_RenderCopyEx(renderer, texture->sdl_texture, NULL, &temp_rect, param_rectangle->GetUniRotation(), &sdl_center, SDL_FLIP_HORIZONTAL);
            break;
        case 2:
            SDL_RenderCopyEx(renderer, texture->sdl_texture, NULL, &temp_rect, param_rectangle->GetUniRotation(), &sdl_center, SDL_FLIP_VERTICAL);
            break;
        case 3:
            SDL_RenderCopyEx(renderer, texture->sdl_texture, NULL, &temp_rect, param_rectangle->GetUniRotation() + 180.0, &sdl_center, SDL_FLIP_NONE);
            break;
        }
    }
}
void Engine::BasicDrawSprite(Sprite* sprite, Camera* camera)
{
    if (sprite->animation != nullptr)
    {
        sprite->texture = sprite->animation->GetCurrentFrame()->texture;
    }

    BasicDrawTexture(sprite->texture, camera, &sprite->rect);
}
void Engine::BasicDrawTextBoxData(TextBoxData* param_text_box, Camera* camera)
{
    for (int i = 0; i < param_text_box->lines.size(); i++)
    {
        for (int j = param_text_box->lines[i]->first_index; j <= param_text_box->lines[i]->last_index; j++)
        {
            const TextBoxCharData* const current_char = param_text_box->chars[j];
            const Texture* const current_texture = current_char->font_char->texture;
            if (current_char->a_mod != 0)
            {
                SDL_SetTextureColorMod(current_texture->sdl_texture, current_char->r_mod, current_char->g_mod, current_char->b_mod);
                SDL_SetTextureAlphaMod(current_texture->sdl_texture, current_char->a_mod);
                BasicDrawTexture(current_texture, camera, &current_char->rectangle);
            }
        }
    }
}
void Engine::BasicDrawTextBox(TextBox* param_text_box, Camera* camera)
{
    for (size_t i = 0; i < param_text_box->lines.size(); i++)
    {
        for (size_t j = param_text_box->lines[i]->first_index; j <= param_text_box->lines[i]->last_index; j++)
        {
            const TextBoxChar* const current_char = param_text_box->chars[j];
            const Texture* const current_texture = current_char->font_char->texture;
            if (current_char->a_mod != 0)
            {
                SDL_SetTextureColorMod(current_texture->sdl_texture, current_char->r_mod, current_char->g_mod, current_char->b_mod);
                SDL_SetTextureAlphaMod(current_texture->sdl_texture, current_char->a_mod);
                BasicDrawTexture(current_texture, camera, &current_char->rect);
            }
        }
    }
}
void Engine::BasicDrawButton(Button* param_button, Camera* camera)
{
    if (param_button->visable)
    {
        if (param_button->press_data.pressed)
        {
            BasicDrawSprite(&param_button->pressed_sprite, camera);
        }
        else
        {
            if (param_button->press_data.hovering)
            {
                if (param_button->hovering_sprite.texture == nullptr)
                {
                    BasicDrawSprite(&param_button->pressed_sprite, camera);
                }
                else
                {
                    BasicDrawSprite(&param_button->hovering_sprite, camera);
                }
            }
            else
            {
                BasicDrawSprite(&param_button->released_sprite, camera);
            }
        }
    }
}
void Engine::BasicDrawTextButton(TextButton* param_text_button, Camera* camera)
{
    BasicDrawButton(&param_text_button->button, camera);
    BasicDrawTextBox(&param_text_button->text_box, camera);
}
void Engine::BasicDrawSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera)
{
    Rectangle temp_rect_data = param_simple_text_button->parent_rect;

    if (!param_simple_text_button->press_data.pressed)
    {
        BasicBasicDrawRectangle(&temp_rect_data, SDL_Color{ 100, 100, 100, 255 }, camera);
    }

    const Size2D temp_size_scale = temp_rect_data.GetSizeScale();

    temp_rect_data.size.height -= param_simple_text_button->scaled_drop_amount;
    if (param_simple_text_button->press_data.pressed)
    {
        temp_rect_data.pos.y -= (param_simple_text_button->scaled_drop_amount / 2.0);
    }
    else
    {
        temp_rect_data.pos.y += (param_simple_text_button->scaled_drop_amount / 2.0);
    }

    BasicBasicDrawRectangle(&temp_rect_data, SDL_Color{ 0, 0, 0, 255 }, camera);

    temp_rect_data.size.width -= (param_simple_text_button->scaled_border_width * 2.0);
    temp_rect_data.size.height -= (param_simple_text_button->scaled_border_width * 2.0);

    SDL_Color temp_color;
    if (param_simple_text_button->press_data.hovering)
    {
        temp_color = { 255, 255, 255, 255 };
    }
    else
    {
        temp_color = { 205, 205, 205, 255 };
    }

    BasicBasicDrawRectangle(&temp_rect_data, temp_color, camera);

    BasicDrawTextBox(&param_simple_text_button->text_box, camera);
}
void Engine::BasicDrawScrollBar(ScrollBar* param_scroll_bar, Camera* camera)
{
    if (param_scroll_bar->horizontal_scroll_bar)
    {
        if (!(param_scroll_bar->bar_rect.size.width == param_scroll_bar->full_bar_rect.base_size.width))
        {
            BasicBasicDrawRectangle(&param_scroll_bar->full_bar_rect, { 175, 175, 175, 255 }, camera);
            BasicBasicDrawRectangle(&param_scroll_bar->bar_rect, { 120, 120, 120, 255 }, camera);
        }
    }
    else
    {
        if (!(param_scroll_bar->bar_rect.size.height == param_scroll_bar->full_bar_rect.base_size.height))
        {
            BasicBasicDrawRectangle(&param_scroll_bar->full_bar_rect, { 175, 175, 175, 255 }, camera);
            BasicBasicDrawRectangle(&param_scroll_bar->bar_rect, { 120, 120, 120, 255 }, camera);
        }
    }
}


void Engine::DrawRectangle(Rectangle* param_rectangle, SDL_Color color, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicBasicDrawRectangle(param_rectangle, color, temp_cam_pointer);
}
void Engine::DrawRectangleScaledBorder(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawRectangleScaledBorder(param_rectangle, filling_color, border_scaled_size, border_centering, border_color, temp_cam_pointer);
}
void Engine::DrawRectangleScaledBorderScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawRectangleScaledBorderScaledShadow(param_rectangle, filling_color, border_scaled_size, border_centering, border_color, shadow_scaled_offset, shadow_color, temp_cam_pointer);
}
void Engine::DrawRectangleEx(Rectangle* param_rectangle, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawRectangle(param_rectangle, filling_color, right_border_scaled_size, right_border_centering, bottom_border_scaled_size, bottom_border_centering, left_border_scaled_size, left_border_centering, top_border_scaled_size, top_border_centering, border_color, shadow_scaled_offset, shadow_color, temp_cam_pointer);
}
void Engine::DrawRectangleScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawRectangleScaledShadow(param_rectangle, filling_color, shadow_scaled_offset, shadow_color, temp_cam_pointer);
}
void Engine::DrawRectangleOutline(Rectangle* param_rectangle, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawRectangleOutline(param_rectangle, border_scaled_size, border_centering, border_color, temp_cam_pointer);
}

void Engine::DrawRectStructOne(RectStructOne* param_rect_struct_one, SDL_Color color, Camera* camera)
{
    BasicDrawRectStructOne(param_rect_struct_one, color, camera);
}


void Engine::DrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawPoint(param_point, param_size, color, temp_cam_pointer);
}
void Engine::DrawSprite(Sprite* sprite, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawSprite(sprite, temp_cam_pointer);

    if (boundary_view)
    {
        BasicBasicDrawRectangle(&sprite->rect, SDL_Color{ 0, 0, 255, 50 }, temp_cam_pointer);
    }
}
void Engine::DrawTexture(Texture* texture, Camera* camera, Rectangle* param_rectangle)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawTexture(texture, temp_cam_pointer, param_rectangle);

    if (boundary_view)
    {
        BasicBasicDrawRectangle(param_rectangle, SDL_Color{ 255, 0, 0, 50 }, temp_cam_pointer);
    }
}
void Engine::DrawTextBox(TextBox* param_text_box, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    if (debug_mode && boundary_view)
    {
        Rectangle parent_rectangle_data_copy = param_text_box->parent_rect;

        if (param_text_box->parent_rect.GetUniWidth() < 4.0)
        {
            parent_rectangle_data_copy.SetWidthWithUniWidth(4.0);
        }
        if (param_text_box->parent_rect.GetUniHeight() < 4.0)
        {
            parent_rectangle_data_copy.SetHeightWithUniHeight(4.0);
        }
        BasicBasicDrawRectangle(&parent_rectangle_data_copy, { 0, 0, 0, 50 }, temp_cam_pointer);



        for (size_t i = 0; i < param_text_box->lines.size(); i++)
        {
            BasicBasicDrawRectangle(&param_text_box->lines[i]->rect, { 0, 0, 0, 50 }, temp_cam_pointer);

            for (size_t j = param_text_box->lines[i]->first_index; j <= param_text_box->lines[i]->last_index; j++)
            {
                BasicBasicDrawRectangle(&param_text_box->chars[j]->rect, { 0, 0, 0, 50 }, temp_cam_pointer);
            }
        }
    }

    BasicDrawTextBox(param_text_box, temp_cam_pointer);
}
void Engine::DrawButton(Button* param_button, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawButton(param_button, temp_cam_pointer);
}
void Engine::DrawTextButton(TextButton* param_text_button, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    if (param_text_button->button.press_data.hovering)
    {
        if (param_text_button->button.press_data.pressed)
        {
            param_text_button->text_box.parent_rect.offset.x += param_text_button->additional_offset_pressed.x;
            param_text_button->text_box.parent_rect.offset.y += param_text_button->additional_offset_pressed.y;

            BasicDrawTextButton(param_text_button, temp_cam_pointer);

            param_text_button->text_box.parent_rect.offset.x -= param_text_button->additional_offset_pressed.x;
            param_text_button->text_box.parent_rect.offset.y -= param_text_button->additional_offset_pressed.y;
        }
        else
        {
            param_text_button->text_box.parent_rect.offset.x += param_text_button->additional_offset_hovering.x;
            param_text_button->text_box.parent_rect.offset.y += param_text_button->additional_offset_hovering.y;

            BasicDrawTextButton(param_text_button, temp_cam_pointer);

            param_text_button->text_box.parent_rect.offset.x -= param_text_button->additional_offset_hovering.x;
            param_text_button->text_box.parent_rect.offset.y -= param_text_button->additional_offset_hovering.y;
        }
    }
    else
    {
        param_text_button->text_box.parent_rect.offset.x += param_text_button->additional_offset_released.x;
        param_text_button->text_box.parent_rect.offset.y += param_text_button->additional_offset_released.y;

        BasicDrawTextButton(param_text_button, temp_cam_pointer);

        param_text_button->text_box.parent_rect.offset.x -= param_text_button->additional_offset_released.x;
        param_text_button->text_box.parent_rect.offset.y -= param_text_button->additional_offset_released.y;
    }
}
void Engine::DrawSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawSimpleTextButton(param_simple_text_button, temp_cam_pointer);
}
void Engine::DrawScrollBar(ScrollBar* param_scroll_bar, Camera* camera)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = camera; }

    BasicDrawScrollBar(param_scroll_bar, temp_cam_pointer);
}

void Engine::DrawQueueSprite(QueueSprite* param_sprite)
{
    Camera* temp_cam_pointer = nullptr;

    if (debug_mode) { temp_cam_pointer = debug_camera; }
    else { temp_cam_pointer = param_sprite->camera; }

    DrawTexture(param_sprite->texture, temp_cam_pointer, &param_sprite->rect);

    if (boundary_view)
    {
        DrawRectangle(&param_sprite->rect, SDL_Color{ 0, 0, 255, 50 }, temp_cam_pointer);
    }
}
void Engine::DrawQueue()
{
    sort(sprite_queue.begin(), sprite_queue.end(), [](const QueueSpriteQueue& a, const QueueSpriteQueue& b) {
        return a.layer < b.layer;
        });

    for (int i = 0; i < sprite_queue.size(); i++)
    {
        sort(sprite_queue[i].queue.begin(), sprite_queue[i].queue.end(), [](const QueueSprite& a, const QueueSprite& b) {
            return a.layer < b.layer;
            });

        for (int j = 0; j < sprite_queue[i].queue.size(); i++)
        {
            DrawQueueSprite(&sprite_queue[i].queue.at(j));
        }

        sprite_queue[i].queue.clear();
    }

    sprite_queue.clear();
}


Camera* Engine::NewCamera(const char* const name)
{
    Camera* temp_cam = new Camera();
    temp_cam->rect.base_size.width = (double)window_width;
    temp_cam->rect.base_size.height = (double)window_height;
    temp_cam->rect.SetSizeWithSizeScale(Size2D{ 1.0, 1.0 });

    temp_cam->debug_data_container.InitLeast({ &engine_debug_data_container }, &default_font, name, &temp_cam->rect, {}, 0);
    temp_cam->debug_data_container.camera_container = 1;

    temp_cam->debug_data_container.AddRectangleData(&temp_cam->rect, "Rectangle");
    

    cameras.push_back(temp_cam);

    return temp_cam;
}


Point2D Engine::GetMousePos(Camera* reference_camera)
{
    //WARNING

    Point2D temp_point = SDLPointToUniPoint({ input.mouse_x, input.mouse_y }, { 0 }, { 0 }, reference_camera);
    return temp_point;
}


void Engine::LoadEngineTexture(Texture* param_texture, const char path[])
{
    param_texture->LoadTexture(renderer, path);
    textures.push_back(param_texture);
}
void Engine::LoadEngineTextures() {
    solid_color_pixel_texture = new Texture();
    LoadEngineTexture(solid_color_pixel_texture, "images/solid.png");

    solid_color_circle_8_texture = new Texture();
    LoadEngineTexture(solid_color_circle_8_texture, "images/8x8_circle.png");

    solid_color_circle_32_texture = new Texture();
    LoadEngineTexture(solid_color_circle_32_texture, "images/32x32_circle.png");

    example_texture = new Texture();
    LoadEngineTexture(example_texture, "images/nineteen.png");

    corner_outline_t = new Texture();
    LoadEngineTexture(corner_outline_t, "images/corner_outline.png");

    camera_icon_t = new Texture();
    LoadEngineTexture(camera_icon_t, "images/camera_icon_small.png");

    pause_icon_t = new Texture();
    LoadEngineTexture(pause_icon_t, "images/pause_icon.png");

    play_icon_t = new Texture();
    LoadEngineTexture(play_icon_t, "images/play_icon.png");

    example_button_pressed_t = new Texture();
    LoadEngineTexture(example_button_pressed_t, "images/example_button_pressed.png");
    example_button_released_t = new Texture();
    LoadEngineTexture(example_button_released_t, "images/example_button_released.png");
    example_button_hovering_t = new Texture();
    LoadEngineTexture(example_button_hovering_t, "images/example_button_hovering.png");

    boundary_view_pressed_t = new Texture();
    LoadEngineTexture(boundary_view_pressed_t, "images/boundary_view_pressed.png");
    boundary_view_released_t = new Texture();
    LoadEngineTexture(boundary_view_released_t, "images/boundary_view_released.png");
    boundary_view_hovering_t = new Texture();
    LoadEngineTexture(boundary_view_hovering_t, "images/boundary_view_hovering.png");
}
void Engine::DeleteEngineTextures() {
    for (int i = 0; i < textures.size(); i++)
    {
        SDL_DestroyTexture(textures[i]->sdl_texture);
    }
}

void Engine::UnloadEngineSoundChunk(Mix_Chunk** const param_chunk)
{
    Mix_FreeChunk(*param_chunk);
    *param_chunk = nullptr;
}
void Engine::LoadEngineSounds()
{
    click_press_sound = Mix_LoadWAV("sounds/click_press.wav");
    click_release_sound = Mix_LoadWAV("sounds/click_release.wav");
}
void Engine::DeleteEngineSounds()
{
    UnloadEngineSoundChunk(&click_press_sound);
    UnloadEngineSoundChunk(&click_release_sound);
}


void Engine::UpdateTextBox(TextBox* param_text_box)
{
    for (int i = 0; i < input.all_keys.size(); i++)
    {
        if (input.all_keys[i]->first_frame_pressed)
        {
            bool primary = 1;
            if (input.left_shift.pressed || input.right_shift.pressed)
            {
                primary = 0;
            }

            char char_val = input.KeyIndexToCharValue(i, primary);
            if (char_val != NULL)
            {
                param_text_box->AddChar(char_val);
                param_text_box->UpdateCharPos();
            }

            if (input.all_keys[i] == &input.backspace)
            {
                if (param_text_box->chars.size() > 0)
                {
                    param_text_box->chars.pop_back();
                    param_text_box->UpdateCharPos();
                }
            }
        }
    }
}
void Engine::UpdatePressData(PressData* param_press_data, Rectangle* param_hitbox, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers)
{
    param_press_data->previous_frame_hovering = param_press_data->hovering;
    param_press_data->previous_frame_pressed = param_press_data->pressed;

    if (mouse_layer->active)
    {
        Point2D mouse_pos = GetMousePos(camera);
        bool temp_hovering = OverlapPoint2DWithRectangle(&mouse_pos, param_hitbox, 1);

        if (param_press_data->hoverable)
        {
            param_press_data->hovering = temp_hovering;
        }
        else
        {
            param_press_data->hovering = 0;
        }

        if (param_press_data->pressable)
        {
            if (param_press_data->hovering || (!param_press_data->hoverable))
            {
                param_press_data->pressed = input.mouse_left.pressed;
            }
            else
            {
                param_press_data->pressed = 0;
            }
        }
        else
        {
            param_press_data->pressed = 0;
        }
    
        if (temp_hovering)
        {
            DeactivateMouseLayers(mouse_layer_removal_white_list, mouse_layer_removal_target_layers);
        }
    }
    else
    {
        param_press_data->hovering = 0;
        param_press_data->pressed = 0;
    }

    param_press_data->first_frame_hovering = (param_press_data->hovering && (!param_press_data->previous_frame_hovering));
    param_press_data->first_frame_not_hovering = ((!param_press_data->hovering) && param_press_data->previous_frame_hovering);

    param_press_data->first_frame_pressed = (param_press_data->pressed && (!param_press_data->previous_frame_pressed));
    param_press_data->first_frame_released = ((!param_press_data->pressed) && param_press_data->previous_frame_pressed);
}
void Engine::UpdateButton(Button* param_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers)
{
    UpdatePressData(&param_button->press_data, &param_button->hitbox, camera, mouse_layer, mouse_layer_removal_white_list, mouse_layer_removal_target_layers);
}
void Engine::UpdateTextButton(TextButton* param_text_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers)
{
    UpdateButton(&param_text_button->button, camera, mouse_layer, mouse_layer_removal_white_list, mouse_layer_removal_target_layers);
}
void Engine::UpdateSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers)
{
    UpdatePressData(&param_simple_text_button->press_data, &param_simple_text_button->parent_rect, camera, mouse_layer, mouse_layer_removal_white_list, mouse_layer_removal_target_layers);
    if (param_simple_text_button->press_data.pressed)
    {
        param_simple_text_button->text_box.parent_rect.pos.y = (param_simple_text_button->scaled_drop_amount / param_simple_text_button->parent_rect.GetHeightScale()) / -2.0;
    }
    else
    {
        param_simple_text_button->text_box.parent_rect.pos.y = (param_simple_text_button->scaled_drop_amount / param_simple_text_button->parent_rect.GetHeightScale()) / 2.0;
    }
}
void Engine::UpdateScrollBar(ScrollBar* param_scroll_bar, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers)
{
    if (param_scroll_bar->total_scroll_length != 0.0)
    {
        if (mouse_layer->active)
        {
            Point2D mouse_pos = GetMousePos(camera);

            if (OverlapPoint2DWithRectangle(&mouse_pos, &param_scroll_bar->scroll_area, 1))
            {
                if (input.mouse_scroll_y != 0)
                {
                    param_scroll_bar->scroll_value -= ((double)input.mouse_scroll_y * param_scroll_bar->scroll_rate);

                    if (param_scroll_bar->scroll_value < 0.0)
                    {
                        param_scroll_bar->scroll_value = 0.0;
                    }
                    const double temp_max_scroll_value = param_scroll_bar->GetMaxScrollValue();
                    if (param_scroll_bar->scroll_value > temp_max_scroll_value)
                    {
                        param_scroll_bar->scroll_value = temp_max_scroll_value;
                    }

                    param_scroll_bar->SetBarRectPosWithScrollValue();
                }

                if (input.mouse_left.first_frame_released)
                {
                    param_scroll_bar->clicked_on_bar = 0;
                }

                if (param_scroll_bar->clicked_on_bar)
                {
                    if (param_scroll_bar->horizontal_scroll_bar)
                    {
                        param_scroll_bar->bar_rect.pos.x = mouse_pos.x + param_scroll_bar->saved_mouse_y_bar_rect_y_diff;
                    }
                    else
                    {
                        param_scroll_bar->bar_rect.pos.y = mouse_pos.y + param_scroll_bar->saved_mouse_y_bar_rect_y_diff;
                    }

                    param_scroll_bar->SetScrollValueWithBarRectPos();


                    //Adjust for boundaries
                    bool temp_reached_scroll_limit = 0;
                    if (param_scroll_bar->scroll_value < 0.0)
                    {
                        param_scroll_bar->scroll_value = 0.0;
                        temp_reached_scroll_limit = 1;
                    }
                    const double temp_max_scroll_value = param_scroll_bar->GetMaxScrollValue();
                    if (param_scroll_bar->scroll_value > temp_max_scroll_value)
                    {
                        param_scroll_bar->scroll_value = temp_max_scroll_value;
                        temp_reached_scroll_limit = 1;
                    }

                    if (temp_reached_scroll_limit)
                    {
                        param_scroll_bar->SetBarRectPosWithScrollValue();
                    }
                }

                if (input.mouse_left.first_frame_pressed && (!input.mouse_left.first_frame_released))
                {
                    if (param_scroll_bar->horizontal_scroll_bar)
                    {
                        param_scroll_bar->saved_mouse_y_bar_rect_y_diff = param_scroll_bar->bar_rect.pos.x - mouse_pos.x;
                    }
                    else
                    {
                        param_scroll_bar->saved_mouse_y_bar_rect_y_diff = param_scroll_bar->bar_rect.pos.y - mouse_pos.y;
                    }
                    param_scroll_bar->clicked_on_bar = 1;
                }



                DeactivateMouseLayers(mouse_layer_removal_white_list, mouse_layer_removal_target_layers);
            }
        }
    }
    else
    {
        cout << "INITIALIZE THE SCROLL BAR WITH THE \'INITBASIC()\' FUNCTION FIRST";
    }
}


void Engine::UpdateCameraLabels()
{
    for (int i = 0; i < cameras.size(); i++)
    {
        Point2D temp_point;
        temp_point.x = cameras[i]->rect.GetUniEdge({ 2 }) + (100.0 * debug_camera->rect.GetWidthScale());
        temp_point.y = cameras[i]->rect.GetUniEdge({ 3 });

        UpdateDebugLabelPosWithTargetPos(&cameras[i]->debug_data_container.label, temp_point);
    }
}
void Engine::UpdateDebugData()
{
    Point2D temp_blank_mouse_pos = GetMousePos(blank_camera);



    highlighting_path_item = 0;

    if (container_path_display_layer.active)
    {
        RectStructOne temp = RectangleToRectStructOne(&container_path_rectangle);

        if (OverlapPoint2DWithRectStructOne(&temp_blank_mouse_pos, &temp, 1))
        {
            DeactivateMouseLayers(0, { &container_path_display_layer });

            size_t char_index = 6;
            for (size_t i = 0; i < saved_container_name_sizes.size(); i++)
            {
                RectStructOne temp_name_rect_struct_one = container_path_text_box.GetSegmentHitbox(char_index, char_index + saved_container_name_sizes[i] - 1)->at(0); //CURRENTLY CANNOT SCALE WITH RESOLUTION

                temp_name_rect_struct_one.uni_bottom_edge -= 6.0;
                temp_name_rect_struct_one.uni_left_edge -= 6.0;
                temp_name_rect_struct_one.uni_top_edge += 6.0;
                temp_name_rect_struct_one.uni_right_edge += 6.0;

                if (OverlapPoint2DWithRectStructOne(&temp_blank_mouse_pos, &temp_name_rect_struct_one, 1))
                {
                    saved_highlighted_path_item = temp_name_rect_struct_one;
                    highlighting_path_item = 1;

                    if (input.mouse_left.first_frame_pressed)
                    {
                        selected_debug_data_container = saved_container_path[i];

                        saved_container_path.resize(i + 1);
                        saved_container_name_sizes.resize(i + 1);

                        first_frame_selected_debug_data_container = 1;
                        UpdateContainerPathTextBox();

                        break;
                    }
                }

                char_index += saved_container_name_sizes[i] + 4;
            }
        }
    }





    const size_t saved_saved_label_rects_size = saved_label_rects.size();

    first_frame_selected_debug_data_container = 0;

    Point2D temp_mouse_pos = GetMousePos(debug_camera);

    if (debug_data_container_layer.active)
    {
        if (input.mouse_left.first_frame_pressed)
        {
            DebugDataContainer* saved_selected_debug_data_container = selected_debug_data_container;

            for (int i = 0; i < order.size(); i++)
            {
                if (!(camera_view && order[i]->camera_container))
                {
                    UpdateDebugLabelPos(&order[i]->label);
                }

                if (OverlapPoint2DWithRectangle(&temp_mouse_pos, &order[i]->label.rectangle, 1))
                {
                    if (order[i] == saved_selected_debug_data_container)
                    {
                        selected_debug_data_container = &engine_debug_data_container;

                        saved_container_path.clear();
                        saved_container_path.push_back(&engine_debug_data_container);
                        saved_container_name_sizes.clear();
                        saved_container_name_sizes.push_back(27);

                        UpdateContainerPathTextBox();
                    }
                    else
                    {
                        selected_debug_data_container = order[i];

                        //Check to see if user is "stepping-back" in the path
                        DebugDataContainer* second_to_last = nullptr;
                        if (saved_container_path.size() > 1)
                        {
                            second_to_last = saved_container_path[saved_container_path.size() - 2];
                        }

                        if (selected_debug_data_container == second_to_last)
                        {
                            saved_container_path.pop_back();
                            saved_container_name_sizes.pop_back();
                        }
                        else
                        {
                            saved_container_path.push_back(order[i]);
                            saved_container_name_sizes.push_back(order[i]->label.text_box_data.chars.size());
                        }

                        UpdateContainerPathTextBox();
                    }
                    first_frame_selected_debug_data_container = 1;
                    DeactivateMouseLayers(0, { &debug_data_container_layer });

                    break;
                }
            }



            if (!first_frame_selected_debug_data_container)
            {
                double saved_area = DBL_MAX;
                for (int i = 0; i < order.size(); i++)
                {
                    if (order[i] != saved_selected_debug_data_container)
                    {
                        if (OverlapPoint2DWithRectangle(&temp_mouse_pos, order[i]->clickable_rectangle, 1))
                        {
                            const double current_area = order[i]->clickable_rectangle->size.width * order[i]->clickable_rectangle->size.height;

                            if ((current_area) < saved_area)
                            {
                                first_frame_selected_debug_data_container = 1;
                                DeactivateMouseLayers(0, { &debug_data_container_layer });

                                selected_debug_data_container = order[i];

                                saved_area = current_area;
                            }
                        }
                    }
                }


                if (first_frame_selected_debug_data_container)
                {
                    //Check to see if user is "stepping-back" in the path
                    DebugDataContainer* second_to_last = nullptr;
                    if (saved_container_path.size() > 1)
                    {
                        second_to_last = saved_container_path[saved_container_path.size() - 2];
                    }

                    if (selected_debug_data_container == second_to_last)
                    {
                        saved_container_path.pop_back();
                        saved_container_name_sizes.pop_back();
                    }
                    else
                    {
                        saved_container_path.push_back(selected_debug_data_container);
                        saved_container_name_sizes.push_back(selected_debug_data_container->label.text_box_data.chars.size());
                    }

                    UpdateContainerPathTextBox();
                }
                else
                {
                    selected_debug_data_container = &engine_debug_data_container;

                    saved_container_path.clear();
                    saved_container_path.push_back(&engine_debug_data_container);
                    saved_container_name_sizes.clear();
                    saved_container_name_sizes.push_back(27);

                    UpdateContainerPathTextBox();
                }
            }


            /*
            selected_debug_data_container = nullptr;

            Point2D temp_mouse_pos = GetMousePos(debug_camera);

            for (int i = 0; i < engine_debug_data_container.owned_data.size(); i++)
            {
                if (engine_debug_data_container.owned_data[i]->IsActive(scene))
                {
                    if (OverlapPoint2DWithRectangleData(&temp_mouse_pos, engine_debug_data_container.owned_data[i]->clickable_rectangle_data, 1))
                    {
                        first_frame_selected_debug_data_container = 1;
                        current_mouse_layer = 1;
                        selected_debug_data_container = engine_debug_data_container.owned_data[i];
                    }
                }
            }
            */
        }
    }

    if (selected_debug_data_container != &engine_debug_data_container)
    {
        //Write to and update debug_text_box if selected_debug_data_container is included in the current scene. Else, set selected_debug_data_container to nullptr
        if (selected_debug_data_container->IsActive(scene))
        {
            debug_data_text_box.Clear();



            int temp_index = 0;
            bool found_value = 0;

            //Loop through all debug values and add them to the text_box (in order of the index values)
            while (true)
            {
                found_value = 0;



                // -------- CHECK BOOLS --------

                for (int i = 0; i < selected_debug_data_container->bools.size(); i++)
                {
                    if (selected_debug_data_container->bools[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->bools[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        if (*selected_debug_data_container->bools[i].data_value == 0)
                        {
                            debug_data_text_box.AddChar('0', DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        }
                        else
                        {
                            debug_data_text_box.AddChar('1', DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        }
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK CHARS --------

                for (int i = 0; i < selected_debug_data_container->chars.size(); i++)
                {
                    if (selected_debug_data_container->chars[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->chars[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddChar(*selected_debug_data_container->chars[i].data_value, DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK INTS --------

                for (int i = 0; i < selected_debug_data_container->ints.size(); i++)
                {
                    if (selected_debug_data_container->ints[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->ints[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddString(to_string(*selected_debug_data_container->ints[i].data_value), DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK FLOATS --------

                for (int i = 0; i < selected_debug_data_container->floats.size(); i++)
                {
                    if (selected_debug_data_container->floats[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->floats[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddString(FloatToString(*selected_debug_data_container->floats[i].data_value, 4), DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK DOUBLES --------

                for (int i = 0; i < selected_debug_data_container->doubles.size(); i++)
                {
                    if (selected_debug_data_container->doubles[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->doubles[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddString(DoubleToString(*selected_debug_data_container->doubles[i].data_value, 4), DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK CONST CHARS --------

                for (int i = 0; i < selected_debug_data_container->const_chars.size(); i++)
                {
                    if (selected_debug_data_container->const_chars[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->const_chars[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->const_chars[i].data_value, DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK STRINGS --------

                for (int i = 0; i < selected_debug_data_container->strings.size(); i++)
                {
                    if (selected_debug_data_container->strings[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->strings[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddString(*selected_debug_data_container->strings[i].data_value, DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK RIGID CENTERINGS --------

                for (int i = 0; i < selected_debug_data_container->rigid_centerings.size(); i++)
                {
                    if (selected_debug_data_container->rigid_centerings[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->rigid_centerings[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);

                        switch (selected_debug_data_container->rigid_centerings[i].data_value->value)
                        {
                        case 0:
                            debug_data_text_box.AddCharPtr("0 (left/bottom)", DEBUG_DATA_TEXT_COLOR_RIGID_CENTERING);
                            break;
                        case 1:
                            debug_data_text_box.AddCharPtr("1 (middle)", DEBUG_DATA_TEXT_COLOR_RIGID_CENTERING);
                            break;
                        case 2:
                            debug_data_text_box.AddCharPtr("2 (right/top)", DEBUG_DATA_TEXT_COLOR_RIGID_CENTERING);
                            break;
                        case 3:
                            debug_data_text_box.AddCharPtr("3 (UNDEFINED)", DEBUG_DATA_TEXT_COLOR_RIGID_CENTERING);
                            break;
                        }

                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK POINT 2DS --------

                for (int i = 0; i < selected_debug_data_container->point_2ds.size(); i++)
                {
                    if (selected_debug_data_container->point_2ds[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->point_2ds[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->point_2ds[i].data_value->x, 4), DEBUG_DATA_TEXT_COLOR_POINT2D);
                        debug_data_text_box.AddCharPtr(", ", DEBUG_DATA_TEXT_COLOR_POINT2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->point_2ds[i].data_value->y, 4), DEBUG_DATA_TEXT_COLOR_POINT2D);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK SIZE 2DS --------

                for (int i = 0; i < selected_debug_data_container->size_2ds.size(); i++)
                {
                    if (selected_debug_data_container->size_2ds[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->size_2ds[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr(": ", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr("W: ", DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->size_2ds[i].data_value->width, 4), DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddCharPtr(", H: ", DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->size_2ds[i].data_value->height, 4), DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddChar('\n');

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }



                // -------- CHECK RECTANGLES --------

                for (int i = 0; i < selected_debug_data_container->rectangle_datas.size(); i++)
                {
                    if (selected_debug_data_container->rectangle_datas[i].index == temp_index)
                    {
                        debug_data_text_box.AddCharPtr(selected_debug_data_container->rectangle_datas[i].data_name, DEBUG_DATA_TEXT_COLOR_NAME);

                        debug_data_text_box.AddCharPtr(": {", DEBUG_DATA_TEXT_COLOR_NAME);
                        debug_data_text_box.AddCharPtr("\nPos: ", DEBUG_DATA_TEXT_COLOR_SUB_NAME);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->pos.x, 4), DEBUG_DATA_TEXT_COLOR_POINT2D);
                        debug_data_text_box.AddCharPtr(", ", DEBUG_DATA_TEXT_COLOR_POINT2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->pos.y, 4), DEBUG_DATA_TEXT_COLOR_POINT2D);

                        debug_data_text_box.AddCharPtr("\nOffset: ", DEBUG_DATA_TEXT_COLOR_SUB_NAME);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->offset.x, 4), DEBUG_DATA_TEXT_COLOR_POINT2D);
                        debug_data_text_box.AddCharPtr(", ", DEBUG_DATA_TEXT_COLOR_POINT2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->offset.y, 4), DEBUG_DATA_TEXT_COLOR_POINT2D);

                        debug_data_text_box.AddCharPtr("\nBaseSize: ", DEBUG_DATA_TEXT_COLOR_SUB_NAME);
                        debug_data_text_box.AddCharPtr("W: ", DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->base_size.width, 4), DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddCharPtr(", H: ", DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->base_size.height, 4), DEBUG_DATA_TEXT_COLOR_SIZE2D);

                        debug_data_text_box.AddCharPtr("\nSize: ", DEBUG_DATA_TEXT_COLOR_SUB_NAME);
                        debug_data_text_box.AddCharPtr("W: ", DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->size.width, 4), DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddCharPtr(", H: ", DEBUG_DATA_TEXT_COLOR_SIZE2D);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->size.height, 4), DEBUG_DATA_TEXT_COLOR_SIZE2D);

                        debug_data_text_box.AddCharPtr("\nFlip: ", DEBUG_DATA_TEXT_COLOR_SUB_NAME);
                        switch (selected_debug_data_container->rectangle_datas[i].data_value->flip.value)
                        {
                        case 0:
                            debug_data_text_box.AddCharPtr("none", DEBUG_DATA_TEXT_COLOR_OTHER);
                            break;
                        case 1:
                            debug_data_text_box.AddCharPtr("horizontal", DEBUG_DATA_TEXT_COLOR_OTHER);
                            break;
                        case 2:
                            debug_data_text_box.AddCharPtr("vertical", DEBUG_DATA_TEXT_COLOR_OTHER);
                            break;
                        case 3:
                            debug_data_text_box.AddCharPtr("both", DEBUG_DATA_TEXT_COLOR_OTHER);
                            break;
                        }

                        debug_data_text_box.AddCharPtr("\nRotation: ", DEBUG_DATA_TEXT_COLOR_SUB_NAME);
                        debug_data_text_box.AddString(DoubleToString(selected_debug_data_container->rectangle_datas[i].data_value->rotation, 4), DEBUG_DATA_TEXT_COLOR_PRIMARY_TYPE);

                        debug_data_text_box.AddCharPtr(" }\n");

                        found_value = 1;
                        break;
                    }
                }
                if (found_value)
                {
                    temp_index++;
                    continue;
                }


                break;
            }


            debug_data_text_box.UpdateCharPos();
        }
        else
        {
            selected_debug_data_container = &engine_debug_data_container;

            saved_container_path.clear();
            saved_container_path.push_back(&engine_debug_data_container);
            saved_container_name_sizes.clear();
            saved_container_name_sizes.push_back(27);

            UpdateContainerPathTextBox();
        }
    }

    GenerateContainerOrder(1);

    saved_label_rects.resize(saved_saved_label_rects_size);
    for (int i = 0; i < order.size(); i++)
    {
        if (!(camera_view && order[i]->camera_container))
        {
            UpdateDebugLabelPos(&order[i]->label);
        }

        order[i]->hovering = 0;
    }

    if (debug_data_container_layer.active)
    {
        bool hovering_over_label = 0;

        for (int i = 0; i < order.size(); i++)
        {
            if (OverlapPoint2DWithRectangle(&temp_mouse_pos, &order[i]->label.rectangle, 1))
            {
                order[i]->hovering = 1;

                DeactivateMouseLayers(0, { &debug_data_container_layer });

                hovering_over_label = 1;

                break;
            }
        }



        if (!hovering_over_label)
        {
            DebugDataContainer* previous_container = nullptr;

            double saved_area = DBL_MAX;
            for (int i = 0; i < order.size(); i++)
            {
                if (order[i] != selected_debug_data_container)
                {
                    if (OverlapPoint2DWithRectangle(&temp_mouse_pos, order[i]->clickable_rectangle, 1))
                    {
                        const double current_area = order[i]->clickable_rectangle->size.width * order[i]->clickable_rectangle->size.height;

                        if ((current_area) < saved_area)
                        {
                            order[i]->hovering = 1;

                            DeactivateMouseLayers(0, { &debug_data_container_layer });

                            saved_area = current_area;

                            if (previous_container)
                            {
                                previous_container->hovering = 0;
                            }

                            previous_container = order[i];
                        }
                    }
                }
            }
        }
    }
}
void Engine::SetDebugDataScrollBarLength()
{
    if (selected_debug_data_container != &engine_debug_data_container)
    {
        if (first_frame_selected_debug_data_container)
        {
            const double temp_margin = DEBUG_DATA_TEXT_BOX_MARGIN;

            double temp_total_scroll_height = debug_data_text_box.GetActualBaseHeight() * debug_data_text_box.parent_rect.GetUniHeightScale();
            double temp_text_box_uni_height = debug_data_text_box.parent_rect.GetUniHeight();
            if (temp_total_scroll_height < temp_text_box_uni_height)
            {
                temp_total_scroll_height = temp_text_box_uni_height;
            }

            temp_total_scroll_height += temp_margin;
            temp_text_box_uni_height += temp_margin;

            debug_data_scroll_bar.SetScrollLength(temp_total_scroll_height, temp_text_box_uni_height, temp_text_box_uni_height);
        }

        debug_data_text_box.parent_rect.pos.y = debug_data_scroll_bar.scroll_value;
    }
}
void Engine::DrawDebugData()
{
    //Draw the debug_data_containers in "order" (the vector)
    for (size_t i = order.size() - 1; i != SIZE_MAX; i--)
    {
        DrawDebugDataContainer(order[i]);
    }

    for (size_t i = order.size() - 1; i != SIZE_MAX; i--)
    {
        if (!(camera_view && order[i]->camera_container))
        {
            BasicDrawDebugLabel(&order[i]->label);
        }
    }

    //Draw container path display
    container_path_rectangle.size.width = container_path_text_box.GetActualBaseWidth() * container_path_text_box.parent_rect.GetWidthScale();
    container_path_rectangle.size.width += 12.0;
    container_path_rectangle.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 2 }), { 2 });
    BasicDrawRectangleScaledBorder(&container_path_rectangle, { 225, 225, 225, 255 }, 2.0, { 2 }, { 0, 0, 0, 255 }, blank_camera);

    if (highlighting_path_item)
    {
        BasicDrawRectStructOne(&saved_highlighted_path_item, { 255, 255, 255, 255 }, blank_camera);
    }

    BasicDrawTextBox(&container_path_text_box, blank_camera);

    //Draw debug_data_sidebar if applicable
    if (selected_debug_data_container != &engine_debug_data_container)
    {
        Rectangle temp_rectangle_data;

        temp_rectangle_data.size.height = blank_camera->rect.base_size.height;
        temp_rectangle_data.size.width = blank_camera->rect.base_size.width / 4.0;
        temp_rectangle_data.SetBaseSizeWithSizeScale({ 1.0, 1.0 });
        temp_rectangle_data.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 0 }), { 0 });

        BasicDrawRectangleScaledBorder(&temp_rectangle_data, { 220, 220, 220, 255 }, 8.0, { 2 }, { 0, 0, 0, 255 }, blank_camera);

        BasicDrawTextBox(&debug_data_text_box, blank_camera);
    }
}
void Engine::DrawDebugDataContainer(DebugDataContainer* const param_debug_data_container)
{
    if (param_debug_data_container->clickable_rectangle)
    {
        Size2D temp_debug_camera_uni_size_scale = debug_camera->rect.GetUniSizeScale();

        if (param_debug_data_container == selected_debug_data_container)
        {
            BasicDrawRectangleScaledBorder(param_debug_data_container->clickable_rectangle, param_debug_data_container->fill_color, 4.0 * temp_debug_camera_uni_size_scale.width, { 0 }, param_debug_data_container->outline_color, debug_camera);
        }
        else
        {
            if (param_debug_data_container->hovering)
            {
                SDL_Color temp_fill_color = param_debug_data_container->fill_color;
                temp_fill_color.a /= 2;

                BasicDrawRectangleScaledBorder(param_debug_data_container->clickable_rectangle, temp_fill_color, 4.0 * temp_debug_camera_uni_size_scale.width, { 0 }, param_debug_data_container->outline_color, debug_camera);
            }
            else
            {
                BasicDrawRectangleOutline(param_debug_data_container->clickable_rectangle, 4.0 * temp_debug_camera_uni_size_scale.width, { 0 }, param_debug_data_container->outline_color, debug_camera);
            }
        }


        /*
        debug_data_container_name_text_box.parent_rect.SetSizeWithSizeScale({ 4.0 * temp_debug_camera_uni_size_scale.width, 4.0 * temp_debug_camera_uni_size_scale.height });
        debug_data_container_name_text_box.parent_rect.SetPosWithUniEdge(param_debug_data_container->clickable_rectangle_data->GetUniEdge({ 2 }), { 2 });
        debug_data_container_name_text_box.parent_rect.SetPosWithUniEdge(param_debug_data_container->clickable_rectangle_data->GetUniEdge({ 3 }), { 1 });

        debug_data_container_name_text_box.Clear();
        debug_data_container_name_text_box.AddString(param_debug_data_container->name);
        debug_data_container_name_text_box.UpdateCharPos();

        Rectangle temp_back_rectangle_data = debug_data_container_name_text_box.lines[0].rect;

        BasicBasicDrawRectangle(&temp_back_rectangle_data, { 255, 255, 255, 175 }, debug_camera);
        BasicDrawTextBox(&debug_data_container_name_text_box, debug_camera);
        */
    }
}

void Engine::GenerateContainerOrder(const bool generate_colors)
{
    order.clear();

    //Add owned data to order
    for (size_t i = selected_debug_data_container->owned_data.size() - 1; i != SIZE_MAX; i--)
    {
        if (generate_colors)
        {
            selected_debug_data_container->owned_data[i]->outline_color = { 150, 255, 0, 255 };
            selected_debug_data_container->owned_data[i]->fill_color = { 150, 255, 0, 50 };
        }

        order.push_back(selected_debug_data_container->owned_data[i]);
    }

    //Add selected container to order
    if (selected_debug_data_container != &engine_debug_data_container)
    {
        if (generate_colors)
        {
            selected_debug_data_container->outline_color = { 255, 255, 0, 255 };
            selected_debug_data_container->fill_color = { 255, 255, 0, 50 };
        }

        order.push_back(selected_debug_data_container);
    }

    //Add all owners and owners of owners and owners of owners of owners etc to order
    unsigned int layer_count = 0;
    vector<DebugDataContainer*> current_layer = { selected_debug_data_container };
    vector<DebugDataContainer*> next_layer;

    //Continue cycle until no more owners
    while (true)
    {
        //Loops through each element in current_layer
        for (size_t i = current_layer.size() - 1; i != SIZE_MAX; i--)
        {
            //Loops through all the owners of current_layer[i]
            for (size_t j = current_layer[i]->owners.size() - 1; j != SIZE_MAX; j--)
            {
                //Runs code if current_data_container->owners[i] isn't part of order
                if (find(order.begin(), order.end(), current_layer[i]->owners[j]) == order.end())
                {
                    if (current_layer[i]->owners[j] != &engine_debug_data_container)
                    {
                        if (generate_colors)
                        {
                            const double g_value = 255.0 / pow(1.5, layer_count + 1);
                            const int int_g_value = (int)round(g_value);
                            const unsigned char unsigned_char_g_value = (unsigned char)int_g_value;
                            current_layer[i]->owners[j]->outline_color = { 255, unsigned_char_g_value, 0, 255};
                            current_layer[i]->owners[j]->fill_color = { 255, unsigned_char_g_value, 0, 50 };
                        }

                        order.push_back(current_layer[i]->owners[j]);
                        next_layer.push_back(current_layer[i]->owners[j]);
                    }
                }
            }
        }

        current_layer = next_layer;
        next_layer.clear();

        if (current_layer.size() == 0)
        {
            break;
        }

        layer_count++;
    }
}

void Engine::UpdateContainerPathTextBox()
{
    container_path_text_box.Clear();
    container_path_text_box.AddCharPtr("Path: engine_debug_data_container");

    for (int i = 1; i < saved_container_path.size(); i++)
    {
        container_path_text_box.AddCharPtr(" -> ");
        container_path_text_box.AddString(saved_container_path[i]->label.text_box_data.GetText());
    }

    container_path_text_box.UpdateCharPos();
}


void Engine::DeactivateMouseLayers(const bool white_list, vector<MouseLayer*> target_layers)
{
    for (int i = 0; i < mouse_layers.size(); i++)
    {
        auto found_layer = std::find(target_layers.begin(), target_layers.end(), mouse_layers[i]);

        if (white_list)
        {
            if (found_layer != target_layers.end())
            {
                mouse_layers[i]->active = 0;
            }
        }
        else
        {
            if (found_layer == target_layers.end())
            {
                mouse_layers[i]->active = 0;
            }
        }

        if (found_layer != target_layers.end())
        {
            target_layers.erase(found_layer);
        }
    }
}


Engine::Engine() : p(nullptr), RunPointer(nullptr) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    window = SDL_CreateWindow("GameEngine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600, 400,
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_GetWindowSize(window, &window_width, &window_height);






    scene = 1;

    // -----------------   MOUSE LAYER FRAMEWORK   -----------------

    always_activated_layer.active = 1;
    always_deactivated_layer.active = 0;

    debug_data_container_layer.Init(&mouse_layers);
    visual_button_layer.Init(&mouse_layers);
    debug_data_scroll_bar_layer.Init(&mouse_layers);
    container_path_display_layer.Init(&mouse_layers);






    // -----------------   DEFINE SCROLL BAR THICKNESS   -----------------

    const double temp_scroll_bar_thickness = (double)(window_height / 36);
    scroll_bar_thickness = (double)(window_width / 64);
    if (temp_scroll_bar_thickness < scroll_bar_thickness)
    {
        scroll_bar_thickness = temp_scroll_bar_thickness;
    }






    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    default_font.Init("default_white", renderer, 1.0, 1.0, 7.0);

    input = {};
    input.FormatKeys();

    frame_rate = 144.0;
    frame_factor = (60.0 / frame_rate);
    frame_delay = (Uint32)(1000.0 / frame_rate);

    debug_mode = 0;
    running_game = 1;

    boundary_view = 0;
    

    blank_camera = NewCamera("blank_camera");

    debug_camera = new Camera();
    debug_camera->rect.base_size.width = (double)window_width;
    debug_camera->rect.base_size.height = (double)window_height;
    debug_camera->rect.SetSizeWithSizeScale({ 1.0, 1.0 });
    //debug_camera->debug_data_container.InitLeast({ &engine_debug_data_container }, &default_font, "debug_camera", &debug_camera->rect, {});

    LoadEngineTextures();
    LoadEngineSounds();

    boundary_view_button.InitWithTexturesAndSizeScale(boundary_view_released_t, boundary_view_hovering_t, boundary_view_pressed_t, Size2D{4.0, 4.0});
    boundary_view_button.pressed_sprite.rect.pos.y = -2.0;

    boundary_view_button.parent_rect.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 0 }), { 0 });
    boundary_view_button.parent_rect.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 3 }), { 3 });






    // -----------------   CREATE ENGINE DEBUG DATA CONTAINER   -----------------

    engine_debug_data_container.InitLeast({}, &default_font, "Engine Debug Data Container", nullptr, {}, 1);
    selected_debug_data_container = &engine_debug_data_container;
    GenerateContainerOrder(1);






    // -----------------   CREATE DEBUG DATA TEXT BOX   -----------------

    const double temp_margin = DEBUG_DATA_TEXT_BOX_MARGIN;

    debug_data_text_box.InitLeast(&default_font);
    debug_data_text_box.parent_rect.size.height = blank_camera->rect.base_size.height - temp_margin;
    debug_data_text_box.parent_rect.size.width = (blank_camera->rect.base_size.width / 4.0);
    debug_data_text_box.parent_rect.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 0 }), { 0 });
    debug_data_text_box.parent_rect.size.width -= temp_margin;
    debug_data_text_box.parent_rect.size.width -= scroll_bar_thickness;
    debug_data_text_box.parent_rect.pos.x -= (scroll_bar_thickness / 2.0);
    debug_data_text_box.parent_rect.SetBaseSizeWithSizeScale({ 2.8, 2.8 });
    debug_data_text_box.horizontal_text_centering = { 0 };
    debug_data_text_box.vertical_text_centering = { 2 };
    debug_data_text_box.text_wrap = 1;






    // -----------------   CREATE DEBUG DATA CONTAINER NAME TEXT BOX   -----------------

    debug_data_container_name_text_box.InitLeast(&default_font);
    debug_data_container_name_text_box.horizontal_text_centering = { 0 };
    debug_data_container_name_text_box.vertical_text_centering = { 0 };
    debug_data_container_name_text_box.parent_rect.base_size = { 1.0, 1.0 };
    debug_data_container_name_text_box.parent_rect.offset = { 0.5, 0.5 };






    // -----------------   CREATE DEBUG DATA SCROLL BAR   -----------------

    Rectangle temp_rectangle_data;

    temp_rectangle_data.size.height = blank_camera->rect.base_size.height;
    temp_rectangle_data.size.width = blank_camera->rect.base_size.width / 4.0;
    temp_rectangle_data.SetBaseSizeWithSizeScale({ 1.0, 1.0 });
    temp_rectangle_data.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 0 }), { 0 });

    debug_data_scroll_bar.InitBasic(blank_camera->rect.base_size.height, blank_camera->rect.base_size.height, temp_rectangle_data, scroll_bar_thickness, 0);






    // -----------------   CREATE CONTAINER PATH TEXT BOX AND RECTANGLE   -----------------

    container_path_rectangle.size.width = blank_camera->rect.size.width;
    container_path_rectangle.size.height = 2.0;
    container_path_rectangle.SetBaseSizeWithSizeScale({ 2.0, 2.0 });
    container_path_rectangle.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 1 }), { 1 });
    container_path_rectangle.pos.x += 6.0;
    container_path_rectangle.pos.y += 6.0;

    container_path_text_box.InitMost(&default_font, container_path_rectangle, "Path: engine_debug_data_container", { 0 }, { 0 }, 0);

    container_path_rectangle.size.height = 26.0;
    container_path_rectangle.base_size = { 1.0, 1.0 };
    container_path_rectangle.SetPosWithUniEdge(blank_camera->rect.GetUniEdge({ 1 }), { 1 });






    // -----------------   INITIALIZE SAVED CONTAINER PATH AND SIZES   -----------------

    saved_container_path = { &engine_debug_data_container };
    saved_container_name_sizes = { 27 };
}
Engine::~Engine()
{
    DeleteEngineTextures();
    DeleteEngineSounds();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}


void Engine::DrawScreen()
{
    if (debug_mode)
    {
        if (camera_view)
        {
            for (int i = 0; i < cameras.size(); i++)
            {
                Size2D temp_size_scale = debug_camera->rect.GetUniSizeScale();


                Rectangle temp_rectangle_data = {};
                temp_rectangle_data.base_size = corner_outline_t->size;
                temp_rectangle_data.SetSizeWithSizeScale(Size2D{ 4.0 * temp_size_scale.width, 4.0 * temp_size_scale.height });

                temp_rectangle_data.SetPosWithUniEdge(cameras[i]->rect.GetUniEdge({ 2 }), { 2 });
                temp_rectangle_data.SetPosWithUniEdge(cameras[i]->rect.GetUniEdge({ 3 }), { 3 });
                temp_rectangle_data.flip = { 0 };
                BasicDrawTexture(corner_outline_t, debug_camera, &temp_rectangle_data);

                temp_rectangle_data.SetPosWithUniEdge(cameras[i]->rect.GetUniEdge({ 0 }), { 0 });
                temp_rectangle_data.flip = { 1 };
                BasicDrawTexture(corner_outline_t, debug_camera, &temp_rectangle_data);

                temp_rectangle_data.SetPosWithUniEdge(cameras[i]->rect.GetUniEdge({ 1 }), { 1 });
                temp_rectangle_data.flip = { 3 };
                BasicDrawTexture(corner_outline_t, debug_camera, &temp_rectangle_data);

                temp_rectangle_data.SetPosWithUniEdge(cameras[i]->rect.GetUniEdge({ 2 }), { 2 });
                temp_rectangle_data.flip = { 2 };
                BasicDrawTexture(corner_outline_t, debug_camera, &temp_rectangle_data);

                //Draw camera icon
                temp_rectangle_data.base_size = camera_icon_t->size;
                temp_rectangle_data.SetSizeWithSizeScale(Size2D{ 4.0 * temp_size_scale.width, 4.0 * temp_size_scale.height });
                Point2D temp_cam_point;
                temp_cam_point.x = cameras[i]->rect.GetUniEdge({ 2 });
                temp_cam_point.y = cameras[i]->rect.GetUniEdge({ 3 });
                temp_rectangle_data.SetPosWithUniEdge(temp_cam_point.x, { 2 });
                temp_rectangle_data.SetPosWithUniEdge(temp_cam_point.y + (4.0 * temp_size_scale.height), { 1 });
                temp_rectangle_data.flip = { 0 };
                BasicDrawTexture(camera_icon_t, debug_camera, &temp_rectangle_data);



                BasicDrawDebugLabel(&cameras[i]->debug_data_container.label);
            }
        }

        if (running_game)
        {
            Rectangle temp_rectangle_data = {};
            temp_rectangle_data.base_size = play_icon_t->size;
            temp_rectangle_data.SetSizeWithSizeScale(Size2D{ 4.0, 4.0 });

            Point2D temp_blank_cam_point;
            temp_blank_cam_point.x = blank_camera->rect.GetUniEdge( { 2 });
            temp_blank_cam_point.y = blank_camera->rect.GetUniEdge({ 3 });
            temp_rectangle_data.SetPosWithUniEdge(temp_blank_cam_point.x + 12.0, { 2 });
            temp_rectangle_data.SetPosWithUniEdge(temp_blank_cam_point.y - 12.0, { 3 });

            BasicDrawTexture(play_icon_t, blank_camera, &temp_rectangle_data);
        }
        else
        {
            Rectangle temp_rectangle_data = {};
            temp_rectangle_data.base_size = pause_icon_t->size;
            temp_rectangle_data.SetSizeWithSizeScale(Size2D{ 4.0, 4.0 });

            Point2D temp_blank_cam_point;
            temp_blank_cam_point.x = blank_camera->rect.GetUniEdge({ 2 });
            temp_blank_cam_point.y = blank_camera->rect.GetUniEdge({ 3 });
            temp_rectangle_data.SetPosWithUniEdge(temp_blank_cam_point.x + 12.0, { 2 });
            temp_rectangle_data.SetPosWithUniEdge(temp_blank_cam_point.y - 12.0, { 3 });

            BasicDrawTexture(pause_icon_t, blank_camera, &temp_rectangle_data);
        }

        BasicDrawButton(&boundary_view_button, blank_camera);

        DrawDebugData();
        if (selected_debug_data_container)
        {
            BasicDrawScrollBar(&debug_data_scroll_bar, blank_camera);
        }
    }
}

void Engine::UpdateInput()
{
    for (int i = 0; i < input.all_keys.size(); i++)
    {
        input.all_keys[i]->previous_frame_pressed = input.all_keys[i]->pressed;
        input.all_keys[i]->first_frame_pressed = 0;
        input.all_keys[i]->first_frame_released = 0;
    }
    input.mouse_scroll_x = 0;
    input.mouse_scroll_y = 0;

    int previous_mouse_scroll_x = 0, previous_mouse_scroll_y = 0;
    while (SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEWHEEL:
            input.mouse_scroll_x = sdl_event.wheel.x;
            input.mouse_scroll_y = sdl_event.wheel.y;
            input.mouse_scroll_flipped = sdl_event.wheel.direction;
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (sdl_event.button.button)
            {
            case SDL_BUTTON_LEFT:
                input.mouse_left.pressed = 1;
                input.mouse_left.first_frame_pressed = 1;
                break;
            case SDL_BUTTON_RIGHT:
                input.mouse_right.pressed = 1;
                input.mouse_right.first_frame_pressed = 1;
                break;
            case SDL_BUTTON_MIDDLE:
                input.mouse_middle.pressed = 1;
                input.mouse_middle.first_frame_pressed = 1;
                break;
            case SDL_BUTTON_X1:
                input.mouse_extra_one.pressed = 1;
                input.mouse_extra_one.first_frame_pressed = 1;
                break;
            case SDL_BUTTON_X2:
                input.mouse_extra_two.pressed = 1;
                input.mouse_extra_two.first_frame_pressed = 1;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (sdl_event.button.button)
            {
            case SDL_BUTTON_LEFT:
                input.mouse_left.pressed = 0;
                input.mouse_left.first_frame_released = 1;
                break;
            case SDL_BUTTON_RIGHT:
                input.mouse_right.pressed = 0;
                input.mouse_right.first_frame_released = 1;
                break;
            case SDL_BUTTON_MIDDLE:
                input.mouse_middle.pressed = 0;
                input.mouse_middle.first_frame_released = 1;
                break;
            case SDL_BUTTON_X1:
                input.mouse_extra_one.pressed = 0;
                input.mouse_extra_one.first_frame_released = 1;
                break;
            case SDL_BUTTON_X2:
                input.mouse_extra_two.pressed = 0;
                input.mouse_extra_two.first_frame_released = 1;
                break;
            }
            break;
        case SDL_KEYDOWN:
            switch (sdl_event.key.keysym.sym) 
            {
            case SDLK_a:
                input.a.pressed = 1;
                input.a.first_frame_pressed = 1;
                break;
            case SDLK_b:
                input.b.pressed = 1;
                input.b.first_frame_pressed = 1;
                break;
            case SDLK_c:
                input.c.pressed = 1;
                input.c.first_frame_pressed = 1;
                break;
            case SDLK_d:
                input.d.pressed = 1;
                input.d.first_frame_pressed = 1;
                break;
            case SDLK_e:
                input.e.pressed = 1;
                input.e.first_frame_pressed = 1;
                break;
            case SDLK_f:
                input.f.pressed = 1;
                input.f.first_frame_pressed = 1;
                break;
            case SDLK_g:
                input.g.pressed = 1;
                input.g.first_frame_pressed = 1;
                break;
            case SDLK_h:
                input.h.pressed = 1;
                input.h.first_frame_pressed = 1;
                break;
            case SDLK_i:
                input.i.pressed = 1;
                input.i.first_frame_pressed = 1;
                break;
            case SDLK_j:
                input.j.pressed = 1;
                input.j.first_frame_pressed = 1;
                break;
            case SDLK_k:
                input.k.pressed = 1;
                input.k.first_frame_pressed = 1;
                break;
            case SDLK_l:
                input.l.pressed = 1;
                input.l.first_frame_pressed = 1;
                break;
            case SDLK_m:
                input.m.pressed = 1;
                input.m.first_frame_pressed = 1;
                break;
            case SDLK_n:
                input.n.pressed = 1;
                input.n.first_frame_pressed = 1;
                break;
            case SDLK_o:
                input.o.pressed = 1;
                input.o.first_frame_pressed = 1;
                break;
            case SDLK_p:
                input.p.pressed = 1;
                input.p.first_frame_pressed = 1;
                break;
            case SDLK_q:
                input.q.pressed = 1;
                input.q.first_frame_pressed = 1;
                break;
            case SDLK_r:
                input.r.pressed = 1;
                input.r.first_frame_pressed = 1;
                break;
            case SDLK_s:
                input.s.pressed = 1;
                input.s.first_frame_pressed = 1;
                break;
            case SDLK_t:
                input.t.pressed = 1;
                input.t.first_frame_pressed = 1;
                break;
            case SDLK_u:
                input.u.pressed = 1;
                input.u.first_frame_pressed = 1;
                break;
            case SDLK_v:
                input.v.pressed = 1;
                input.v.first_frame_pressed = 1;
                break;
            case SDLK_w:
                input.w.pressed = 1;
                input.w.first_frame_pressed = 1;
                break;
            case SDLK_x:
                input.x.pressed = 1;
                input.x.first_frame_pressed = 1;
                break;
            case SDLK_y:
                input.y.pressed = 1;
                input.y.first_frame_pressed = 1;
                break;
            case SDLK_z:
                input.z.pressed = 1;
                input.z.first_frame_pressed = 1;
                break;


            case SDLK_0:
                input.zero.pressed = 1;
                input.zero.first_frame_pressed = 1;
                break;
            case SDLK_1:
                input.one.pressed = 1;
                input.one.first_frame_pressed = 1;
                break;
            case SDLK_2:
                input.two.pressed = 1;
                input.two.first_frame_pressed = 1;
                break;
            case SDLK_3:
                input.three.pressed = 1;
                input.three.first_frame_pressed = 1;
                break;
            case SDLK_4:
                input.four.pressed = 1;
                input.four.first_frame_pressed = 1;
                break;
            case SDLK_5:
                input.five.pressed = 1;
                input.five.first_frame_pressed = 1;
                break;
            case SDLK_6:
                input.six.pressed = 1;
                input.six.first_frame_pressed = 1;
                break;
            case SDLK_7:
                input.seven.pressed = 1;
                input.seven.first_frame_pressed = 1;
                break;
            case SDLK_8:
                input.eight.pressed = 1;
                input.eight.first_frame_pressed = 1;
                break;
            case SDLK_9:
                input.nine.pressed = 1;
                input.nine.first_frame_pressed = 1;
                break;


            case SDLK_SPACE:
                input.space.pressed = 1;
                input.space.first_frame_pressed = 1;
                break;
            case SDLK_BACKSPACE:
                input.backspace.pressed = 1;
                input.backspace.first_frame_pressed = 1;
                break;
            case SDLK_LSHIFT:
                input.left_shift.pressed = 1;
                input.left_shift.first_frame_pressed = 1;
                break;
            case SDLK_RSHIFT:
                input.right_shift.pressed = 1;
                input.right_shift.first_frame_pressed = 1;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (sdl_event.key.keysym.sym) {
            case SDLK_a:
                input.a.pressed = 0;
                input.a.first_frame_released = 1;
                break;
            case SDLK_b:
                input.b.pressed = 0;
                input.b.first_frame_released = 1;
                break;
            case SDLK_c:
                input.c.pressed = 0;
                input.c.first_frame_released = 1;
                break;
            case SDLK_d:
                input.d.pressed = 0;
                input.d.first_frame_released = 1;
                break;
            case SDLK_e:
                input.e.pressed = 0;
                input.e.first_frame_released = 1;
                break;
            case SDLK_f:
                input.f.pressed = 0;
                input.f.first_frame_released = 1;
                break;
            case SDLK_g:
                input.g.pressed = 0;
                input.g.first_frame_released = 1;
                break;
            case SDLK_h:
                input.h.pressed = 0;
                input.h.first_frame_released = 1;
                break;
            case SDLK_i:
                input.i.pressed = 0;
                input.i.first_frame_released = 1;
                break;
            case SDLK_j:
                input.j.pressed = 0;
                input.j.first_frame_released = 1;
                break;
            case SDLK_k:
                input.k.pressed = 0;
                input.k.first_frame_released = 1;
                break;
            case SDLK_l:
                input.l.pressed = 0;
                input.l.first_frame_released = 1;
                break;
            case SDLK_m:
                input.m.pressed = 0;
                input.m.first_frame_released = 1;
                break;
            case SDLK_n:
                input.n.pressed = 0;
                input.n.first_frame_released = 1;
                break;
            case SDLK_o:
                input.o.pressed = 0;
                input.o.first_frame_released = 1;
                break;
            case SDLK_p:
                input.p.pressed = 0;
                input.p.first_frame_released = 1;
                break;
            case SDLK_q:
                input.q.pressed = 0;
                input.q.first_frame_released = 1;
                break;
            case SDLK_r:
                input.r.pressed = 0;
                input.r.first_frame_released = 1;
                break;
            case SDLK_s:
                input.s.pressed = 0;
                input.s.first_frame_released = 1;
                break;
            case SDLK_t:
                input.t.pressed = 0;
                input.t.first_frame_released = 1;
                break;
            case SDLK_u:
                input.u.pressed = 0;
                input.u.first_frame_released = 1;
                break;
            case SDLK_v:
                input.v.pressed = 0;
                input.v.first_frame_released = 1;
                break;
            case SDLK_w:
                input.w.pressed = 0;
                input.w.first_frame_released = 1;
                break;
            case SDLK_x:
                input.x.pressed = 0;
                input.x.first_frame_released = 1;
                break;
            case SDLK_y:
                input.y.pressed = 0;
                input.y.first_frame_released = 1;
                break;
            case SDLK_z:
                input.z.pressed = 0;
                input.z.first_frame_released = 1;
                break;


            case SDLK_0:
                input.zero.pressed = 0;
                input.zero.first_frame_released = 1;
                break;
            case SDLK_1:
                input.one.pressed = 0;
                input.one.first_frame_released = 1;
                break;
            case SDLK_2:
                input.two.pressed = 0;
                input.two.first_frame_released = 1;
                break;
            case SDLK_3:
                input.three.pressed = 0;
                input.three.first_frame_released = 1;
                break;
            case SDLK_4:
                input.four.pressed = 0;
                input.four.first_frame_released = 1;
                break;
            case SDLK_5:
                input.five.pressed = 0;
                input.five.first_frame_released = 1;
                break;
            case SDLK_6:
                input.six.pressed = 0;
                input.six.first_frame_released = 1;
                break;
            case SDLK_7:
                input.seven.pressed = 0;
                input.seven.first_frame_released = 1;
                break;
            case SDLK_8:
                input.eight.pressed = 0;
                input.eight.first_frame_released = 1;
                break;
            case SDLK_9:
                input.nine.pressed = 0;
                input.nine.first_frame_released = 1;
                break;


            case SDLK_SPACE:
                input.space.pressed = 0;
                input.space.first_frame_pressed = 0;
                break;
            case SDLK_BACKSPACE:
                input.backspace.pressed = 0;
                input.backspace.first_frame_pressed = 0;
                break;
            case SDLK_LSHIFT:
                input.left_shift.pressed = 0;
                input.left_shift.first_frame_pressed = 0;
                break;
            case SDLK_RSHIFT:
                input.right_shift.pressed = 0;
                input.right_shift.first_frame_pressed = 0;
                break;
            }
            break;
        }
    }

    SDL_GetMouseState(&input.mouse_x, &input.mouse_y);
}

void Engine::ActivateAllMouseLayers()
{
    for (int i = 0; i < mouse_layers.size(); i++)
    {
        mouse_layers[i]->active = 1;
    }
}

void Engine::Run()
{
    running = true;
    while (running) {
        frame_start = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        UpdateInput();

        ActivateAllMouseLayers();


        if (boundary_view_button.press_data.first_frame_released) { boundary_view = !boundary_view; }

        if (input.p.first_frame_pressed) {debug_mode = !debug_mode;}

        if (debug_mode)
        {
            if (input.o.first_frame_pressed) { running_game = !running_game; }
        }

        if (debug_mode)
        {
            if (selected_debug_data_container != &engine_debug_data_container)
            {
                UpdateScrollBar(&debug_data_scroll_bar, blank_camera, &debug_data_scroll_bar_layer, 0, { &debug_data_scroll_bar_layer });
            }

            UpdateButton(&boundary_view_button, blank_camera, &visual_button_layer, 0, { &visual_button_layer });


            saved_label_rects.clear();

            if (camera_view)
            {
                UpdateCameraLabels();
            }

            UpdateDebugData();

            SetDebugDataScrollBarLength();


            if (!running_game)
            {
                MoveDebugCamera();
            }
        }

        //Call run pointer if applicable
        if (debug_mode)
        {
            if (running_game)
            {
                (p->*RunPointer)();
            }
        }
        else
        {
            (p->*RunPointer)();
        }

        //Call draw pointer
        (p->*DrawPointer)();

        //Call post draw run pointer if applicable
        if (debug_mode)
        {
            if (running_game)
            {
                (p->*PostDrawRunPointer)();
            }
        }
        else
        {
            (p->*PostDrawRunPointer)();
        }

        DrawScreen();

        SDL_RenderPresent(renderer);

        frame_duration = SDL_GetTicks() - frame_start;
        if (frame_duration < frame_delay) {
            SDL_Delay(frame_delay - frame_duration); // Wait enough to maintain the desired frame rate
        }
    }
}