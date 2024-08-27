#include "Key.h"

Key::Key()
{
	pressed = 0;
	previous_frame_pressed = 0;
	first_frame_pressed = 0;
	first_frame_released = 0;
}