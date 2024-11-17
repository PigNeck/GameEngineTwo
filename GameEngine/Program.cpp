#include "Program.h"

#define PI 3.14159265

#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080

#define NEW_LINE_WAIT_MULTIPLIER 0.15

#define NUMBER_OF_CHANNELS 16

void TextLink::InitLeast(const size_t param_linked_portion_index, const size_t param_begin_char, const size_t param_end_char)
{
	linked_portion_index = param_linked_portion_index;
	begin_char = param_begin_char;
	end_char = param_end_char;
}



void Bar::SetTargetWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar)
{
	SetTargetWidth(100.0 * (double)discrete_progress / (double)discrete_capacity, light_bar);
}
void Bar::SetTargetWidth(const double percent, const bool light_bar)
{
	target_width = progress_back_rect_pointer->size.width * (percent / 100.0);

	if (light_bar)
	{
		lighting_level = 101.0;
	}
}


void ProgressBar::SetTargetWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar)
{
	if (bars.size() > size_t(0))
	{
		bars[0].SetTargetWidth(discrete_progress, discrete_capacity, light_bar);
	}
	else
	{
		cout << "Failed because bars.size() == 0. Try calling BasicInit(...) to fix this issue. Sent by ProgressBar::SetTargetWidth(...)." << endl;
	}
}
void ProgressBar::SetTargetWidth(const double percent, const bool light_bar)
{
	if (bars.size() > size_t(0))
	{
		bars[0].SetTargetWidth(percent, light_bar);
	}
	else
	{
		cout << "Failed because bars.size() == 0. Try calling BasicInit(...) to fix this issue. Sent by ProgressBar::SetTargetWidth(...)." << endl;
	}
}

void ProgressBar::SetTargetWidthWithIndex(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar, const size_t bar_index)
{
	if (bar_index < bars.size())
	{
		bars[bar_index].SetTargetWidth(discrete_progress, discrete_capacity, light_bar);
	}
	else
	{
		cout << "bar_index out of range :(. Sent by ProgressBar::SetTargetWidthWithIndex(...)." << endl;
	}
}
void ProgressBar::SetTargetWidthWithIndex(const double percent, const bool light_bar, const size_t bar_index)
{
	if (bar_index < bars.size())
	{
		bars[bar_index].SetTargetWidth(percent, light_bar);
	}
	else
	{
		cout << "bar_index out of range :(. Sent by ProgressBar::SetTargetWidthWithIndex(...)." << endl;
	}
}

void ProgressBar::InitLeast()
{
	//Do nothing lamo (you)
}
void ProgressBar::InitMost(const vector<Bar> param_bars, const Rectangle param_back_rect, const SDL_Color param_back_color, const Rectangle param_progress_back_rect, const SDL_Color param_progress_back_color)
{
	bars = param_bars;
	back_rect = param_back_rect;
	back_color = param_back_color;
	progress_back_rect = param_progress_back_rect;
	progress_back_color = param_progress_back_color;
}
void ProgressBar::InitBasic(const Point2D position, const Size2D back_rect_size, const double outline_thickness, const size_t discrete_progress, const size_t discrete_capacity)
{
	back_rect.pos = position;
	back_rect.size = back_rect_size;
	back_rect.base_size = back_rect_size;

	progress_back_rect.size = { back_rect_size.width - (outline_thickness * 2.0), back_rect_size.height - (outline_thickness * 2.0) };

	AddBar(discrete_progress, discrete_capacity);
}
void ProgressBar::InitBasic(const Point2D position, const Size2D back_rect_size, const double outline_thickness, const double percent)
{
	back_rect.pos = position;
	back_rect.size = back_rect_size;
	back_rect.base_size = back_rect_size;

	progress_back_rect.size = { back_rect_size.width - (outline_thickness * 2.0), back_rect_size.height - (outline_thickness * 2.0) };

	AddBar(percent);
}

void ProgressBar::SetDefaultBarColor(const size_t index)
{
	switch (bars.size())
	{
	case 1:
		bars[index].progress_color = { 0, 200, 0, 255 };
		bars[index].secondary_progress_color = { 50, 255, 50, 255 };
		break;
	case 2:
		bars[index].progress_color = { 0, 0, 200, 255 };
		bars[index].secondary_progress_color = { 50, 50, 255, 255 };
		break;
	case 3:
		bars[index].progress_color = { 200, 0, 0, 255 };
		bars[index].secondary_progress_color = { 255, 50, 50, 255 };
		break;
	default:
		bars[index].progress_color = { 100, 100, 100, 255 };
		bars[index].secondary_progress_color = { 200, 200, 200, 255 };
	}
}

void ProgressBar::AddBar(const size_t discrete_progress, const size_t discrete_capacity)
{
	bars.push_back(Bar());
	bars.back().progress_rect.size.height = progress_back_rect.size.height;
	bars.back().progress_rect.reference_rectangle = &back_rect;
	bars.back().progress_back_rect_pointer = &progress_back_rect;

	bars.back().SetTargetWidth(discrete_progress, discrete_capacity, 0);
	bars.back().progress_rect.size.width = bars.back().target_width;
	SetDefaultBarColor(bars.size() - size_t(1));
}
void ProgressBar::AddBar(const double percent)
{
	bars.push_back(Bar());
	bars.back().progress_rect.size.height = progress_back_rect.size.height;
	bars.back().progress_rect.reference_rectangle = &back_rect;
	bars.back().progress_back_rect_pointer = &progress_back_rect;

	bars.back().SetTargetWidth(percent, 0);
	bars.back().progress_rect.size.width = bars.back().target_width;
	SetDefaultBarColor(bars.size() - size_t(1));
}

ProgressBar::ProgressBar()
{
	back_rect.base_size = { 100.0, 50.0 };
	back_rect.size = { 100.0, 50.0 };

	progress_back_rect.size = { 92.0, 42.0 };
	progress_back_rect.reference_rectangle = &back_rect;
}



void TextPortion::InitLeast(const char* const param_text, const char default_sound_id)
{
	text.clear();
	for (const char* ptr = param_text; *ptr != '\0'; ++ptr) {
		double wait_multiplier = 1.0;
		char sound_id = default_sound_id;
		switch (*ptr)
		{
		case '\n':
			wait_multiplier = NEW_LINE_WAIT_MULTIPLIER;
			sound_id = 0;
			break;
		case ' ':
			wait_multiplier = 1.0;
			sound_id = 0;
			break;
		case '.':
			wait_multiplier = 0.1;
			break;
		case ',':
			wait_multiplier = 0.3;
			break;
		}
		text.push_back({ *ptr, sound_id, wait_multiplier });
	}
}
void TextPortion::InitBack(const char* const param_text, const char default_sound_id, const size_t param_back_path_index, const bool param_back_lesson_select)
{
	InitLeast(param_text, default_sound_id);

	back_path_index = param_back_path_index;
	back_lesson_select = param_back_lesson_select;
}
void TextPortion::InitNext(const char* const param_text, const char default_sound_id, const size_t param_next_path_index, const bool param_next_lesson_select)
{
	InitLeast(param_text, default_sound_id);
	
	next_path_index = param_next_path_index;
	next_lesson_select = param_next_lesson_select;
}
void TextPortion::InitMost(const char* const param_text, const char default_sound_id, const size_t param_back_path_index, const bool param_back_lesson_select, const size_t param_next_path_index, const bool param_next_lesson_select)
{
	InitLeast(param_text, default_sound_id);

	back_path_index = param_back_path_index;
	back_lesson_select = param_back_lesson_select;

	next_path_index = param_next_path_index;
	next_lesson_select = param_next_lesson_select;
}

size_t TextPortion::CharPartOfLink(const size_t char_index)
{
	for (size_t i = 0; i < links.size(); i++)
	{
		if ((char_index >= links[i].begin_char) && (char_index <= links[i].end_char))
		{
			return i;
		}
	}

	return numeric_limits<size_t>::max();
}

TextPortion* CoursePath::GetCurrentPortion()
{
	return portions[current_portion_index];
}



void Program::SetCurrentTextPortionTextBoxProgression(const double target_visable_char_progression)
{
	current_visable_char_progression = target_visable_char_progression;

	//Send warning if current_visable_char_progression is set out of range.
	if (current_visable_char_progression > (double)current_text_portion_text_box.chars.size())
	{
		cout << "Set current_visable_char_progression ABOVE MAX (current_text_portion_text_box.chars.size()). Sent from SetCurrentTextPortionTextBoxProgression(...)" << endl;
	}

	if (current_visable_char_progression >= 0.0)
	{
		const size_t trunc_index = (size_t)current_visable_char_progression;

		for (size_t i = 0; (i <= trunc_index) && (i < current_text_portion_text_box.chars.size()); i++)
		{
			current_text_portion_text_box.chars[i]->a_mod = 255;

		}
	}
}

void Program::UpdateConfetti()
{
	for (size_t i = 0; i < confetti.size(); i++)
	{
		confetti[i].velocity.x *= pow(0.98, e->frame_factor_inverse);

		confetti[i].velocity.y -= 0.1 * e->frame_factor_inverse;
		confetti[i].velocity.y *= pow(0.98, e->frame_factor_inverse);

		confetti[i].position.x += confetti[i].velocity.x;
		confetti[i].position.y += confetti[i].velocity.y;

		confetti[i].rotation += 1.0;
	}
}
void Program::DrawConfetti(Camera* const camera)
{
	Rectangle conf_rect;
	conf_rect.size.width = 20.0;
	conf_rect.size.height = 10.0;
	SDL_Color conf_color = { 0, 0, 0, 255 };
	const unsigned char conf_alpha = (unsigned char)round((1.0 - (complete_lesson_cutscene_timer / 2.3)) * 255.0) * (unsigned char)(complete_lesson_cutscene_timer <= 2.3);

	for (size_t i = 0; i < confetti.size(); i++)
	{
		conf_rect.pos = confetti[i].position;
		conf_rect.rotation = confetti[i].rotation;

		switch (confetti[i].color_id)
		{
		case 0:
			conf_color = { 255, 0, 0, conf_alpha };
			break;
		case 1:
			conf_color = { 0, 255, 0, conf_alpha };
			break;
		case 2:
			conf_color = { 0, 0, 255, conf_alpha };
			break;
		case 3:
			conf_color = { 255, 255, 0, conf_alpha };
			break;
		case 4:
			conf_color = { 255, 0, 255, conf_alpha };
			break;
		case 5:
			conf_color = { 0, 255, 255, conf_alpha };
			break;
		}

		e->DrawRectangle(&conf_rect, conf_color, camera);
	}
}

void Program::UpdateProgressBar(ProgressBar* const progress_bar)
{
	for (size_t i = 0; i < progress_bar->bars.size(); i++)
	{
		Bar* const current_bar = &progress_bar->bars[i];


		const double diff = current_bar->target_width - current_bar->progress_rect.size.width;
		if (diff != 0.0)
		{
			//Set bar width
			current_bar->progress_rect.size.width += diff * (1.0 - pow((100.0 - current_bar->bar_advance_rate) / 100.0, e->frame_factor_inverse));
			//Set bar x
			current_bar->progress_rect.pos.x = (progress_bar->progress_back_rect.size.width / -2.0) + (current_bar->progress_rect.size.width / 2.0);

			//If diff is negligable, finish the job >:)
			if ((abs(current_bar->target_width - current_bar->progress_rect.size.width) / progress_bar->progress_back_rect.size.width) < 0.0001)
			{
				//Set bar width
				current_bar->progress_rect.size.width = current_bar->target_width;
				//Set bar x
				current_bar->progress_rect.pos.x = (progress_bar->progress_back_rect.size.width / -2.0) + (current_bar->progress_rect.size.width / 2.0);
			}
		}

		if (current_bar->lighting_level != 0.0)
		{
			if (current_bar->lighting_level > 100.0)
			{
				current_bar->lighting_level = 100.0;
			}
			else
			{
				current_bar->lighting_level *= pow((100.0 - current_bar->lighting_advance_rate) / 100.0, e->frame_factor_inverse);

				if (current_bar->lighting_level < 0.01)
				{
					current_bar->lighting_level = 0.0;
				}
			}
		}
	}
}
void Program::DrawProgressBar(ProgressBar* const progress_bar, Camera* const camera)
{
	e->DrawRectangle(&progress_bar->back_rect, progress_bar->back_color, camera);
	e->DrawRectangle(&progress_bar->progress_back_rect, progress_bar->progress_back_color, camera);

	SDL_Color calculated_color;
	for (size_t i = 0; i < progress_bar->bars.size(); i++)
	{
		Bar* const current_bar = &progress_bar->bars[i];

		const double lighting_propotion = current_bar->lighting_level / 100.0;
		const double inverse_lighting_proportion = (100.0 - current_bar->lighting_level) / 100.0;

		calculated_color.r = (unsigned char)round(((double)current_bar->secondary_progress_color.r * lighting_propotion) + ((double)current_bar->progress_color.r * inverse_lighting_proportion));
		calculated_color.g = (unsigned char)round(((double)current_bar->secondary_progress_color.g * lighting_propotion) + ((double)current_bar->progress_color.g * inverse_lighting_proportion));
		calculated_color.b = (unsigned char)round(((double)current_bar->secondary_progress_color.b * lighting_propotion) + ((double)current_bar->progress_color.b * inverse_lighting_proportion));
		calculated_color.a = (unsigned char)round(((double)current_bar->secondary_progress_color.a * lighting_propotion) + ((double)current_bar->progress_color.a * inverse_lighting_proportion));

		e->DrawRectangle(&current_bar->progress_rect, calculated_color, camera);
	}
}

bool Program::CheckForLinkClicksAndGenerateSavedLinkRects(const double rate, const Size2D stretch_multiplier, const int text_sound_channel_num, const int link_click_channel_num)
{
	bool found_overlapping_link = 0;
	bool found_clicked_link = 0;

	saved_link_rects.clear();

	const vector<TextLink>* current_links = &course_paths[current_course_path_index]->GetCurrentPortion()->links;
	for (size_t i = 0; i < current_links->size(); i++)
	{
		if (current_visable_char_progression >= (double)current_links->at(i).begin_char)
		{
			const size_t temp_begin_index = current_links->at(i).begin_char;

			size_t temp_end_index;
			if (current_visable_char_progression >= (double)current_links->at(i).end_char)
			{
				temp_end_index = current_links->at(i).end_char;
			}
			else
			{
				temp_end_index = (size_t)current_visable_char_progression;
			}

			vector<RectStructOne>* const temp_hitboxes = current_text_portion_text_box.GetSegmentHitbox(temp_begin_index, temp_end_index);

			for (size_t j = 0; j < temp_hitboxes->size(); j++)
			{
				Size2D temp_text_box_uni_size_scale = current_text_portion_text_box.parent_rect.GetUniSizeScale();
				temp_hitboxes->at(j).uni_right_edge += temp_text_box_uni_size_scale.width;
				temp_hitboxes->at(j).uni_bottom_edge -= temp_text_box_uni_size_scale.height;
				temp_hitboxes->at(j).uni_left_edge -= temp_text_box_uni_size_scale.width;
				temp_hitboxes->at(j).uni_top_edge += temp_text_box_uni_size_scale.height;

				saved_link_rects.push_back({ temp_hitboxes->at(j), 0, 0 });

				if (!found_overlapping_link)
				{
					const Point2D mouse_pos = e->GetMousePos(e->blank_camera);
					if (OverlapPoint2DWithRectStructOne(&mouse_pos, &temp_hitboxes->at(j), 1))
					{
						saved_link_rects.back().hovering = 1;
						saved_link_rects.back().pressed = e->input.mouse_left.pressed;

						found_overlapping_link = 1;

						if (e->input.mouse_left.first_frame_pressed)
						{
							Mix_PlayChannel(link_click_channel_num, e->click_press_sound, 0);
						}
						if (e->input.mouse_left.first_frame_released)
						{
							Mix_PlayChannel(link_click_channel_num, e->click_release_sound, 0);

							SetCurrentTextPortionIndex(current_links->at(i).linked_portion_index);
							AdvanceCurrentTextPortionTextBox(rate, stretch_multiplier, text_sound_channel_num);
							found_clicked_link = 1;
						}
					}
				}
			}
		}
	}

	return found_clicked_link;
}
void Program::AdvanceCurrentTextPortionTextBox(const double rate, const Size2D stretch_multiplier, const int channel_num)
{
	double remaining_wait = rate * e->frame_factor_inverse;
	TextPortion* const current_text_portion = course_paths[current_course_path_index]->GetCurrentPortion();
	
	char sound_effect_id = 0;

	while ((remaining_wait > 0.0) && (current_visable_char_progression < (double)current_text_portion->text.size()))
	{
		size_t current_visable_char;
		double current_visable_char_wait_multiplier;
		if (current_visable_char_progression >= 0.0)
		{
			current_visable_char = (size_t)current_visable_char_progression;
			current_visable_char_wait_multiplier = current_text_portion->text[current_visable_char].wait_multiplier;
		}
		else
		{
			current_visable_char = numeric_limits<size_t>::max();
			current_visable_char_wait_multiplier = 1.0;
		}

		const double next_visable_char_progression = (double)(current_visable_char + size_t(1));
		const double next_visable_char_wait_diff = next_visable_char_progression - current_visable_char_progression;
		const double multiplied_remaining_wait = remaining_wait * current_visable_char_wait_multiplier;
		if ((current_visable_char_progression + multiplied_remaining_wait) >= next_visable_char_progression)
		{
			current_visable_char_progression = next_visable_char_progression;
			remaining_wait = (multiplied_remaining_wait - next_visable_char_wait_diff) / current_visable_char_wait_multiplier;

			const size_t trunc_current_visable_char_progression = (size_t)current_visable_char_progression;
			if (trunc_current_visable_char_progression < current_text_portion_text_box.chars.size())
			{
				current_text_portion_text_box.chars[trunc_current_visable_char_progression]->a_mod = 255;
				current_text_portion_text_box.chars[trunc_current_visable_char_progression]->rect.size.width = saved_char_sizes[trunc_current_visable_char_progression].width * stretch_multiplier.width;
				current_text_portion_text_box.chars[trunc_current_visable_char_progression]->rect.size.height = saved_char_sizes[trunc_current_visable_char_progression].height * stretch_multiplier.height;
			}
			if (trunc_current_visable_char_progression < current_text_portion->text.size())
			{
				if (current_text_portion->text[trunc_current_visable_char_progression].sound_id != 0)
				{
					sound_effect_id = current_text_portion->text[trunc_current_visable_char_progression].sound_id;
				}
			}
		}
		else
		{
			current_visable_char_progression += multiplied_remaining_wait;
			remaining_wait = 0.0;
		}
	}

	//Update the appropriate saved_visable_char_progression value
	if (course_paths[current_course_path_index]->current_portion_index >= course_paths[current_course_path_index]->progress)
	{
		course_paths[current_course_path_index]->saved_visable_char_progression = current_visable_char_progression;
	}


	if (sound_effect_id != 0)
	{
		switch (sound_effect_id)
		{
		case 1:
			Mix_PlayChannel(channel_num, text_sound_1, 0);
			break;
		case 2:
			Mix_PlayChannel(channel_num, text_sound_2, 0);
			break;
		case 3:
			Mix_PlayChannel(channel_num, text_sound_3, 0);
			break;
		case 4:
			Mix_PlayChannel(channel_num, text_sound_4, 0);
			break;
		}
	}
}
void Program::ReduceStretchInCurrentTextPortionTextBox(const double rate)
{
	//Loop through all visable chars and reduce height modifier
	bool done = 0;
	for (size_t i = 0; (i < current_text_portion_text_box.lines.size()) && (!done); i++)
	{
		for (size_t j = current_text_portion_text_box.lines[i]->first_index; j <= current_text_portion_text_box.lines[i]->last_index; j++)
		{
			if (j <= trunc(current_visable_char_progression))
			{
				const Size2D current_size = current_text_portion_text_box.chars[j]->rect.size;
				const Size2D current_saved_size = saved_char_sizes[j];
				if (current_size.height > (current_saved_size.height + 0.001))
				{
					current_text_portion_text_box.chars[j]->rect.size.width -= (current_size.width - current_saved_size.width) * rate;
					current_text_portion_text_box.chars[j]->rect.size.height -= (current_size.height - current_saved_size.height) * rate;
				}
				else
				{
					current_text_portion_text_box.chars[j]->rect.size = saved_char_sizes[j];
				}
			}
			else
			{
				done = 1;
				break;
			}
		}
	}
}

void Program::InitSounds()
{
	Mix_AllocateChannels(NUMBER_OF_CHANNELS);

	Mix_Volume(-1, 64);

	text_sound_1 = Mix_LoadWAV("sounds/text_sound_1.wav");
	Mix_VolumeChunk(text_sound_1, 64);
	text_sound_2 = Mix_LoadWAV("sounds/text_sound_2.wav");
	Mix_VolumeChunk(text_sound_2, 64);
	text_sound_3 = Mix_LoadWAV("sounds/text_sound_3.wav");
	Mix_VolumeChunk(text_sound_3, 64);

	confetti_sound = Mix_LoadWAV("sounds/confetti_sound.wav");
	Mix_VolumeChunk(confetti_sound, 128);
}
void Program::DestroySounds()
{
	Mix_FreeChunk(text_sound_1);
	text_sound_1 = nullptr;
	Mix_FreeChunk(text_sound_2);
	text_sound_2 = nullptr;
	Mix_FreeChunk(text_sound_3);
	text_sound_3 = nullptr;

	Mix_FreeChunk(confetti_sound);
	confetti_sound = nullptr;
}


void Program::UpdatePlayer(Player* param_player)
{
	param_player->previous_frame_running = param_player->running;
	param_player->running = 0;

	if (e->input.a.pressed)
	{
		param_player->hitbox.pos.x -= 2.0;
		param_player->running = 1;

		param_player->sprite.rect.flip.value = 1;
	}
	if (e->input.d.pressed)
	{
		param_player->hitbox.pos.x += 2.0;
		param_player->running = 1;

		param_player->sprite.rect.flip.value = 0;
	}
	if (e->input.s.pressed)
	{
		param_player->hitbox.pos.y -= 2.0;
		param_player->running = 1;
	}
	if (e->input.w.pressed)
	{
		param_player->hitbox.pos.y += 2.0;
		param_player->running = 1;
	}

	param_player->first_frame_running = 0;
	if (param_player->running && (!param_player->previous_frame_running)) { param_player->first_frame_running = 1; }

	param_player->first_frame_idle = 0;
	if (param_player->previous_frame_running && (!param_player->running)) { param_player->first_frame_idle = 1; }

	if (param_player->first_frame_running)
	{
		param_player->sprite.LoadAnimation(&run_anim);
	}

	if (param_player->first_frame_idle)
	{
		param_player->sprite.LoadAnimation(&idle_anim);
	}

	if (e->input.t.pressed && e->input.r.first_frame_pressed)
	{
		param_player->sprite.LoadAnimation(&pride_anim);
	}

	param_player->sprite.rect.pos = param_player->hitbox.pos;

	//SDL_Rect temp_sdl_rect = RectangleToSDLRect(&param_player->sprite.rect, main_camera);
}

void Program::UpdateMainCamera()
{
	Point2D player_pos = player.hitbox.GetUniPos();
	Point2D cam_pos = main_camera->rect.GetUniPos();
	main_camera->rect.pos.x += (player_pos.x - cam_pos.x) * 0.1 * e->frame_factor_inverse;
	main_camera->rect.pos.y += (player_pos.y - cam_pos.y) * 0.1 * e->frame_factor_inverse;
}

void Program::DrawGround(Ground* param_ground, Camera* camera)
{
	Rectangle tile_rectangle_data;
	tile_rectangle_data.base_size = { 64.0, 24.0 };
	tile_rectangle_data.SetSizeWithSizeScale({ 4.0, 4.0 });

	//Rectangle accessory_rect;
	//accessory_rect.base_size = tree.size;
	//accessory_rect.SetSizeScale({ 4.0, 4.0 });

	int tile_counter = 0;

	for (int y = 49; y >= 0; y--)
	{
		for (int x = 0; x < 50; x++)
		{
			if (param_ground->tile_data[x][y] != NULL)
			{
				const double tile_rise_time = (param_ground->rise_time / 1.6) - ((double)tile_counter * 0.01);

				if (tile_rise_time > 0.0)
				{
					tile_rectangle_data.pos.x = (x * 180.0) + (y * 72.0);

					if (tile_rise_time < 1.0)
					{
						tile_rectangle_data.pos.y = (y * 72.0) + (1000.0 * sin(tile_rise_time * PI / 2.0)) - 1000.0;
					}
					else
					{
						tile_rectangle_data.pos.y = (y * 72.0);
					}



					double TIME_FOR_SINGLE_CYCLE;
					double MIN_HIGHLIGHT_VALUE;
					double MAX_HIGHLIGHT_VALUE;

					double cycle_time;
					double sin_time;
					double double_alpha;


					switch (param_ground->tile_data[x][y])
					{
					case 1:
						e->DrawTexture(&light_ground, camera, &tile_rectangle_data);
						break;
					case 2:
						e->DrawTexture(&dark_ground, camera, &tile_rectangle_data);
						break;
					case 3:
						e->DrawTexture(&grassy_ground, camera, &tile_rectangle_data);
						break;
					case 4:
						e->DrawTexture(&cobble_ground, camera, &tile_rectangle_data);
						break;
					case 5:
						e->DrawTexture(&grassy_ground, camera, &tile_rectangle_data);

						TIME_FOR_SINGLE_CYCLE = 2.0;
						MIN_HIGHLIGHT_VALUE = 20.0;
						MAX_HIGHLIGHT_VALUE = 100.0;

						cycle_time = fmod(param_ground->rise_time, TIME_FOR_SINGLE_CYCLE) / TIME_FOR_SINGLE_CYCLE;

						sin_time = sin(cycle_time * 2.0 * PI);

						double_alpha = MIN_HIGHLIGHT_VALUE + (((sin_time + 1.0) / 2.0) * (MAX_HIGHLIGHT_VALUE - MIN_HIGHLIGHT_VALUE));

						SDL_SetTextureAlphaMod(ground_highlight.sdl_texture, (int)round(double_alpha));
						e->DrawTexture(&ground_highlight, camera, &tile_rectangle_data);
						SDL_SetTextureAlphaMod(ground_highlight.sdl_texture, 255);
						break;
					case 6:
						e->DrawTexture(water_ground.GetCurrentFrame()->texture, camera, &tile_rectangle_data);
						break;
					}
				}

				tile_counter++;
			}
		}
	}

	param_ground->rise_time += e->frame_factor_inverse / 60.0;

	water_ground.Update(e->frame_factor_inverse);
}

//Clicks should be done BEFORE this function is called
void Program::UpdateCellSet(CellSet* const param_cell_set)
{
	for (size_t i = 0; i < param_cell_set->set.size(); i++)
	{
		param_cell_set->set[i]->Update(e->frame_factor_inverse);
	}

	const Rectangle temp_full_hitbox = param_cell_set->GenerateFullHitbox();
	const Point2D temp_mouse_pos = e->GetMousePos(e->blank_camera);

	hovering_over_tset = 0;
	if (OverlapPoint2DWithRectangle(&temp_mouse_pos, &temp_full_hitbox, 1))
	{
		size_t selected_index = 0;
		Rectangle temp_cell_cropped_hitbox;
		for (size_t i = 0; i < param_cell_set->set.size(); i++)
		{
			temp_cell_cropped_hitbox = param_cell_set->GenerateHitboxCropped(i);
			if (OverlapPoint2DWithRectangle(&temp_mouse_pos, &temp_cell_cropped_hitbox, 1))
			{
				selected_index = i;
			}
		}
		param_cell_set->UpdateNumberDisplay(selected_index);
		hovering_over_tset = 1;
	}
}
void Program::DrawCellSet(CellSet* const param_cell_set, Camera* const camera)
{
	for (size_t i = 0; i < param_cell_set->set.size(); i++)
	{
		Rectangle outer_hitbox = param_cell_set->GenerateHitbox(i);
		Rectangle inner_hitbox = param_cell_set->GenerateInnerHitbox(i);

		SDL_Color cell_color = { 0, 0, 0, 255 };
		const double delta_y = param_cell_set->GetTrueScale().height * param_cell_set->set[i]->animation_movement_percent / 100.0;
		if (param_cell_set->set[i]->state == 1)
		{
			cell_color.r = 255;
			cell_color.g = 255;
			cell_color.b = (char)round(255.0 * param_cell_set->set[i]->animation_color_percent / 100.0);

			outer_hitbox.pos.y += delta_y;
			inner_hitbox.pos.y += delta_y;
		}
		else
		{
			const char rg = (char)50 + (char)round(78.0 * param_cell_set->set[i]->animation_color_percent / 100.0);
			cell_color.r = rg;
			cell_color.g = rg;
			cell_color.b = (char)50 - (char)round(50.0 * param_cell_set->set[i]->animation_color_percent / 100.0);

			//const char uni_val = (char)50 - (char)round(50.0 * param_transistor_set->set[i]->animation_color_percent / 100.0);
			//cell_color.r = uni_val;
			//cell_color.g = uni_val;
			//cell_color.b = uni_val;

			outer_hitbox.pos.y -= delta_y;
			inner_hitbox.pos.y -= delta_y;
		}

		e->DrawRectangle(&outer_hitbox, { 0, 0, 0, 255 }, camera);
		e->DrawRectangle(&inner_hitbox, cell_color, camera);
	}

	if (hovering_over_tset)
	{
		e->DrawTextBox(&param_cell_set->number_display, camera);
	}
}

void Program::SetCurrentPathAndPortionIndexes(const size_t param_path_index, size_t param_portion_index)
{
	bool changed_path_index = 0;

	if (param_path_index != numeric_limits<size_t>::max())
	{
		if ((param_path_index >= 0) && (param_path_index < course_paths.size()))
		{
			if (current_course_path_index != param_path_index)
			{
				current_course_path_index = param_path_index;
				changed_path_index = 1;

				course_path_text_box.Clear();
				course_path_text_box.AddCharPtr(course_paths[current_course_path_index]->full_path_text);
				course_path_text_box.UpdateCharPos();
			}
		}
		else
		{
			cout << "param_path_index out of range, so function quit. Sent from SetCurrentTextPortionIndex(...)" << endl;
			return;
		}
	}

	const size_t course_text_size = course_paths[current_course_path_index]->portions.size();
	if (course_text_size > 0)
	{
		bool changed_portion_index = 0;
		bool changed_progress = 0;
		bool finished_portion = 0;



		//Set current_portion_index, changed_portion_index, and (progress, changed_progress, and finished_portion if finished_portion) appropriately
		size_t* const current_portion_index = &course_paths[current_course_path_index]->current_portion_index;
		size_t* const progress = &course_paths[current_course_path_index]->progress;

		if (param_portion_index == course_text_size)
		{
			if (*progress != course_text_size)
			{
				*progress = course_text_size;
				changed_progress = 1;
			}

			param_portion_index = course_text_size - size_t(1);
			finished_portion = 1;
		}
		if (param_portion_index > course_text_size)
		{
			if (*progress != course_text_size)
			{
				*progress = course_text_size;
				changed_progress = 1;
			}

			param_portion_index = course_text_size - size_t(1);
			cout << "param_text_portion_index TOO HIGH. Set current_text_portion_index to last course_text index instead. Sent from SetCurrentTextPortionIndex(...)" << endl;
		}

		if (*current_portion_index != param_portion_index)
		{
			*current_portion_index = param_portion_index;
			changed_portion_index = 1;
		}
		changed_portion_index = changed_portion_index || changed_path_index;
		changed_progress = changed_progress || changed_path_index;





		//Add all the chars from current_portion to current_text_portion_text_box (blue if part of a link).
		if (changed_portion_index)
		{
			TextPortion* const current_portion = course_paths[current_course_path_index]->GetCurrentPortion();

			current_text_portion_text_box.Clear();
			for (size_t i = 0; i < current_portion->text.size(); i++)
			{
				if (current_portion->CharPartOfLink(i) == numeric_limits<size_t>::max())
				{
					current_text_portion_text_box.AddChar(current_portion->text[i].value);
				}
				else
				{
					current_text_portion_text_box.AddChar(current_portion->text[i].value, 0, 0, 200, 255);
				}
			}
			current_text_portion_text_box.UpdateCharPos();





			//Set current_visable_char_progression and progress
			const size_t current_portion_text_size = current_text_portion_text_box.chars.size();
			if (!finished_portion)
			{
				if (*current_portion_index > *progress)
				{
					*progress = *current_portion_index;
					changed_progress = 1;

					current_visable_char_progression = -1.0;
				}
				else
				{
					if (*current_portion_index == *progress)
					{
						current_visable_char_progression = course_paths[current_course_path_index]->saved_visable_char_progression - 30.0;
						if (current_visable_char_progression <= -1.0)
						{
							current_visable_char_progression = -1.0;
						}
						else
						{
							if ((current_visable_char_progression + 30.0) >= ((double)current_portion_text_size - 12.0))
							{
								current_visable_char_progression = (double)current_portion_text_size;
							}
						}
					}
					else
					{
						current_visable_char_progression = (double)current_portion_text_size;
					}
				}
			}





			//Set the initial visibility of chars and push_back to saved_char_sizes
			saved_char_sizes.clear();
			const bool trunc_visable_char_progression_valid = (current_visable_char_progression >= 0.0);
			size_t trunc_visable_char_progression = (size_t)current_visable_char_progression;
			for (size_t i = 0; i < current_text_portion_text_box.chars.size(); i++)
			{
				//Determine visibility of chars based on param_visable_char_progression
				if (trunc_visable_char_progression_valid)
				{
					if (i > trunc_visable_char_progression)
					{
						current_text_portion_text_box.chars[i]->a_mod = 0;
					}
					else
					{
						current_text_portion_text_box.chars[i]->a_mod = 255;
					}
				}
				else
				{
					current_text_portion_text_box.chars[i]->a_mod = 0;
				}

				saved_char_sizes.push_back(current_text_portion_text_box.chars[i]->rect.size);
			}
		}



		//Set front progress bar length
		if (finished_portion)
		{
			path_progress_bar.SetTargetWidthWithIndex(100.0, 1, 1);
		}
		else
		{
			if (changed_portion_index)
			{
				path_progress_bar.SetTargetWidthWithIndex(course_paths[current_course_path_index]->current_portion_index, course_paths[current_course_path_index]->portions.size(), 1, 1);
			}
		}





		if (changed_progress)
		{
			const size_t path_progress = course_paths[current_course_path_index]->progress;

			//Set back progress bar length
			path_progress_bar.SetTargetWidthWithIndex(path_progress, course_paths[current_course_path_index]->portions.size(), 1, 0);

			//Set progress_bar_text_box.chars
			progress_bar_text_box.Clear();
			progress_bar_text_box.AddCharPtr(to_string(path_progress).c_str());
			progress_bar_text_box.AddChar('/');
			progress_bar_text_box.AddCharPtr(to_string(course_text_size).c_str());
			progress_bar_text_box.AddCharPtr(" completed");
			progress_bar_text_box.UpdateCharPos();
		}
	}
	else
	{
		//Set progress bar length
		path_progress_bar.SetTargetWidthWithIndex(0.0, 1, 0);
		path_progress_bar.SetTargetWidthWithIndex(0.0, 1, 1);



		cout << "course_text_size == 0, so function quit. Sent from SetCurrentTextPortionIndex(...)" << endl;
	}
}
void Program::SetCurrentTextPortionIndex(size_t param_portion_index)
{
	SetCurrentPathAndPortionIndexes(numeric_limits<size_t>::max(), param_portion_index);
}

void Program::Run()
{
	NumSwitchScene();

	switch (e->scene)
	{
	case 1:
		RunScene1();
		break;
	case 2:
		RunScene2();
		break;
	case 3:
		RunScene3();
		break;
	case 4:
		RunScene4();
		break;
	case 5:
		RunScene5();
		break;
	case 6:
		RunScene6();
		break;
	case 7:
		RunScene7();
		break;
	case 8:
		RunScene8();
		break;
	case 9:
		RunScene9();
		break;
	}
}
void Program::Draw()
{
	switch (e->scene)
	{
	case 1:
		DrawScene1();
		break;
	case 2:
		DrawScene2();
		break;
	case 3:
		DrawScene3();
		break;
	case 4:
		DrawScene4();
		break;
	case 5:
		DrawScene5();
		break;
	case 6:
		DrawScene6();
		break;
	case 7:
		DrawScene7();
		break;
	case 8:
		DrawScene8();
		break;
	case 9:
		DrawScene9();
		break;
	}
}
void Program::PostDrawRun()
{
	switch (e->scene)
	{
	case 1:
		PostDrawRunScene1();
		break;
	case 2:
		PostDrawRunScene2();
		break;
	case 3:
		PostDrawRunScene3();
		break;
	case 4:
		PostDrawRunScene4();
		break;
	case 5:
		PostDrawRunScene5();
		break;
	case 6:
		PostDrawRunScene6();
		break;
	case 7:
		PostDrawRunScene7();
		break;
	case 8:
		PostDrawRunScene8();
		break;
	case 9:
		PostDrawRunScene9();
		break;
	}
}

void Program::SetScene1()
{
	main_camera->rect.pos = { 0.0, 0.0 };
}
void Program::EndScene1()
{

}
void Program::RunScene1()
{
	e->UpdateSimpleTextButton(&run_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&code_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&images_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&sounds_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&other_files_button, main_camera, &main_layer, 1, {});

	if (run_button.press_data.first_frame_released)
	{
		SetScene(2, 0);
		return;
	}

	if (code_button.press_data.first_frame_released || images_button.press_data.first_frame_released || sounds_button.press_data.first_frame_released || other_files_button.press_data.first_frame_released)
	{
		SetScene(3, 0);
		return;
	}

	if (e->input.g.pressed)
	{
		Size2D temp_current_size = test_box.parent_rect.size;

		test_box.parent_rect.size = { temp_current_size.width + 1.0, temp_current_size.height + 0.5 };
	}
}
void Program::DrawScene1()
{
	e->DrawSimpleTextButton(&run_button, main_camera);
	e->DrawSimpleTextButton(&code_button, main_camera);
	e->DrawSimpleTextButton(&images_button, main_camera);
	e->DrawSimpleTextButton(&sounds_button, main_camera);
	e->DrawSimpleTextButton(&other_files_button, main_camera);


	e->DrawRectangle(&test_rect, { 255, 0, 0, 255 }, main_camera);

	//e->DrawTextBox(&test_box, main_camera);
}
void Program::PostDrawRunScene1()
{

}

void Program::SetScene2()
{
	ground.rise_time = 0.0;
}
void Program::EndScene2()
{

}
void Program::RunScene2()
{
	UpdatePlayer(&player);

	UpdateMainCamera();
}
void Program::DrawScene2()
{
	DrawGround(&ground, main_camera);

	e->DrawSprite(&player.sprite, main_camera);
}
void Program::PostDrawRunScene2()
{
	player.sprite.animation->Update(e->frame_factor_inverse);
}

void Program::SetScene3()
{
	main_camera->rect.pos = { 0.0, 0.0 };
}
void Program::EndScene3()
{

}
void Program::RunScene3()
{
	e->UpdateSimpleTextButton(&back_button, main_camera, &main_layer, 1, {});

	if (back_button.press_data.first_frame_released)
	{
		SetScene(1, 0);
		return;
	}
}
void Program::DrawScene3()
{
	e->DrawSimpleTextButton(&back_button, main_camera);

	e->DrawRectangleScaledBorderScaledShadow(&test_rect, { 255, 0, 0, 100 }, 4.0, { 2 }, { 0, 0, 0, 100 }, { -4.0, -4.0 }, { 0, 0, 0, 70 }, main_camera);
}
void Program::PostDrawRunScene3()
{

}

void Program::SetScene4()
{
	SetCurrentPathAndPortionIndexes(0, 0);
	complete_lesson_cutscene_timer = -1.0;
}
void Program::EndScene4()
{
	confetti.clear();
}
void Program::RunScene4()
{
	//Update the accessibility of the previous, next, return, and finish portion buttons
	const bool at_last_portion = (course_paths[current_course_path_index]->current_portion_index + size_t(1)) >= course_paths[current_course_path_index]->portions.size();
	const bool all_portion_chars_visable = current_visable_char_progression >= (double)(current_text_portion_text_box.chars.size() - size_t(1));

	const bool next_portion_button_accessibility = all_portion_chars_visable && !at_last_portion;
	next_portion_button.press_data.pressable = next_portion_button_accessibility;
	next_portion_button.press_data.hoverable = next_portion_button_accessibility;
	const bool previous_portion_button_accessibility = (course_paths[current_course_path_index]->current_portion_index != size_t(0));
	previous_portion_button.press_data.pressable = previous_portion_button_accessibility;
	previous_portion_button.press_data.hoverable = previous_portion_button_accessibility;
	const bool finish_portion_button_accessibility = all_portion_chars_visable && at_last_portion;
	finish_portion_button.press_data.pressable = finish_portion_button_accessibility;
	finish_portion_button.press_data.hoverable = finish_portion_button_accessibility;


	e->UpdateSimpleTextButton(&next_portion_button, e->blank_camera, &main_layer, 0, { &main_layer });
	e->UpdateSimpleTextButton(&previous_portion_button, e->blank_camera, &main_layer, 0, { &main_layer });
	e->UpdateSimpleTextButton(&previous_return_portion_button, e->blank_camera, &main_layer, 0, { &main_layer });
	e->UpdateSimpleTextButton(&next_return_portion_button, e->blank_camera, &main_layer, 0, { &main_layer });
	e->UpdateSimpleTextButton(&finish_portion_button, e->blank_camera, &main_layer, 0, { &main_layer });


	if (complete_lesson_cutscene_timer == -1.0)
	{
		if (next_portion_button.press_data.first_frame_released || e->input.j.first_frame_pressed)
		{
			SetCurrentTextPortionIndex(course_paths[current_course_path_index]->current_portion_index + size_t(1));
		}
		if (previous_portion_button.press_data.first_frame_released)
		{
			SetCurrentTextPortionIndex(course_paths[current_course_path_index]->current_portion_index - size_t(1));
		}


		if (finish_portion_button.press_data.first_frame_released)
		{
			SetCurrentTextPortionIndex(course_paths[current_course_path_index]->portions.size());
			complete_lesson_cutscene_timer = 0.0;

			Mix_PlayChannel(2, confetti_sound, 0);
			for (size_t i = 0; i < size_t(50); i++)
			{
				confetti.push_back({ (unsigned char)e->GetRandInt(0, 5), {0.0, path_progress_bar.back_rect.GetUniEdge({3})}, {e->GetRandDouble(-8.0, 8.0), e->GetRandDouble(5.0, 15.0)}, 0.0 });
			}
		}



		AdvanceCurrentTextPortionTextBox(0.64, { 0.66667, 1.5 }, 1);
		CheckForLinkClicksAndGenerateSavedLinkRects(0.8, { 0.66667, 1.5 }, 1, 0);


		//Test code for cell_set
		if (e->input.h.first_frame_pressed)
		{
			if (test_cset.set[0]->state)
			{
				Mix_PlayChannel(2, e->click_release_sound, 0);
				test_cset.Click(0, 0);
			}
			else
			{
				Mix_PlayChannel(2, e->click_press_sound, 0);
				test_cset.Click(0, 1);
			}
		}
	}
	if (complete_lesson_cutscene_timer != -1.0)
	{
		if (complete_lesson_cutscene_timer >= 2.3)
		{
			SetScene(5, 0);
			return;
		}

		UpdateConfetti();


		complete_lesson_cutscene_timer += 1.0 / e->frame_rate;
	}


	//Update visual-related member variables
	ReduceStretchInCurrentTextPortionTextBox(0.2);
	UpdateCellSet(&test_cset);

	UpdateProgressBar(&path_progress_bar);

	/*
	//Move progress bar closer to target width
	if (course_path_progress_bar.size.width != course_path_progress_bar_target_width)
	{
		if ((course_path_progress_bar.size.width >= (course_path_progress_bar_target_width - 0.025)) && (course_path_progress_bar.size.width <= (course_path_progress_bar_target_width + 0.025)))
		{
			proportion_progress_bar_moved_reverse = 0.0;

			course_path_progress_bar.size.width = course_path_progress_bar_target_width;
		}
		else
		{
			//Set progression percent of progress bar
			if (course_paths[current_course_path_index]->portions.size() != 0)
			{
				proportion_progress_bar_moved_reverse = abs(course_path_progress_bar_target_width - course_path_progress_bar.size.width) / (course_path_progress_bar_back_middle.size.width / (double)course_paths[current_course_path_index]->portions.size());
				if (proportion_progress_bar_moved_reverse > 1.0)
				{
					proportion_progress_bar_moved_reverse = 1.0;
				}
			}
			else
			{
				cout << "Current path has NO PORTIONS (path.size() == 0). Sent from RunScene4()" << endl;
			}
			
			//Set progress bar width
			course_path_progress_bar.size.width += (course_path_progress_bar_target_width - course_path_progress_bar.size.width) * (1.0 - pow(0.8, e->frame_factor_inverse));
		}
	}
	*/
}
void Program::DrawScene4()
{
	DrawCellSet(&test_cset, e->blank_camera);
	e->DrawTextBox(&current_text_portion_text_box, e->blank_camera);

	for (size_t i = 0; i < saved_link_rects.size(); i++)
	{
		if (saved_link_rects[i].hovering)
		{
			if (saved_link_rects[i].pressed)
			{
				e->DrawRectStructOne(&saved_link_rects[i].rect, { 0, 0, 200, 60 }, e->blank_camera);
			}
			else
			{
				e->DrawRectStructOne(&saved_link_rects[i].rect, { 0, 0, 200, 40 }, e->blank_camera);
			}
		}
		else
		{
			e->DrawRectStructOne(&saved_link_rects[i].rect, { 0, 0, 200, 20 }, e->blank_camera);
		}
	}

	/*
	for (size_t i = 0; i < course_text[current_text_portion_index]->links.size(); i++)
	{
		const TextLink current_link = course_text[current_text_portion_index]->links[i];
		vector<RectStructOne>* temp_rects = current_text_portion_text_box.GetSegmentHitbox(current_link.begin_char, current_link.end_char);
		for (size_t j = 0; j < temp_rects->size(); j++)
		{
			e->DrawRectStructOne(&temp_rects->at(j), { 0, 0, 200, 50 }, e->blank_camera);
		}
	}
	*/

	if (course_path_text_box.chars.size() > 0)
	{
		//e->DrawRectangle(&course_path_rectangle, { 220, 220, 220, 255 }, e->blank_camera);
		e->DrawTextBox(&course_path_text_box, e->blank_camera);
	}

	DrawProgressBar(&path_progress_bar, e->blank_camera);
	const Point2D mouse_blank = e->GetMousePos(e->blank_camera);
	if (OverlapPoint2DWithRectangle(&mouse_blank, &path_progress_bar.back_rect, 1))
	{
		e->DrawTextBox(&progress_bar_text_box, e->blank_camera);
	}


	//Draw the previous, next, return, and finish buttons
	const bool at_last_portion = (course_paths[current_course_path_index]->current_portion_index + size_t(1)) >= course_paths[current_course_path_index]->portions.size();
	
	if (!at_last_portion)
	{
		e->DrawSimpleTextButton(&next_portion_button, e->blank_camera);
	}

	e->DrawSimpleTextButton(&previous_portion_button, e->blank_camera);

	if (at_last_portion)
	{
		e->DrawSimpleTextButton(&finish_portion_button, e->blank_camera);
	}

	//Draw Confetti
	DrawConfetti(e->blank_camera);
}
void Program::PostDrawRunScene4()
{
	//Nothin
}

void Program::SetScene5()
{

}
void Program::EndScene5()
{

}
void Program::RunScene5()
{

}
void Program::DrawScene5()
{

}
void Program::PostDrawRunScene5()
{

}

void Program::SetScene6()
{

}
void Program::EndScene6()
{

}
void Program::RunScene6()
{

}
void Program::DrawScene6()
{

}
void Program::PostDrawRunScene6()
{

}

void Program::SetScene7()
{

}
void Program::EndScene7()
{

}
void Program::RunScene7()
{

}
void Program::DrawScene7()
{

}
void Program::PostDrawRunScene7()
{

}

void Program::SetScene8()
{

}
void Program::EndScene8()
{

}
void Program::RunScene8()
{

}
void Program::DrawScene8()
{

}
void Program::PostDrawRunScene8()
{

}

void Program::SetScene9()
{

}
void Program::EndScene9()
{

}
void Program::RunScene9()
{

}
void Program::DrawScene9()
{

}
void Program::PostDrawRunScene9()
{

}

Program::Program() : e(nullptr)
{
	e = new Engine();

	e->p = this;
	e->RunPointer = &Program::Run;
	e->DrawPointer = &Program::Draw;
	e->PostDrawRunPointer = &Program::PostDrawRun;

	main_camera = e->NewCamera("Main");

	const double blank_camera_right_edge = e->blank_camera->rect.GetUniEdge({ 0 });
	const double blank_camera_bottom_edge = e->blank_camera->rect.GetUniEdge({ 1 });
	const double blank_camera_left_edge = e->blank_camera->rect.GetUniEdge({ 2 });
	const double blank_camera_top_edge = e->blank_camera->rect.GetUniEdge({ 3 });






	//-----------------   COURSE STUFFS SCENE 4   -----------------

	test_cset.InitLeast(&e->default_font);
	test_cset.number_display.CreateDebugData({ &e->engine_debug_data_container }, &e->default_font, "number_display", { 2 }, 1);
	test_cset.set.push_back(new Cell());
	test_cset.set.push_back(new Cell());
	test_cset.set.push_back(new Cell());



	//Initialze portion_text_box
	current_text_portion_text_box.InitLeast(&e->default_font);
	current_text_portion_text_box.text_wrap = 1;
	current_text_portion_text_box.parent_rect.size.width = e->blank_camera->rect.size.width;
	current_text_portion_text_box.parent_rect.size.height = e->blank_camera->rect.size.height / 3.0;
	current_text_portion_text_box.parent_rect.SetBaseSizeWithSizeScale({ 4.0, 4.0 });
	current_text_portion_text_box.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });



	//Initialize the next, previous, return, and finish buttons
	next_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Next", &e->default_font, { 40.0, 13.0 }, 4.0, 4.0, { 0.0, 0.0 }, 0);
	next_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_right_edge, { 0 });
	next_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
	next_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

	previous_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Prev", &e->default_font, { 40.0, 13.0 }, 4.0, 4.0, { 0.0, 0.0 }, 0);
	previous_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_left_edge, { 2 });
	previous_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
	previous_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

	previous_return_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Return", &e->default_font, { 40.0, 13.0 }, 4.0, 4.0, { 0.0, 0.0 }, 0);
	previous_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_left_edge, { 2 });
	previous_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
	previous_return_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };
	previous_return_portion_button.press_data.hoverable = 0;
	previous_return_portion_button.press_data.pressable = 0;

	next_return_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Return", &e->default_font, { 40.0, 13.0 }, 4.0, 4.0, { 0.0, 0.0 }, 0);
	next_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_right_edge, { 0 });
	next_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
	next_return_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };
	next_return_portion_button.press_data.hoverable = 0;
	next_return_portion_button.press_data.pressable = 0;

	finish_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Finish", &e->default_font, { 40.0, 13.0 }, 4.0, 4.0, { 0.0, 0.0 }, 0);
	finish_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_right_edge, { 0 });
	finish_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
	finish_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };
	finish_portion_button.press_data.hoverable = 0;
	finish_portion_button.press_data.pressable = 0;



	//Initialize progress bar rectangles

	Size2D temp_size = { next_portion_button.parent_rect.GetUniEdge({ 2 }) - previous_portion_button.parent_rect.GetUniEdge({ 0 }) + 8.0, previous_portion_button.parent_rect.size.height };

	path_progress_bar.InitBasic(
		{ 0.0, e->blank_camera->rect.GetUniEdge({ 1 }) + (temp_size.height / 2.0) },
		temp_size,
		4.0,
		0.0
	);
	path_progress_bar.bars.back().progress_color = { 0, 190, 0, 255 };
	path_progress_bar.bars.back().secondary_progress_color = { 30, 255, 30, 255 };

	path_progress_bar.AddBar(0.0);
	path_progress_bar.bars.back().progress_color = { 0, 210, 0, 255 };
	path_progress_bar.bars.back().secondary_progress_color = { 70, 255, 70, 255 };



	progress_bar_text_box.InitLeast(&e->default_font);
	progress_bar_text_box.parent_rect.size = path_progress_bar.progress_back_rect.size;
	progress_bar_text_box.parent_rect.pos = path_progress_bar.back_rect.pos;
	progress_bar_text_box.horizontal_text_centering = { 1 };
	progress_bar_text_box.vertical_text_centering = { 1 };
	progress_bar_text_box.parent_rect.SetBaseSizeWithSizeScale({ 4.0, 4.0 });





	course_path_rectangle.size.width = e->blank_camera->rect.size.width;
	course_path_rectangle.size.height = 26.0;
	course_path_rectangle.SetBaseSizeWithSizeScale({ 2.0, 2.0 });
	//course_path_rectangle.SetPosWithUniEdge(course_path_progress_bar_back.GetUniEdge({ 3 }), { 1 });
	course_path_rectangle.SetPosWithUniEdge(path_progress_bar.back_rect.GetUniEdge({ 3 }), { 1 });
	course_path_rectangle.SetPosWithUniEdge(e->blank_camera->rect.GetUniEdge({ 2 }), { 2 });
	course_path_rectangle.pos.x += 6.0;
	course_path_rectangle.pos.y += 6.0;

	course_path_text_box.InitMost(&e->default_font, course_path_rectangle, "Path: main", { 0 }, { 0 }, 0);

	course_path_rectangle.base_size = { 1.0, 1.0 };
	course_path_rectangle.pos.x -= 6.0;
	course_path_rectangle.pos.y -= 6.0;






	// ----   CREATE COURSE DATA   ----

	intro_main.full_path_text = "Path: main";

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("Ello, it's me, lead developer of PLACEHOLDER!", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("I\'m going to assume that you wish to learn how to develop games, seeing as you clicked the \"how to develop games\" button.", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("If not, you can always skedaddle by clicking the aptly named \"skedaddle\" button.", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("For those of you who do wish to learn game development though, I should give you some information before we start the course.", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("First of all, game development takes a LOT of effort. Video games incorporate computer programming, digital art, and sound design all into one package.", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("Even simple-looking games like Undertale or Omori can easily take upwards of 5 years to complete!", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("Essentially, this is my reminder to be patient.", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("This course should only take around 20 hours to complete though (hopefully not 5 years).", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("And if you finish, you should be ready to start developing your first (or maybe not first) game!", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("You don\'t need to know anything about computer programming to take this course, but if you do, you can skip things you already know.", 1);

	intro_main.portions.push_back(new TextPortion());
	intro_main.portions.back()->InitLeast("Okay, that\'s it for the intro, good luck!", 1);

	course_paths.push_back(&intro_main);



	lesson_1_main.full_path_text = "Path: main";

	lesson_1_main.portions.push_back(new TextPortion());
	lesson_1_main.portions.back()->InitLeast("This is the first portion. Skibidi bop mm dada", 1);

	lesson_1_main.portions.push_back(new TextPortion());
	lesson_1_main.portions.back()->InitLeast("This is the second portion.", 2);
	lesson_1_main.portions.back()->links.push_back(TextLink());
	lesson_1_main.portions.back()->links.back().InitLeast(3, 8, 25);

	lesson_1_main.portions.push_back(new TextPortion());
	lesson_1_main.portions.back()->InitLeast("This is the third portion.", 3);

	lesson_1_main.portions.push_back(new TextPortion());
	lesson_1_main.portions.back()->InitLeast("This is the fourth portion.", 2);

	lesson_1_main.portions.push_back(new TextPortion());
	lesson_1_main.portions.back()->InitLeast("This is the fifth portion.", 1);

	course_paths.push_back(&lesson_1_main);






	//-----------------   COURSE STUFFS SCENE 4   -----------------

	lessons.push_back(new Lesson());
	lessons.back()->button.InitWithBaseSize({ 4.0, 4.0 }, "Intro", & e->default_font, { 100.0, 24.0 }, 4.0, 4.0, { 0.0, 0.0 }, 0);
	lessons.back()->main_path_index = 0;
	lessons.back()->minute_estimate = 10;






	// -----------------   SOUNDS   -----------------

	InitSounds();






	// -----------------   INITIALIZE MOUSE LAYERS   -----------------
	
	main_layer.Init(&e->mouse_layers);






	// -----------------   INITIALIZE GAME HOME SCREEN   -----------------

	const double window_width_scaling = (double)e->window_width / (double)DEFAULT_WINDOW_WIDTH;
	const double window_height_scaling = (double)e->window_height / (double)DEFAULT_WINDOW_HEIGHT;
	
	double lesser_scale;
	if (window_width_scaling <= window_height_scaling)
	{
		lesser_scale = window_width_scaling;
	}
	else
	{
		lesser_scale = window_height_scaling;
	}
	const double five_lesser_scale = lesser_scale * 5.0;

	Size2D editing_button_size = { 100.0, 24.0 };
	const double editing_button_list_x = 600.0;
	const double editing_button_list_y = 400.0;
	const double editing_button_spacing_y = 180.0;

	code_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Code", & e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, {0.0, 0.0}, 0);
	//code_button.CreateDebugData({ &e->engine_debug_data_container }, "Code Button", { 1 });
	code_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 0.0)) / window_height_scaling };
	code_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

	images_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Images", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	images_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 1.0)) / window_height_scaling };
	images_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

	sounds_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Sounds", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	sounds_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 2.0)) / window_height_scaling };
	sounds_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

	other_files_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Other Files", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	other_files_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 3.0)) / window_height_scaling };
	other_files_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

	run_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Run", &e->default_font, { 200.0, 24.0 }, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	run_button.parent_rect.pos.x = -300.0 / window_width_scaling;
	run_button.parent_rect.SetPosWithUniEdge(other_files_button.parent_rect.GetUniEdge({ 1 }), { 1 });
	run_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };


	back_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Back", &e->default_font, { 14.0, e->window_height / five_lesser_scale }, five_lesser_scale, five_lesser_scale, { 14.0 * five_lesser_scale, 0.0 }, 1);
	//back_button.CreateDebugData({ &e->engine_debug_data_container }, "Back Button", {});
	back_button.parent_rect.SetPosWithUniEdge(main_camera->rect.GetUniEdge({ 2 }), { 2 });
	back_button.text_box.text_wrap = 1;
	back_button.text_box.parent_rect.base_size.width = 4.0;
	back_button.text_box.parent_rect.size.width = 4.0;
	back_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };


	run_anim.LoadFrames(e->renderer, "images/program/player/run_anim", 8, 10.0);

	idle_anim.LoadFrames(e->renderer, "images/program/player/idle_anim", 3, 2.0);
	idle_anim.frames.back().frame_length = 0.1;

	swim_anim.LoadFrames(e->renderer, "images/program/player/swim_anim", 5, 10.0);

	pride_anim.LoadFrames(e->renderer, "images/program/player/pride_anim", 6, 10.0);
	pride_anim.offset.x = 4.5;

	player.hitbox.base_size = idle_anim.dimentions;
	player.hitbox.SetSizeWithSizeScale(Size2D{ 4.0, 4.0 });
	player.hitbox.base_size = player.hitbox.size;

	player.sprite.rect = player.hitbox;
	player.sprite.rect.SetBaseSizeWithSizeScale({ 4.0, 4.0 });
	player.sprite.LoadAnimation(&idle_anim);


	light_ground.LoadTexture(e->renderer, "images/program/ground_tiles/light_ground.png");
	dark_ground.LoadTexture(e->renderer, "images/program/ground_tiles/dark_ground.png");
	grassy_ground.LoadTexture(e->renderer, "images/program/ground_tiles/grass.png");
	cobble_ground.LoadTexture(e->renderer, "images/program/ground_tiles/cobble.png");
	ground_highlight.LoadTexture(e->renderer, "images/program/ground_tiles/ground_highlight.png");
	water_ground.LoadFrames(e->renderer, "images/program/ground_tiles/water", 38, 5.0);

	tree.LoadTexture(e->renderer, "images/program/ground_accessories/tree.png");

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			ground.tile_data[x][y] = 3;
		}
	}

	ground.tile_data[0][0] = 1;
	ground.tile_data[1][0] = 2;
	ground.tile_data[2][0] = 4;
	ground.tile_data[3][0] = 5;
	ground.tile_data[4][0] = 6;

	test_box.InitLeast(&e->default_font);
	test_box.CreateDebugData({ &e->engine_debug_data_container }, &e->default_font, "Test Box", { 1 }, 1);
	test_box.parent_rect.base_size = { 100.0, 50.0 };
	test_box.parent_rect.SetSizeWithSizeScale({ 1.0, 1.0 });
	test_box.AddCharPtr("Here are words that \nare cool");
	test_box.UpdateCharPos();


	test_rect.pos = { 100.0, 100.0 };
	test_rect.base_size = { 80.0, 80.0 };
	test_rect.SetSizeWithSizeScale({ 1.0, 1.0 });


	/*
	test_box_two.InitLeast(&e->default_font);
	test_box_two.CreateDebugData({ &e->engine_debug_data_container }, "Test Box Two", { 1 });
	test_box_two.debug_data_container.debug_id = 4;
	test_box_two.parent_rect.base_size = { 100.0, 50.0 };
	test_box_two.parent_rect.SetSizeWithSizeScale({ 1.0, 1.0 });
	//test_box->AddCharPtr("Here are words that \nare cool");
	test_box_two.AddCharPtr("Skibidi");
	test_box_two.UpdateCharPos();
	*/

	test_container.InitLeast({}, &e->default_font, "Test Container", nullptr, {}, 1);
}
Program::~Program()
{
	delete e;

	DestroySounds();
}

// -----------------   SET SCENE FUNCTIONS   -----------------

void Program::NumSwitchScene()
{
	if (e->input.one.first_frame_pressed)
	{
		SetScene(1, 0);
		return;
	}
	if (e->input.two.first_frame_pressed)
	{
		SetScene(2, 0);
		return;
	}
	if (e->input.three.first_frame_pressed)
	{
		SetScene(3, 0);
		return;
	}
	if (e->input.four.first_frame_pressed)
	{
		SetScene(4, 0);
		return;
	}
	if (e->input.five.first_frame_pressed)
	{
		SetScene(5, 0);
		return;
	}
	if (e->input.six.first_frame_pressed)
	{
		SetScene(6, 0);
		return;
	}
	if (e->input.seven.first_frame_pressed)
	{
		SetScene(7, 0);
		return;
	}
	if (e->input.eight.first_frame_pressed)
	{
		SetScene(8, 0);
		return;
	}
	if (e->input.nine.first_frame_pressed)
	{
		SetScene(9, 0);
		return;
	}
}
void Program::SetScene(const int param_scene, const bool run_new_scene)
{
	EndScene();

	e->scene = param_scene;
	switch (param_scene)
	{
	case 1:
		SetScene1();
		break;
	case 2:
		SetScene2();
		break;
	case 3:
		SetScene3();
		break;
	case 4:
		SetScene4();
		break;
	case 5:
		SetScene5();
		break;
	case 6:
		SetScene6();
		break;
	case 7:
		SetScene7();
		break;
	case 8:
		SetScene8();
		break;
	case 9:
		SetScene9();
		break;
	}

	if (run_new_scene)
	{
		Run();
	}
}
void Program::EndScene()
{
	switch (e->scene)
	{
	case 1:
		EndScene1();
		break;
	case 2:
		EndScene2();
		break;
	case 3:
		EndScene3();
		break;
	case 4:
		EndScene4();
		break;
	case 5:
		EndScene5();
		break;
	case 6:
		EndScene6();
		break;
	case 7:
		EndScene7();
		break;
	case 8:
		EndScene8();
		break;
	case 9:
		EndScene9();
		break;
	}
}