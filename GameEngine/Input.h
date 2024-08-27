#pragma once
#include "Key.h"
#include <vector>

using namespace std;

struct Input
{
	Key a;
	Key b;
	Key c;
	Key d;
	Key e;
	Key f;
	Key g;
	Key h;
	Key i;
	Key j;
	Key k;
	Key l;
	Key m;
	Key n;
	Key o;
	Key p;
	Key q;
	Key r;
	Key s;
	Key t;
	Key u;
	Key v;
	Key w;
	Key x;
	Key y;
	Key z;

	Key zero;
	Key one;
	Key two;
	Key three;
	Key four;
	Key five;
	Key six;
	Key seven;
	Key eight;
	Key nine;

	Key space;
	Key backspace;
	Key left_shift;
	Key right_shift;

	Key mouse_left;
	Key mouse_right;
	Key mouse_middle;
	Key mouse_extra_one;
	Key mouse_extra_two;

	/*
	Key mouse_left_mask;
	Key mouse_right_mask;
	Key mouse_middle_mask;
	Key mouse_extra_button_one_mask;
	Key mouse_extra_button_two_mask;
	*/


	//change to array
	vector<Key*> all_keys;

	int mouse_scroll_x = 0;
	int mouse_scroll_y = 0;
	bool mouse_scroll_flipped = 0;

	int mouse_x = 0;
	int mouse_y = 0;

	char KeyToCharValue(Key* param_key, bool primary);
	char KeyIndexToCharValue(int index, bool primary);
	void FormatKeys();
};