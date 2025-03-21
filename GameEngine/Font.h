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









struct LineParameters
{
	double pixel_height = 0.0;

	double pixel_spacing_top = 0.0;
	double pixel_spacing_bottom = 0.0;

	double pixel_max_width = -1.0; //If set to a negative value, [pixel_max_width] will be treated as the width of the text box rect.

	Point2DNew pixel_offset;

	bool scale_height_with_highest_char_scale = 0; //When set to true, the line scales its [pixel_height] the largest [scale.height_scale] of its chars when the line is generated.
	bool ignore_char_spacing_on_line_ends = 0; //When set to true, the first char of the line does not apply its [unscaled_pixel_left_spacing] and the last char of the line does not apply its [unscaled_pixel_right_spacing].
	bool bunch_words_together = 1; //When set to true, groups of characters seperated by spaces are not split when going to a new line.

	LineParameters(const double i_pixel_height = 0.0, const double i_pixel_spacing_top = 0.0, const double i_pixel_spacing_bottom = 0.0, const double i_pixel_max_width = -1.0, const Point2DNew i_pixel_offset = { 0.0, 0.0 }, const bool i_ignore_char_spacing_on_line_ends = 0, const bool i_bunch_words_together = 1);
};
struct IndexedLineParameters : LineParameters
{
	size_t index = numeric_limits<size_t>::max(); //If this is left as numeric_limits<size_t>::max() (which it is set to by default), then the index this object is at in [line_parameters] will be used instead.

	IndexedLineParameters(const double i_pixel_height = 0.0, const double i_pixel_spacing_top = 0.0, const double i_pixel_spacing_bottom = 0.0, const double i_pixel_max_width = -1.0, const Point2DNew i_pixel_offset = { 0.0, 0.0 }, const bool i_ignore_char_spacing_on_line_ends = 0, const bool i_bunch_words_together = 1);
	IndexedLineParameters(const size_t i_index, const double i_pixel_height = 0.0, const double i_pixel_spacing_top = 0.0, const double i_pixel_spacing_bottom = 0.0, const double i_pixel_max_width = -1.0, const Point2DNew i_pixel_offset = { 0.0, 0.0 }, const bool i_ignore_char_spacing_on_line_ends = 0, const bool i_bunch_words_together = 1);
};

struct BasicFont //Only supports ASCII english right now unfortunately :(
{
	// -------------  Char format  -------------

	const char* font_name = nullptr;
	const char* chars_file_type = nullptr; //SHOULDN'T include the dot!!

	//Uppercase letters:
	BasicFontChar A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;

	//Lowercase letters:
	BasicFontChar a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;

	//Numbers:
	BasicFontChar num_0, num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9;

	//Symbols (these are the most confusingly named ones. All the symbol char names only use lowercase letters and underscores (none of the actual symbols!)):
	BasicFontChar exclaimation_mark, double_quote, hashtag, dollar_sign, percent_sign, ampersand, single_quote, open_parenthesis, close_parenthesis, asterisk, plus_sign, comma, minus_sign, period, slash, colon, semicolon, less_than_sign, equals_sign, greater_than_sign, question_mark, at_sign, open_bracket, backslash, close_bracket, caret, underscore, backtick, open_brace, vertical_slash, close_brace, tilde;

	//Typically invisible chars:
	BasicFontChar space, new_line, NULL_char;

	BasicFontChar* all_chars[97]{}; //List of all BasicFontChars in ASCII order (with NULL_char at the end) (97 total)
	BasicFontChar* uppercase_letters[26]{}; //A-Z (26 total)
	BasicFontChar* lowercase_letters[26]{}; //a-z (26 total)
	BasicFontChar* numbers[10]{}; //0-9 (10 total)
	BasicFontChar* symbols[32]{}; //exclaimation_mark-tilde (32 total)
	BasicFontChar* misc[3]{};




	// -------------  Line format  -------------

	LineParameters template_line_parameters;



	BasicFont();
	//Loads all of the BasicFontChars with the corresponding pngs found in images/fonts/[i_font_name].[chars_file_type]. [chars_file_type] SHOULDN'T include the dot!!
	BasicFont(const char* const i_font_name, const char* const i_chars_file_type, const LineParameters i_template_line_parameters, const double default_template_unscaled_pixel_spacing_left = 0.0, const double default_template_unscaled_pixel_spacing_right = 0.0, const Point2DNew default_template_unscaled_pixel_offset = { 0.0, 0.0 });

	//Loads all of the BasicFontChars with the corresponding pngs found in images/fonts/[i_font_name].[chars_file_type]. [chars_file_type] SHOULDN'T include the dot!!
	void Init(const char* const i_font_name, const char* const i_chars_file_type, const LineParameters i_template_line_parameters, const double default_template_unscaled_pixel_spacing_left = 0.0, const double default_template_unscaled_pixel_spacing_right = 0.0, const Point2DNew default_template_unscaled_pixel_offset = { 0.0, 0.0 });

	//[font_name] and [chars_file_type] must be set properly for this function to work! They can be set by both the pareameterized constructor and Init(...).
	void LoadCharTextures();

	const BasicFontChar* GetFontCharConst(const char char_value) const;
	BasicFontChar* GetFontChar(const char char_value);

private:
	const Texture* LoadCharTexture(const char* const path) const;
};