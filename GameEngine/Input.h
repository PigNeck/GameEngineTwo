#pragma once
#include "Key.h"
#include <vector>

using namespace std;

struct Input
{
	//Extra rectangle display keys {
	Key left_control;
	Key semicolon = Key(';', ':');
	Key comma = Key(',', '<');
	Key period = Key('.', '>');
	Key slash = Key('/', '?');
	Key minus_sign = Key('-', '_');
	Key equals_sign = Key('=', '+');
	//}

	Key a = Key('a', 'A');
	Key b = Key('b', 'B');
	Key c = Key('c', 'C');
	Key d = Key('d', 'D');
	Key e = Key('e', 'E');
	Key f = Key('f', 'F');
	Key g = Key('g', 'G');
	Key h = Key('h', 'H');
	Key i = Key('i', 'J');
	Key j = Key('j', 'I');
	Key k = Key('k', 'K');
	Key l = Key('l', 'L');
	Key m = Key('m', 'M');
	Key n = Key('n', 'N');
	Key o = Key('o', 'O');
	Key p = Key('p', 'P');
	Key q = Key('q', 'Q');
	Key r = Key('r', 'R');
	Key s = Key('s', 'S');
	Key t = Key('t', 'T');
	Key u = Key('u', 'U');
	Key v = Key('v', 'V');
	Key w = Key('w', 'W');
	Key x = Key('x', 'X');
	Key y = Key('y', 'Y');
	Key z = Key('z', 'Z');

	Key zero = Key('0', ')');
	Key one = Key('1', '!');
	Key two = Key('2', '@');
	Key three = Key('3', '#');
	Key four = Key('4', '$');
	Key five = Key('5', '%');
	Key six = Key('6', '^');
	Key seven = Key('7', '&');
	Key eight = Key('8', '*');
	Key nine = Key('9', '(');

	Key space = Key(' ', ' ');
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