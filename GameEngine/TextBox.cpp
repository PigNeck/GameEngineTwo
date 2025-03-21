#include "TextBox.h"

void Line::Init()
{
	//Do nothing lmao
}

void Line::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list)
{
	debug_data_container.InitLeast(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &rect, param_debug_data_container_active_scenes, param_white_list);
	debug_data_container.AddRectangleData(&rect, "Rect");
	//debug_data_container.AddInt(&first_index, "First index");
	//debug_data_container.AddInt(&last_index, "Last index");
	//Add stuff like default_font name and so on later
}






void TextBox::BasicInitTextBox(RectangleOld param_parent_rectangle_data, Font* param_font, string param_chars)
{
	Clear();

	parent_rect = param_parent_rectangle_data;

	default_text_box_font = param_font;

	default_line_spacing = param_font->default_default_line_spacing;
	default_line_height = param_font->default_default_line_height;

	for (int i = 0; i < param_chars.size(); i++)
	{
		chars.push_back(new TextBoxChar());
		chars.back()->InitLeast(&parent_rect, param_font->GetFontChar(param_chars[i]));
	}
}

void TextBox::InitLeast(Font* const param_default_font)
{
	Clear();

	SetDefaultFont(param_default_font);
}
void TextBox::InitMost(Font* const param_default_font, const RectangleOld param_parent_rectangle_data, const char* const param_chars, const RigidCentering param_horizontal_centering, const RigidCentering param_vertical_centering, const bool param_text_wrap)
{
	Clear();

	SetDefaultFont(param_default_font);
	parent_rect = param_parent_rectangle_data;
	AddCharPtr(param_chars);
	horizontal_text_centering = param_horizontal_centering;
	vertical_text_centering = param_vertical_centering;
	text_wrap = param_text_wrap;

	UpdateCharPos();
}

double TextBox::GetLineHeight(int index)
{
	if (index < line_height.size())
	{
		return line_height[index];
	}
	else
	{
		return default_line_height;
	}
}
double TextBox::GetLineSpacing(int index)
{
	if (index < line_spacing.size())
	{
		return line_spacing[index];
	}
	else
	{
		return default_line_spacing;
	}
}

void TextBox::GenerateLine(const int starting_char_index, const int line_index, int* const next_starting_index)
{
	//Cancel function if there are no chars
	if (chars.size() == 0)
	{
		return;
	}


	// -----------------   INITIALIZE LOCAL VARIABLES   -----------------

	double saved_line_width = NULL;
	double current_line_width = 0.0;

	bool space_in_line = 0;
	int saved_char_index = NULL;
	int current_char_index = starting_char_index;

	bool broke_from_loop = 0;
	bool new_line_encountered = 0;






	// -----------------   ADD FIRST BLUEPRINT CHAR TO LINE   -----------------

	current_line_width += chars[current_char_index]->rect.size.width;

	//Increment char index
	current_char_index++;






	// -----------------   LOOP OVER REST OF BLUEPRINT CHARS   -----------------

	while (current_char_index < chars.size())
	{
		//Save line width and char index if applicable
		if (!space_in_line)
		{
			saved_char_index = current_char_index - 1;
			saved_line_width = current_line_width;
		}
		if (chars[current_char_index]->font_char->char_value == ' ')
		{
			saved_char_index = current_char_index - 1;
			saved_line_width = current_line_width;
			space_in_line = 1;
		}
		if (chars[current_char_index]->font_char->char_value == '\n')
		{
			saved_char_index = current_char_index - 1;
			saved_line_width = current_line_width;
		}

		//Add current char and spacing to width
		current_line_width += chars[current_char_index - 1]->char_spacing;
		current_line_width += chars[current_char_index]->char_spacing;
		current_line_width += chars[current_char_index]->rect.size.width;

		//If current_char == '\n'
		if (chars[current_char_index]->font_char->char_value == '\n')
		{
			broke_from_loop = 1;
			new_line_encountered = 1;
			break;
		}

		//If width exceeds limit, new line
		if ((current_line_width > parent_rect.base_size.width) && text_wrap)
		{
			broke_from_loop = 1;
			break;
		}

		//Increment char index
		current_char_index++;
	}






	// -----------------   INTERPRET DATA   -----------------

	if (broke_from_loop)
	{
		//Create a line rect with only width and height data
		lines.push_back(new Line());
		lines.back()->Init();

		if (debug_data_container.owners.size() != 0)
		{
			string temp_to_string = "Line ";
			temp_to_string += to_string(lines.size() - 1);
			const char* temp_name = temp_to_string.c_str();
			lines.back()->CreateDebugData({ &debug_data_container }, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
		}

		lines.back()->rect.base_size.width = saved_line_width;
		lines.back()->rect.base_size.height = GetLineHeight(line_index);
		lines.back()->rect.SetSizeWithSizeScale({ 1.0, 1.0 });
		lines.back()->rect.reference_rectangle = &parent_rect;
		lines.back()->first_index = starting_char_index;
		lines.back()->last_index = saved_char_index;

		int temp_next_starting_index;
		if (space_in_line || new_line_encountered)
		{
			temp_next_starting_index = saved_char_index + 2;
		}
		else
		{
			temp_next_starting_index = saved_char_index + 1;
		}

		if (temp_next_starting_index < chars.size())
		{
			//New line starting at temp_next_starting_index
			*next_starting_index = temp_next_starting_index;
		}
		else
		{
			//No new line
			*next_starting_index = -1;
		}
	}
	else
	{
		//Create a line rect with only width and height data
		lines.push_back(new Line());
		lines.back()->Init();

		if (debug_data_container.owners.size() != 0)
		{
			string temp_to_string = "Line ";
			temp_to_string += to_string(lines.size() - 1);
			const char* temp_name = temp_to_string.c_str();
			lines.back()->CreateDebugData({ &debug_data_container }, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
		}

		lines.back()->rect.base_size.width = current_line_width;
		lines.back()->rect.base_size.height = GetLineHeight(line_index);
		lines.back()->rect.SetSizeWithSizeScale({ 1.0, 1.0 });
		lines.back()->rect.reference_rectangle = &parent_rect;
		lines.back()->first_index = starting_char_index;
		lines.back()->last_index = chars.size() - 1;

		//No new line
		*next_starting_index = -1;
	}
}

void TextBox::UpdateCharPos()
{
	//Cancel function if there are no chars
	if (chars.size() == 0)
	{
		return;
	}

	GenerateLineSizes();
	GenerateLinePositions();
	GenerateCharPositions();
}

void TextBox::GenerateLineSizes()
{
	lines.clear();

	//Cancel function if there are no chars
	if (chars.size() == 0)
	{
		return;
	}

	int starting_index = 0;
	int line_index = 0;

	while (starting_index != -1)
	{
		GenerateLine(starting_index, line_index, &starting_index);
		line_index++;
	}
}
void TextBox::GenerateLinePositions()
{
	//Cancel function if there are no chars
	if (chars.size() == 0)
	{
		return;
	}

	// --------   LINE X   --------
	switch (horizontal_text_centering.value)
	{
	case 0:
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]->rect.pos.x = (parent_rect.base_size.width - lines[i]->rect.size.width) / -2.0;
		}
		break;
	case 1:
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]->rect.pos.x = 0.0;
		}
		break;
	case 2:
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]->rect.pos.x = (parent_rect.base_size.width - lines[i]->rect.size.width) / 2.0;
		}
		break;
	case 3:
		//Bruh this ain't defined
		//Sea kelp
		break;
	}




	// --------   LINE Y   --------
	double actual_height;
	double temp_line_y = 0.0;

	switch (vertical_text_centering.value)
	{
	case 0:
		if (lines.size() > 0)
		{
			actual_height = GetActualBaseHeight();
			temp_line_y = (parent_rect.base_size.height / -2.0) + actual_height;
		}
		break;
	case 1:
		if (lines.size() > 0)
		{
			actual_height = GetActualBaseHeight();
			temp_line_y = (actual_height / 2.0);
		}
		break;
	case 2:
		if (lines.size() > 0)
		{
			temp_line_y = (parent_rect.base_size.height / 2.0);
		}
		break;
	case 3:
		//Bruh this ain't defined
		//Sea kelp
		break;
	}

	if (lines.size() > 0)
	{
		temp_line_y -= (lines[0]->rect.size.height / 2.0);
		lines[0]->rect.pos.y = temp_line_y;

		for (int i = 1; i < lines.size(); i++)
		{
			temp_line_y -= (lines[i - 1]->rect.size.height / 2.0);
			temp_line_y -= GetLineSpacing(i - 1);
			temp_line_y -= GetLineSpacing(i);
			temp_line_y -= (lines[i]->rect.size.height / 2.0);
			lines[i]->rect.pos.y = temp_line_y;
		}
	}
}
void TextBox::GenerateCharPositions()
{
	//Cancel function if there are no chars
	if (chars.size() == 0)
	{
		return;
	}

	for (size_t i = 0; i < lines.size(); i++)
	{
		double temp_char_x = lines[i]->rect.pos.x - (lines[i]->rect.size.width / 2.0);
		temp_char_x += chars[lines[i]->first_index]->rect.size.width / 2.0;
		chars[lines[i]->first_index]->rect.pos.x = temp_char_x;
		chars[lines[i]->first_index]->rect.pos.y = lines[i]->rect.pos.y - ((lines[i]->rect.size.height - chars[lines[i]->first_index]->rect.size.height) / 2.0);

		for (size_t j = lines[i]->first_index + 1; j <= lines[i]->last_index; j++)
		{
			chars[j]->rect.pos.y = lines[i]->rect.pos.y - ((lines[i]->rect.size.height - chars[j]->rect.size.height) / 2.0);

			temp_char_x += chars[j - 1]->rect.size.width / 2.0;
			temp_char_x += chars[j - 1]->char_spacing;
			temp_char_x += chars[j]->char_spacing;
			temp_char_x += chars[j]->rect.size.width / 2.0;
			chars[j]->rect.pos.x = temp_char_x;
		}
	}
}



void TextBox::AddChar(char param_char)
{
	if (default_text_box_font)
	{
		chars.push_back(new TextBoxChar());
		chars.back()->InitLeast(&parent_rect, default_text_box_font->GetFontChar(param_char));

		if (debug_data_container.owners.size() != 0)
		{
			string temp_to_string = "Char ";
			temp_to_string += to_string(chars.size() - 1);
			const char* temp_name = temp_to_string.c_str();
			chars.back()->CreateDebugData({ &debug_data_container }, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first\n";
	}
}
void TextBox::AddChar(char param_char, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod)
{
	if (default_text_box_font)
	{
		chars.push_back(new TextBoxChar());
		chars.back()->InitMost(&parent_rect, default_text_box_font->GetFontChar(param_char), r_mod, g_mod, b_mod, a_mod);

		if (debug_data_container.owners.size() != 0)
		{
			string temp_to_string = "Char ";
			temp_to_string += to_string(chars.size() - 1);
			const char* temp_name = temp_to_string.c_str();
			chars.back()->CreateDebugData({ &debug_data_container }, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first\n";
	}
}
void TextBox::AddString(string param_string)
{
	if (default_text_box_font)
	{
		for (int i = 0; i < param_string.size(); i++)
		{
			chars.push_back(new TextBoxChar());
			chars.back()->InitLeast(&parent_rect, default_text_box_font->GetFontChar(param_string[i]));

			if (debug_data_container.owners.size() != 0)
			{
				string temp_to_string = "Char ";
				temp_to_string += to_string(chars.size() - 1);
				const char* temp_name = temp_to_string.c_str();
				chars.back()->CreateDebugData({ &debug_data_container }, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
			}
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first\n";
	}
}
void TextBox::AddString(string param_string, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod)
{
	if (default_text_box_font)
	{
		for (int i = 0; i < param_string.size(); i++)
		{
			chars.push_back(new TextBoxChar());
			chars.back()->InitMost(&parent_rect, default_text_box_font->GetFontChar(param_string[i]), r_mod, g_mod, b_mod, a_mod);

			if (debug_data_container.owners.size() != 0)
			{
				string temp_to_string = "Char ";
				temp_to_string += to_string(chars.size() - 1);
				const char* temp_name = temp_to_string.c_str();
				chars.back()->CreateDebugData({ &debug_data_container }, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
			}
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first\n";
	}
}
void TextBox::AddCharPtr(const char* param_char_pointer)
{
	if (default_text_box_font)
	{
		while (*param_char_pointer != '\0') 
		{
			AddChar(*param_char_pointer);
			param_char_pointer++;
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first\n";
	}
}
void TextBox::AddCharPtr(const char* param_char_pointer, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod)
{
	if (default_text_box_font)
	{
		while (*param_char_pointer != '\0') 
		{
			AddChar(*param_char_pointer, r_mod, g_mod, b_mod, a_mod);
			param_char_pointer++;
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first\n";
	}
}

void TextBox::Clear()
{
	for (int i = 0; i < chars.size(); i++)
	{
		delete chars[i];
	}

	chars.clear();
	lines.clear();
}

double TextBox::GetActualBaseWidth()
{
	double highest_width = 0.0;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->rect.size.width > highest_width)
		{
			highest_width = lines[i]->rect.size.width;
		}
	}

	return highest_width;
}
double TextBox::GetActualBaseHeight()
{
	if (lines.size() > 0)
	{
		double temp_height = 0.0;

		temp_height = lines[0]->rect.size.height;

		for (int i = 1; i < lines.size(); i++)
		{
			temp_height += GetLineHeightWithPreviousSpacing(i);
		}

		return temp_height;
	}
	else
	{
		return 0.0;
	}
}

double TextBox::GetLineHeightWithPreviousSpacing(int index)
{
	double temp_height = 0.0;

	if ((index < lines.size()) && (index >= 0))
	{
		if (index > 0)
		{
			temp_height += GetLineSpacing(index - 1);
		}

		temp_height += GetLineSpacing(index);
		temp_height += lines[index]->rect.size.height;

		return temp_height;
	}
	else
	{
		return NULL;
	}
}

TextBox::TextBox()
{
	parent_rect.base_size = { 100.0, 25.0 };
	parent_rect.SetSizeWithSizeScale({ 1.0, 1.0 });

	chars = vector<TextBoxChar*>{};

	default_text_box_font = nullptr;

	horizontal_text_centering = { 1 };
	vertical_text_centering = { 1 };

	default_line_spacing = 0;
	default_line_height = 0;

	text_wrap = 0;
}

void TextBox::SetDefaultFont(Font* param_default_font)
{
	default_text_box_font = param_default_font;

	default_line_spacing = param_default_font->default_default_line_spacing;
	default_line_height = param_default_font->default_default_line_height;
}

void TextBox::CreateDebugData(const vector<DebugDataContainer*> param_owner_debug_data_containers, Font* default_debug_data_container_label_font, const char* const param_debug_data_container_label_chars, const vector<int> param_debug_data_container_active_scenes, const bool param_white_list)
{
	if (debug_data_container.owners.size() == 0)
	{
		debug_data_container.InitLeast(param_owner_debug_data_containers, default_debug_data_container_label_font, param_debug_data_container_label_chars, &parent_rect, param_debug_data_container_active_scenes, param_white_list);
		debug_data_container.AddRectangleData(&parent_rect, "Parent Rect");
		debug_data_container.AddString(&default_text_box_font->font_name, "Default Font");
		debug_data_container.AddRigidCentering(&horizontal_text_centering, "Horizontal Text Centering");
		debug_data_container.AddRigidCentering(&vertical_text_centering, "Vertical Text Centering");
		debug_data_container.AddBool(&text_wrap, "Text Wrap");
		//Add stuff like default_font name and so on later

		for (int i = 0; i < lines.size(); i++)
		{
			string temp_to_string = "Line ";
			temp_to_string += to_string(i);
			const char* temp_name = temp_to_string.c_str();

			lines[i]->CreateDebugData({ &debug_data_container }, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
		}
		
		for (int i = 0; i < chars.size(); i++)
		{
			string temp_to_string = "Char ";
			temp_to_string += to_string(i);
			const char* temp_name = temp_to_string.c_str();
			chars[i]->CreateDebugData({&debug_data_container}, debug_data_container.label.text_box_data.default_text_box_font, temp_name, debug_data_container.active_scenes, debug_data_container.white_list);
		}
	}
	else
	{
		cout << "Already created debug data  -  (debug_data_container.owners.size() == 0) returned false\n";
	}
}




string TextBox::GetText()
{
	string temp_string;

	for (size_t i = 0; i < chars.size(); i++)
	{
		temp_string += chars[i]->font_char->char_value;
	}

	return temp_string;
}
//Indexed elements ARE INCLUDED
string TextBox::GetText(const size_t begin_index, const size_t end_index)
{
	string temp_string;

	if (end_index < chars.size())
	{
		if (begin_index >= 0)
		{
			for (size_t i = begin_index; i <= end_index; i++)
			{
				temp_string += chars[i]->font_char->char_value;
			}
		}
		else
		{
			cout << "begin_index too loww (printed from TextBoxData::GetText(const size_t begin_index, const size_t end_index))";
		}
	}
	else
	{
		cout << "end_index too highh (printed from TextBoxData::GetText(const size_t begin_index, const size_t end_index))";
	}

	return temp_string;
}

vector<RectStructOne>* TextBox::GetSegmentHitbox(size_t begin_index, size_t end_index)
{
	size_t line_progression = GetLineIndexWithCharIndex(begin_index, 0, 1);

	size_t end_line_index = GetLineIndexWithCharIndex(end_index, 0, 0);

	vector<RectStructOne>* temp_rects = new vector<RectStructOne>();

	while (line_progression <= end_line_index)
	{
		RectStructOne temp_rect_struct_one;

		temp_rect_struct_one.uni_bottom_edge = lines[line_progression]->rect.GetUniEdge({ 1 });
		temp_rect_struct_one.uni_top_edge = lines[line_progression]->rect.GetUniEdge({ 3 });

		if (begin_index >= lines[line_progression]->first_index)
		{
			temp_rect_struct_one.uni_left_edge = chars[begin_index]->rect.GetUniEdge({ 2 });
		}
		else
		{
			temp_rect_struct_one.uni_left_edge = chars[lines[line_progression]->first_index]->rect.GetUniEdge({ 2 });
		}

		if (end_index <= lines[line_progression]->last_index)
		{
			temp_rect_struct_one.uni_right_edge = chars[end_index]->rect.GetUniEdge({ 0 });
		}
		else
		{
			temp_rect_struct_one.uni_right_edge = chars[lines[line_progression]->last_index]->rect.GetUniEdge({ 0 });
		}

		temp_rects->push_back(temp_rect_struct_one);
		line_progression++;
	}

	return temp_rects;



	/*
	RectStructOne temp_rect_struct_one;

	Line* saved_line_data_pointer = GetLineWithCharIndex(end_index);
	if (saved_line_data_pointer)
	{
		temp_rect_struct_one.uni_bottom_edge = saved_line_data_pointer->rect.GetUniEdge({ 1 });
	}
	else
	{
		cout << "end_index had no accociated line (printed from TextBoxData::GetSegmentHitbox(const size_t begin_index, const size_t end_index))";
	}
	saved_line_data_pointer = GetLineWithCharIndex(begin_index);
	if (saved_line_data_pointer)
	{
		temp_rect_struct_one.uni_top_edge = saved_line_data_pointer->rect.GetUniEdge({ 3 });
	}
	else
	{
		cout << "begin_index had no accociated line (printed from TextBoxData::GetSegmentHitbox(const size_t begin_index, const size_t end_index))";
	}

	temp_rect_struct_one.uni_left_edge = chars[begin_index]->rect.GetUniEdge({ 2 });
	temp_rect_struct_one.uni_right_edge = chars[end_index]->rect.GetUniEdge({ 0 });

	return new vector<RectStructOne>{ temp_rect_struct_one };
	*/
}

Line* TextBox::GetLineWithCharIndex(const size_t char_index, const bool can_return_nullptr, const bool return_next_line)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		if ((!can_return_nullptr) && (return_next_line))
		{
			bool check_one;
			if (i > 0)
			{
				check_one = (char_index > lines[i - size_t(1)]->last_index);
			}
			else
			{
				check_one = 1;
			} 
			const bool check_two = (char_index < lines[i]->first_index);

			if (check_one && check_two)
			{
				return lines[i];
			}
		}

		if ((char_index >= lines[i]->first_index) && (char_index <= lines[i]->last_index))
		{
			return lines[i];
		}

		if ((!can_return_nullptr) && (!return_next_line))
		{
			const bool check_one = char_index > lines[i]->last_index;
			bool check_two;
			if ((i + size_t(1)) < lines.size())
			{
				check_two = (char_index < lines[i + size_t(1)]->first_index);
			}
			else
			{
				check_two = 1;
			}

			if (check_one && check_two)
			{
				return lines[i];
			}
		}
	}

	return nullptr;
}
size_t TextBox::GetLineIndexWithCharIndex(const size_t char_index, const bool can_return_nullptr, const bool return_next_line)
{
	return GetLineIndexWithLinePointer(GetLineWithCharIndex(char_index, can_return_nullptr, return_next_line));
}

size_t TextBox::GetLineIndexWithLinePointer(const Line* const line_ptr) const
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i] == line_ptr)
		{
			return i;
		}
	}

	return numeric_limits<size_t>::max();
}















BasicLine::BasicLine(const RefRectangleNewest i_rect, const size_t i_first_index, const size_t i_last_index, const double i_last_space_x, const double i_pixel_spacing_top, const double i_pixel_spacing_bottom, const LineParameters* const i_source_parameters)
	: rect(i_rect),
	first_index(i_first_index),
	last_index(i_last_index),
	last_space_x(i_last_space_x),
	pixel_spacing_top(i_pixel_spacing_top),
	pixel_spacing_bottom(i_pixel_spacing_bottom),
	source_parameters(i_source_parameters) {}

double BasicLine::GetLineWidthWithEndingSpaces() const
{
	//This method requires [source_parameters] to be a valid pointer!
	return 0.0;
}
RefRectangleNewest BasicLine::GetLineRectWithEndingSpaces() const
{
	//This method requires [source_parameters] to be a valid pointer!
	return {};
}






// ----------------------------------   BASIC TEXT BOX   ----------------------------------


// -----------------   CONSTRUCTORS/INIT FUNCTIONS   -----------------

BasicTextBox::BasicTextBox() {}
BasicTextBox::BasicTextBox(const BasicFont* const i_default_font, const RefRectangleNewest i_rect, const Centering2DNew i_text_centering, const bool i_ignore_line_spacing_on_text_box_ends)
	: default_font(i_default_font),
	default_line_parameters(i_default_font->template_line_parameters),
	rect(i_rect),
	text_centering(i_text_centering),
	ignore_line_spacing_on_text_box_ends(i_ignore_line_spacing_on_text_box_ends) {}
BasicTextBox::BasicTextBox(const LineParameters i_default_line_parameters, const BasicFont* const i_default_font, const RefRectangleNewest i_rect, const Centering2DNew i_text_centering, const bool i_ignore_line_spacing_on_text_box_ends)
	: default_line_parameters(i_default_line_parameters),
	default_font(i_default_font),
	rect(i_rect),
	text_centering(i_text_centering),
	ignore_line_spacing_on_text_box_ends(i_ignore_line_spacing_on_text_box_ends) {}
void BasicTextBox::Init(const BasicFont* const i_default_font, const char* const i_text, const RefRectangleNewest i_rect, const Centering2DNew i_text_centering, const bool i_ignore_line_spacing_on_text_box_ends)
{
	default_font = i_default_font;
	default_line_parameters = default_font->template_line_parameters;
	rect = i_rect;
	text_centering = i_text_centering;
	ignore_line_spacing_on_text_box_ends = i_ignore_line_spacing_on_text_box_ends;
	AddCharPtr(i_text);
}
void BasicTextBox::Init(const LineParameters i_default_line_parameters, const BasicFont* const i_default_font, const char* const i_text, const RefRectangleNewest i_rect, const Centering2DNew i_text_centering, const bool i_ignore_line_spacing_on_text_box_ends)
{
	default_font = i_default_font;
	default_line_parameters = i_default_line_parameters;
	rect = i_rect;
	text_centering = i_text_centering;
	ignore_line_spacing_on_text_box_ends = i_ignore_line_spacing_on_text_box_ends;
	AddCharPtr(i_text);
}




// -----------------   FUNCTIONS   -----------------

void BasicTextBox::GenerateFull()
{
	GenerateLines();
	GenerateCharRects();
}

void BasicTextBox::GenerateLines()
{
	GenerateLineSizes();
	GenerateLinePositions();
}
void BasicTextBox::GenerateLineSizes()
{
	lines.clear();


	const size_t size_of_chars = chars.size();
	if (size_of_chars != 0)
	{
		size_t current_line_index = 0;
		const LineParameters* current_line_parameters = GetLineParametersConst(size_t(0));
		double line_length_prog = current_line_parameters->ignore_char_spacing_on_line_ends ?
			(chars[0].GetScaledPixelWidth()) :
			(chars[0].GetScaledPixelSpacingLeft() + chars[0].GetScaledPixelWidth() + chars[0].GetScaledPixelSpacingRight());

		size_t current_char_index = 0;

		size_t saved_char_index = 0;
		double saved_line_length_prog = 0.0;

		while (true)
		{
			const double length_limit = (current_line_parameters->pixel_max_width < 0.0) ? rect.unscaled_size.width : current_line_parameters->pixel_max_width;

			//If the accumulated chars exceed the length limit of the line...
			if (line_length_prog > (length_limit + (numeric_limits<double>::epsilon() * 500.0)))
			{
				const size_t temp_begin_index = (current_line_index == size_t(0)) ? size_t(0) : lines.back().last_index + size_t(1);

				//Append a BasicLine with the appropriate properties to [lines].
				lines.push_back(BasicLine(
					RefRectangleNewest(
						&rect,
						{ 0.0, 0.0 },
						{ saved_line_length_prog,
						current_line_parameters->scale_height_with_highest_char_scale ? (GetHighestCharHeightScale(temp_begin_index, saved_char_index) * current_line_parameters->pixel_height) : current_line_parameters->pixel_height },
						{ 1.0, -1.0 }
					),
					temp_begin_index,
					saved_char_index,
					saved_line_length_prog + chars[saved_char_index].GetScaledPixelSpacingRight(),
					current_line_parameters->pixel_spacing_top,
					current_line_parameters->pixel_spacing_bottom,
					current_line_parameters
				));

				//current_char_index needs to be set to saved_char_index++ because if a line exceeds it's length limit with a single character, the character is still asigned to the line to prevent an infinite loop. If this happens, [current_char_index] SHOULD advance, but if it doesn't, [current_char_index] SHOULDN'T advance. This code does that.
				current_char_index = saved_char_index + size_t(1);
				saved_char_index = current_char_index;

				//If reached the end of [chars], break from loop
				if (current_char_index >= size_of_chars)
				{
					break;
				}

				//Set [current_line_index] and [line_length_prog] accordingly
				current_line_index++;
				current_line_parameters = GetLineParametersConst(current_line_index);
				line_length_prog = current_line_parameters->ignore_char_spacing_on_line_ends ?
					(chars[current_char_index].GetScaledPixelWidth()) :
					(chars[current_char_index].GetScaledPixelSpacingLeft() + chars[current_char_index].GetScaledPixelWidth() + chars[current_char_index].GetScaledPixelSpacingRight());
				saved_line_length_prog = line_length_prog;
			}
			else
			{
				//Set saved values to last iteration values.
				saved_char_index = current_char_index;
				saved_line_length_prog = line_length_prog;

				current_char_index++;

				if (current_char_index >= size_of_chars)
				{
					const size_t temp_begin_index = (current_line_index == size_t(0)) ? size_t(0) : lines.back().last_index + size_t(1);

					//Append a BasicLine with the appropriate properties to [lines].
					lines.push_back(BasicLine(
						RefRectangleNewest(
							&rect,
							{ 0.0, 0.0 },
							{ saved_line_length_prog,
							current_line_parameters->scale_height_with_highest_char_scale ? (GetHighestCharHeightScale(temp_begin_index, saved_char_index) * current_line_parameters->pixel_height) : current_line_parameters->pixel_height },
							{ 1.0, -1.0 }
						),
						temp_begin_index,
						saved_char_index,
						saved_line_length_prog + chars[saved_char_index].GetScaledPixelSpacingRight(),
						current_line_parameters->pixel_spacing_top,
						current_line_parameters->pixel_spacing_bottom,
						current_line_parameters
					));

					break;
				}

				line_length_prog += (chars[saved_char_index].GetScaledPixelSpacingRight() + chars[current_char_index].GetScaledPixelSpacingLeft() + chars[current_char_index].GetScaledPixelWidth()); //If [ignore_char_spacing_on_line_ends]
				line_length_prog += current_line_parameters->ignore_char_spacing_on_line_ends ?
					(chars[saved_char_index].GetScaledPixelSpacingRight() + chars[current_char_index].GetScaledPixelSpacingLeft() + chars[current_char_index].GetScaledPixelWidth()) :
					(chars[current_char_index].GetScaledPixelSpacingLeft() + chars[current_char_index].GetScaledPixelWidth() + chars[current_char_index].GetScaledPixelSpacingRight());
			}
		}
	}
}
void BasicTextBox::GenerateLinePositions()
{
	const size_t size_of_lines = lines.size();

	double line_y_prog = 0.0;
	size_t i;
	for (i = 0; i < size_of_lines; i++)
	{
		lines[i].rect.pos.x = (text_centering.x_centering == -1.0) ?
			rect.pos.x :
			rect.pos.x + ((rect.unscaled_size.width - lines[i].rect.unscaled_size.width) * (1.0 + text_centering.x_centering) / 2.0);

		if (i == 0)
		{
			line_y_prog = ignore_line_spacing_on_text_box_ends ? 0.0 : lines[0].pixel_spacing_top;
		}
		else
		{
			line_y_prog += (lines[i - 1].rect.unscaled_size.height + lines[i - 1].pixel_spacing_bottom + lines[i].pixel_spacing_top);
		}

		lines[i].rect.pos.y = line_y_prog;
	}



	//Adjust each line's position for [text_centering.y_centering]

	if (i != 0)
	{
		line_y_prog += ignore_line_spacing_on_text_box_ends ? lines[i - 1].rect.unscaled_size.height : (lines[i - 1].rect.unscaled_size.height + lines[i - 1].pixel_spacing_bottom);
	}

	const double y_adjustment_value = (rect.unscaled_size.height - line_y_prog) * (1.0 - text_centering.y_centering) / -2.0;

	if (y_adjustment_value != 0.0)
	{
		for (i = 0; i < size_of_lines; i++)
		{
			lines[i].rect.pos.y += y_adjustment_value;
		}
	}
}

void BasicTextBox::GenerateCharRects()
{
	const size_t size_of_chars = chars.size();

	double line_length_prog;

	for (size_t i = 0; i < lines.size(); i++)
	{
		line_length_prog = lines[i].source_parameters->ignore_char_spacing_on_line_ends ? -chars[lines[i].first_index].GetScaledPixelSpacingLeft() : 0.0;
		for (size_t j = lines[i].first_index; (j <= lines[i].last_index) && (j < size_of_chars); j++)
		{
			chars[j].rect.unscaled_size.width = chars[j].unscaled_pixel_width;
			chars[j].rect.unscaled_size.height = lines[i].rect.unscaled_size.height;

			chars[j].rect.transformations.scale = Scale2DNew(chars[j].scale);

			chars[j].rect.SetReference(&lines[i].rect);

			chars[j].rect.pos.y = -lines[i].rect.unscaled_size.height;

			line_length_prog += chars[j].GetScaledPixelSpacingLeft();
			chars[j].rect.pos.x = line_length_prog;
			line_length_prog += chars[j].GetScaledPixelWidth() + chars[j].GetScaledPixelSpacingRight();
		}
	}
}


void BasicTextBox::AddChar(const char char_value)
{
	if (default_font)
	{
		chars.push_back(BasicTextBoxChar(default_font->GetFontCharConst(char_value)));
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddChar(const char char_value, const GLColor overwriting_color_mod)
{
	if (default_font)
	{
		const BasicFontChar* const temp_char = default_font->GetFontCharConst(char_value);

		chars.push_back(BasicTextBoxChar(char_value, temp_char->texture, temp_char->template_unscaled_pixel_spacing_left, temp_char->template_unscaled_pixel_spacing_right, temp_char->template_unscaled_pixel_offset, temp_char->template_scale, overwriting_color_mod));
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddChar(const char char_value, const Scale90 overwriting_scale)
{
	if (default_font)
	{
		const BasicFontChar* const temp_char = default_font->GetFontCharConst(char_value);

		chars.push_back(BasicTextBoxChar(char_value, temp_char->texture, temp_char->template_unscaled_pixel_spacing_left, temp_char->template_unscaled_pixel_spacing_right, temp_char->template_unscaled_pixel_offset, overwriting_scale, temp_char->template_color_mod));
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddChar(const char char_value, const GLColor overwriting_color_mod, const Scale90 overwriting_scale)
{
	if (default_font)
	{
		const BasicFontChar* const temp_char = default_font->GetFontCharConst(char_value);

		chars.push_back(BasicTextBoxChar(char_value, temp_char->texture, temp_char->template_unscaled_pixel_spacing_left, temp_char->template_unscaled_pixel_spacing_right, temp_char->template_unscaled_pixel_offset, overwriting_scale, overwriting_color_mod));
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}

void BasicTextBox::AddCharPtr(const char* chars)
{
	if (default_font)
	{
		while (*chars != '\0')
		{
			AddChar(*chars);
			chars++;
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddCharPtr(const char* chars, const GLColor overwriting_color_mod)
{
	if (default_font)
	{
		while (*chars != '\0')
		{
			AddChar(*chars, overwriting_color_mod);
			chars++;
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddCharPtr(const char* chars, const Scale90 overwriting_scale)
{
	if (default_font)
	{
		while (*chars != '\0')
		{
			AddChar(*chars, overwriting_scale);
			chars++;
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddCharPtr(const char* chars, const GLColor overwriting_color_mod, const Scale90 overwriting_scale)
{
	if (default_font)
	{
		while (*chars != '\0')
		{
			AddChar(*chars, overwriting_color_mod, overwriting_scale);
			chars++;
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}

void BasicTextBox::AddString(const string string_value)
{
	if (default_font)
	{
		for (size_t i = 0; i < string_value.size(); i++)
		{
			AddChar(string_value[i]);
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddString(const string string_value, const GLColor overwriting_color_mod)
{
	if (default_font)
	{
		for (size_t i = 0; i < string_value.size(); i++)
		{
			AddChar(string_value[i], overwriting_color_mod);
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddString(const string string_value, const Scale90 overwriting_scale)
{
	if (default_font)
	{
		for (size_t i = 0; i < string_value.size(); i++)
		{
			AddChar(string_value[i], overwriting_scale);
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}
void BasicTextBox::AddString(const string string_value, const GLColor overwriting_color_mod, const Scale90 overwriting_scale)
{
	if (default_font)
	{
		for (size_t i = 0; i < string_value.size(); i++)
		{
			AddChar(string_value[i], overwriting_color_mod, overwriting_scale);
		}
	}
	else
	{
		cout << "[default_font] was nullptr! Calling AddChar(...), AddCharPtr(...), or AddString(...) requires [default_font] to be set beforehand. Sent by void BasicTextBox::AddChar(const char char_value)." << endl;
		throw;
	}
}


void BasicTextBox::Clear()
{
	lines.clear();
	chars.clear();
}


double BasicTextBox::GetTextBindingWidth(const bool p_include_ending_spaces) const
{
	double highest_width = 0.0;
	if (p_include_ending_spaces)
	{
		for (size_t i = 0; i < lines.size(); i++)
		{
			if (lines[i].GetLineWidthWithEndingSpaces() < highest_width)
			{
				highest_width = lines[i].GetLineWidthWithEndingSpaces();
			}
		}
	}
	else
	{
		for (size_t i = 0; i < lines.size(); i++)
		{
			if (lines[i].rect.unscaled_size.width < highest_width)
			{
				highest_width = lines[i].rect.unscaled_size.width;
			}
		}
	}

	return highest_width;
}
double BasicTextBox::GetTextBindingHeight() const
{
	//This method requires [source_parameters] to be a valid pointer!
	if (ignore_line_spacing_on_text_box_ends)
	{
		switch (lines.size())
		{
		case 0:
			return 0.0;
		case 1:
			return lines[0].rect.unscaled_size.height;
		default:
			const size_t last_lines_index = lines.size() - size_t(1);

			//Make sure that all the lines have valid [source_parameters] pointers if you got an error here!
			double return_val = (lines[0].rect.unscaled_size.height + lines[0].source_parameters->pixel_spacing_bottom) + (lines[last_lines_index].rect.unscaled_size.height + lines[last_lines_index].source_parameters->pixel_spacing_top);
			for (size_t i = 1; i < last_lines_index; i++)
			{
				return_val += lines[i].source_parameters->pixel_spacing_bottom + lines[i].rect.unscaled_size.height + lines[i].source_parameters->pixel_spacing_top;
			}
			return return_val;
		}
	}
	else
	{
		double return_val = 0.0;

		//Make sure that all the lines have valid [source_parameters] pointers if you got an error here!
		for (size_t i = 0; i < lines.size(); i++)
		{
			return_val += lines[i].source_parameters->pixel_spacing_bottom + lines[i].rect.unscaled_size.height + lines[i].source_parameters->pixel_spacing_top;
		}
		return return_val;
	}
}
RefRectangleNewest BasicTextBox::GetTextBinding(const bool p_include_ending_spaces) const
{
	if (lines.size() == size_t(0))
	{
		return RefRectangleNewest(
			&rect,
			{
				(rect.unscaled_size.width * (rect.centering.x_centering + text_centering.x_centering) / 2.0),
				(rect.unscaled_size.height * (rect.centering.y_centering + text_centering.y_centering) / 2.0)
			},
			{ 0.0, 0.0 },
			{ 1.0, -1.0 }
		);
	}
	else
	{
		return RefRectangleNewest(
			&rect,
			{ lines[0].rect.pos.x, lines[0].rect.pos.y },
			{ GetTextBindingWidth(p_include_ending_spaces), GetTextBindingHeight() },
			{ 1.0, -1.0 }
		);
	}
}


string BasicTextBox::GetSegmentText(const size_t begin_index, const size_t end_index) const
{
	size_t lower_bound;
	if ((chars.size() - size_t(1)) > end_index)
	{
		lower_bound = end_index;
	}
	else
	{
		lower_bound = chars.size() - size_t(1);
	}

	string return_val = "";
	for (size_t i = begin_index; i < lower_bound; i++)
	{
		return_val += chars[i].char_value;
	}

	return return_val;
}
vector<RectStructOne>* BasicTextBox::GetSegmentHitbox(const size_t begin_index, const size_t end_index) const
{
	return nullptr;
}


LineParameters* BasicTextBox::GetLineParameters(const size_t line_index)
{
	for (size_t i = 0; i < line_parameters.size(); i++)
	{
		if (line_parameters[i].index == numeric_limits<size_t>::max())
		{
			if (i == line_index)
			{
				return &line_parameters[i];
			}
		}
		else
		{
			if (line_parameters[i].index == line_index)
			{
				return &line_parameters[i];
			}
		}
	}
	return &default_line_parameters;
}
const LineParameters* BasicTextBox::GetLineParametersConst(const size_t line_index) const
{
	for (size_t i = 0; i < line_parameters.size(); i++)
	{
		if (line_parameters[i].index == numeric_limits<size_t>::max())
		{
			if (i == line_index)
			{
				return &line_parameters[i];
			}
		}
		else
		{
			if (line_parameters[i].index == line_index)
			{
				return &line_parameters[i];
			}
		}
	}
	return &default_line_parameters;
}




// -----------------  PRIVATE STUFFS  -----------------

double BasicTextBox::GetHighestCharHeightScale(const size_t begin_index, const size_t end_index) const
{
	//Potentially unsafe (uh-oh)

	double return_val = 0.0;
	for (size_t i = begin_index; i <= end_index; i++)
	{
		if (chars[i].scale.height_scale > return_val)
		{
			return_val = chars[i].scale.height_scale;
		}
	}

	return return_val;
}