#pragma once

struct GLColor
{
	float r = 1.f;
	float g = 1.f;
	float b = 1.f;
	float a = 1.f;

	GLColor();
	GLColor(const float i_r, const float i_g, const float i_b);
	GLColor(const float i_r, const float i_g, const float i_b, const float i_a);
};