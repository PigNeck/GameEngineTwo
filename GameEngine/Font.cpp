#include "Font.h"

#define TBC(a) new FontChar(LoadCharTexture(("images/fonts/" + param_name + "/" + GetTextureName(a)).c_str()), a, param_default_default_char_spacing)

Texture* Font::LoadCharTexture(const char* path)
{
	Texture* texture = new Texture();
	texture->LoadTexture(path);
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

void Font::Init(string param_name, SDL_Renderer* renderer, const double param_default_default_char_spacing, const double param_default_default_line_spacing, const double param_default_default_line_height)
{
	font_name = param_name;

	NULL_texture = new Texture();
	NULL_texture->LoadTexture(("images/fonts/" + param_name + "/Char_null.png").c_str());

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
	g->default_unscaled_y_offset = -2.0;
	h = TBC('h');
	i = TBC('i');
	j = TBC('j');
	k = TBC('k');
	l = TBC('l');
	m = TBC('m');
	n = TBC('n');
	o = TBC('o');
	p = TBC('p');
	p->default_unscaled_y_offset = -2.0;
	q = TBC('q');
	q->default_unscaled_y_offset = -2.0;
	r = TBC('r');
	s = TBC('s');
	t = TBC('t');
	u = TBC('u');
	v = TBC('v');
	w = TBC('w');
	x = TBC('x');
	y = TBC('y');
	y->default_unscaled_y_offset = -2.0;
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
	acute->default_unscaled_y_offset = 4.0;
	tilde = TBC('~');
	tilde->default_unscaled_y_offset = 2.0;
	exclaimation_point = TBC('!');
	at_sign = TBC('@');
	hashtag = TBC('#');
	hashtag->default_unscaled_y_offset = 1.0;
	dollar_sign = TBC('$');
	percent_sign = TBC('%');
	caret = TBC('^');
	caret->default_unscaled_y_offset = 2.0;
	ampersand = TBC('&');
	asterisk = TBC('*');
	asterisk->default_unscaled_y_offset = 2.0;
	open_parenthesis = TBC('(');
	close_parenthesis = TBC(')');
	minus_sign = TBC('-');
	minus_sign->default_unscaled_y_offset = 3.0;
	underscore = TBC('_');
	equals_sign = TBC('=');
	equals_sign->default_unscaled_y_offset = 2.0;
	plus_sign = TBC('+');
	plus_sign->default_unscaled_y_offset = 1.0;
	open_bracket = TBC('[');
	close_bracket = TBC(']');
	open_curly_bracket = TBC('{');
	close_curly_bracket = TBC('}');
	backslash = TBC('\\');
	vertical_slash = TBC('|');
	semicolon = TBC(';');
	colon = TBC(':');
	single_quote = TBC('\'');
	single_quote->default_unscaled_y_offset = 3.0;
	double_quote = TBC('\"');
	double_quote->default_unscaled_y_offset = 3.0;
	comma = TBC(',');
	comma->default_unscaled_y_offset = -1.0;
	less_than_sign = TBC('<');
	less_than_sign->default_unscaled_y_offset = 1.0;
	period = TBC('.');
	greater_than_sign = TBC('>');
	greater_than_sign->default_unscaled_y_offset = 1.0;
	slash = TBC('/');
	question_mark = TBC('?');
	space = TBC(' ');
	new_line = TBC('\n');

	default_default_line_spacing = param_default_default_line_spacing;
	default_default_line_height = param_default_default_line_height;
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









LineParameters::LineParameters(const double i_pixel_height, const double i_pixel_spacing_top, const double i_pixel_spacing_bottom, const double i_pixel_max_width, const Point2DNew i_pixel_offset, const bool i_ignore_char_spacing_on_line_ends, const bool i_bunch_words_together)
	: pixel_height(i_pixel_height),
	pixel_spacing_top(i_pixel_spacing_top),
	pixel_spacing_bottom(i_pixel_spacing_bottom),
	pixel_max_width(i_pixel_max_width),
	pixel_offset(i_pixel_offset),
	ignore_char_spacing_on_line_ends(i_ignore_char_spacing_on_line_ends),
	bunch_words_together(i_bunch_words_together) {}


IndexedLineParameters::IndexedLineParameters(const double i_pixel_height, const double i_pixel_spacing_top, const double i_pixel_spacing_bottom, const double i_pixel_max_width, const Point2DNew i_pixel_offset, const bool i_ignore_char_spacing_on_line_ends, const bool i_bunch_words_together)
	: LineParameters(i_pixel_height, i_pixel_spacing_top, i_pixel_spacing_bottom, i_pixel_max_width, i_pixel_offset, i_ignore_char_spacing_on_line_ends, i_bunch_words_together) {}

IndexedLineParameters::IndexedLineParameters(const size_t i_index, const double i_pixel_height, const double i_pixel_spacing_top, const double i_pixel_spacing_bottom, const double i_pixel_max_width, const Point2DNew i_pixel_offset, const bool i_ignore_char_spacing_on_line_ends, const bool i_bunch_words_together)
	: index(i_index), LineParameters(i_pixel_height, i_pixel_spacing_top, i_pixel_spacing_bottom, i_pixel_max_width, i_pixel_offset, i_ignore_char_spacing_on_line_ends, i_bunch_words_together) {}




BasicFont::BasicFont() {}
BasicFont::BasicFont(const char* const i_font_name, const char* const i_chars_file_type, const LineParameters i_template_line_parameters, const double default_template_unscaled_pixel_spacing_left, const double default_template_unscaled_pixel_spacing_right, const Point2DNew default_template_unscaled_pixel_offset)
	: font_name(i_font_name),
	chars_file_type(i_chars_file_type),
	template_line_parameters(i_template_line_parameters),
	A(5.0, this, 'A', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
    B(this, 'B', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	C(this, 'C', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	D(this, 'D', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	E(this, 'E', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	F(this, 'F', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	G(this, 'G', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	H(this, 'H', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	I(this, 'I', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	J(this, 'J', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	K(this, 'K', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	L(this, 'L', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	M(this, 'M', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	N(this, 'N', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	O(this, 'O', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	P(this, 'P', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	Q(this, 'Q', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	R(this, 'R', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	S(this, 'S', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	T(this, 'T', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	U(this, 'U', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	V(this, 'V', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	W(this, 'W', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	X(this, 'X', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	Y(this, 'Y', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	Z(this, 'Z', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	a(this, 'a', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	b(this, 'b', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	c(this, 'c', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	d(this, 'd', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	e(this, 'e', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	f(this, 'f', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	g(this, 'g', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	h(this, 'h', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	i(this, 'i', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	j(this, 'j', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	k(this, 'k', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	l(this, 'l', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	m(this, 'm', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	n(this, 'n', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	o(this, 'o', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	p(this, 'p', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	q(this, 'q', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	r(this, 'r', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	s(this, 's', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	t(this, 't', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	u(this, 'u', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	v(this, 'v', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	w(this, 'w', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	x(this, 'x', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	y(this, 'y', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	z(this, 'z', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_0(this, '0', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_1(this, '1', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_2(this, '2', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_3(this, '3', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_4(this, '4', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_5(this, '5', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_6(this, '6', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_7(this, '7', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_8(this, '8', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	num_9(this, '9', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	exclaimation_mark(this, '!', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	double_quote(this, '\"', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	hashtag(this, '#', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	dollar_sign(this, '$', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	percent_sign(this, '%', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	ampersand(this, '&', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	single_quote(this, '\'', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	open_parenthesis(this, '(', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	close_parenthesis(this, ')', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	asterisk(this, '*', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	plus_sign(this, '+', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	comma(this, ',', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	minus_sign(this, '-', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	period(this, '.', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	slash(this, '/', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	colon(this, ':', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	semicolon(this, ';', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	less_than_sign(this, '<', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	equals_sign(this, '=', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	greater_than_sign(this, '>', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	question_mark(this, '?', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	at_sign(this, '@', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	open_bracket(this, '[', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	backslash(this, '\\', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	close_bracket(this, ']', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	caret(this, '^', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	underscore(this, '_', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	backtick(this, '`', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	open_brace(this, '{', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	vertical_slash(this, '|', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	close_brace(this, '}', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	tilde(this, '~', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	space(this, ' ', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	new_line(this, '\n', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),
	NULL_char(this, 0, default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset),

	all_chars{ &NULL_char, &new_line, &space, &exclaimation_mark, &double_quote, &hashtag, &dollar_sign, &percent_sign, &ampersand, &single_quote, &open_parenthesis, &close_parenthesis, &asterisk, &plus_sign, &comma, &minus_sign, &period, &slash, &num_0, &num_1, &num_2, &num_3, &num_4, &num_5, &num_6, &num_7, &num_8, &num_9, &colon, &semicolon, &less_than_sign, &equals_sign, &greater_than_sign, &question_mark, &at_sign, &A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z, &open_bracket, &backslash, &close_bracket, &caret, &underscore, &backtick, &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z , &open_brace, &vertical_slash, &close_brace, &tilde },
	uppercase_letters{ &A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z },
	lowercase_letters{ &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z },
	numbers{ &num_0, &num_1, &num_2, &num_3, &num_4, &num_5, &num_6, &num_7, &num_8, &num_9 },
	symbols{ &exclaimation_mark, &double_quote, &hashtag, &dollar_sign, &percent_sign, &ampersand, &single_quote, &open_parenthesis, &close_parenthesis, &asterisk, &plus_sign, &comma, &minus_sign, &period, &slash, &colon, &semicolon, &less_than_sign, &equals_sign, &greater_than_sign, &question_mark, &at_sign, &open_bracket, &backslash, &close_bracket, &caret, &underscore, &backtick, &open_brace, &vertical_slash, &close_brace, &tilde },
	misc{ &NULL_char, &new_line, &space }
{

}

void BasicFont::Init(const char* const i_font_name, const char* const i_chars_file_type, const LineParameters i_template_line_parameters, const double default_template_unscaled_pixel_spacing_left, const double default_template_unscaled_pixel_spacing_right, const Point2DNew default_template_unscaled_pixel_offset)
{
	font_name = i_font_name;
	chars_file_type = i_chars_file_type;
	template_line_parameters = i_template_line_parameters;

	A = BasicFontChar(this, 'A', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	B = BasicFontChar(this, 'B', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	C = BasicFontChar(this, 'C', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	D = BasicFontChar(this, 'D', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	E = BasicFontChar(this, 'E', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	F = BasicFontChar(this, 'F', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	G = BasicFontChar(this, 'G', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	H = BasicFontChar(this, 'H', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	I = BasicFontChar(this, 'I', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	J = BasicFontChar(this, 'J', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	K = BasicFontChar(this, 'K', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	L = BasicFontChar(this, 'L', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	M = BasicFontChar(this, 'M', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	N = BasicFontChar(this, 'N', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	O = BasicFontChar(this, 'O', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	P = BasicFontChar(this, 'P', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	Q = BasicFontChar(this, 'Q', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	R = BasicFontChar(this, 'R', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	S = BasicFontChar(this, 'S', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	T = BasicFontChar(this, 'T', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	U = BasicFontChar(this, 'U', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	V = BasicFontChar(this, 'V', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	W = BasicFontChar(this, 'W', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	X = BasicFontChar(this, 'X', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	Y = BasicFontChar(this, 'Y', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	Z = BasicFontChar(this, 'Z', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	a = BasicFontChar(this, 'a', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	b = BasicFontChar(this, 'b', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	c = BasicFontChar(this, 'c', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	d = BasicFontChar(this, 'd', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	e = BasicFontChar(this, 'e', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	f = BasicFontChar(this, 'f', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	g = BasicFontChar(this, 'g', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	h = BasicFontChar(this, 'h', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	i = BasicFontChar(this, 'i', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	j = BasicFontChar(this, 'j', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	k = BasicFontChar(this, 'k', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	l = BasicFontChar(this, 'l', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	m = BasicFontChar(this, 'm', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	n = BasicFontChar(this, 'n', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	o = BasicFontChar(this, 'o', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	p = BasicFontChar(this, 'p', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	q = BasicFontChar(this, 'q', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	r = BasicFontChar(this, 'r', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	s = BasicFontChar(this, 's', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	t = BasicFontChar(this, 't', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	u = BasicFontChar(this, 'u', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	v = BasicFontChar(this, 'v', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	w = BasicFontChar(this, 'w', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	x = BasicFontChar(this, 'x', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	y = BasicFontChar(this, 'y', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	z = BasicFontChar(this, 'z', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_0 = BasicFontChar(this, '0', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_1 = BasicFontChar(this, '1', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_2 = BasicFontChar(this, '2', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_3 = BasicFontChar(this, '3', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_4 = BasicFontChar(this, '4', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_5 = BasicFontChar(this, '5', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_6 = BasicFontChar(this, '6', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_7 = BasicFontChar(this, '7', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_8 = BasicFontChar(this, '8', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	num_9 = BasicFontChar(this, '9', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	exclaimation_mark = BasicFontChar(this, '!', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	double_quote = BasicFontChar(this, '\"', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	hashtag = BasicFontChar(this, '#', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	dollar_sign = BasicFontChar(this, '$', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	percent_sign = BasicFontChar(this, '%', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	ampersand = BasicFontChar(this, '&', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	single_quote = BasicFontChar(this, '\'', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	open_parenthesis = BasicFontChar(this, '(', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	close_parenthesis = BasicFontChar(this, ')', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	asterisk = BasicFontChar(this, '*', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	plus_sign = BasicFontChar(this, '+', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	comma = BasicFontChar(this, ',', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	minus_sign = BasicFontChar(this, '-', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	period = BasicFontChar(this, '.', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	slash = BasicFontChar(this, '/', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	colon = BasicFontChar(this, ':', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	semicolon = BasicFontChar(this, ';', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	less_than_sign = BasicFontChar(this, '<', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	equals_sign = BasicFontChar(this, '=', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	greater_than_sign = BasicFontChar(this, '>', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	question_mark = BasicFontChar(this, '?', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	at_sign = BasicFontChar(this, '@', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	open_bracket = BasicFontChar(this, '[', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	backslash = BasicFontChar(this, '\\', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	close_bracket = BasicFontChar(this, ']', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	caret = BasicFontChar(this, '^', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	underscore = BasicFontChar(this, '_', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	backtick = BasicFontChar(this, '`', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	open_brace = BasicFontChar(this, '{', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	vertical_slash = BasicFontChar(this, '|', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	close_brace = BasicFontChar(this, '}', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	tilde = BasicFontChar(this, '~', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	space = BasicFontChar(this, ' ', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	new_line = BasicFontChar(this, '\n', default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);
	NULL_char = BasicFontChar(this, 0, default_template_unscaled_pixel_spacing_left, default_template_unscaled_pixel_spacing_right, default_template_unscaled_pixel_offset);

	LoadCharTextures();

	BasicFontChar* temp_all_chars[97] = { &NULL_char, &new_line, &space, &exclaimation_mark, &double_quote, &hashtag, &dollar_sign, &percent_sign, &ampersand, &single_quote, &open_parenthesis, &close_parenthesis, &asterisk, &plus_sign, &comma, &minus_sign, &period, &slash, &num_0, &num_1, &num_2, &num_3, &num_4, &num_5, &num_6, &num_7, &num_8, &num_9, &colon, &semicolon, &less_than_sign, &equals_sign, &greater_than_sign, &question_mark, &at_sign, &A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z, &open_bracket, &backslash, &close_bracket, &caret, &underscore, &backtick, &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z , &open_brace, &vertical_slash, &close_brace, &tilde };
	copy(begin(temp_all_chars), end(temp_all_chars), all_chars);

	BasicFontChar* temp_uppercase_letters[26] = { &A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z };
	copy(begin(temp_uppercase_letters), end(temp_uppercase_letters), uppercase_letters);

	BasicFontChar* temp_lowercase_letters[26] = { &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z };
	copy(begin(temp_lowercase_letters), end(temp_lowercase_letters), lowercase_letters);

	BasicFontChar* temp_numbers[10] = { &num_0, &num_1, &num_2, &num_3, &num_4, &num_5, &num_6, &num_7, &num_8, &num_9 };
	copy(begin(temp_numbers), end(temp_numbers), numbers);

	BasicFontChar* temp_symbols[32] = { &exclaimation_mark, &double_quote, &hashtag, &dollar_sign, &percent_sign, &ampersand, &single_quote, &open_parenthesis, &close_parenthesis, &asterisk, &plus_sign, &comma, &minus_sign, &period, &slash, &colon, &semicolon, &less_than_sign, &equals_sign, &greater_than_sign, &question_mark, &at_sign, &open_bracket, &backslash, &close_bracket, &caret, &underscore, &backtick, &open_brace, &vertical_slash, &close_brace, &tilde };
	copy(begin(temp_symbols), end(temp_symbols), symbols);

	BasicFontChar* temp_misc[3] = { &NULL_char, &new_line, &space };
	copy(begin(temp_misc), end(temp_misc), misc);
}

void BasicFont::LoadCharTextures()
{
	A.SetTexture(LoadCharTexture("A"));
	B.SetTexture(LoadCharTexture("B"));
	C.SetTexture(LoadCharTexture("C"));
	D.SetTexture(LoadCharTexture("D"));
	E.SetTexture(LoadCharTexture("E"));
	F.SetTexture(LoadCharTexture("F"));
	G.SetTexture(LoadCharTexture("G"));
	H.SetTexture(LoadCharTexture("H"));
	I.SetTexture(LoadCharTexture("I"));
	J.SetTexture(LoadCharTexture("J"));
	K.SetTexture(LoadCharTexture("K"));
	L.SetTexture(LoadCharTexture("L"));
	M.SetTexture(LoadCharTexture("M"));
	N.SetTexture(LoadCharTexture("N"));
	O.SetTexture(LoadCharTexture("O"));
	P.SetTexture(LoadCharTexture("P"));
	Q.SetTexture(LoadCharTexture("Q"));
	R.SetTexture(LoadCharTexture("R"));
	S.SetTexture(LoadCharTexture("S"));
	T.SetTexture(LoadCharTexture("T"));
	U.SetTexture(LoadCharTexture("U"));
	V.SetTexture(LoadCharTexture("V"));
	W.SetTexture(LoadCharTexture("W"));
	X.SetTexture(LoadCharTexture("X"));
	Y.SetTexture(LoadCharTexture("Y"));
	Z.SetTexture(LoadCharTexture("Z"));

	a.SetTexture(LoadCharTexture("a"));
	b.SetTexture(LoadCharTexture("b"));
	c.SetTexture(LoadCharTexture("c"));
	d.SetTexture(LoadCharTexture("d"));
	e.SetTexture(LoadCharTexture("e"));
	f.SetTexture(LoadCharTexture("f"));
	g.SetTexture(LoadCharTexture("g"));
	h.SetTexture(LoadCharTexture("h"));
	i.SetTexture(LoadCharTexture("i"));
	j.SetTexture(LoadCharTexture("j"));
	k.SetTexture(LoadCharTexture("k"));
	l.SetTexture(LoadCharTexture("l"));
	m.SetTexture(LoadCharTexture("m"));
	n.SetTexture(LoadCharTexture("n"));
	o.SetTexture(LoadCharTexture("o"));
	p.SetTexture(LoadCharTexture("p"));
	q.SetTexture(LoadCharTexture("q"));
	r.SetTexture(LoadCharTexture("r"));
	s.SetTexture(LoadCharTexture("s"));
	t.SetTexture(LoadCharTexture("t"));
	u.SetTexture(LoadCharTexture("u"));
	v.SetTexture(LoadCharTexture("v"));
	w.SetTexture(LoadCharTexture("w"));
	x.SetTexture(LoadCharTexture("x"));
	y.SetTexture(LoadCharTexture("y"));
	z.SetTexture(LoadCharTexture("z"));

	num_0.SetTexture(LoadCharTexture("num_0"));
	num_1.SetTexture(LoadCharTexture("num_1"));
	num_2.SetTexture(LoadCharTexture("num_2"));
	num_3.SetTexture(LoadCharTexture("num_3"));
	num_4.SetTexture(LoadCharTexture("num_4"));
	num_5.SetTexture(LoadCharTexture("num_5"));
	num_6.SetTexture(LoadCharTexture("num_6"));
	num_7.SetTexture(LoadCharTexture("num_7"));
	num_8.SetTexture(LoadCharTexture("num_8"));
	num_9.SetTexture(LoadCharTexture("num_9"));

	exclaimation_mark.SetTexture(LoadCharTexture("exclaimation_mark"));
	double_quote.SetTexture(LoadCharTexture("double_quote"));
	hashtag.SetTexture(LoadCharTexture("hashtag"));
	dollar_sign.SetTexture(LoadCharTexture("dollar_sign"));
	percent_sign.SetTexture(LoadCharTexture("percent_sign"));
	ampersand.SetTexture(LoadCharTexture("ampersand"));
	single_quote.SetTexture(LoadCharTexture("single_quote"));
	open_parenthesis.SetTexture(LoadCharTexture("open_parenthesis"));
	close_parenthesis.SetTexture(LoadCharTexture("close_parenthesis"));
	asterisk.SetTexture(LoadCharTexture("asterisk"));
	plus_sign.SetTexture(LoadCharTexture("plus_sign"));
	comma.SetTexture(LoadCharTexture("comma"));
	minus_sign.SetTexture(LoadCharTexture("minus_sign"));
	period.SetTexture(LoadCharTexture("period"));
	slash.SetTexture(LoadCharTexture("slash"));
	colon.SetTexture(LoadCharTexture("colon"));
	semicolon.SetTexture(LoadCharTexture("semicolon"));
	less_than_sign.SetTexture(LoadCharTexture("less_than_sign"));
	equals_sign.SetTexture(LoadCharTexture("equals_sign"));
	greater_than_sign.SetTexture(LoadCharTexture("greater_than_sign"));
	question_mark.SetTexture(LoadCharTexture("question_mark"));
	at_sign.SetTexture(LoadCharTexture("at_sign"));
	open_bracket.SetTexture(LoadCharTexture("open_bracket"));
	backslash.SetTexture(LoadCharTexture("backslash"));
	close_bracket.SetTexture(LoadCharTexture("close_bracket"));
	caret.SetTexture(LoadCharTexture("caret"));
	underscore.SetTexture(LoadCharTexture("underscore"));
	backtick.SetTexture(LoadCharTexture("backtick"));
	open_brace.SetTexture(LoadCharTexture("open_brace"));
	vertical_slash.SetTexture(LoadCharTexture("vertical_slash"));
	close_brace.SetTexture(LoadCharTexture("close_brace"));
	tilde.SetTexture(LoadCharTexture("tilde"));
	space.SetTexture(LoadCharTexture("space"));
	new_line.SetTexture(LoadCharTexture("new_line"));
	NULL_char.SetTexture(LoadCharTexture("NULL_char"));
}

const BasicFontChar* BasicFont::GetFontCharConst(const char char_value) const
{
	switch (char_value)
	{
	case 0: return &NULL_char;
	case 10: return &new_line;
	case 32: return &space;
	case 33: return &exclaimation_mark;
	case 34: return &double_quote;
	case 35: return &hashtag;
	case 36: return &dollar_sign;
	case 37: return &percent_sign;
	case 38: return &ampersand;
	case 39: return &single_quote;
	case 40: return &open_parenthesis;
	case 41: return &close_parenthesis;
	case 42: return &asterisk;
	case 43: return &plus_sign;
	case 44: return &comma;
	case 45: return &minus_sign;
	case 46: return &period;
	case 47: return &slash;
	case 48: return &num_0;
	case 49: return &num_1;
	case 50: return &num_2;
	case 51: return &num_3;
	case 52: return &num_4;
	case 53: return &num_5;
	case 54: return &num_6;
	case 55: return &num_7;
	case 56: return &num_8;
	case 57: return &num_9;
	case 58: return &colon;
	case 59: return &semicolon;
	case 60: return &less_than_sign;
	case 61: return &equals_sign;
	case 62: return &greater_than_sign;
	case 63: return &question_mark;
	case 64: return &at_sign;
	case 65: return &A;
	case 66: return &B;
	case 67: return &C;
	case 68: return &D;
	case 69: return &E;
	case 70: return &F;
	case 71: return &G;
	case 72: return &H;
	case 73: return &I;
	case 74: return &J;
	case 75: return &K;
	case 76: return &L;
	case 77: return &M;
	case 78: return &N;
	case 79: return &O;
	case 80: return &P;
	case 81: return &Q;
	case 82: return &R;
	case 83: return &S;
	case 84: return &T;
	case 85: return &U;
	case 86: return &V;
	case 87: return &W;
	case 88: return &X;
	case 89: return &Y;
	case 90: return &Z;
	case 91: return &open_bracket;
	case 92: return &backslash;
	case 93: return &close_bracket;
	case 94: return &caret;
	case 95: return &underscore;
	case 96: return&backtick;
	case 97: return &a;
	case 98: return &b;
	case 99: return &c;
	case 100: return &d;
	case 101: return &e;
	case 102: return &f;
	case 103: return &g;
	case 104: return &h;
	case 105: return &i;
	case 106: return &j;
	case 107: return &k;
	case 108: return &l;
	case 109: return &m;
	case 110: return &n;
	case 111: return &o;
	case 112: return &p;
	case 113: return &q;
	case 114: return &r;
	case 115: return &s;
	case 116: return &t;
	case 117: return &u;
	case 118: return &v;
	case 119: return &w;
	case 120: return &x;
	case 121: return &y;
	case 122: return &z;
	case 123: return &open_brace;
	case 124: return &vertical_slash;
	case 125: return &close_brace;
	case 126: return &tilde;
	default: return nullptr;
	}
}
BasicFontChar* BasicFont::GetFontChar(const char char_value)
{
	switch (char_value)
	{
	case 0: return &NULL_char;
	case 10: return &new_line;
	case 32: return &space;
	case 33: return &exclaimation_mark;
	case 34: return &double_quote;
	case 35: return &hashtag;
	case 36: return &dollar_sign;
	case 37: return &percent_sign;
	case 38: return &ampersand;
	case 39: return &single_quote;
	case 40: return &open_parenthesis;
	case 41: return &close_parenthesis;
	case 42: return &asterisk;
	case 43: return &plus_sign;
	case 44: return &comma;
	case 45: return &minus_sign;
	case 46: return &period;
	case 47: return &slash;
	case 48: return &num_0;
	case 49: return &num_1;
	case 50: return &num_2;
	case 51: return &num_3;
	case 52: return &num_4;
	case 53: return &num_5;
	case 54: return &num_6;
	case 55: return &num_7;
	case 56: return &num_8;
	case 57: return &num_9;
	case 58: return &colon;
	case 59: return &semicolon;
	case 60: return &less_than_sign;
	case 61: return &equals_sign;
	case 62: return &greater_than_sign;
	case 63: return &question_mark;
	case 64: return &at_sign;
	case 65: return &A;
	case 66: return &B;
	case 67: return &C;
	case 68: return &D;
	case 69: return &E;
	case 70: return &F;
	case 71: return &G;
	case 72: return &H;
	case 73: return &I;
	case 74: return &J;
	case 75: return &K;
	case 76: return &L;
	case 77: return &M;
	case 78: return &N;
	case 79: return &O;
	case 80: return &P;
	case 81: return &Q;
	case 82: return &R;
	case 83: return &S;
	case 84: return &T;
	case 85: return &U;
	case 86: return &V;
	case 87: return &W;
	case 88: return &X;
	case 89: return &Y;
	case 90: return &Z;
	case 91: return &open_bracket;
	case 92: return &backslash;
	case 93: return &close_bracket;
	case 94: return &caret;
	case 95: return &underscore;
	case 96: return&backtick;
	case 97: return &a;
	case 98: return &b;
	case 99: return &c;
	case 100: return &d;
	case 101: return &e;
	case 102: return &f;
	case 103: return &g;
	case 104: return &h;
	case 105: return &i;
	case 106: return &j;
	case 107: return &k;
	case 108: return &l;
	case 109: return &m;
	case 110: return &n;
	case 111: return &o;
	case 112: return &p;
	case 113: return &q;
	case 114: return &r;
	case 115: return &s;
	case 116: return &t;
	case 117: return &u;
	case 118: return &v;
	case 119: return &w;
	case 120: return &x;
	case 121: return &y;
	case 122: return &z;
	case 123: return &open_brace;
	case 124: return &vertical_slash;
	case 125: return &close_brace;
	case 126: return &tilde;
	default: return nullptr;
	}
}



const Texture* BasicFont::LoadCharTexture(const char* const path) const
{
	std::string full_path = "images/fonts/";
	full_path += font_name;
	full_path += "/";
	full_path += path;
	full_path += ".";
	full_path += chars_file_type;

	Texture* const return_val = new Texture(full_path.c_str());

	return return_val;
}