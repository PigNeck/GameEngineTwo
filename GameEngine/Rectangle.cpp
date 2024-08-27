#include "Rectangle.h"
#include <iostream>

using namespace std;






// -----------------   CONSTRUCTORS   -----------------

Rectangle::Rectangle() {} //CHECK LATER (is code in the cpp file needed?)

Rectangle::Rectangle(Rectangle* param_reference_rectangle) : reference_rectangle(param_reference_rectangle) {}








void Rectangle::SetReferenceRectangle(Rectangle* const param_reference_rectangle)
{
    reference_rectangle = param_reference_rectangle;
    data.reference_rectangle_data = &param_reference_rectangle->data;


}