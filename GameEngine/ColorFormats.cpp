#include "ColorFormats.h"

GLColor::GLColor() {}
GLColor::GLColor(const float i_r, const float i_g, const float i_b) : r(i_r), g(i_g), b(i_b), a(1.f) {}
GLColor::GLColor(const float i_r, const float i_g, const float i_b, const float i_a) : r(i_r), g(i_g), b(i_b), a(i_a) {}