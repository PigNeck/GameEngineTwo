#include "ToolTip.h"

ToolTip::ToolTip()
{
	text_box.parent_rect.base_size = { 1.0, 1.0 };
	text_box.parent_rect.size = { 4.0, 4.0 };
	text_box.horizontal_text_centering = { 1 };
	text_box.vertical_text_centering = { 1 };
}
void ToolTip::InitLeast(Font* param_default_font)
{
	text_box.InitLeast(param_default_font);
}

void ToolTip::UpdateSavedBox()
{
	saved_box.base_size.width = text_box.GetActualBaseWidth() + (2.0 * margin_scaled_size.width / 4.0);
	saved_box.base_size.height = text_box.GetActualBaseHeight() + (2.0 * margin_scaled_size.height / 4.0);
	saved_box.SetSizeWithSizeScale({ 4.0, 4.0 });
}

void ToolTip::SetText(const char* const param_chars)
{
	text_box.Clear();
	text_box.AddCharPtr(param_chars);
	text_box.UpdateCharPos();

	UpdateSavedBox();
}
void ToolTip::SetText(const string param_string)
{
	text_box.Clear();
	text_box.AddString(param_string);
	text_box.UpdateCharPos();

	UpdateSavedBox();
}
void ToolTip::SetText(const char param_char)
{
	text_box.Clear();
	text_box.AddChar(param_char);
	text_box.UpdateCharPos();

	UpdateSavedBox();
}