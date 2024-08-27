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

struct Program;

struct Engine {
	// -----------------   ESSENTIAL WINDOW OBJECTS   -----------------

	SDL_Window* window;
	int window_width, window_height;
	SDL_Renderer* renderer;

	SDL_Event sdl_event;
	Input input;

	Uint32 frame_start, frame_duration;
	double frame_rate;
	Uint32 frame_delay;
	double frame_factor;

	bool running;
	bool running_game;

	Program* p;
	void (Program::* RunPointer)();
	void (Program::* DrawPointer)();
	void (Program::* PostDrawRunPointer)();






	// -----------------   SCENES DATA STRUCTURE   -----------------
	
	int scene;






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






	// -----------------   UI ELEMENTS   -----------------

	Font default_font;

	Button boundary_view_button;

	double scroll_bar_thickness;
	ScrollBar debug_data_scroll_bar;

	bool found_mouse_layer = 0;
	string current_mouse_layer = "";

	

	


	// 	-----------------   CONSTRUCTORS/DESTRUCTORS   -----------------

	Engine();
	~Engine();






	// -----------------   DEFAULT UPDATE FUNCTIONS   -----------------

	void UpdateTextBox(TextBox* param_text_box);
	void UpdatePressData(PressData* param_press_data, RectangleData* param_hitbox_data, Camera* camera, const int mouse_layer);
	void UpdateButton(Button* param_button, Camera* camera, const int mouse_layer);
	void UpdateTextButton(TextButton* param_text_button, Camera* camera, const int mouse_layer);
	void UpdateSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera, const int mouse_layer);
	void UpdateScrollBar(ScrollBar* param_scroll_bar, Camera* camera, const int mouse_layer);






	// -----------------   DRAWING FUNCTIONS   -----------------

	//Draws a solid-color rectangle
	void DrawRectangle(RectangleData* param_rectangle_data, SDL_Color color, Camera* camera);
	void DrawRectangleScaledBorder(RectangleData* param_rectangle_data, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void DrawRectangleScaledBorderScaledShadow(RectangleData* param_rectangle_data, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void DrawRectangleScaledShadow(RectangleData* param_rectangle_data, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void DrawRectangleOutline(RectangleData* param_rectangle_data, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void DrawRectangleEx(RectangleData* param_rectangle_data, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);

	//Draws a point (used mainly for DEBUG)
	void DrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera);

	//Draws a texture that has been mapped onto a rectangle
	void DrawTexture(Texture* texture, Camera* camera, RectangleData* param_rectangle_data);

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






	// -----------------   MISCELLANEOUS FUNCTIONS   -----------------

	void Run();
	void LoadEngineTexture(Texture* param_texture, const char path[]);
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
	void UpdateInput();
	void MoveDebugCamera();
	void UpdateDebugData();
	void DrawDebugData();
	void DrawDebugDataContainer(DebugDataContainer* const param_debug_data_container);

	void GenerateContainerOrder(const bool generate_colors);





	// -----------------   BASIC DRAWING FUNCTIONS   -----------------

	//Draws the screen! Calls all the drawing functions needed by the engine
	void DrawScreen();

	//Draws all queue sprites in queue. Is called at the end of each frame
	void DrawQueue();

	//Basic draws a solid-color rectangle
	void BasicBasicDrawRectangle(RectangleData* param_rectangle_data, SDL_Color color, Camera* camera);
	void BasicDrawRectangle(RectangleData* param_rectangle_data, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleScaledBorder(RectangleData* param_rectangle_data, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void BasicDrawRectangleScaledBorderScaledShadow(RectangleData* param_rectangle_data, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleScaledShadow(RectangleData* param_rectangle_data, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleOutline(RectangleData* param_rectangle_data, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);


	void UpdateDebugLabelPos(DebugLabel* const param_debug_label);
	void BasicDrawDebugLabel(DebugLabel* const param_debug_label);

	//Basic draws a point (used mainly for DEBUG)
	void BasicDrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera);

	//Basic draws a texture that has been mapped onto a rectangle
	void BasicDrawTexture(Texture* texture, Camera* camera, RectangleData* param_rectangle_data);

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
	
	//BLANK






	// -----------------   OBSELETE FUNCTIONS   -----------------
};