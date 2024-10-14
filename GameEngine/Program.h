#pragma once
#include "TransistorSet.h"

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

struct TextLink
{
	size_t linked_portion_index = numeric_limits<size_t>::max();
	size_t begin_char = numeric_limits<size_t>::max();
	size_t end_char = numeric_limits<size_t>::max();

	void InitLeast(const size_t param_linked_portion_index, const size_t param_begin_char, const size_t param_end_char);
};

struct CharWithWaitMultiplier
{
	char value = 'A';
	char sound_id = 0;
	double wait_multiplier = 1.0;
};

struct TextPortion
{
	vector<CharWithWaitMultiplier> text;
	size_t back_text_index = numeric_limits<size_t>::max();
	size_t next_text_index = numeric_limits<size_t>::max();
	vector<TextLink> links = {};

	void InitLeast(const char* const param_text, const char default_sound_id);
	void InitBack(const char* const param_text, const char default_sound_id, const size_t param_back_text_index);
	void InitNext(const char* const param_text, const char default_sound_id, const size_t param_next_text_index);
	void InitMost(const char* const param_text, const char default_sound_id, const size_t param_back_text_index, const size_t param_next_text_index);

	//Returns the first link the char_index belongs to. If it belongs to none, numeric_limits<size_t>::max() is returned.
	size_t CharPartOfLink(const size_t char_index);
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






	//-----------------   COURSE STUFFS   -----------------
	
	bool hovering_over_tset = 0;
	CellSet test_cset;

	vector<Size2D> saved_char_sizes;
	//Remove lower line later
	//size_t current_visable_char = numeric_limits<size_t>::max();
	double current_visable_char_progression = -1.0;
	TextBox current_text_portion_text_box;
	size_t current_text_portion_index = 0;
	vector<TextPortion*> course_text = {};

	SimpleTextButton next_portion_button;
	SimpleTextButton previous_portion_button;


	//The higher rate is, the faster letters appear (good default == 0.5)
	void AdvanceCurrentTextPortionTextBox(const double rate, const Size2D stretch_multiplier, const int channel_num);
	//The higher rate is, the faster letters normalize (0.0 < rate < 1.0) (good default == 0.2)
	void ReduceStretchInCurrentTextPortionTextBox(const double rate);



	// ----   CREATE COURSE DATA   ----

	TextPortion p1;
	TextPortion p2;
	TextPortion p3;
	TextPortion p4;
	TextPortion p5;






	// -----------------   SOUNDS   -----------------

	Mix_Chunk* text_sound_1 = nullptr;
	Mix_Chunk* text_sound_2 = nullptr;
	Mix_Chunk* text_sound_3 = nullptr;
	Mix_Chunk* text_sound_4 = nullptr;

	void InitSounds();
	void DestroySounds();






	// -----------------   MOUSE LAYERS   -----------------
	
	MouseLayer main_layer;






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
	float test_float = 1.23f;
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

	//Clicks should be done BEFORE this function is called
	void UpdateCellSet(CellSet* const param_cell_set);
	void DrawCellSet(CellSet* const param_cell_set, Camera* const camera);

	void SetCurrentTextPortionIndex(size_t param_text_portion_index);






	// -----------------   SET SCENE FUNCTIONS   -----------------

	void NumSwitchScene();

	void SetScene(int param_scene);

	void EndScene();

	void RunScene4();
	void DrawScene4();
	void PostDrawRunScene4();
};