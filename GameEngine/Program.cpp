#include "Program.h"

#define PI 3.14159265

#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080

#define NUMBER_OF_CHANNELS 16

void TextLink::InitLeast(const size_t param_linked_portion_index, const size_t param_begin_char, const size_t param_end_char)
{
	linked_portion_index = param_linked_portion_index;
	begin_char = param_begin_char;
	end_char = param_end_char;
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
			wait_multiplier = 10000.0;
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
void TextPortion::InitBack(const char* const param_text, const char default_sound_id, const size_t param_back_text_index)
{
	InitLeast(param_text, default_sound_id);
	back_text_index = param_back_text_index;
}
void TextPortion::InitNext(const char* const param_text, const char default_sound_id, const size_t param_next_text_index)
{
	InitLeast(param_text, default_sound_id);
	next_text_index = param_next_text_index;
}
void TextPortion::InitMost(const char* const param_text, const char default_sound_id, const size_t param_back_text_index, const size_t param_next_text_index)
{
	InitLeast(param_text, default_sound_id);
	back_text_index = param_back_text_index;
	next_text_index = param_next_text_index;
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



void Program::AdvanceCurrentTextPortionTextBox(const double rate, const Size2D stretch_multiplier, const int channel_num)
{
	double remaining_wait = rate * e->frame_factor;
	TextPortion* const current_text_portion = course_text[current_text_portion_index];
	
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

	text_sound_1 = Mix_LoadWAV("sounds/text_sound_1.wav");
	Mix_VolumeChunk(text_sound_1, 32);
	text_sound_2 = Mix_LoadWAV("sounds/text_sound_2.wav");
	Mix_VolumeChunk(text_sound_2, 32);
	text_sound_3 = Mix_LoadWAV("sounds/text_sound_3.wav");
	Mix_VolumeChunk(text_sound_3, 32);
}
void Program::DestroySounds()
{
	Mix_FreeChunk(text_sound_1);
	text_sound_1 = nullptr;
	Mix_FreeChunk(text_sound_2);
	text_sound_2 = nullptr;
	Mix_FreeChunk(text_sound_3);
	text_sound_3 = nullptr;
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
	main_camera->rect.pos.x += (player_pos.x - cam_pos.x) * 0.1 * e->frame_factor;
	main_camera->rect.pos.y += (player_pos.y - cam_pos.y) * 0.1 * e->frame_factor;
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

	param_ground->rise_time += e->frame_factor / 60.0;

	water_ground.Update(e->frame_factor);
}

//Clicks should be done BEFORE this function is called
void Program::UpdateCellSet(CellSet* const param_cell_set)
{
	for (size_t i = 0; i < param_cell_set->set.size(); i++)
	{
		param_cell_set->set[i]->Update(e->frame_factor);
	}

	const Rectangle temp_full_hitbox = param_cell_set->GenerateFullHitbox();
	const Point2D temp_mouse_pos = e->GetMousePos(main_camera);

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

void Program::SetCurrentTextPortionIndex(size_t param_text_portion_index)
{
	const size_t course_text_size = course_text.size();
	if (course_text_size > 0)
	{
		if (param_text_portion_index >= course_text_size)
		{
			param_text_portion_index = course_text_size - size_t(1);
			cout << "param_text_portion_index TOO HIGH. Set current_text_portion_index to last course_text index instead. Sent from SetCurrentTextPortionIndex(...)" << endl;
		}

		current_text_portion_index = param_text_portion_index;
		current_text_portion_text_box.Clear();
		for (size_t i = 0; i < course_text[current_text_portion_index]->text.size(); i++)
		{
			if (course_text[current_text_portion_index]->CharPartOfLink(i) == numeric_limits<size_t>::max())
			{
				current_text_portion_text_box.AddChar(course_text[current_text_portion_index]->text[i].value);
			}
			else
			{
				current_text_portion_text_box.AddChar(course_text[current_text_portion_index]->text[i].value, 0, 0, 200, 255);
			}
		}
		current_text_portion_text_box.UpdateCharPos();

		saved_char_sizes.clear();

		for (size_t i = 0; i < current_text_portion_text_box.chars.size(); i++)
		{
			current_text_portion_text_box.chars[i]->a_mod = 0;
			saved_char_sizes.push_back(current_text_portion_text_box.chars[i]->rect.size);
		}

		current_visable_char_progression = -1.0;

		for (size_t i = 0; i < current_text_portion_text_box.lines.size(); i++)
		{
			for (size_t j = current_text_portion_text_box.lines[i]->first_index; j <= current_text_portion_text_box.lines[i]->last_index; j++)
			{
				current_text_portion_text_box.chars[j]->a_mod = 0;
			}
		}
	}
	else
	{
		cout << "course_text_size == 0, so function quit. Sent from SetCurrentTextPortionIndex(...)" << endl;
	}
}

void Program::Run()
{
	NumSwitchScene();

	switch (e->scene)
	{
	case 1:
		e->UpdateSimpleTextButton(&run_button, main_camera, &main_layer, 1, {});
		e->UpdateSimpleTextButton(&code_button, main_camera, &main_layer, 1, {});
		e->UpdateSimpleTextButton(&images_button, main_camera, &main_layer, 1, {});
		e->UpdateSimpleTextButton(&sounds_button, main_camera, &main_layer, 1, {});
		e->UpdateSimpleTextButton(&other_files_button, main_camera, &main_layer, 1, {});

		if (run_button.press_data.first_frame_pressed)
		{
			Mix_PlayChannel(0, e->click_press_sound, 0);
		}

		if (run_button.press_data.first_frame_released)
		{
			Mix_PlayChannel(0, e->click_release_sound, 0);
			SetScene(2);
			break;
		}

		if (code_button.press_data.first_frame_released || images_button.press_data.first_frame_released || sounds_button.press_data.first_frame_released || other_files_button.press_data.first_frame_released)
		{
			SetScene(3);
			break;
		}

		if (e->input.g.pressed)
		{
			Size2D temp_current_size = test_box.parent_rect.size;

			test_box.parent_rect.size = { temp_current_size.width + 1.0, temp_current_size.height + 0.5 };
		}
		break;
	case 2:
		UpdatePlayer(&player);

		UpdateMainCamera();
		break;
	case 3:
		e->UpdateSimpleTextButton(&back_button, main_camera, &main_layer, 1, {});

		if (back_button.press_data.first_frame_released)
		{
			SetScene(1);
		}
		break;
	case 4:
		RunScene4();
		break;
	case 5:
		//Nuthin
		break;
	case 6:
		//Nuthin
		break;
	case 7:
		//Nuthin
		break;
	case 8:
		//Nuthin
		break;
	case 9:
		//Nuthin
		break;
	}
}
void Program::Draw()
{
	switch (e->scene)
	{
	case 1:
		e->DrawSimpleTextButton(&run_button, main_camera);
		e->DrawSimpleTextButton(&code_button, main_camera);
		e->DrawSimpleTextButton(&images_button, main_camera);
		e->DrawSimpleTextButton(&sounds_button, main_camera);
		e->DrawSimpleTextButton(&other_files_button, main_camera);


		e->DrawRectangle(&test_rect, { 255, 0, 0, 255 }, main_camera);

		//e->DrawTextBox(&test_box, main_camera);
		break;
	case 2:
		DrawGround(&ground, main_camera);

		e->DrawSprite(&player.sprite, main_camera);
		break;
	case 3:
		e->DrawSimpleTextButton(&back_button, main_camera);

		e->DrawRectangleScaledBorderScaledShadow(&test_rect, { 255, 0, 0, 100 }, 4.0, { 2 }, { 0, 0, 0, 100 }, { -4.0, -4.0 }, { 0, 0, 0, 70 }, main_camera);
		break;
	case 4:
		DrawScene4();
		break;
	case 5:
		//Nothin
		break;
	case 6:
		//Nothin
		break;
	case 7:
		//Nothin
		break;
	case 8:
		//Nothin
		break;
	case 9:
		//Nothin
		break;
	}
}
void Program::PostDrawRun()
{
	switch (e->scene)
	{
	case 1:
		//Nothin
		break;
	case 2:
		player.sprite.animation->Update(e->frame_factor);
		break;
	case 3:
		//Nothin
		break;
	case 4:
		PostDrawRunScene4();
		break;
	case 5:
		//Nothin
		break;
	case 6:
		//Nothin
		break;
	case 7:
		//Nothin
		break;
	case 8:
		//Nothin
		break;
	case 9:
		//Nothin
		break;
	}
}

void Program::RunScene4()
{
	e->UpdateSimpleTextButton(&next_portion_button, e->blank_camera, &main_layer, 0, { &main_layer });
	e->UpdateSimpleTextButton(&previous_portion_button, e->blank_camera, &main_layer, 0, { &main_layer });

	if (next_portion_button.press_data.first_frame_released)
	{
		const size_t current_next_index = course_text[current_text_portion_index]->next_text_index;
		if (current_next_index == numeric_limits<size_t>::max())
		{
			SetCurrentTextPortionIndex(current_text_portion_index + size_t(1));
		}
		else
		{
			SetCurrentTextPortionIndex(current_next_index);
		}
	}
	if (previous_portion_button.press_data.first_frame_released)
	{
		const size_t current_back_index = course_text[current_text_portion_index]->back_text_index;
		if (current_back_index == numeric_limits<size_t>::max())
		{
			SetCurrentTextPortionIndex(current_text_portion_index - size_t(1));
		}
		else
		{
			SetCurrentTextPortionIndex(current_back_index);
		}
	}


	AdvanceCurrentTextPortionTextBox(0.8, { 0.66667, 1.5 }, 1);
	ReduceStretchInCurrentTextPortionTextBox(0.2);






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
	UpdateCellSet(&test_cset);
}
void Program::DrawScene4()
{
	DrawCellSet(&test_cset, e->blank_camera);
	e->DrawTextBox(&current_text_portion_text_box, e->blank_camera);

	for (size_t i = 0; i < course_text[current_text_portion_index]->links.size(); i++)
	{
		const TextLink current_link = course_text[current_text_portion_index]->links[i];
		vector<RectStructOne>* temp_rects = current_text_portion_text_box.GetSegmentHitbox(current_link.begin_char, current_link.end_char);
		for (size_t j = 0; j < temp_rects->size(); j++)
		{
			e->DrawRectStructOne(&temp_rects->at(j), { 0, 0, 200, 50 }, e->blank_camera);
		}
	}

	e->DrawSimpleTextButton(&next_portion_button, e->blank_camera);
	e->DrawSimpleTextButton(&previous_portion_button, e->blank_camera);
}
void Program::PostDrawRunScene4()
{
	//Nothin
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






	//-----------------   COURSE STUFFS   -----------------

	test_cset.InitLeast(&e->default_font);
	test_cset.number_display.CreateDebugData({ &e->engine_debug_data_container }, &e->default_font, "number_display", { 2 }, 1);
	test_cset.set.push_back(new Cell());
	test_cset.set.push_back(new Cell());
	test_cset.set.push_back(new Cell());

	current_text_portion_text_box.InitLeast(&e->default_font);
	current_text_portion_text_box.text_wrap = 1;
	current_text_portion_text_box.parent_rect.size.width = e->blank_camera->rect.size.width;
	current_text_portion_text_box.parent_rect.size.height = e->blank_camera->rect.size.height / 3.0;
	current_text_portion_text_box.parent_rect.SetBaseSizeWithSizeScale({ 4.0, 4.0 });
	current_text_portion_text_box.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });

	next_portion_button.InitWithMargin({ 4.0, 4.0 }, "Next", &e->default_font, { 12.0, 12.0 }, 4.0, 4.0);
	next_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_right_edge, { 0 });
	next_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });

	previous_portion_button.InitWithMargin({ 4.0, 4.0 }, "Prev", &e->default_font, { 12.0, 12.0 }, 4.0, 4.0);
	previous_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_left_edge, { 2 });
	previous_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });






	// ----   CREATE COURSE DATA   ----

	p1.InitLeast("This is the first portion. Skibidi bop mm dada", 1);
	course_text.push_back(&p1);

	p2.InitLeast("This is the second portion.", 2);
	course_text.push_back(&p2);
	p2.links.push_back(TextLink());
	p2.links.back().InitLeast(4, 8, 25);

	p3.InitNext("This is the third portion.", 3, 4);
	course_text.push_back(&p3);

	p4.InitLeast("This is the fourth portion.", 2);
	course_text.push_back(&p4);

	p5.InitBack("This is the fifth portion.", 1, 2);
	course_text.push_back(&p5);






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

	images_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Images", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	images_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 1.0)) / window_height_scaling };

	sounds_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Sounds", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	sounds_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 2.0)) / window_height_scaling };

	other_files_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Other Files", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	other_files_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 3.0)) / window_height_scaling };

	run_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Run", &e->default_font, { 200.0, 24.0 }, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	run_button.parent_rect.pos.x = -300.0 / window_width_scaling;
	run_button.parent_rect.SetPosWithUniEdge(other_files_button.parent_rect.GetUniEdge({ 1 }), { 1 });

	back_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Back", &e->default_font, { 14.0, e->window_height / five_lesser_scale }, five_lesser_scale, five_lesser_scale, { 14.0 * five_lesser_scale, 0.0 }, 1);
	//back_button.CreateDebugData({ &e->engine_debug_data_container }, "Back Button", {});
	back_button.parent_rect.SetPosWithUniEdge(main_camera->rect.GetUniEdge({ 2 }), { 2 });
	back_button.text_box.text_wrap = 1;
	back_button.text_box.parent_rect.base_size.width = 4.0;
	back_button.text_box.parent_rect.size.width = 4.0;


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
		EndScene();
		SetScene(1);
		return;
	}
	if (e->input.two.first_frame_pressed)
	{
		EndScene();
		SetScene(2);
		return;
	}
	if (e->input.three.first_frame_pressed)
	{
		EndScene();
		SetScene(3);
		return;
	}
	if (e->input.four.first_frame_pressed)
	{
		EndScene();
		SetScene(4);
		return;
	}
	if (e->input.five.first_frame_pressed)
	{
		EndScene();
		SetScene(5);
		return;
	}
	if (e->input.six.first_frame_pressed)
	{
		EndScene();
		SetScene(6);
		return;
	}
	if (e->input.seven.first_frame_pressed)
	{
		EndScene();
		SetScene(7);
		return;
	}
	if (e->input.eight.first_frame_pressed)
	{
		EndScene();
		SetScene(8);
		return;
	}
	if (e->input.nine.first_frame_pressed)
	{
		EndScene();
		SetScene(9);
		return;
	}
}

void Program::SetScene(int param_scene)
{
	e->scene = param_scene;
	switch (param_scene)
	{
	case 1:
		main_camera->rect.pos = { 0.0, 0.0 };
		break;
	case 2:
		ground.rise_time = 0.0;
		break;
	case 3:
		main_camera->rect.pos = { 0.0, 0.0 };
		break;
	case 4:
		SetCurrentTextPortionIndex(0);
		break;
	case 5:
		//Nothin
		break;
	case 6:
		//Nothin
		break;
	case 7:
		//Nothin
		break;
	case 8:
		//Nothin
		break;
	case 9:
		//Nothin
		break;
	}
}

void Program::EndScene()
{
	switch (e->scene)
	{
	case 1:
		//Beans
		break;
	case 2:
		//Beans v2
		break;
	case 3:
		//Beans v3
		break;
	case 4:
		//Beans v4
		break;
	case 5:
		//Beans v5
		break;
	case 6:
		//Beans v6
		break;
	case 7:
		//Beans v7
		break;
	case 8:
		//Beans v8
		break;
	case 9:
		//Orange
		break;
	}
}