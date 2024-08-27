#include "Animation.h"

using namespace std;

Frame::Frame()
{
	texture = nullptr;
	frame_length = 0.1;
}

void Animation::Update(const double game_frame_factor)
{
	double time_passing = game_frame_factor / 60.0;

	bool looping = 1;
	while (looping)
	{
		const Frame* const current_frame = GetCurrentFrame();

		const double fraction_of_current_frame_remaining = trunc(frame_progression + 1.0) - frame_progression;

		const double seconds_of_current_frame_remaining = fraction_of_current_frame_remaining * current_frame->frame_length;

		if (time_passing < seconds_of_current_frame_remaining)
		{
			frame_progression += time_passing / current_frame->frame_length;

			looping = 0;
			break;
		}
		else
		{
			frame_progression = trunc(frame_progression + 1.0);
			if (frame_progression == frames.size())
			{
				frame_progression = 0.0;
			}

			if (seconds_of_current_frame_remaining != time_passing)
			{
				time_passing -= seconds_of_current_frame_remaining;
			}
			else
			{
				looping = 0;
				break;
			}
		}
	}
}

Frame* Animation::GetCurrentFrame()
{
	return &frames[trunc(frame_progression)];
}

void Animation::LoadFrames(SDL_Renderer* const renderer, const char* folder_path, const int number_of_frames, const double frame_rate)
{
	for (int i = 0; i < number_of_frames; i++)
	{
		Frame temp_frame;

		temp_frame.frame_length = 1.0 / frame_rate;

		string string_path = string(folder_path);
		string_path += "/";
		string_path += to_string(i + 1);
		string_path += ".png";
		const char* final_path = string_path.c_str();
		temp_frame.texture = new Texture();
		temp_frame.texture->LoadTexture(renderer, final_path);

		frames.push_back(temp_frame);
	}

	if (frames.size() > 0)
	{
		if (frames.front().texture)
		{
			dimentions = frames.front().texture->size;
		}
	}
}