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

	Texture* LoadCharTexture(SDL_Renderer* renderer, const char* path);
	FontChar* GetFontChar(char char_value);

	void Init(string param_name, SDL_Renderer* renderer, const double param_default_default_char_spacing, const double param_default_default_line_spacing, const double param_default_default_line_height);
};

