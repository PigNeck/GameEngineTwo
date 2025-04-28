#pragma once
#include <cmath>

struct HSVA;
struct GLColor
{
	float r;
	float g;
	float b;
	float a;

	//Default is opaque white btw
	GLColor(const float i_r = 1.f, const float i_g = 1.f, const float i_b = 1.f, const float a = 1.f);
	GLColor(const HSVA& i_hsva);

	//Sets r to its base value on the interval [0.f, 1.f]
	void SetRToBaseR();
	//Gets the base value of r on the interval [0.f, 1.f]
	float GetBaseR() const;

	//Sets g to its base value on the interval [0.f, 1.f]
	void SetGToBaseG();
	//Gets the base value of g on the interval [0.f, 1.f]
	float GetBaseG() const;

	//Sets b to its base value on the interval [0.f, 1.f]
	void SetBToBaseB();
	//Gets the base value of b on the interval [0.f, 1.f]
	float GetBaseB() const;

	//Sets a to its base value on the interval [0.f, 1.f]
	void SetAToBaseA();
	//Gets the base value of a on the interval [0.f, 1.f]
	float GetBaseA() const;
};

struct HSVA
{
	float h; //Hue;  repeats every 6.f (for the 6 different sectors of color!);  0.f is red;
	float s; //Saturation;  Ranges from 0.f (greyscale) to 1.f (vibrant);  Anything outside of this range is treated as either 0 or 1 accordingly.
	float v; //Value, aka. lightness;  Ranges from 0.f (full black) to 1.f (no black);  Anything outside of this range is treated as either 0 or 1 accordingly.
	float a; //Ranges from 0.f (invisible) to 1.f (opaque);  Anything outside of this range is treated as either 0 or 1 accordingly.

	//Default is vibrant opaque red btw
	HSVA(const float i_h = 0.f, const float i_s = 1.f, const float i_v = 1.f, const float i_a = 1.f);
	HSVA(const GLColor& i_gl_color);

	//Sets h to its base value on the interval [0.f, 6.f)
	void SetHToBaseH();
	//Gets the base value of h on the interval [0.f, 6.f)
	float GetBaseH() const;

	//Sets s to its base value on the interval [0.f, 1.f]
	void SetSToBaseS();
	//Gets the base value of s on the interval [0.f, 1.f]
	float GetBaseS() const;

	//Sets v to its base value on the interval [0.f, 1.f]
	void SetVToBaseV();
	//Gets the base value of v on the interval [0.f, 1.f]
	float GetBaseV() const;

	//Sets a to its base value on the interval [0.f, 1.f]
	void SetAToBaseA();
	//Gets the base value of a on the interval [0.f, 1.f]
	float GetBaseA() const;
};