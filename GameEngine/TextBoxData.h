#pragma once
#include "Rectangle.h"
#include "Font.h"
#include <vector>
#include "TextBoxCharData.h"

struct LineData
{
	Rectangle rectangle;
	int first_index = 0;
	int last_index = 0;

	void Init();
};

struct TextBoxData
{
	// -----------------   PARAMETER DATA   -----------------

	Rectangle parent_rectangle;
	Font* default_text_box_font;

	RigidCentering horizontal_text_centering;
	RigidCentering vertical_text_centering;

	//On both sides. scales with rect.GetHeightScale()
	double default_line_spacing;
	vector<double> line_spacing;

	double default_line_height;
	vector<double> line_height;

	vector<TextBoxCharData*> chars;






	// -----------------   GENERATED DATA   -----------------

	vector<LineData*> lines;






	void BasicInitTextBox(Rectangle param_parent_rectangle, Font* param_font, string param_chars);

	void InitLeast(Font* const param_default_font);
	void InitMost(Font* const param_default_font, const Rectangle param_parent_rectangle, const char* const param_chars, const RigidCentering param_horizontal_centering, const RigidCentering param_vertical_centering);

	void UpdateCharPos();
	void GenerateLineSizes();
	void GenerateLinePositions();
	void GenerateCharPositions();

	void AddChar(char param_char);
	void AddChar(char param_char, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod);
	void AddString(string param_string);
	void AddString(string param_string, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod);
	void AddCharPtr(const char* param_char_pointer);
	void AddCharPtr(const char* param_char_pointer, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod);

	void Clear();

	double GetActualBaseWidth();
	double GetActualBaseHeight();

	TextBoxData();

	void SetDefaultFont(Font* param_default_font);

	string GetText();
	//Indexed elements ARE INCLUDED
	string GetText(const size_t begin_index, const size_t end_index);

	vector<RectStructOne>* GetSegmentHitbox(size_t begin_index, size_t end_index);

	//UNTESTED If can_return_nullptr, returns nullptr if char belongs to no line. (Spaces at the ends of lines or \n chars have no associated line). If not, the line that is returned is determined by return_next_line. If the next line (or previous line) does not exist, then the function will return the line closest existing line to the non-existent line. STILL RETURNS NULLPTR IF LINES.SIZE() == 0
	LineData* GetLineWithCharIndex(const size_t char_data_index, const bool can_return_nullptr, const bool return_next_line);
	size_t GetLineIndexWithCharIndex(const size_t char_data_index, const bool can_return_nullptr, const bool return_next_line);

	//Returns numeric_limits<size_t>::max() if line not found
	size_t GetLineIndexWithLinePointer(const LineData* const line_data_ptr) const;

private:
	double GetLineHeight(int index);
	double GetLineSpacing(int index);

	void GenerateLine(const int starting_char_index, const int line_index, int* const next_starting_index);



	double GetLineHeightWithPreviousSpacing(int index);
};

