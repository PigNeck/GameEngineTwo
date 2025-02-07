#include "TextBoxData.h"

void LineData::Init()
{
	//Do nothing lmao
}






void TextBoxData::BasicInitTextBox(RectangleOld param_parent_rectangle, Font* param_font, string param_chars)
{
	Clear();

	parent_rectangle = param_parent_rectangle;

	default_text_box_font = param_font;

	default_line_spacing = param_font->default_default_line_spacing;
	default_line_height = param_font->default_default_line_height;

	for (int i = 0; i < param_chars.size(); i++)
	{
		chars.push_back(new TextBoxCharData());
		chars.back()->InitLeast(&parent_rectangle, param_font->GetFontChar(param_chars[i]));
	}
}

void TextBoxData::InitLeast(Font* const param_default_font)
{
	Clear();

	default_text_box_font = param_default_font;

	default_line_spacing = default_text_box_font->default_default_line_spacing;
	default_line_height = default_text_box_font->default_default_line_height;
}
void TextBoxData::InitMost(Font* const param_default_font, const RectangleOld param_parent_rectangle, const char* const param_chars, const RigidCentering param_horizontal_centering, const RigidCentering param_vertical_centering)
{
	Clear();

	SetDefaultFont(param_default_font);
	parent_rectangle = param_parent_rectangle;
	AddCharPtr(param_chars);
	horizontal_text_centering = param_horizontal_centering;
	vertical_text_centering = param_vertical_centering;

	UpdateCharPos();
}

double TextBoxData::GetLineHeight(int index)
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
double TextBoxData::GetLineSpacing(int index)
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

void TextBoxData::GenerateLine(const int starting_char_index, const int line_index, int* const next_starting_index)
{
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

	current_line_width += chars[current_char_index]->rectangle.size.width;

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
		current_line_width += chars[current_char_index]->rectangle.size.width;

		//If current_char == '\n'
		if (chars[current_char_index]->font_char->char_value == '\n')
		{
			broke_from_loop = 1;
			new_line_encountered = 1;
			break;
		}

		//Increment char index
		current_char_index++;
	}






	// -----------------   INTERPRET DATA   -----------------

	if (broke_from_loop)
	{
		LineData temp_line = LineData();

		//Create a line rect with only width and height data
		lines.push_back(new LineData());
		lines.back()->Init();

		lines.back()->rectangle.base_size.width = saved_line_width;
		lines.back()->rectangle.base_size.height = GetLineHeight(line_index);
		lines.back()->rectangle.SetSizeWithSizeScale({ 1.0, 1.0 });
		lines.back()->rectangle.reference_rectangle = &parent_rectangle;
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
		LineData temp_line = LineData();

		//Create a line rect with only width and height data
		lines.push_back(new LineData());
		lines.back()->Init();

		lines.back()->rectangle.base_size.width = current_line_width;
		lines.back()->rectangle.base_size.height = GetLineHeight(line_index);
		lines.back()->rectangle.SetSizeWithSizeScale({ 1.0, 1.0 });
		lines.back()->rectangle.reference_rectangle = &parent_rectangle;
		lines.back()->first_index = starting_char_index;
		lines.back()->last_index = (int)chars.size() - 1;

		//No new line
		*next_starting_index = -1;
	}
}

void TextBoxData::UpdateCharPos()
{
	GenerateLineSizes();
	GenerateLinePositions();
	GenerateCharPositions();
}

void TextBoxData::GenerateLineSizes()
{
	lines.clear();

	int starting_index = 0;
	int line_index = 0;

	while (starting_index != -1)
	{
		GenerateLine(starting_index, line_index, &starting_index);
		line_index++;
	}
}
void TextBoxData::GenerateLinePositions()
{
	// --------   LINE X   --------
	switch (horizontal_text_centering.value)
	{
	case 0:
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]->rectangle.pos.x = (parent_rectangle.base_size.width - lines[i]->rectangle.size.width) / -2.0;
		}
		break;
	case 1:
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]->rectangle.pos.x = 0.0;
		}
		break;
	case 2:
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]->rectangle.pos.x = (parent_rectangle.base_size.width - lines[i]->rectangle.size.width) / 2.0;
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
			temp_line_y = (parent_rectangle.base_size.height / -2.0) + actual_height;
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
			temp_line_y = (parent_rectangle.base_size.height / 2.0);
		}
		break;
	case 3:
		//Bruh this ain't defined
		//Sea kelp
		break;
	}

	if (lines.size() > 0)
	{
		temp_line_y -= (lines[0]->rectangle.size.height / 2.0);
		lines[0]->rectangle.pos.y = temp_line_y;

		for (int i = 1; i < lines.size(); i++)
		{
			temp_line_y -= (lines[i - 1]->rectangle.size.height / 2.0);
			temp_line_y -= GetLineSpacing(i - 1);
			temp_line_y -= GetLineSpacing(i);
			temp_line_y -= (lines[i]->rectangle.size.height / 2.0);
			lines[i]->rectangle.pos.y = temp_line_y;
		}
	}
}
void TextBoxData::GenerateCharPositions()
{
	for (int i = 0; i < lines.size(); i++)
	{
		double temp_char_x = lines[i]->rectangle.pos.x - (lines[i]->rectangle.size.width / 2.0);
		temp_char_x += chars[lines[i]->first_index]->rectangle.size.width / 2.0;
		chars[lines[i]->first_index]->rectangle.pos.x = temp_char_x;
		chars[lines[i]->first_index]->rectangle.pos.y = lines[i]->rectangle.pos.y - ((lines[i]->rectangle.size.height - chars[lines[i]->first_index]->rectangle.size.height) / 2.0);

		for (int j = lines[i]->first_index + 1; j <= lines[i]->last_index; j++)
		{
			chars[j]->rectangle.pos.y = lines[i]->rectangle.pos.y - ((lines[i]->rectangle.size.height - chars[j]->rectangle.size.height) / 2.0);

			temp_char_x += chars[j - 1]->rectangle.size.width / 2.0;
			temp_char_x += chars[j - 1]->char_spacing;
			temp_char_x += chars[j]->char_spacing;
			temp_char_x += chars[j]->rectangle.size.width / 2.0;
			chars[j]->rectangle.pos.x = temp_char_x;
		}
	}
}



void TextBoxData::AddChar(char param_char)
{
	if (default_text_box_font)
	{
		chars.push_back(new TextBoxCharData());
		chars.back()->InitLeast(&parent_rectangle, default_text_box_font->GetFontChar(param_char));
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first (TextBoxData)\n";
	}
}
void TextBoxData::AddChar(char param_char, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod)
{
	if (default_text_box_font)
	{
		chars.push_back(new TextBoxCharData());
		chars.back()->InitMost(&parent_rectangle, default_text_box_font->GetFontChar(param_char), r_mod, g_mod, b_mod, a_mod);
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first (TextBoxData)\n";
	}
}
void TextBoxData::AddString(string param_string)
{
	if (default_text_box_font)
	{
		for (int i = 0; i < param_string.size(); i++)
		{
			chars.push_back(new TextBoxCharData());
			chars.back()->InitLeast(&parent_rectangle, default_text_box_font->GetFontChar(param_string[i]));
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first (TextBoxData)\n";
	}
}
void TextBoxData::AddString(string param_string, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod)
{
	if (default_text_box_font)
	{
		for (int i = 0; i < param_string.size(); i++)
		{
			chars.push_back(new TextBoxCharData());
			chars.back()->InitMost(&parent_rectangle, default_text_box_font->GetFontChar(param_string[i]), r_mod, g_mod, b_mod, a_mod);
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first (TextBoxData)\n";
	}
}
void TextBoxData::AddCharPtr(const char* param_char_pointer)
{
	if (default_text_box_font)
	{
		while (*param_char_pointer != '\0') {
			AddChar(*param_char_pointer);
			param_char_pointer++;
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first (TextBoxData)\n";
	}
}
void TextBoxData::AddCharPtr(const char* param_char_pointer, Uint8 r_mod, Uint8 g_mod, Uint8 b_mod, Uint8 a_mod)
{
	if (default_text_box_font)
	{
		while (*param_char_pointer != '\0') {
			AddChar(*param_char_pointer, r_mod, g_mod, b_mod, a_mod);
			param_char_pointer++;
		}
	}
	else
	{
		cout << "Hmmm bozo, try setting the default_text_box_font first (TextBoxData)\n";
	}
}

void TextBoxData::Clear()
{
	chars.clear();
	lines.clear();
}

double TextBoxData::GetActualBaseWidth()
{
	double highest_width = 0.0;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->rectangle.size.width > highest_width)
		{
			highest_width = lines[i]->rectangle.size.width;
		}
	}

	return highest_width;
}
double TextBoxData::GetActualBaseHeight()
{
	if (lines.size() > 0)
	{
		double temp_height = 0.0;

		temp_height = lines[0]->rectangle.size.height;

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

double TextBoxData::GetLineHeightWithPreviousSpacing(int index)
{
	double temp_height = 0.0;

	if ((index < lines.size()) && (index >= 0))
	{
		if (index > 0)
		{
			temp_height += GetLineSpacing(index - 1);
		}

		temp_height += GetLineSpacing(index);
		temp_height += lines[index]->rectangle.size.height;

		return temp_height;
	}
	else
	{
		return NULL;
	}
}

TextBoxData::TextBoxData()
{
	parent_rectangle.base_size = { 100.0, 25.0 };
	parent_rectangle.SetSizeWithSizeScale({ 1.0, 1.0 });

	chars = vector<TextBoxCharData*>{};

	default_text_box_font = nullptr;

	horizontal_text_centering = { 1 };
	vertical_text_centering = { 1 };

	default_line_spacing = 0;
	default_line_height = 0;
}

void TextBoxData::SetDefaultFont(Font* param_default_font)
{
	default_text_box_font = param_default_font;

	default_line_spacing = param_default_font->default_default_line_spacing;
	default_line_height = param_default_font->default_default_line_height;
}


string TextBoxData::GetText()
{
	string temp_string;

	for (size_t i = 0; i < chars.size(); i++)
	{
		temp_string += chars[i]->font_char->char_value;
	}

	return temp_string;
}
//Indexed elements ARE INCLUDED
string TextBoxData::GetText(const size_t begin_index, const size_t end_index)
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

vector<RectStructOne>* TextBoxData::GetSegmentHitbox(size_t begin_index, size_t end_index)
{
	size_t line_progression = GetLineIndexWithCharIndex(begin_index, 0, 1);

	size_t end_line_index = GetLineIndexWithCharIndex(end_index, 0, 0);

	vector<RectStructOne>* temp_rects = new vector<RectStructOne>();

	while (line_progression <= end_line_index)
	{
		RectStructOne temp_rect_struct_one;

		temp_rect_struct_one.uni_bottom_edge = lines[line_progression]->rectangle.GetUniEdge({ 1 });
		temp_rect_struct_one.uni_top_edge = lines[line_progression]->rectangle.GetUniEdge({ 3 });

		if (begin_index >= lines[line_progression]->first_index)
		{
			temp_rect_struct_one.uni_left_edge = chars[begin_index]->rectangle.GetUniEdge({ 2 });
		}
		else
		{
			temp_rect_struct_one.uni_left_edge = chars[lines[line_progression]->first_index]->rectangle.GetUniEdge({ 2 });
		}

		if (end_index <= lines[line_progression]->last_index)
		{
			temp_rect_struct_one.uni_right_edge = chars[end_index]->rectangle.GetUniEdge({ 0 });
		}
		else
		{
			temp_rect_struct_one.uni_right_edge = chars[lines[line_progression]->last_index]->rectangle.GetUniEdge({ 0 });
		}

		temp_rects->push_back(temp_rect_struct_one);
		line_progression++;
	}

	return temp_rects;
}

LineData* TextBoxData::GetLineWithCharIndex(const size_t char_data_index, const bool can_return_nullptr, const bool return_next_line)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		if ((!can_return_nullptr) && (return_next_line))
		{
			bool check_one;
			if (i > 0)
			{
				check_one = (char_data_index > lines[i - size_t(1)]->last_index);
			}
			else
			{
				check_one = 1;
			}
			const bool check_two = (char_data_index < lines[i]->first_index);

			if (check_one && check_two)
			{
				return lines[i];
			}
		}

		if ((char_data_index >= lines[i]->first_index) && (char_data_index <= lines[i]->last_index))
		{
			return lines[i];
		}

		if ((!can_return_nullptr) && (!return_next_line))
		{
			const bool check_one = char_data_index > lines[i]->last_index;
			bool check_two;
			if ((i + size_t(1)) < lines.size())
			{
				check_two = (char_data_index < lines[i + size_t(1)]->first_index);
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
size_t TextBoxData::GetLineIndexWithCharIndex(const size_t char_data_index, const bool can_return_nullptr, const bool return_next_line)
{
	return GetLineIndexWithLinePointer(GetLineWithCharIndex(char_data_index, can_return_nullptr, return_next_line));
}

size_t TextBoxData::GetLineIndexWithLinePointer(const LineData* const line_data_ptr) const
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i] == line_data_ptr)
		{
			return i;
		}
	}

	return numeric_limits<size_t>::max();
}