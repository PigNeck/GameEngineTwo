#include "Font.h"

#define TBC(a) new FontChar(LoadCharTexture(renderer, ("images/fonts/" + param_name + "/" + GetTextureName(a)).c_str()), a, default_default_char_spacing)

Texture* Font::LoadCharTexture(SDL_Renderer* renderer, const char* path)
{
	Texture* texture = new Texture();
	texture->LoadTexture(renderer, path);
	if (!texture)
	{
		return NULL_texture;
	}
	else
	{
		return texture;
	}
}

using namespace std;

Font::Font()
{
	all_chars[0] = A;
	all_chars[1] = B;
	all_chars[2] = C;
	all_chars[3] = D;
	all_chars[4] = E;
	all_chars[5] = F;
	all_chars[6] = G;
	all_chars[7] = H;
	all_chars[8] = I;
	all_chars[9] = J;
	all_chars[10] = K;
	all_chars[11] = L;
	all_chars[12] = M;
	all_chars[13] = N;
	all_chars[14] = O;
	all_chars[15] = P;
	all_chars[16] = Q;
	all_chars[17] = R;
	all_chars[18] = S;
	all_chars[19] = T;
	all_chars[20] = U;
	all_chars[21] = V;
	all_chars[22] = W;
	all_chars[23] = X;
	all_chars[24] = Y;
	all_chars[25] = Z;
	all_chars[26] = a;
	all_chars[27] = b;
	all_chars[28] = c;
	all_chars[29] = d;
	all_chars[30] = e;
	all_chars[31] = f;
	all_chars[32] = g;
	all_chars[33] = h;
	all_chars[34] = i;
	all_chars[35] = j;
	all_chars[36] = k;
	all_chars[37] = l;
	all_chars[38] = m;
	all_chars[39] = n;
	all_chars[40] = o;
	all_chars[41] = p;
	all_chars[42] = q;
	all_chars[43] = r;
	all_chars[44] = s;
	all_chars[45] = t;
	all_chars[46] = u;
	all_chars[47] = v;
	all_chars[48] = w;
	all_chars[49] = x;
	all_chars[50] = y;
	all_chars[51] = z;
	all_chars[52] = num_0;
	all_chars[53] = num_1;
	all_chars[54] = num_2;
	all_chars[55] = num_3;
	all_chars[56] = num_4;
	all_chars[57] = num_5;
	all_chars[58] = num_6;
	all_chars[59] = num_7;
	all_chars[60] = num_8;
	all_chars[61] = num_9;
	all_chars[62] = acute;
	all_chars[63] = tilde;
	all_chars[64] = exclaimation_point;
	all_chars[65] = at_sign;
	all_chars[66] = hashtag;
	all_chars[67] = dollar_sign;
	all_chars[68] = percent_sign;
	all_chars[69] = caret;
	all_chars[70] = ampersand;
	all_chars[71] = asterisk;
	all_chars[72] = open_parenthesis;
	all_chars[73] = close_parenthesis;
	all_chars[74] = minus_sign;
	all_chars[75] = underscore;
	all_chars[76] = equals_sign;
	all_chars[77] = plus_sign;
	all_chars[78] = open_bracket;
	all_chars[79] = close_bracket;
	all_chars[80] = open_curly_bracket;
	all_chars[81] = close_curly_bracket;
	all_chars[82] = backslash;
	all_chars[83] = vertical_slash;
	all_chars[84] = semicolon;
	all_chars[85] = colon;
	all_chars[86] = single_quote;
	all_chars[87] = double_quote;
	all_chars[88] = comma;
	all_chars[89] = less_than_sign;
	all_chars[90] = period;
	all_chars[91] = greater_than_sign;
	all_chars[92] = slash;
	all_chars[93] = question_mark;
	all_chars[94] = space;
	all_chars[95] = new_line;
}

void Font::InitFont(string param_name, SDL_Renderer* renderer)
{
	font_name = param_name;

	default_default_char_spacing = 1;

	NULL_texture = new Texture();
	NULL_texture->LoadTexture(renderer, ("images/fonts/" + param_name + "/Char_null.png").c_str());

	A = TBC('A');
	B = TBC('B');
	C = TBC('C');
	D = TBC('D');
	E = TBC('E');
	F = TBC('F');
	G = TBC('G');
	H = TBC('H');
	I = TBC('I');
	J = TBC('J');
	K = TBC('K');
	L = TBC('L');
	M = TBC('M');
	N = TBC('N');
	O = TBC('O');
	P = TBC('P');
	Q = TBC('Q');
	R = TBC('R');
	S = TBC('S');
	T = TBC('T');
	U = TBC('U');
	V = TBC('V');
	W = TBC('W');
	X = TBC('X');
	Y = TBC('Y');
	Z = TBC('Z');

	a = TBC('a');
	b = TBC('b');
	c = TBC('c');
	d = TBC('d');
	e = TBC('e');
	f = TBC('f');
	g = TBC('g');
	h = TBC('h');
	i = TBC('i');
	j = TBC('j');
	k = TBC('k');
	l = TBC('l');
	m = TBC('m');
	n = TBC('n');
	o = TBC('o');
	p = TBC('p');
	q = TBC('q');
	r = TBC('r');
	s = TBC('s');
	t = TBC('t');
	u = TBC('u');
	v = TBC('v');
	w = TBC('w');
	x = TBC('x');
	y = TBC('y');
	z = TBC('z');

	num_0 = TBC('0');
	num_1 = TBC('1');
	num_2 = TBC('2');
	num_3 = TBC('3');
	num_4 = TBC('4');
	num_5 = TBC('5');
	num_6 = TBC('6');
	num_7 = TBC('7');
	num_8 = TBC('8');
	num_9 = TBC('9');

	acute = TBC('`');
	tilde = TBC('~');
	exclaimation_point = TBC('!');
	at_sign = TBC('@');
	hashtag = TBC('#');
	dollar_sign = TBC('$');
	percent_sign = TBC('%');
	caret = TBC('^');
	ampersand = TBC('&');
	asterisk = TBC('*');
	open_parenthesis = TBC('(');
	close_parenthesis = TBC(')');
	minus_sign = TBC('-');
	underscore = TBC('_');
	equals_sign = TBC('=');
	plus_sign = TBC('+');
	open_bracket = TBC('[');
	close_bracket = TBC(']');
	open_curly_bracket = TBC('{');
	close_curly_bracket = TBC('}');
	backslash = TBC('\\');
	vertical_slash = TBC('|');
	semicolon = TBC(';');
	colon = TBC(':');
	single_quote = TBC('\'');
	double_quote = TBC('\"');
	comma = TBC(',');
	less_than_sign = TBC('<');
	period = TBC('.');
	greater_than_sign = TBC('>');
	slash = TBC('/');
	question_mark = TBC('?');
	space = TBC(' ');
	new_line = TBC('\n');

	default_default_line_spacing = round(A->default_height / 7);
	default_default_line_height = A->default_height;
}

FontChar* Font::GetFontChar(char char_value)
{
	switch (char_value)
	{
	case 0: return nullptr;
	case 1: return nullptr;
	case 2: return nullptr;
	case 3: return nullptr;
	case 4: return nullptr;
	case 5: return nullptr;
	case 6: return nullptr;
	case 7: return nullptr;
	case 8: return nullptr;
	case 9: return nullptr;
	case 10: return new_line;
	case 11: return nullptr;
	case 12: return nullptr;
	case 13: return nullptr;
	case 14: return nullptr;
	case 15: return nullptr;
	case 16: return nullptr;
	case 17: return nullptr;
	case 18: return nullptr;
	case 19: return nullptr;
	case 20: return nullptr;
	case 21: return nullptr;
	case 22: return nullptr;
	case 23: return nullptr;
	case 24: return nullptr;
	case 25: return nullptr;
	case 26: return nullptr;
	case 27: return nullptr;
	case 28: return nullptr;
	case 29: return nullptr;
	case 30: return nullptr;
	case 31: return nullptr;
	case 32: return space;
	case 33: return exclaimation_point;
	case 34: return double_quote;
	case 35: return hashtag;
	case 36: return dollar_sign;
	case 37: return percent_sign;
	case 38: return ampersand;
	case 39: return single_quote;
	case 40: return open_parenthesis;
	case 41: return close_parenthesis;
	case 42: return asterisk;
	case 43: return plus_sign;
	case 44: return comma;
	case 45: return minus_sign;
	case 46: return period;
	case 47: return slash;
	case 48: return num_0;
	case 49: return num_1;
	case 50: return num_2;
	case 51: return num_3;
	case 52: return num_4;
	case 53: return num_5;
	case 54: return num_6;
	case 55: return num_7;
	case 56: return num_8;
	case 57: return num_9;
	case 58: return colon;
	case 59: return semicolon;
	case 60: return less_than_sign;
	case 61: return equals_sign;
	case 62: return greater_than_sign;
	case 63: return question_mark;
	case 64: return at_sign;
	case 65: return A;
	case 66: return B;
	case 67: return C;
	case 68: return D;
	case 69: return E;
	case 70: return F;
	case 71: return G;
	case 72: return H;
	case 73: return I;
	case 74: return J;
	case 75: return K;
	case 76: return L;
	case 77: return M;
	case 78: return N;
	case 79: return O;
	case 80: return P;
	case 81: return Q;
	case 82: return R;
	case 83: return S;
	case 84: return T;
	case 85: return U;
	case 86: return V;
	case 87: return W;
	case 88: return X;
	case 89: return Y;
	case 90: return Z;
	case 91: return open_bracket;
	case 92: return backslash;
	case 93: return close_bracket;
	case 94: return caret;
	case 95: return underscore;
	case 96: return acute;
	case 97: return a;
	case 98: return b;
	case 99: return c;
	case 100: return d;
	case 101: return e;
	case 102: return f;
	case 103: return g;
	case 104: return h;
	case 105: return i;
	case 106: return j;
	case 107: return k;
	case 108: return l;
	case 109: return m;
	case 110: return n;
	case 111: return o;
	case 112: return p;
	case 113: return q;
	case 114: return r;
	case 115: return s;
	case 116: return t;
	case 117: return u;
	case 118: return v;
	case 119: return w;
	case 120: return x;
	case 121: return y;
	case 122: return z;
	case 123: return open_curly_bracket;
	case 124: return vertical_slash;
	case 125: return close_curly_bracket;
	case 126: return tilde;
	case 127: return nullptr;
	}

	return nullptr;
}