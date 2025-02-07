#pragma once
#include "Rectangle.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "Texture.h"

using namespace std;

struct Frame
{
	Texture* texture = nullptr;
	//frame_length is measured in seconds
	double frame_length = 0.1;
};

struct Animation
{
	Size2D dimentions = { 0.0, 0.0 };
	Point2D offset = { 0.0, 0.0 };

	vector<Frame> frames;

	double frame_progression = 0.0;

	void Update(const double game_frame_factor);

	Frame* GetCurrentFrame();

	void LoadFrames(const char* const folder_path, const int number_of_frames, const double frame_rate);
};

