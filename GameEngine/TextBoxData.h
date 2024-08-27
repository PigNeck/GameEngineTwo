#pragma once
#include "RectangleData.h"
#include "Font.h"
#include <vector>
#include "TextBoxCharData.h"

struct LineData
{
	RectangleData rectangle_data;
	int first_index = 0;
	int last_index = 0;

	void Init();
};

struct TextBoxData
{
	// -----------------   PARAMETER DATA   -----------------

	RectangleData parent_rectangle_data;
	Font* default_text_box_font;

	RigidCentering horizontal_text_centering;
	RigidCentering vertical_text_centering;

	//On both sides. scales with rect.GetHeightScale()
	double default_line_spacing;
	vector<double> line_spacing;

	double default_line_height;
	vector<double> line_height;

	vector<TextBoxCharData> chars;






	// -----------------   GENERATED DATA   -----------------

	vector<LineData> lines;






	void BasicInitTextBox(RectangleData param_parent_rectangle_data, Font* param_font, string param_chars);

	void InitLeast(Font* const param_default_font);
	void InitMost(Font* const param_default_font, const RectangleData param_parent_rectangle_data, const char* const param_chars, const RigidCentering param_horizontal_centering, const RigidCentering param_vertical_centering);

	void UpdateCharPos();
	void GenerateLineSizes();
	void GenerateLinePositions();
	void GenerateCharPositions();

	void AddChar(char param_char);
	void AddChar(char param_char, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod);
	void AddString(string param_string);
	void AddString(string param_string, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod);
	void AddCharPtr(const char* param_char_pointer);
	void AddCharPtr(const char* param_char_pointer, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod);

	void Clear();

	double GetActualBaseWidth();
	double GetActualBaseHeight();

	TextBoxData();

	void SetDefaultFont(Font* param_default_font);

private:
	void GetLineLength();
	void GetLineLengths();


	double GetLineCenteredY(int index);
	tuple<double, double> GetCurrentXAndY(int index);

	double GetLineHeight(int index);
	double GetLineSpacing(int index);

	void GenerateLine(const int starting_char_index, const int line_index, int* const next_starting_index);



	double GetLineHeightWithPreviousSpacing(int index);
};

