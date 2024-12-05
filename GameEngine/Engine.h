#pragma once
#include "Rectangle.h"
#include "Camera.h"
#include "Input.h"
#include "Font.h"
#include "TextBox.h"
#include "QueueSprite.h"
#include "Button.h"
#include "TextButton.h"
#include "Animation.h"
#include "DebugDataContainer.h"
#include "ScrollBar.h"
#include "MouseLayer.h"
#include "ToolTip.h"

struct RunDrawAndPostDrawRunMethods
{
	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void PostDrawRun() = 0;

	virtual ~RunDrawAndPostDrawRunMethods() = default;
};

struct Engine {
	// -----------------   ESSENTIAL WINDOW OBJECTS   -----------------

	Mix_Chunk* click_press_sound;
	Mix_Chunk* click_release_sound;

	SDL_Window* window;
	int window_width, window_height;
	SDL_Renderer* renderer;

	SDL_Event sdl_event;
	Input input;

	Uint32 frame_start, frame_duration;
	double frame_rate;
	Uint32 frame_delay;
	double frame_factor; // = frame_rate / 60.0
	double frame_factor_inverse; // = 60.0 / frame_rate

	bool running;
	bool running_game;

	RunDrawAndPostDrawRunMethods* methods_pointer = nullptr;






	// -----------------   SCENES DATA STRUCTURE   -----------------
	
	int scene;






	// -----------------   DEBUG VIEW OPTIONS   -----------------
	
	bool camera_view = 1;
	bool debug_data_container_view = 1;






	// -----------------   CAMERA DATA STRUCTURE   -----------------

	Camera* blank_camera;
	Camera* debug_camera;
	vector<Camera*> cameras;






	// -----------------   TEXTURE DATA STRUCTURE   -----------------

	vector<Texture*> textures;

	Texture* solid_color_pixel_texture;
	Texture* solid_color_circle_8_texture;
	Texture* solid_color_circle_32_texture;
	Texture* example_texture;
	Texture* corner_outline_t;
	Texture* camera_icon_t;
	Texture* pause_icon_t;
	Texture* play_icon_t;
	Texture* example_button_released_t;
	Texture* example_button_hovering_t;
	Texture* example_button_pressed_t;

	Texture* boundary_view_released_t;
	Texture* boundary_view_hovering_t;
	Texture* boundary_view_pressed_t;

	Texture* test_t;






	// -----------------   SPRITE QUEUE DATA STRUCTURE   -----------------

	vector<QueueSpriteQueue> sprite_queue;






	// -----------------   DEBUG DATA CONTAINER STRUCTURE   -----------------
	
	DebugDataContainer engine_debug_data_container;

	bool first_frame_selected_debug_data_container = 0;
	DebugDataContainer* selected_debug_data_container;

	TextBox debug_data_container_name_text_box;
	TextBox debug_data_text_box;

	vector<DebugDataContainer*> order;


	vector<RectStructOne> saved_label_rects;

	vector<DebugDataContainer*> saved_container_path;
	vector<size_t> saved_container_name_sizes;

	Rectangle container_path_rectangle; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	TextBox container_path_text_box; //CURRENTLY CANNOT SCALE WITH RESOLUTION

	RectStructOne saved_highlighted_path_item; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	bool highlighting_path_item = 0;






	// -----------------   UI ELEMENTS   -----------------

	Font default_font;

	Button boundary_view_button;

	double scroll_bar_thickness;
	ScrollBar debug_data_scroll_bar;






	// -----------------   MOUSE LAYER FRAMEWORK   -----------------

	vector<MouseLayer*> mouse_layers;

	MouseLayer always_activated_layer;
	MouseLayer always_deactivated_layer;

	MouseLayer debug_data_container_layer;
	MouseLayer visual_button_layer;
	MouseLayer debug_data_scroll_bar_layer;
	MouseLayer container_path_display_layer;

	//1 for whitelist, 0 for blacklist
	void DeactivateMouseLayers(const bool white_list, vector<MouseLayer*> target_layers);

	

	


	// 	-----------------   CONSTRUCTORS/DESTRUCTORS   -----------------

	Engine();
	~Engine();






	// -----------------   DEFAULT UPDATE FUNCTIONS   -----------------

	void UpdateTextBox(TextBox* param_text_box);
	void UpdatePressData(PressData* param_press_data, Rectangle* param_hitbox, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	void UpdateButtonSounds(PressData* const press_data, ButtonSoundData* const sounds) const;
	void UpdateButton(Button* param_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	void UpdateTextButton(TextButton* param_text_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	void UpdateSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	void UpdateScrollBar(ScrollBar* param_scroll_bar, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	//"camera" is used to determine if the tool_tip goes out of visible range. If this happens, the tool_tip is moved to visible range. Also, make sure to move "camera" BEFORE this function is called if it will move this frame.
	void UpdateToolTip(ToolTip* const param_tool_tip, Camera* const camera);






	// -----------------   DRAWING FUNCTIONS   -----------------

	//Draws a solid-color rectangle
	void DrawRectangle(Rectangle* param_rectangle, SDL_Color color, Camera* camera);
	void DrawRectangleScaledBorder(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void DrawRectangleScaledBorderScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void DrawRectangleScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void DrawRectangleOutline(Rectangle* param_rectangle, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void DrawRectangleEx(Rectangle* param_rectangle, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);

	void DrawRectStructOne(RectStructOne* param_rect_struct_one, SDL_Color color, Camera* camera);


	//Draws a point (used mainly for DEBUG)
	void DrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera);

	//Draws a texture that has been mapped onto a rectangle
	void DrawTexture(Texture* texture, Camera* camera, Rectangle* param_rectangle);

	//Basic draws a texture using the data from "sprite"
	void DrawSprite(Sprite* sprite, Camera* camera);

	//Default basic drawing progression for a text box
	void DrawTextBox(TextBox* param_text_box, Camera* camera);
	//Default basic drawing progression for a button
	void DrawButton(Button* param_button, Camera* camera);
	//Default basic drawing progression for a text button
	void DrawTextButton(TextButton* param_text_button, Camera* camera);
	//Default basic drawing progression for a simple text button
	void DrawSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera);

	//Adds a queue sprite to the sprite queue
	void DrawQueueSprite(QueueSprite* param_sprite);

	void DrawScrollBar(ScrollBar* param_scroll_bar, Camera* camera);

	void DrawToolTip(ToolTip* const param_tool_tip, Camera* const camera);






	// -----------------   RANDOM STUFFS   -----------------

	std::random_device rd;
	std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()

	//Includes both min and max in the range of possible return values
	double GetRandDouble(const double min, double max);
	//Includes both min and max in the range of possible return values
	int GetRandInt(const int min, const int max);



	


	// -----------------   MISCELLANEOUS FUNCTIONS   -----------------

	void Run();
	void LoadEngineTexture(Texture* param_texture, const char path[]);
	void UnloadEngineSoundChunk(Mix_Chunk** const param_chunk);
	Camera* NewCamera(const char* const name);
	Point2D GetMousePos(Camera* reference_camera);






	// -----------------   OBSELETE FUNCTIONS   -----------------




private:  // -----------------   P R I V A T E   S E C T I O N   -----------------

	// -----------------   DEBUG TOOL VARIABLES   -----------------

	bool debug_mode;
	bool boundary_view;





	// -----------------   ORGANIZATIONAL FUNCTIONS   -----------------

	void LoadEngineTextures();
	void DeleteEngineTextures();
	void LoadEngineSounds();
	void DeleteEngineSounds();
	void UpdateInput();
	void MoveDebugCamera();
	void UpdateCameraLabels();
	void UpdateDebugData();
	void DrawDebugData();
	void DrawDebugDataContainer(DebugDataContainer* const param_debug_data_container);

	void GenerateContainerOrder(const bool generate_colors);

	void UpdateContainerPathTextBox();

	void SetDebugDataScrollBarLength();





	// -----------------   BASIC DRAWING FUNCTIONS   -----------------

	//Draws the screen! Calls all the drawing functions needed by the engine
	void DrawScreen();

	//Draws all queue sprites in queue. Is called at the end of each frame
	void DrawQueue();

	//Basic draws a solid-color rectangle
	void BasicBasicDrawRectangle(Rectangle* param_rectangle, SDL_Color color, Camera* camera);
	void BasicDrawRectangle(Rectangle* param_rectangle, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleScaledBorder(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void BasicDrawRectangleScaledBorderScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleScaledShadow(Rectangle* param_rectangle, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleOutline(Rectangle* param_rectangle, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);

	void BasicDrawRectStructOne(RectStructOne* param_rect_struct_one, SDL_Color color, Camera* camera);


	void ScaleDebugLabel(DebugLabel* const param_debug_label);
	void AlignDebugLabelAndPushbackToSavedLabelRects(DebugLabel* const param_debug_label);

	void UpdateDebugLabelPos(DebugLabel* const param_debug_label);
	void UpdateDebugLabelPosWithTargetPos(DebugLabel* const param_debug_label, const Point2D param_bottom_left_point);
	void BasicDrawDebugLabel(DebugLabel* const param_debug_label);

	//Basic draws a point (used mainly for DEBUG)
	void BasicDrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera);

	//Basic draws a texture that has been mapped onto a rectangle
	void BasicDrawTexture(const Texture* const texture, const Camera* const camera, const Rectangle* const param_rectangle);

	//Basic draws a texture using the data from "sprite"
	void BasicDrawSprite(Sprite* sprite, Camera* camera);

	void BasicDrawTextBoxData(TextBoxData* param_text_box, Camera* camera);
	//Default basic drawing progression for a text box
	void BasicDrawTextBox(TextBox* param_text_box, Camera* camera);

	//Default basic drawing progression for a button
	void BasicDrawButton(Button* param_button, Camera* camera);

	//Default basic drawing progression for a text button
	void BasicDrawTextButton(TextButton* param_text_button, Camera* camera);

	//Default basic drawing progression for a simple text button
	void BasicDrawSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera);

	void BasicDrawScrollBar(ScrollBar* param_scroll_bar, Camera* camera);






	// -----------------   MISCELLANEOUS FUNCTIONS   -----------------
	
	void ActivateAllMouseLayers();






	// -----------------   OBSELETE FUNCTIONS   -----------------
};