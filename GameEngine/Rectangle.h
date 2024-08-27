#pragma once
#include "SDL.h"
#include "RectangleData.h"

struct Rectangle
{
    // -----------------   DATA   -----------------
    RectangleData data;
    Rectangle* reference_rectangle = nullptr;






    // -----------------   CONSTRUCTORS   -----------------

    Rectangle();
    Rectangle(Rectangle* param_reference_rectangle);






    // -----------------   EXTRA FUNCTIONS   -----------------

    void SetReferenceRectangle(Rectangle* const param_reference_rectangle);
};