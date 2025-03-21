#pragma once
#include "TextBoxChar.h"
#include "Rectangle.h"
#include "DebugDataContainer.h"
#include <vector>
#include <tuple>

using namespace std;

struct Line
{
	RectangleOld rect;
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

	RectangleOld parent_rect;
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






	void BasicInitTextBox(RectangleOld param_parent_rectangle_data, Font* param_font, string param_chars);

	void InitLeast(Font* const param_default_font);
	void InitMost(Font* const param_default_font, const RectangleOld param_parent_rectangle_data, const char* const param_chars, const RigidCentering param_horizontal_centering, const RigidCentering param_vertical_centering, const bool param_text_wrap);

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





/*
struct LineSpacing
{
	double top = 0.0;
	double bottom = 0.0;

	LineSpacing();
	LineSpacing(const double i_top, const double i_bottom);
};
struct IndexedLineSpacing : LineSpacing //If [line_index] is left as numeric_limits<size_t>::max() (which it is set to by default), then the index this object is at in [line_spacings] will be used instead.
{
	size_t line_index = numeric_limits<size_t>::max();

	IndexedLineSpacing();
	IndexedLineSpacing(const double i_top, const double i_bottom);
	IndexedLineSpacing(const double i_top, const double i_bottom, const size_t i_line_index);
};

struct IndexedLineHeight //If [line_index] is left as numeric_limits<size_t>::max() (which it is set to by default), then the index this object is at in [line_heightss] will be used instead.
{
	size_t line_index = numeric_limits<size_t>::max();
	double height;

	IndexedLineHeight();
	IndexedLineHeight(const double height);
	IndexedLineHeight(const double height, const size_t i_line_index);
};
*/

struct BasicLine
{
	// -----------------  Primary Data  -----------------

	RefRectangleNewest rect; //Rotation and Scale are not supported for this rect!

	size_t first_index = 0;
	size_t last_index = 0;

	double last_space_x = 0.0;

	double pixel_spacing_top = 0.0;
	double pixel_spacing_bottom = 0.0;




	// -----------------  Meta Data  -----------------

	const LineParameters* source_parameters = nullptr; //IMPORTANT!!!: If you fiddle around with [BasicTextBox::default_line_parameters] or [BasicTextBox::line_parameters] after generating the lines, you might delete the object this pointer is pointing to, leaving this member variable as a dangling pointer!




	// -----------------  Functions  -----------------

	BasicLine(const RefRectangleNewest i_rect = RefRectangleNewest(), const size_t i_first_index = 0, const size_t i_last_index = 0, const double i_last_space_x = 0.0, const double i_pixel_spacing_top = 0.0, const double i_pixel_spacing_bottom = 0.0, const LineParameters* const i_source_parameters = nullptr);

	double GetLineWidthWithEndingSpaces() const;
	RefRectangleNewest GetLineRectWithEndingSpaces() const;
};

struct BasicTextBox
{
	RefRectangleNewest rect;

	const BasicFont* default_font = nullptr; //When adding chars to a text box and a font is not provided, default_font is used.

	Centering2DNew text_centering; //{ 0.0, 0.0 } = text is centered;  { -1.0, 1.0 } = top left corner of the text is aligned with the top left corner of [rect];  Other values can be used for different centering options!

	LineParameters default_line_parameters;
	vector<IndexedLineParameters> line_parameters = {};

	vector<BasicTextBoxChar> chars = {};

	bool ignore_line_spacing_on_text_box_ends = 0;




	// -----------------   GENERATED DATA   -----------------

	vector<BasicLine> lines = {};




	// -----------------   CONSTRUCTORS/INIT FUNCTIONS   -----------------

	BasicTextBox();
	//This is the constructor you should typically use (unless you need more specific initialization);  Make sure to pass a c-style string literal for [i_text]!;  This constructor also sets [default_line_parameters] to [i_default_font]->template_line_parameters.
	BasicTextBox(const BasicFont* const i_default_font, const RefRectangleNewest i_rect = RefRectangleNewest(), const Centering2DNew i_text_centering = Centering2DNew(), const bool i_ignore_line_spacing_on_text_box_ends = 0);
	//This is the typically non-recommended constructor. It initializes all non-vector member variables directly.
	BasicTextBox(const LineParameters i_default_line_parameters, const BasicFont* const i_default_font = nullptr, const RefRectangleNewest i_rect = RefRectangleNewest(), const Centering2DNew i_text_centering = Centering2DNew(), const bool i_ignore_line_spacing_on_text_box_ends = 0);

	//Recommended;  IMPORTANT!!!: If [i_text] != "", [i_default_font->LoadCharTextures()] must have called before this init function;  Make sure to pass a c-style string literal for [i_text]!;  This method also sets [default_line_parameters] to [i_default_font]->template_line_parameters.
	void Init(const BasicFont* const i_default_font, const char* const i_text = "", const RefRectangleNewest i_rect = RefRectangleNewest(), const Centering2DNew i_text_centering = Centering2DNew(), const bool i_ignore_line_spacing_on_text_box_ends = 0);
	//Not recommended;  IMPORTANT!!!: If [i_text] != "", [i_default_font->LoadCharTextures()] must have called before this init function;
	void Init(const LineParameters i_default_line_parameters, const BasicFont* const i_default_font = nullptr, const char* const i_text = "", const RefRectangleNewest i_rect = RefRectangleNewest(), const Centering2DNew i_text_centering = Centering2DNew(), const bool i_ignore_line_spacing_on_text_box_ends = 0);




	// -----------------   FUNCTIONS   -----------------

	//TODO: seperate GenerateLines() into GenerateLineSizes() and GenerateLinePositions().

	//Calls GenerateLines() and GenerateCharRects() sequentially;  Line positions are generated depending on [rect.centering], so whenever [rect.centering] is changed, lines must be regenerated!
	void GenerateFull();

	//Calls GenerateLineSizes() and GenerateLinePositions sequentially;  Line positions are generated depending on [rect.centering], so whenever [rect.centering] is changed, lines must be either moved manually or regenerated!
	void GenerateLines();
	//Clears [lines] and adds all the generated lines to it afterwards. GenerateLinePositions() only adjusts the lines added by this method.
	void GenerateLineSizes();
	//This method only adjusts the lines previously added by GenerateLineSizes;  Line positions are generated depending on [rect.centering], so whenever [rect.centering] is changed, lines must be either moved manually or regenerated!
	void GenerateLinePositions();

	//Uses [lines[i].begin_index] and [lines[i].end_index] to define where each char is placed.
	void GenerateCharRects();



	//The new BasicTextBoxChar will inherit the template values from [default_font];  If more control is needed (over the member variables of the new BasicTextBoxChar), BasicTextBoxChars can also be added to [chars] directly!
	void AddChar(const char char_value);
	//The new BasicTextBoxChar will inherit the template values from [default_font] (aside from the color_mod);  If more control is needed (over the member variables of the new BasicTextBoxChar), BasicTextBoxChars can also be added to [chars] directly!
	void AddChar(const char char_value, const GLColor overwriting_color_mod);
	//The new BasicTextBoxChar will inherit the template values from [default_font] (aside from the scale);  If more control is needed (over the member variables of the new BasicTextBoxChar), BasicTextBoxChars can also be added to [chars] directly!
	void AddChar(const char char_value, const Scale90 overwriting_scale);
	//The new BasicTextBoxChar will inherit the template values from [default_font] (aside from the color_mod and scale);  If more control is needed (over the member variables of the new BasicTextBoxChar), BasicTextBoxChars can also be added to [chars] directly!
	void AddChar(const char char_value, const GLColor overwriting_color_mod, const Scale90 overwriting_scale);

	//Suggested for adding string literals!;  The new BasicTextBoxChars will inherit the template values from [default_font];  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddCharPtr(const char* chars);
	//Suggested for adding string literals!;  The new BasicTextBoxChars will inherit the template values from [default_font] (aside from the color_mod);  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddCharPtr(const char* chars, const GLColor overwriting_color_mod);
	//Suggested for adding string literals!;  The new BasicTextBoxChars will inherit the template values from [default_font] (aside from the scale);  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddCharPtr(const char* chars, const Scale90 overwriting_scale);
	//Suggested for adding string literals!;  The new BasicTextBoxChars will inherit the template values from [default_font] (aside from the color_mod and scale);  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddCharPtr(const char* chars, const GLColor overwriting_color_mod, const Scale90 overwriting_scale);

	//The new BasicTextBoxChars will inherit the template values from [default_font];  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddString(const string string_value);
	//The new BasicTextBoxChars will inherit the template values from [default_font] (aside from the color_mod);  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddString(const string string_value, const GLColor overwriting_color_mod);
	//The new BasicTextBoxChars will inherit the template values from [default_font] (aside from the scale);  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddString(const string string_value, const Scale90 overwriting_scale);
	//The new BasicTextBoxChars will inherit the template values from [default_font] (aside from the color_mod and scale);  If more control is needed (over the member variables of the new BasicTextBoxChars), BasicTextBoxChars can also be added to [chars] directly!
	void AddString(const string string_value, const GLColor overwriting_color_mod, const Scale90 overwriting_scale);


	//Empties both the [chars] and [lines] vectors.
	void Clear();


	//Returns the unscaled length of the longest line in the text_box on the plane of this.[rect]. Includes the length of the spaces on the line ends if specified.
	double GetTextBindingWidth(const bool p_include_ending_spaces = 0) const;
	//Returns the unscaled total vertical space taken up by all the lines in the text_box on the plane of this.[rect]. Includes the length of the spaces on the line ends if specified.
	double GetTextBindingHeight() const;
	//Returns the rectangle relative to [rect] that covers all of the actual space taken up by the text.
	RefRectangleNewest GetTextBinding(const bool p_include_ending_spaces = 0) const;


	//Indexed elements ARE INCLUDED. end_index can go beyond the size of [chars]!
	string GetSegmentText(const size_t begin_index = 0, const size_t end_index = numeric_limits<size_t>::max()) const;
	//Indexed elements ARE INCLUDED. end_index can go beyond the size of [chars]!
	vector<RectStructOne>* GetSegmentHitbox(const size_t begin_index = 0, const size_t end_index = numeric_limits<size_t>::max()) const;


	LineParameters* GetLineParameters(const size_t line_index);
	const LineParameters* GetLineParametersConst(const size_t line_index) const;


private:
	double GetHighestCharHeightScale(const size_t begin_index, const size_t end_index) const;



	/*

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
	*/
};