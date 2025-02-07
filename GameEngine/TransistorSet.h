#pragma once
#include "Engine.h"
#include <iostream>
#include <vector>
#include <bitset>

// 1 NEEDS to be width of outline
#define T_WIDTH 6.0
#define T_HEIGHT 8.0

#define T_ONE_LESS_WIDTH 5.0
#define T_HALF_WIDTH 3.0

#define T_INNER_WIDTH 4.0
#define T_INNER_HEIGHT 6.0

using namespace std;

struct Cell
{
	bool state = 0;

	double animation_movement_percent = 0.0;
	double animation_color_percent = 0.0;

	void Click(const bool target_state);

	//Clicks should be done BEFORE Update() is called
	void Update(const double frame_factor_inverse);
};

struct CellSet
{
	TextBox number_display;
	//TextBox relative_number_display;

	vector<Cell*> set = {};

	Point2D pos;
	Size2D size_scale;

	void InitLeast(Font* const num_display_font);

	void UpdateNumberDisplay(const size_t selected_index);

	void ClickAll(const bool target_state);
	void Click(const size_t index, const bool target_state);

	//Clicks all the transistors from begin_index to end_index, including both begin_index and end_index
	void ClickSection(const size_t begin_index, const size_t end_index, const bool target_state);

	//Clicks 8 transistors starting at and including the begin_index according to the char variable passed
	void ClickChar(const char value, const size_t begin_index, const bool target_state);

	//Clicks 8 transistors starting at and including the begin_index according to the char variable passed
	void ClickShort(const short value, const size_t begin_index, const bool target_state);

	//Clicks 32 transistors starting at and including the begin_index according to the char variable passed
	void ClickUnsigned32Int(const uint32_t value, const size_t begin_index, const bool target_state);


	Size2D GetTrueScale() const;

	RectangleOld GenerateFullHitbox() const;
	RectangleOld GenerateFullInnerHitbox() const;
	RectangleOld GenerateHitbox(const size_t index) const;
	RectangleOld GenerateInnerHitbox(const size_t index) const;

	//Only includes half of each of the two horizontal sides (if applicable)
	RectangleOld GenerateHitboxCropped(const size_t index) const;

	RectangleOld GenerateHitboxRange(const size_t begin_index, const size_t end_index) const;
	RectangleOld GenerateInnerHitboxRange(const size_t begin_index, const size_t end_index) const;
	//Only includes half of each of the two horizontal sides (if applicable)
	RectangleOld GenerateHitboxRangeCropped(const size_t begin_index, const size_t end_index) const;
};

