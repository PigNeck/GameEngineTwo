#include "Program.h"

#define PI 3.14159265

#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080

void Program::UpdatePlayer(Player* param_player)
{
	param_player->previous_frame_running = param_player->running;
	param_player->running = 0;

	if (e->input.a.pressed)
	{
		param_player->hitbox.data.pos.x -= 2.0;
		param_player->running = 1;

		param_player->sprite.rect.data.flip.value = 1;
	}
	if (e->input.d.pressed)
	{
		param_player->hitbox.data.pos.x += 2.0;
		param_player->running = 1;

		param_player->sprite.rect.data.flip.value = 0;
	}
	if (e->input.s.pressed)
	{
		param_player->hitbox.data.pos.y -= 2.0;
		param_player->running = 1;
	}
	if (e->input.w.pressed)
	{
		param_player->hitbox.data.pos.y += 2.0;
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

	param_player->sprite.rect.data.pos = param_player->hitbox.data.pos;

	//SDL_Rect temp_sdl_rect = RectangleToSDLRect(&param_player->sprite.rect, main_camera);
}

void Program::UpdateMainCamera()
{
	Point2D player_pos = player.hitbox.data.GetUniPos();
	Point2D cam_pos = main_camera->rect.data.GetUniPos();
	main_camera->rect.data.pos.x += (player_pos.x - cam_pos.x) * 0.1 * e->frame_factor;
	main_camera->rect.data.pos.y += (player_pos.y - cam_pos.y) * 0.1 * e->frame_factor;
}

void Program::DrawGround(Ground* param_ground, Camera* camera)
{
	RectangleData tile_rectangle_data;
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

						SDL_SetTextureAlphaMod(ground_highlight.sdl_texture, round(double_alpha));
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

void Program::Run()
{
	if (e->input.one.first_frame_pressed)
	{
		EndScene();

		SetScene(1);
	}
	if (e->input.two.first_frame_pressed)
	{
		EndScene();

		SetScene(2);
	}
	if (e->input.three.first_frame_pressed)
	{
		EndScene();

		SetScene(3);
	}

	switch (e->scene)
	{
	case 1:
		e->UpdateSimpleTextButton(&run_button, main_camera, 0);
		e->UpdateSimpleTextButton(&code_button, main_camera, 0);
		e->UpdateSimpleTextButton(&images_button, main_camera, 0);
		e->UpdateSimpleTextButton(&sounds_button, main_camera, 0);
		e->UpdateSimpleTextButton(&other_files_button, main_camera, 0);

		if (run_button.press_data.first_frame_released)
		{
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
			Size2D temp_current_size = test_box.parent_rect.data.size;

			test_box.parent_rect.data.size = { temp_current_size.width + 1.0, temp_current_size.height + 0.5 };
		}
		break;
	case 2:
		UpdatePlayer(&player);

		UpdateMainCamera();
		break;
	case 3:
		e->UpdateSimpleTextButton(&back_button, main_camera, 0);

		if (back_button.press_data.first_frame_released)
		{
			SetScene(1);
		}
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


		e->DrawRectangle(&test_rect.data, { 255, 0, 0, 255 }, main_camera);

		//e->DrawTextBox(&test_box, main_camera);
		break;
	case 2:
		DrawGround(&ground, main_camera);

		e->DrawSprite(&player.sprite, main_camera);
		break;
	case 3:
		e->DrawSimpleTextButton(&back_button, main_camera);

		//e->DrawRectangleScaledBorder(&test_rect, { 255, 0, 0, 255 }, 4.0, { 0 }, { 0, 0, 0, 255 }, main_camera);
		e->DrawRectangleScaledBorderScaledShadow(&test_rect.data, { 255, 0, 0, 100 }, 4.0, { 2 }, { 0, 0, 0, 100 }, { -4.0, -4.0 }, { 0, 0, 0, 70 }, main_camera);
		//e->DrawRectangleEx(&test_rect, { 255, 0, 0, 255 }, 0.0, { 0 }, 0.0, { 0 }, 0.0, { 0 }, 0.0, { 0 }, { 0, 0, 0, 255 }, { 0.0, 0.0 }, { 0, 0, 0, 0 }, main_camera);
	}
}
void Program::PostDrawRun()
{
	player.sprite.animation->Update(e->frame_factor);
}

Program::Program() : e(nullptr)
{
	e = new Engine();

	e->p = this;
	e->RunPointer = &Program::Run;
	e->DrawPointer = &Program::Draw;
	e->PostDrawRunPointer = &Program::PostDrawRun;

	main_camera = e->NewCamera("Main");

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
	code_button.parent_rect.data.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 0.0)) / window_height_scaling };

	images_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Images", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	images_button.parent_rect.data.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 1.0)) / window_height_scaling };

	sounds_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Sounds", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	sounds_button.parent_rect.data.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 2.0)) / window_height_scaling };

	other_files_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Other Files", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	other_files_button.parent_rect.data.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 3.0)) / window_height_scaling };

	run_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Run", &e->default_font, { 200.0, 24.0 }, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
	run_button.parent_rect.data.pos.x = -300.0 / window_width_scaling;
	run_button.parent_rect.data.SetPosWithUniEdge(other_files_button.parent_rect.data.GetUniEdge({ 1 }), { 1 });

	back_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Back", &e->default_font, { 14.0, e->window_height / five_lesser_scale }, five_lesser_scale, five_lesser_scale, { 14.0 * five_lesser_scale, 0.0 }, 1);
	//back_button.CreateDebugData({ &e->engine_debug_data_container }, "Back Button", {});
	back_button.parent_rect.data.SetPosWithUniEdge(main_camera->rect.data.GetUniEdge({ 2 }), { 2 });
	back_button.text_box.text_wrap = 1;
	back_button.text_box.parent_rect.data.base_size.width = 4.0;
	back_button.text_box.parent_rect.data.size.width = 4.0;


	run_anim.LoadFrames(e->renderer, "images/program/player/run_anim", 8, 10.0);

	idle_anim.LoadFrames(e->renderer, "images/program/player/idle_anim", 3, 2.0);
	idle_anim.frames.back().frame_length = 0.1;

	swim_anim.LoadFrames(e->renderer, "images/program/player/swim_anim", 5, 10.0);

	pride_anim.LoadFrames(e->renderer, "images/program/player/pride_anim", 6, 10.0);
	pride_anim.offset.x = 4.5;

	player.hitbox.data.base_size = idle_anim.dimentions;
	player.hitbox.data.SetSizeWithSizeScale(Size2D{ 4.0, 4.0 });
	player.hitbox.data.base_size = player.hitbox.data.size;

	player.sprite.rect = player.hitbox;
	player.sprite.rect.data.SetBaseSizeWithSizeScale({ 4.0, 4.0 });
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
	test_box.CreateDebugData({ &e->engine_debug_data_container }, &e->default_font, "Test Box", { 1 });
	test_box.parent_rect.data.base_size = { 100.0, 50.0 };
	test_box.parent_rect.data.SetSizeWithSizeScale({ 1.0, 1.0 });
	test_box.AddCharPtr("Here are words that \nare cool");
	test_box.UpdateCharPos();


	test_rect.data.pos = { 100.0, 100.0 };
	test_rect.data.base_size = { 80.0, 80.0 };
	test_rect.data.SetSizeWithSizeScale({ 1.0, 1.0 });


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

	test_container.Init({}, &e->default_font, "Test Container", nullptr, {});
}
Program::~Program()
{
	delete e;
}

// -----------------   SET SCENE FUNCTIONS   -----------------

void Program::SetScene(int param_scene)
{
	switch (param_scene)
	{
	case 1:
		e->scene = 1;
		main_camera->rect.data.pos = { 0.0, 0.0 };
		break;
	case 2:
		e->scene = 2;
		ground.rise_time = 0.0;
		break;
	case 3:
		e->scene = 3;
		main_camera->rect.data.pos = { 0.0, 0.0 };
	}
}

void Program::EndScene()
{
	switch (e->scene)
	{
	case 1:
		//I got nuthin
		break;
	case 2:
		//Again, nuthin
		break;
	case 3:
		//Beans
		break;
	}
}