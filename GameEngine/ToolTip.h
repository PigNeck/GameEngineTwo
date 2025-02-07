#pragma once
#include "TextBox.h"

struct ToolTip
{
	RectangleOld saved_box; //This variable contains the saved dimentions and positions of the "actual" text_box parent_rect + margin_size.
	TextBox text_box;

	Size2D border_scaled_size = { 4.0, 4.0 };
	Size2D margin_scaled_size = { 12.0, 12.0 }; //The margin size for EACH side of the saved_box.

	SDL_Color inner_color = { 220, 220, 220, 255 };
	SDL_Color border_color = { 0, 0, 0, 255 };

	ToolTip();
	void InitLeast(Font* param_default_font);

	//This function is meant to be PRIVATE (it should theoretically only be used by ToolTip methods)
	void UpdateSavedBox();

	//Set the text of the text_box and then UpdatesCharPos(...). Do this before calling Engine::UpdateToolTip(...)!
	void SetText(const char* const param_chars);
	//Set the text of the text_box and then UpdatesCharPos(...). Do this before calling Engine::UpdateToolTip(...)!
	void SetText(const string param_string);
	//Set the text of the text_box and then UpdatesCharPos(...). Do this before calling Engine::UpdateToolTip(...)!
	void SetText(const char param_char);
};

