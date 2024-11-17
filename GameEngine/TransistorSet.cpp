#include "TransistorSet.h"

void Cell::Click(const bool target_state)
{
	state = target_state;
	animation_color_percent = 101.0;
	animation_movement_percent = 101.0;
}
void Cell::Update(const double frame_factor_inverse)
{
	// Update animation_color_percent
	if (animation_color_percent > 100.0)
	{
		animation_color_percent = 100.0;
	}
	else
	{
		if (animation_color_percent > 0.3)
		{
			if (state == 1)
			{
				animation_color_percent *= pow(0.96, frame_factor_inverse);
			}
			else
			{
				animation_color_percent *= pow(0.9, frame_factor_inverse);
			}
		}
		else
		{
			animation_color_percent = 0.0;
		}
	}

	// Update animation_movement_percent
	if (animation_movement_percent > 100.0)
	{
		animation_movement_percent = 100.0;
	}
	else
	{
		if (animation_movement_percent > 0.01)
		{
			animation_movement_percent *= pow(0.87, frame_factor_inverse);
		}
		else
		{
			animation_movement_percent = 0.0;
		}
	}
}






void CellSet::InitLeast(Font* const num_display_font)
{
	number_display.InitLeast(num_display_font);
	number_display.parent_rect.base_size = { 1.0, 1.0 };
	number_display.parent_rect.size = { 4.0, 4.0 };
}

void CellSet::UpdateNumberDisplay(const size_t selected_index)
{
	const Size2D true_scale = GetTrueScale();

	number_display.parent_rect.pos.x = pos.x + (((T_ONE_LESS_WIDTH * (double)selected_index) + T_HALF_WIDTH) * true_scale.width);
	number_display.parent_rect.pos.y = pos.y + (T_HEIGHT / 2.0 * true_scale.height) + 32.0;

	number_display.Clear();
	string string_index = to_string(selected_index);
	number_display.AddString(string_index);
	number_display.UpdateCharPos();
}

void CellSet::ClickAll(const bool target_state)
{
	for (size_t i = 0; i < set.size(); i++)
	{
		set[i]->Click(target_state);
	}
}
void CellSet::Click(const size_t index, const bool target_state)
{
	if ((index >= 0) && (index < set.size()))
	{
		set[index]->Click(target_state);
	}
	else
	{
		cout << "index out of range (index == " << index << " and set.size() == " << set.size() << ")" << endl;
	}
}

//Clicks all the transistors from begin_index to end_index, including both begin_index and end_index
void CellSet::ClickSection(const size_t begin_index, const size_t end_index, const bool target_state)
{
	const bool begin_index_valid = (begin_index >= 0) && (begin_index < set.size());
	const bool end_index_valid = (end_index >= 0) && (end_index < set.size());
	const bool end_is_greater = (end_index >= begin_index);

	if (begin_index_valid && end_index_valid && end_is_greater)
	{
		for (size_t i = begin_index; i <= end_index; i++)
		{
			set[i]->Click(target_state);
		}
	}

	//Handles error messaging
	else
	{
		bool already_found_error = 0;
		if (!begin_index_valid)
		{
			cout << "begin_index out of range (begin_index == " << begin_index << " and set.size() == " << set.size() << ")";
			already_found_error = 1;
		}
		if (!end_index_valid)
		{
			if (already_found_error)
			{
				cout << " AND ";
			}
			cout << "end_index out of range (end_index == " << end_index << " and set.size() == " << set.size() << ")";
			if (end_index == set.size())
			{
				cout << "(end index cannot equal set.size() because indexes start at zero and .size() starts at 1)";
			}
			already_found_error = 1;
		}
		if (!end_is_greater)
		{
			if (already_found_error)
			{
				cout << " AND ";
			}
			cout << "end_index is less than begin_index (end_index == " << end_index << " and begin_index == " << begin_index << ")";
		}

		cout << endl;
	}
}

//Clicks 8 transistors starting at and including the begin_index according to the char variable passed
void CellSet::ClickChar(const char value, const size_t begin_index, const bool target_state)
{
	bitset<8> value_bits(value);

	size_t current_index;
	for (size_t i = 0; i < 8; i++)
	{
		current_index = begin_index + i;
		if (current_index < set.size())
		{
			set[current_index]->Click(value_bits[7 - i]);
		}
		else
		{
			cout << "Went out of range! (Sent by ClickChar(...))" << endl;
			break;
		}
	}
}

//Clicks 8 transistors starting at and including the begin_index according to the char variable passed
void CellSet::ClickShort(const short value, const size_t begin_index, const bool target_state)
{
	bitset<16> value_bits(value);

	size_t current_index;
	for (size_t i = 0; i < 16; i++)
	{
		current_index = begin_index + i;
		if (current_index < set.size())
		{
			set[current_index]->Click(value_bits[15 - i]);
		}
		else
		{
			cout << "Went out of range! (Sent by ClickShort(...))" << endl;
			break;
		}
	}
}

//Clicks 32 transistors starting at and including the begin_index according to the char variable passed
void CellSet::ClickUnsigned32Int(const uint32_t value, const size_t begin_index, const bool target_state)
{
	bitset<32> value_bits(value);

	size_t current_index;
	for (size_t i = 0; i < 32; i++)
	{
		current_index = begin_index + i;
		if (current_index < set.size())
		{
			set[current_index]->Click(value_bits[31 - i]);
		}
		else
		{
			cout << "Went out of range! (Sent by ClickUnsigned32Int(...))" << endl;
			break;
		}
	}
}


Size2D CellSet::GetTrueScale() const
{
	return { (8.0 * size_scale.width), (8.0 * size_scale.height) };
}

Rectangle CellSet::GenerateFullHitbox() const
{
	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_HEIGHT * true_scale.height;
	temp_rectangle.size.width = (((float)set.size() * T_ONE_LESS_WIDTH) + 1.0) * true_scale.width;
	temp_rectangle.SetPosWithUniEdge(pos.x, { 2 });
	temp_rectangle.pos.y = pos.y;

	return temp_rectangle;
}
Rectangle CellSet::GenerateFullInnerHitbox() const
{
	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_INNER_HEIGHT * true_scale.height;
	temp_rectangle.size.width = (((float)set.size() * T_ONE_LESS_WIDTH) - 1.0) * true_scale.width;
	temp_rectangle.SetPosWithUniEdge(pos.x + true_scale.width, {2});
	temp_rectangle.pos.y = pos.y;

	return temp_rectangle;
}
Rectangle CellSet::GenerateHitbox(const size_t index) const
{
	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_HEIGHT * true_scale.height;
	temp_rectangle.size.width = T_WIDTH * true_scale.width;
	temp_rectangle.pos.x = pos.x + (((T_ONE_LESS_WIDTH * (double)index) + T_HALF_WIDTH) * true_scale.width);
	temp_rectangle.pos.y = pos.y;

	return temp_rectangle;
}
Rectangle CellSet::GenerateInnerHitbox(const size_t index) const
{
	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_INNER_HEIGHT * true_scale.height;
	temp_rectangle.size.width = T_INNER_WIDTH * true_scale.width;
	temp_rectangle.pos.x = pos.x + (((T_ONE_LESS_WIDTH * (double)index) + T_HALF_WIDTH) * true_scale.width);
	temp_rectangle.pos.y = pos.y;

	return temp_rectangle;
}

//Only includes half of each of the two horizontal sides (if applicable)
Rectangle CellSet::GenerateHitboxCropped(const size_t index) const
{
	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_HEIGHT * true_scale.height;
	temp_rectangle.size.width = T_ONE_LESS_WIDTH * true_scale.width;
	temp_rectangle.pos.x = pos.x + (((T_ONE_LESS_WIDTH * (double)index) + T_HALF_WIDTH) * true_scale.width);

	if (index == 0)
	{
		temp_rectangle.size.width += 0.5 * true_scale.width;
		temp_rectangle.pos.x -= 0.25 * true_scale.width;
	}
	if (index == (set.size() - size_t(1)))
	{
		temp_rectangle.size.width += 0.5 * true_scale.width;
		temp_rectangle.pos.x += 0.25 * true_scale.width;
	}

	temp_rectangle.pos.y = pos.y;

	return temp_rectangle;
}

Rectangle CellSet::GenerateHitboxRange(const size_t begin_index, const size_t end_index) const
{
	const size_t diff = end_index - begin_index;
	const double avrg = (double)(begin_index + end_index) / 2.0;

	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_HEIGHT * true_scale.height;
	temp_rectangle.size.width = ((T_ONE_LESS_WIDTH * (double)diff) + 1.0) * true_scale.width;
	temp_rectangle.pos.x = pos.x + (((T_ONE_LESS_WIDTH * (double)avrg) + T_HALF_WIDTH) * true_scale.width);
	temp_rectangle.pos.y = pos.y;

	return temp_rectangle;
}
Rectangle CellSet::GenerateInnerHitboxRange(const size_t begin_index, const size_t end_index) const
{
	const size_t diff = end_index - begin_index;
	const double avrg = (double)(begin_index + end_index) / 2.0;

	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_INNER_HEIGHT * true_scale.height;
	temp_rectangle.size.width = ((T_ONE_LESS_WIDTH * (double)diff) - 1.0) * true_scale.width;
	temp_rectangle.pos.x = pos.x + (((T_ONE_LESS_WIDTH * (double)avrg) + T_HALF_WIDTH) * true_scale.width);
	temp_rectangle.pos.y = pos.y;

	return temp_rectangle;
}
//Only includes half of each of the two horizontal sides (if applicable)
Rectangle CellSet::GenerateHitboxRangeCropped(const size_t begin_index, const size_t end_index) const
{
	const size_t diff = end_index - begin_index;
	const double avrg = (double)(begin_index + end_index) / 2.0;

	const Size2D true_scale = GetTrueScale();

	Rectangle temp_rectangle;

	temp_rectangle.size.height = T_HEIGHT * true_scale.height;
	temp_rectangle.size.width = (T_ONE_LESS_WIDTH * (double)diff) * true_scale.width;
	temp_rectangle.pos.x = pos.x + (((T_ONE_LESS_WIDTH * (double)avrg) + T_HALF_WIDTH) * true_scale.width);
	temp_rectangle.pos.y = pos.y;

	if (begin_index == 0)
	{
		temp_rectangle.size.width += 0.5 * true_scale.width;
		temp_rectangle.pos.x -= 0.25 * true_scale.width;
	}
	if (end_index == (set.size() - size_t(1)))
	{
		temp_rectangle.size.width += 0.5 * true_scale.width;
		temp_rectangle.pos.x += 0.25 * true_scale.width;
	}

	return temp_rectangle;
}