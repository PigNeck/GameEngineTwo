#pragma once
#include "Engine.h"

struct Player
{
	Rectangle hitbox;

	Sprite sprite;

	bool running = 0;
	bool previous_frame_running = 0;
	bool first_frame_running = 0;
	bool first_frame_idle = 0;
};

struct Ground
{
	char tile_data[50][50] = {};

	double rise_time = 0.0;
};

struct Program
{
	Engine* e;
	Camera* main_camera;

	Animation run_anim;
	Animation idle_anim;
	Animation swim_anim;
	Animation pride_anim;

	Texture light_ground;
	Texture dark_ground;
	Texture grassy_ground;
	Texture cobble_ground;
	Texture ground_highlight;
	Animation water_ground;

	Texture tree;

	Ground ground;

	Player player;

	Rectangle test_rect;


	// -----------------   HOME SCREEN   -----------------


	// -----------------   GAME HOME SCREEN   -----------------

	SimpleTextButton run_button;
	SimpleTextButton code_button;
	SimpleTextButton images_button;
	SimpleTextButton sounds_button;
	SimpleTextButton other_files_button;

	DebugDataContainer test_container;

	SimpleTextButton back_button;


	TextBox test_box;
	//TextBox test_box_two;


	bool test_bool = 0;
	char test_char = 'a';
	int test_int = 123;
	float test_float = 1.23;
	double test_double = 1.2345;
	Point2D test_point_2d = { 5.0, 10.0 };
	Size2D test_size_2d = { 100.0, 200.0 };

	double test_x = 0.0;
	double test_y = 0.0;



	void Run();
	void Draw();
	void PostDrawRun();
	Program();
	~Program();

	void UpdatePlayer(Player* param_player);

	void UpdateMainCamera();

	void DrawGround(Ground* param_ground, Camera* camera);



	// -----------------   SET SCENE FUNCTIONS   -----------------

	void SetScene(int param_scene);

	void EndScene();
};
