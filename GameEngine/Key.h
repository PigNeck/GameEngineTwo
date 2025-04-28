#pragma once

struct Key
{
	bool pressed = false;
	bool previous_frame_pressed = false;
	bool first_frame_pressed = false;
	bool first_frame_released = false;

	char primary_char = 0;
	char secondary_char = 0;

	Key(const char i_primary_char = 0, const char i_secondary_char = 0);
};