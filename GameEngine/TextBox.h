#pragma once
#include "TextBoxChar.h"
#include "Rectangle.h"
#include "DebugDataContainer.h"
#include <vector>
#include <tuple>

using namespace std;

struct Line
{
	Rectangle rect;
	int first_index = 0;
	int last_index = 0;

	DebugDataContainer debug_data_container;

	void Init();

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes);
};

struct TextBox
{
	//double default_text_box_horizontal_scale = 1.0;
	//double default_text_box_vertical_scale = 1.0;




	// -----------------   PARAMETER DATA   -----------------

	Rectangle parent_rect;
	Font* default_text_box_font;

	RigidCentering horizontal_text_centering;
	RigidCentering vertical_text_centering;

	//On both sides. scales with rect.GetHeightScale()
	double default_line_spacing;
	vector<double> line_spacing;

	double default_line_height;
	vector<double> line_height;

	bool text_wrap;

	vector<TextBoxChar> chars;





	// -----------------   GENERATED DATA   -----------------

	vector<Line> lines;






	// -----------------   DEBUG DATA   -----------------

	DebugDataContainer debug_data_container;






	void BasicInitTextBox(RectangleData param_parent_rectangle_data, Font* param_font, string param_chars);

	void InitLeast(Font* const param_default_font);
	void InitMost(Font* const param_default_font, const RectangleData param_parent_rectangle_data, const char* const param_chars, const RigidCentering param_horizontal_centering, const RigidCentering param_vertical_centering, const bool param_text_wrap);

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

	TextBox();

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes);

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