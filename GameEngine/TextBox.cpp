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