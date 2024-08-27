#pragma once

struct Key
{
	bool pressed;
	bool previous_frame_pressed;
	bool first_frame_pressed;
	bool first_frame_released;

	Key();
};