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
	size_t first_index = 0;
	size_t last_index = 0;

	DebugDataContainer debug_data_container;

	void Init();

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list);
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

	vector<TextBoxChar*> chars;





	// -----------------   GENERATED DATA   -----------------

	vector<Line*> lines;






	// -----------------   DEBUG DATA   -----------------

	DebugDataContainer debug_data_container;






	void BasicInitTextBox(Rectangle param_parent_rectangle_data, Font* param_font, string param_chars);

	void InitLeast(Font* const param_default_font);
	void InitMost(Font* const param_default_font, const Rectangle param_parent_rectangle_data, const char* const param_chars, const RigidCentering param_horizontal_centering, const RigidCentering param_vertical_centering, const bool param_text_wrap);

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

	TextBox();

	void CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list);

	void SetDefaultFont(Font* param_default_font);

	string GetText();
	//Indexed elements ARE INCLUDED
	string GetText(const size_t begin_index, const size_t end_index);

	//UNTESTED
	vector<RectStructOne>* GetSegmentHitbox(size_t begin_index, size_t end_index);

	//UNTESTED If can_return_nullptr, returns nullptr if char belongs to no line. (Spaces at the ends of lines or \n chars have no associated line). If not, the line that is returned is determined by return_next_line. If the next line (or previous line) does not exist, then the function will return the line closest existing line to the non-existent line. STILL RETURNS NULLPTR IF LINES.SIZE() == 0
	Line* GetLineWithCharIndex(const size_t char_index, const bool can_return_nullptr, const bool return_next_line);
	size_t GetLineIndexWithCharIndex(const size_t char_index, const bool can_return_nullptr, const bool return_next_line);

	//Returns numeric_limits<size_t>::max() if line not found
	size_t GetLineIndexWithLinePointer(const Line* const line_ptr) const;

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