#include "Input.h"

//128 case switch-case statement:
/*
switch (index)
	{
	case 0: return;
	case 1: return;
	case 2: return;
	case 3: return;
	case 4: return;
	case 5: return;
	case 6: return;
	case 7: return;
	case 8: return;
	case 9: return;
	case 10: return;
	case 11: return;
	case 12: return;
	case 13: return;
	case 14: return;
	case 15: return;
	case 16: return;
	case 17: return;
	case 18: return;
	case 19: return;
	case 20: return;
	case 21: return;
	case 22: return;
	case 23: return;
	case 24: return;
	case 25: return;
	case 26: return;
	case 27: return;
	case 28: return;
	case 29: return;
	case 30: return;
	case 31: return;
	case 32: return;
	case 33: return;
	case 34: return;
	case 35: return;
	case 36: return;
	case 37: return;
	case 38: return;
	case 39: return;
	case 40: return;
	case 41: return;
	case 42: return;
	case 43: return;
	case 44: return;
	case 45: return;
	case 46: return;
	case 47: return;
	case 48: return;
	case 49: return;
	case 50: return;
	case 51: return;
	case 52: return;
	case 53: return;
	case 54: return;
	case 55: return;
	case 56: return;
	case 57: return;
	case 58: return;
	case 59: return;
	case 60: return;
	case 61: return;
	case 62: return;
	case 63: return;
	case 64: return;
	case 65: return;
	case 66: return;
	case 67: return;
	case 68: return;
	case 69: return;
	case 70: return;
	case 71: return;
	case 72: return;
	case 73: return;
	case 74: return;
	case 75: return;
	case 76: return;
	case 77: return;
	case 78: return;
	case 79: return;
	case 80: return;
	case 81: return;
	case 82: return;
	case 83: return;
	case 84: return;
	case 85: return;
	case 86: return;
	case 87: return;
	case 88: return;
	case 89: return;
	case 90: return;
	case 91: return;
	case 92: return;
	case 93: return;
	case 94: return;
	case 95: return;
	case 96: return;
	case 97: return;
	case 98: return;
	case 99: return;
	case 100: return;
	case 101: return;
	case 102: return;
	case 103: return;
	case 104: return;
	case 105: return;
	case 106: return;
	case 107: return;
	case 108: return;
	case 109: return;
	case 110: return;
	case 111: return;
	case 112: return;
	case 113: return;
	case 114: return;
	case 115: return;
	case 116: return;
	case 117: return;
	case 118: return;
	case 119: return;
	case 120: return;
	case 121: return;
	case 122: return;
	case 123: return;
	case 124: return;
	case 125: return;
	case 126: return;
	case 127: return;
	}
*/

#define TBC(a) new FontChar(LoadCharTexture(renderer, ("images/fonts/" + param_name + "/" + GetTextureName(a)).c_str()), a)

#define KTC(a, b) if (param_key == &a) { return b; }

char Input::KeyToCharValue(Key* param_key, bool primary)
{
	if (primary)
	{
		KTC(a, 'a');
		KTC(b, 'b');
		KTC(c, 'c');
		KTC(d, 'd');
		KTC(e, 'e');
		KTC(f, 'f');
		KTC(g, 'g');
		KTC(h, 'h');
		KTC(i, 'i');
		KTC(j, 'j');
		KTC(k, 'k');
		KTC(l, 'l');
		KTC(m, 'm');
		KTC(n, 'n');
		KTC(o, 'o');
		KTC(p, 'p');
		KTC(q, 'q');
		KTC(r, 'r');
		KTC(s, 's');
		KTC(t, 't');
		KTC(u, 'u');
		KTC(v, 'v');
		KTC(w, 'w');
		KTC(x, 'x');
		KTC(y, 'y');
		KTC(z, 'z');
		KTC(zero, '0');
		KTC(one, '1');
		KTC(two, '2');
		KTC(three, '3');
		KTC(four, '4');
		KTC(five, '5');
		KTC(six, '6');
		KTC(seven, '7');
		KTC(eight, '8');
		KTC(nine, '9');

		KTC(space, ' ');
		KTC(backspace, NULL);
		KTC(left_shift, NULL);
		KTC(right_shift, NULL);
	}
	else
	{
		KTC(a, 'A');
		KTC(b, 'B');
		KTC(c, 'C');
		KTC(d, 'D');
		KTC(e, 'E');
		KTC(f, 'F');
		KTC(g, 'G');
		KTC(h, 'H');
		KTC(i, 'I');
		KTC(j, 'J');
		KTC(k, 'K');
		KTC(l, 'L');
		KTC(m, 'M');
		KTC(n, 'N');
		KTC(o, 'O');
		KTC(p, 'P');
		KTC(q, 'Q');
		KTC(r, 'R');
		KTC(s, 'S');
		KTC(t, 'T');
		KTC(u, 'U');
		KTC(v, 'V');
		KTC(w, 'W');
		KTC(x, 'X');
		KTC(y, 'Y');
		KTC(z, 'Z');
		KTC(zero, ')');
		KTC(one, '!');
		KTC(two, '@');
		KTC(three, '#');
		KTC(four, '$');
		KTC(five, '%');
		KTC(six, '^');
		KTC(seven, '&');
		KTC(eight, '*');
		KTC(nine, '(');

		KTC(space, ' ');
		KTC(backspace, NULL);
		KTC(left_shift, NULL);
		KTC(right_shift, NULL);
	}

	return NULL;
}
char Input::KeyIndexToCharValue(int index, bool primary)
{
	if (primary)
	{
		switch (index)
		{
		case 0: return 'a';
		case 1: return 'b';
		case 2: return 'c';
		case 3: return 'd';
		case 4: return 'e';
		case 5: return 'f';
		case 6: return 'g';
		case 7: return 'h';
		case 8: return 'i';
		case 9: return 'j';
		case 10: return 'k';
		case 11: return 'l';
		case 12: return 'm';
		case 13: return 'n';
		case 14: return 'o';
		case 15: return 'p';
		case 16: return 'q';
		case 17: return 'r';
		case 18: return 's';
		case 19: return 't';
		case 20: return 'u';
		case 21: return 'v';
		case 22: return 'w';
		case 23: return 'x';
		case 24: return 'y';
		case 25: return 'z';
		case 26: return '0';
		case 27: return '1';
		case 28: return '2';
		case 29: return '3';
		case 30: return '4';
		case 31: return '5';
		case 32: return '6';
		case 33: return '7';
		case 34: return '8';
		case 35: return '9';
		case 36: return ' ';
		case 37: return NULL;
		case 38: return NULL;
		case 39: return NULL;
		}
	}
	else
	{
		switch (index)
		{
		case 0: return 'A';
		case 1: return 'B';
		case 2: return 'C';
		case 3: return 'D';
		case 4: return 'E';
		case 5: return 'F';
		case 6: return 'G';
		case 7: return 'H';
		case 8: return 'I';
		case 9: return 'J';
		case 10: return 'K';
		case 11: return 'L';
		case 12: return 'M';
		case 13: return 'N';
		case 14: return 'O';
		case 15: return 'P';
		case 16: return 'Q';
		case 17: return 'R';
		case 18: return 'S';
		case 19: return 'T';
		case 20: return 'U';
		case 21: return 'V';
		case 22: return 'W';
		case 23: return 'X';
		case 24: return 'Y';
		case 25: return 'Z';
		case 26: return ')';
		case 27: return '!';
		case 28: return '@';
		case 29: return '#';
		case 30: return '$';
		case 31: return '%';
		case 32: return '^';
		case 33: return '&';
		case 34: return '*';
		case 35: return '(';
		case 36: return ' ';
		case 37: return NULL;
		case 38: return NULL;
		case 39: return NULL;
		}
	}

	return NULL;
}

void Input::FormatKeys()
{
	all_keys.push_back(&left_control);
	all_keys.push_back(&semicolon);
	all_keys.push_back(&comma);
	all_keys.push_back(&period);
	all_keys.push_back(&slash);
	all_keys.push_back(&minus_sign);
	all_keys.push_back(&equals_sign);

	all_keys.push_back(&a);
	all_keys.push_back(&b);
	all_keys.push_back(&c);
	all_keys.push_back(&d);
	all_keys.push_back(&e);
	all_keys.push_back(&f);
	all_keys.push_back(&g);
	all_keys.push_back(&h);
	all_keys.push_back(&i);
	all_keys.push_back(&j);
	all_keys.push_back(&k);
	all_keys.push_back(&l);
	all_keys.push_back(&m);
	all_keys.push_back(&n);
	all_keys.push_back(&o);
	all_keys.push_back(&p);
	all_keys.push_back(&q);
	all_keys.push_back(&r);
	all_keys.push_back(&s);
	all_keys.push_back(&t);
	all_keys.push_back(&u);
	all_keys.push_back(&v);
	all_keys.push_back(&w);
	all_keys.push_back(&x);
	all_keys.push_back(&y);
	all_keys.push_back(&z);

	all_keys.push_back(&zero);
	all_keys.push_back(&one);
	all_keys.push_back(&two);
	all_keys.push_back(&three);
	all_keys.push_back(&four);
	all_keys.push_back(&five);
	all_keys.push_back(&six);
	all_keys.push_back(&seven);
	all_keys.push_back(&eight);
	all_keys.push_back(&nine);

	all_keys.push_back(&space);
	all_keys.push_back(&backspace);
	all_keys.push_back(&left_shift);
	all_keys.push_back(&right_shift);

	all_keys.push_back(&mouse_left);
	all_keys.push_back(&mouse_right);
	all_keys.push_back(&mouse_middle);
	all_keys.push_back(&mouse_extra_one);
	all_keys.push_back(&mouse_extra_two);
}