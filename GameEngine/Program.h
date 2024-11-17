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

	//IMPLEMENT LATER
	char link_type = 0; //0 == nothing, 1 == "Who?", 2 == "What?", 3 == "When?", 4 == "Why?", 5 == "How?"

	void InitLeast(const size_t param_linked_portion_index, const size_t param_begin_char, const size_t param_end_char);
};

struct CharWithWaitMultiplier
{
	char value = 'A';
	char sound_id = 0;
	double wait_multiplier = 1.0;
};

struct Lesson
{
	SimpleTextButton button; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	Rectangle progress_bar; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	Rectangle progress_bar_back; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	Rectangle progress_bar_back_middle; //CURRENTLY CANNOT SCALE WITH RESOLUTION

	unsigned char state;
	unsigned int minute_estimate;
	size_t main_path_index;
};

struct Confetti
{
	unsigned char color_id;
	Point2D position;
	Point2D velocity;
	double rotation;
};

struct Bar
{
	double target_width = 0.0;

	double bar_advance_rate = 20.0; //The percent of the difference between the actual and target width of the progress bar that is covered every 1/60 of a second.

	double lighting_level = 0.0; //The percent of the secondary color that comes through. If =0, progress_color is drawn. If >=100, secondary_progress_color is drawn. Lowest possible value is 0.01
	double lighting_advance_rate = 5.0; //The percent of lighting_level that is shaved off every 1/60 of a second.

	Rectangle progress_rect; //Is a child rect of back_rect.
	SDL_Color progress_color = { 0, 0, 0, 255 };
	SDL_Color secondary_progress_color = { 255, 255, 255, 255 };

	Rectangle* progress_back_rect_pointer;

	//Call this function before Updating this instance of Bar. Percent filled = discrete_progress / discrete_capacity
	void SetTargetWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar);
	//Call this function before Updating this instance of Bar. Thank you choosing American Airlines. We hope you enjoy your flight.
	void SetTargetWidth(const double percent, const bool light_bar);
};

struct ProgressBar //Rotation is not supported for ProgressBar :(
{
	vector<Bar> bars;

	Rectangle back_rect; //Is the parent rect of progress_back_rect. Treat it like a "parent_rect" which is also drawn to the screen as the "outline" of the progress bar.
	SDL_Color back_color = { 0, 0, 0, 255 };
	Rectangle progress_back_rect; //Is a child rect of back_rect.
	SDL_Color progress_back_color = { 215, 215, 215, 255 };

	//Call this function before Updating this instance of Bar. Percent filled = discrete_progress / discrete_capacity
	void SetTargetWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar);
	//Call this function before Updating this instance of Bar. Thank you choosing American Airlines. We hope you enjoy your flight.
	void SetTargetWidth(const double percent, const bool light_bar);

	//Only call this function if there are multiple bars in this instance of ProgressBar. For a normal progress bar, just use SetTargetWidth(...) instead :)
	void SetTargetWidthWithIndex(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar, const size_t bar_index);
	//Only call this function if there are multiple bars in this instance of ProgressBar. For a normal progress bar, just use SetTargetWidth(...) instead :)
	void SetTargetWidthWithIndex(const double percent, const bool light_bar, const size_t bar_index);

	//The suggested way to initialize an instance of ProgressBar is with one of the InitBasic(...) functions
	void InitLeast();
	//The suggested way to initialize an instance of ProgressBar is with one of the InitBasic(...) functions
	void InitMost(const vector<Bar> param_bars, const Rectangle param_back_rect, const SDL_Color param_back_color, const Rectangle param_progress_back_rect, const SDL_Color param_progress_back_color);
	//This is one of the suggested ways to initialize an instance of ProgressBar. There is also the other InitBasic(...) function (which takes different parameters).
	void InitBasic(const Point2D position, const Size2D back_rect_size, const double outline_thickness, const size_t discrete_progress, const size_t discrete_capacity);
	//This is one of the suggested ways to initialize an instance of ProgressBar. There is also the other InitBasic(...) function (which takes different parameters).
	void InitBasic(const Point2D position, const Size2D back_rect_size, const double outline_thickness, const double percent);

	//This function acts like a private function. Typically it is not used outside of the ProgressBar member functions. You can probably ignore it.
	void SetDefaultBarColor(const size_t index);
	//Pushes back a new bar. Bars with higher indexes are drawn above ones with lower indexes.
	void AddBar(const size_t discrete_progress, const size_t discrete_capacity);
	//Pushes back a new bar. Bars with higher indexes are drawn above ones with lower indexes.
	void AddBar(const double percent);

	ProgressBar();
};

struct TextPortion
{
	vector<CharWithWaitMultiplier> text;

	size_t back_path_index = numeric_limits<size_t>::max();
	bool back_lesson_select = 0;

	size_t next_path_index = numeric_limits<size_t>::max();
	bool next_lesson_select = 0;

	vector<TextLink> links = {};

	void InitLeast(const char* const param_text, const char default_sound_id);
	void InitBack(const char* const param_text, const char default_sound_id, const size_t param_back_path_index, const bool param_back_lesson_select);
	void InitNext(const char* const param_text, const char default_sound_id, const size_t param_next_path_index, const bool param_next_lesson_select);
	void InitMost(const char* const param_text, const char default_sound_id, const size_t param_back_path_index, const bool param_back_lesson_select, const size_t param_next_path_index, const bool param_next_lesson_select);

	//Returns the first link the char_index belongs to. If it belongs to none, numeric_limits<size_t>::max() is returned.
	size_t CharPartOfLink(const size_t char_index);
};

struct CoursePath
{
	vector<TextPortion*> portions;
	const char* full_path_text = nullptr;
	Lesson* accociated_lesson = nullptr;
	
	size_t current_portion_index = 0;
	size_t progress = 0;
	double saved_visable_char_progression = -1.0;

	TextPortion* GetCurrentPortion();
};

struct RectStructOnePlusHovering
{
	RectStructOne rect;
	bool hovering = 0;
	bool pressed = 0;
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






	//-----------------   COURSE STUFFS SCENE 4   -----------------
	
	bool hovering_over_tset = 0;
	CellSet test_cset;

	vector<Size2D> saved_char_sizes;
	vector<RectStructOnePlusHovering> saved_link_rects;

	//FIX LATER (visable should be spelled "visible")
	double current_visable_char_progression = -1.0;
	TextBox current_text_portion_text_box;
	void SetCurrentTextPortionTextBoxProgression(const double target_visable_char_progression);

	//Initialize course paths
	vector<CoursePath*> course_paths;
	size_t current_course_path_index = numeric_limits<size_t>::max();

	CoursePath intro_main;
	CoursePath lesson_1_main;
	CoursePath lesson_2_main;
	CoursePath lesson_3_main;

	//size_t current_text_portion_index = 0;

	SimpleTextButton next_portion_button;
	SimpleTextButton previous_portion_button;
	SimpleTextButton finish_portion_button;
	SimpleTextButton next_return_portion_button;
	SimpleTextButton previous_return_portion_button;

	double proportion_progress_bar_moved_reverse = 0.0;
	Rectangle course_path_rectangle; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	TextBox course_path_text_box; //CURRENTLY CANNOT SCALE WITH RESOLUTION

	//Progress bar data
	ProgressBar path_progress_bar;
	TextBox progress_bar_text_box;

	double complete_lesson_cutscene_timer = -1.0;

	//Confetti effect data
	vector<Confetti> confetti;

	void UpdateConfetti();
	void DrawConfetti(Camera* const camera);

	void UpdateProgressBar(ProgressBar* const progress_bar);
	void DrawProgressBar(ProgressBar* const progress_bar, Camera* const camera);


	//Call this AFTER AdvanceCurrentTextPortionTextBox(...). All of the parameters should match the parameters for AdvanceCurrentPortionTextBox(...).
	bool CheckForLinkClicksAndGenerateSavedLinkRects(const double rate, const Size2D stretch_multiplier, const int text_sound_channel_num, const int link_click_channel_num);
	//The higher rate is, the faster letters appear (good default == 0.5)
	void AdvanceCurrentTextPortionTextBox(const double rate, const Size2D stretch_multiplier, const int channel_num);
	//The higher rate is, the faster letters normalize (0.0 < rate < 1.0) (good default == 0.2)
	void ReduceStretchInCurrentTextPortionTextBox(const double rate);






	//-----------------   COURSE STUFFS SCENE 5   -----------------

	//Initialize lessons
	vector<Lesson*> lessons; //LESSONS DO NOT SCALE WITH RESOLUTION YET






	// -----------------   SOUNDS   -----------------

	Mix_Chunk* text_sound_1 = nullptr;
	Mix_Chunk* text_sound_2 = nullptr;
	Mix_Chunk* text_sound_3 = nullptr;
	Mix_Chunk* text_sound_4 = nullptr;

	Mix_Chunk* confetti_sound = nullptr;

	void InitSounds();
	void DestroySounds();

	//Play sound by using Mix_PlayChannel

	//Channel 0: button sounds and (currently) data simulation sounds
	//Channel 1: text sounds
	//Channel 2: sound effects (currently confetti_sound)
	//Channel 3:
	//Channel 4: 
	//Channel 5:
	//Channel 6: 
	//Channel 7:






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

	//To start at the beginning of the portion, make param_visable_char_progression -1.0
	void SetCurrentPathAndPortionIndexes(const size_t param_path_index, size_t param_portion_index);
	//To start at the beginning of the portion, make param_visable_char_progression -1.0
	void SetCurrentTextPortionIndex(size_t param_portion_index);






	// -----------------   SET SCENE FUNCTIONS   -----------------

	void NumSwitchScene();
	//Automatically calls EndScene() before switching the scene. Then calls the appropriate SetScene_() function and sets e->scene.
	void SetScene(const int param_scene, const bool run_new_scene);
	//EndScene() is automatically called by SetScene(...). DON'T CALL THIS IF YOU ALREADY CALLED SetScene(...)
	void EndScene();

	void SetScene1();
	void EndScene1();
	void RunScene1();
	void DrawScene1();
	void PostDrawRunScene1();

	void SetScene2();
	void EndScene2();
	void RunScene2();
	void DrawScene2();
	void PostDrawRunScene2();

	void SetScene3();
	void EndScene3();
	void RunScene3();
	void DrawScene3();
	void PostDrawRunScene3();

	void SetScene4();
	void EndScene4();
	void RunScene4();
	void DrawScene4();
	void PostDrawRunScene4();

	void SetScene5();
	void EndScene5();
	void RunScene5();
	void DrawScene5();
	void PostDrawRunScene5();

	void SetScene6();
	void EndScene6();
	void RunScene6();
	void DrawScene6();
	void PostDrawRunScene6();

	void SetScene7();
	void EndScene7();
	void RunScene7();
	void DrawScene7();
	void PostDrawRunScene7();

	void SetScene8();
	void EndScene8();
	void RunScene8();
	void DrawScene8();
	void PostDrawRunScene8();

	void SetScene9();
	void EndScene9();
	void RunScene9();
	void DrawScene9();
	void PostDrawRunScene9();
};