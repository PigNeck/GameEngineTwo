#pragma once
#include "FontChar.h"

class Font
{
public:
	string font_name;

	FontChar* A = nullptr, *B = nullptr, *C = nullptr, *D = nullptr, *E = nullptr, *F = nullptr, *G = nullptr, *H = nullptr, *I = nullptr, *J = nullptr, *K = nullptr, *L = nullptr, *M = nullptr, *N = nullptr, *O = nullptr, *P = nullptr, *Q = nullptr, *R = nullptr, *S = nullptr, *T = nullptr, *U = nullptr, *V = nullptr, *W = nullptr, *X = nullptr, *Y = nullptr, *Z = nullptr;
	FontChar* a = nullptr, *b = nullptr, *c = nullptr, *d = nullptr, *e = nullptr, *f = nullptr, *g = nullptr, *h = nullptr, *i = nullptr, *j = nullptr, *k = nullptr, *l = nullptr, *m = nullptr, *n = nullptr, *o = nullptr, *p = nullptr, *q = nullptr, *r = nullptr, *s = nullptr, *t = nullptr, *u = nullptr, *v = nullptr, *w = nullptr, *x = nullptr, *y = nullptr, *z = nullptr;
	FontChar* num_0 = nullptr, *num_1 = nullptr, *num_2 = nullptr, *num_3 = nullptr, *num_4 = nullptr, *num_5 = nullptr, *num_6 = nullptr, *num_7 = nullptr, *num_8 = nullptr, *num_9 = nullptr;
	FontChar* acute = nullptr, *tilde = nullptr, *exclaimation_point = nullptr, *at_sign = nullptr, *hashtag = nullptr, *dollar_sign = nullptr, *percent_sign = nullptr, *caret = nullptr, *ampersand = nullptr, *asterisk = nullptr, *open_parenthesis = nullptr, *close_parenthesis = nullptr, *minus_sign = nullptr, *underscore = nullptr, *equals_sign = nullptr, *plus_sign = nullptr, *open_bracket = nullptr, *close_bracket = nullptr, *open_curly_bracket = nullptr, *close_curly_bracket = nullptr, *backslash = nullptr, *vertical_slash = nullptr, *semicolon = nullptr, *colon = nullptr, *single_quote = nullptr, *double_quote = nullptr, *comma = nullptr, *less_than_sign = nullptr, *period = nullptr, *greater_than_sign = nullptr, *slash = nullptr, *question_mark = nullptr, *space = nullptr, *new_line = nullptr;

	FontChar* all_chars[96];

	Texture* NULL_texture = nullptr;

	double default_default_line_spacing = 0.0;
	double default_default_line_height = 0.0;

	Font();

	Texture* LoadCharTexture(const char* path);
	FontChar* GetFontChar(char char_value);

	void Init(string param_name, SDL_Renderer* renderer, const double param_default_default_char_spacing, const double param_default_default_line_spacing, const double param_default_default_line_height);
};





struct BasicFont //Only supports ASCII english right now unfortunately :(
{
	const char* font_name;

	//Uppercase letters:
	BasicFontChar A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;

	//Lowercase letters:
	BasicFontChar a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;

	//Numbers:
	BasicFontChar num_0, num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9;

	//Symbols (these are the most confusingly named ones. All the symbol char names only use lowercase letters and underscores (none of the actual symbols!)):
	BasicFontChar exclaimation_mark, double_quote, hashtag, dollar_sign, percent_sign, ampersand, single_quote, open_parenthesis, clode_parenthesis, asterisk, plus_sign, comma, minus_sign, period, slash, colon, semicolon, less_than_sign, equals_sign, greater_than_sign, question_mark, at_sign, open_bracket, backslash, close_bracket, caret, underscore, acute, open_curly_bracket, vertical_slash, close_curly_bracket, tilde;

	//Typically invisible chars:
	BasicFontChar space, new_line, NULL_char;

	BasicFontChar* all_chars[97]; //List of all BasicFontChars in ASCII order (with NULL_char at the end) (97 total)
	BasicFontChar* uppercase_letters[26]; //A-Z (26 total)
	BasicFontChar* lowercase_letters[26]; //a-z (26 total)
	BasicFontChar* numbers[10]; //0-9 (10 total)
	BasicFontChar* symbols[32]; //exclaimation_mark-tilde (32 total)

	double default_default_line_height = 0.0;
	double default_default_line_spacing = 0.0;

	BasicFont();
	//Loads all of the BasicFontChars with the corresponding pngs found in images/fonts/[i_font_name].
	BasicFont(const char* const i_font_name, const double i_default_default_line_height, const double i_default_default_line_spacing);

	//Add init funcs

	const Texture* LoadCharTexture(const char* path);
	FontChar* GetFontChar(char char_value);

	void Init(string param_name, SDL_Renderer* renderer, const double param_default_default_char_spacing, const double param_default_default_line_spacing, const double param_default_default_line_height);
};