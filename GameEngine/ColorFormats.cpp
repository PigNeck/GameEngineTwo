#include "ColorFormats.h"

namespace {
    float GetFloatSnapped0To1(const float value)
    {
        if (signbit(value))
        {
            return 0.f;
        }
        if (value > 1.f)
        {
            return 1.f;
        }
        return value;
    }

    //Use std::fmod(...) instead if [value] is never negative!
    float GetFloatLooped0ToUpperBound(const float value, const float upper_bound)
    {
        double result = fmod(value, upper_bound);
        if (result < 0.0)
        {
            result += upper_bound;
        }
        return result;
    }
}

GLColor::GLColor(const float i_r, const float i_g, const float i_b, const float i_a)
    : r(i_r), g(i_g), b(i_b), a(i_a) {}
GLColor::GLColor(const HSVA& i_hsva) : a(i_hsva.GetBaseA())
{
    //ChatGPT-ahh code {
    //TO-DO: optimize?

    const float base_h = i_hsva.GetBaseH();
    const float base_s = i_hsva.GetBaseS();
    const float base_v = i_hsva.GetBaseV();
    const float floored_base_h = floor(base_h);

    const int i = static_cast<int>(floored_base_h); // sector 0 to 5
    const float f = base_h - floored_base_h; // fractional part

    const float p = base_v * (1.f - base_s);
    const float q = base_v * (1.f - f * base_s);
    const float t = base_v * (1.f - (1.f - f) * base_s);

    switch (i) {
    case 0: r = base_v; g = t; b = p; break;
    case 1: r = q; g = base_v; b = p; break;
    case 2: r = p; g = base_v; b = t; break;
    case 3: r = p; g = q; b = base_v; break;
    case 4: r = t; g = p; b = base_v; break;
    case 5: r = base_v; g = p; b = q; break;
    default: r = g = b = 0.0f; break; // should not happen
    }
    //}
}

void GLColor::SetRToBaseR()
{
    r = GetBaseR();
}
float GLColor::GetBaseR() const
{
    return GetFloatSnapped0To1(r);
}

void GLColor::SetGToBaseG()
{
    g = GetBaseG();
}
float GLColor::GetBaseG() const
{
    return GetFloatSnapped0To1(g);
}

void GLColor::SetBToBaseB()
{
    b = GetBaseB();
}
float GLColor::GetBaseB() const
{
    return GetFloatSnapped0To1(b);
}

void GLColor::SetAToBaseA()
{
    a = GetBaseA();
}
float GLColor::GetBaseA() const
{
    return GetFloatSnapped0To1(a);
}




HSVA::HSVA(const float i_h, const float i_s, const float i_v, const float i_a)
    : h(i_h), s(i_s), v(i_v), a(i_a) {}
HSVA::HSVA(const GLColor& i_gl_color) : a(i_gl_color.GetBaseA())
{
    //ChatGPT-ahh code {
    //TO-DO: optimize?

    const float base_r = i_gl_color.GetBaseR();
    const float base_g = i_gl_color.GetBaseG();
    const float base_b = i_gl_color.GetBaseB();

    float max = fmax(fmax(base_r, base_g), base_b);
    float min = fmin(fmin(base_r, base_g), base_b);
    float delta = max - min;

    if (delta > 0.f) {
        if (max == base_r) {
            h = (base_g - base_b) / delta;
            if (h < 0.f) h += 6.f;
        }
        else if (max == base_g) {
            h = (base_b - base_r) / delta + 2.f;
        }
        else { //max == base_b
            h = (base_r - base_g) / delta + 4.f;
        }
    }
    else {
        h = 0.f; //undefined hue when base_r == base_g == base_b (gray), but we pick 0
    }

    s = (max == 0.f) ? 0.f : delta / max;
    v = max;
    //}
}

void HSVA::SetHToBaseH()
{
    h = GetBaseH();
}
float HSVA::GetBaseH() const
{
    return GetFloatLooped0ToUpperBound(h, 6.0);
}

void HSVA::SetSToBaseS()
{
    s = GetBaseS();
}
float HSVA::GetBaseS() const
{
    return GetFloatSnapped0To1(s);
}

void HSVA::SetVToBaseV()
{
    v = GetBaseV();
}
float HSVA::GetBaseV() const
{
    return GetFloatSnapped0To1(v);
}

void HSVA::SetAToBaseA()
{
    a = GetBaseA();
}
float HSVA::GetBaseA() const
{
    return GetFloatSnapped0To1(a);
}