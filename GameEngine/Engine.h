#pragma once
#include "Rectangle.h"
#include "RectangleNew.h"
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
#include <array>

struct RunDrawAndPostDrawRunMethods
{
	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void PostDrawRun() = 0;

	virtual ~RunDrawAndPostDrawRunMethods() = default;
};

struct Engine {
	// -----------------   ESSENTIAL WINDOW OBJECTS   -----------------

	Mix_Chunk* click_press_sound = nullptr;
	Mix_Chunk* click_release_sound = nullptr;

	//Set in constructor
	SDL_Window* window = nullptr;
	int window_width = 0;
	int window_height = 0;

	SDL_GLContext gl_context;
	/*
	const char* const vertex_shader_source = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
	TexCoord = aTexCoord;
}
)";
    */
	
	const char* const vertex_shader_source = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 projection;

out vec2 TexCoord;

void main() {
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
	TexCoord = aTexCoord;
}
)";

	const char* const fragment_shader_source = R"(
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform bool useTexture;    // Flag to enable/disable texturing
uniform vec4 colorMod;    // Color for untextured quads

void main() {
    if (useTexture) {
        vec4 texColor = texture(ourTexture, TexCoord); // Sample from texture
        FragColor = texColor * colorMod; 
    } else {
        FragColor = colorMod; // Use solid color
    }
}
)";

	unsigned int rect_indices[6] = {
		0, 1, 2, // First triangle
		2, 3, 0  // Second triangle
	};

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	GLuint vertex_shader = 0;
	GLuint fragment_shader = 0;
	GLuint shader_program = 0;

	array<float, 16> ortho_matrix = {};




	RectangleOld testing_rect;
	Texture testing_texture;



	SDL_Event sdl_event = SDL_Event();
	Input input;

	Uint32 frame_start = 0;
	Uint32 frame_duration = 0;
	double frame_rate = 144.0;
	double frame_factor = frame_rate / 60.0; // = frame_rate / 60.0
	double frame_factor_inverse = 60.0 / frame_rate; // = 60.0 / frame_rate
	Uint32 frame_delay = (Uint32)(1000.0 / frame_rate);

	bool running = 1;
	bool running_game = 1;

	RunDrawAndPostDrawRunMethods* methods_pointer = nullptr;


	float additional_color_index = 0.0;
	SDL_PixelFormat* rgba = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	SDL_Texture* pixel_access_texture = nullptr;






	// -----------------   SCENES DATA STRUCTURE   -----------------
	
	int scene = 1;






	// -----------------   DEBUG VIEW OPTIONS   -----------------
	
	bool camera_view = 1;
	bool debug_data_container_view = 1;






	// -----------------   CAMERA DATA STRUCTURE   -----------------

	Camera* blank_camera = nullptr;
	Camera* debug_camera = nullptr;
	vector<Camera*> cameras;






	// -----------------   TEXTURE DATA STRUCTURE   -----------------

	vector<Texture*> textures;

	Texture* default_texture = nullptr;

	Texture* solid_color_pixel_texture = nullptr;
	Texture* solid_color_circle_8_texture = nullptr;
	Texture* solid_color_circle_32_texture = nullptr;
	Texture* example_texture = nullptr;
	Texture* corner_outline_t = nullptr;
	Texture* camera_icon_t = nullptr;
	Texture* pause_icon_t = nullptr;
	Texture* play_icon_t = nullptr;
	Texture* example_button_released_t = nullptr;
	Texture* example_button_hovering_t = nullptr;
	Texture* example_button_pressed_t = nullptr;

	Texture* boundary_view_released_t = nullptr;
	Texture* boundary_view_hovering_t = nullptr;
	Texture* boundary_view_pressed_t = nullptr;

	Texture* test_t = nullptr;

	Texture* distinguishing_sides_t = nullptr;






	// -----------------   SPRITE QUEUE DATA STRUCTURE   -----------------

	vector<QueueSpriteQueue> sprite_queue;






	// -----------------   DEBUG DATA CONTAINER STRUCTURE   -----------------
	
	DebugDataContainer engine_debug_data_container;

	bool first_frame_selected_debug_data_container = 0;
	DebugDataContainer* selected_debug_data_container = nullptr;

	TextBox debug_data_container_name_text_box;
	TextBox debug_data_text_box;

	vector<DebugDataContainer*> order;


	vector<RectStructOne> saved_label_rects;

	vector<DebugDataContainer*> saved_container_path;
	vector<size_t> saved_container_name_sizes;

	RectangleOld container_path_rectangle; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	TextBox container_path_text_box; //CURRENTLY CANNOT SCALE WITH RESOLUTION

	RectStructOne saved_highlighted_path_item; //CURRENTLY CANNOT SCALE WITH RESOLUTION
	bool highlighting_path_item = 0;






	// -----------------   UI ELEMENTS   -----------------

	Font default_font;

	Button boundary_view_button;

	double scroll_bar_thickness = 0.0;
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
	//IMPORTANT!!!: Even if non-hoverable, if mouse is overlapping with hitbox, mouse_layers will be removed. To avoid this, simply don't call the function and call press_data.Reset(...) as needed.
	void UpdatePressData(PressData* param_press_data, RectangleOld* param_hitbox, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	void UpdateButtonSounds(PressData* const press_data, ButtonSoundData* const sounds) const;
	//IMPORTANT!!!: Even if non-hoverable, if mouse is overlapping with hitbox, mouse_layers will be removed. To avoid this, simply don't call the function and call press_data.Reset(...) as needed.
	void UpdateButton(Button* param_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	//IMPORTANT!!!: Even if non-hoverable, if mouse is overlapping with hitbox, mouse_layers will be removed. To avoid this, simply don't call the function and call press_data.Reset(...) as needed.
	void UpdateTextButton(TextButton* param_text_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	//IMPORTANT!!!: Even if non-hoverable, if mouse is overlapping with hitbox, mouse_layers will be removed. To avoid this, simply don't call the function and call press_data.Reset(...) as needed.
	void UpdateSimpleTextButton(SimpleTextButton* param_simple_text_button, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	void UpdateScrollBar(ScrollBar* param_scroll_bar, Camera* camera, MouseLayer* mouse_layer, const bool mouse_layer_removal_white_list, vector<MouseLayer*> mouse_layer_removal_target_layers);
	//IMPORTANT!!!(ish): Firstly, it is recommended that this function is unintuitively called in a "DrawScene_()" function rather than in an "UpdateScene_()" function unless some code requires that the position of the tool_tip->saved_box or tool_tip->text_box is updated in the "UpdateScene_()" function. This is because the engine calls the appropriate run function, waits the remainder of the frame, and then calls the appropriate draw function. If the mouse position is updated in the "in-between" time, the tool tip will lag an additional one frame behind (very sad). Unfortunately, there is some required delay between when the tool is drawn to the sdl_canvas and when it appears on the screen that I have no control over. Secondly "camera" is used to determine if the tool_tip goes out of visible range. If this happens, the tool_tip is moved to visible range. Also, make sure to move "camera" BEFORE this function is called if it will move this frame.
	void UpdateToolTip(ToolTip* const param_tool_tip, Camera* const camera);






	// -----------------   DRAWING FUNCTIONS   -----------------

	//Draws a solid-color rectangle
	void DrawRectangle(RectangleOld* param_rectangle, SDL_Color color, Camera* camera);
	void DrawRectangleScaledBorder(RectangleOld* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void DrawRectangleScaledBorderScaledShadow(RectangleOld* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void DrawRectangleScaledShadow(RectangleOld* param_rectangle, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void DrawRectangleOutline(RectangleOld* param_rectangle, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void DrawRectangleEx(RectangleOld* param_rectangle, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);

	void DrawRectStructOne(RectStructOne* param_rect_struct_one, SDL_Color color, Camera* camera);


	//Draws a point (used mainly for DEBUG)
	void DrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera);

	//Draws a texture that has been mapped onto a rectangle
	void DrawTexture(Texture* texture, Camera* camera, RectangleOld* param_rectangle);

	//Basic draws a texture using the data from "sprite"
	void DrawSprite(Sprite* sprite, Camera* camera);

	//Default basic drawing progression for a text box
	void DrawTextBox(TextBox* param_text_box, Camera* camera);
	void DrawBasicTextBox(const BasicTextBox* const text_box, const CameraNew* const camera);
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
	void LoadEngineTexture(Texture** const param_texture, const char* path);
	void UnloadEngineSoundChunk(Mix_Chunk** const param_chunk);
	Camera* NewCamera(const char* const name);
	//Returns the top left of the mouse pos pixel as a Point2D
	Point2D GetMousePos(Camera* const reference_camera);
	//NOTE: A pizel_size_vertical value of 0 = TOP, 1 = middle, and 2 = BOTTOM (This follows the traditional computer graphics standard rather than the typical mathematical standard) ---- A pixel_size_horizontal value of 0 = left side, 1 = middle and 2 = right side
	Point2D GetMousePos(Camera* const reference_camera, const RigidCentering pixel_side_horizontal, const RigidCentering pixel_side_vertical);






	// -----------------   OBSELETE FUNCTIONS   -----------------




private:  // -----------------   P R I V A T E   S E C T I O N   -----------------

	// -----------------   DEBUG TOOL VARIABLES   -----------------

	bool debug_mode = 0;
	bool boundary_view = 0;





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
	void BasicBasicDrawRectangle(RectangleOld* param_rectangle, SDL_Color color, Camera* camera);
	void BasicDrawRectangle(RectangleOld* param_rectangle, SDL_Color filling_color, double right_border_scaled_size, RigidCentering right_border_centering, double bottom_border_scaled_size, RigidCentering bottom_border_centering, double left_border_scaled_size, RigidCentering left_border_centering, double top_border_scaled_size, RigidCentering top_border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleScaledBorder(RectangleOld* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);
	void BasicDrawRectangleScaledBorderScaledShadow(RectangleOld* param_rectangle, SDL_Color filling_color, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleScaledShadow(RectangleOld* param_rectangle, SDL_Color filling_color, Point2D shadow_scaled_offset, SDL_Color shadow_color, Camera* camera);
	void BasicDrawRectangleOutline(RectangleOld* param_rectangle, double border_scaled_size, RigidCentering border_centering, SDL_Color border_color, Camera* camera);

	void BasicDrawRectStructOne(RectStructOne* param_rect_struct_one, SDL_Color color, Camera* camera);


	void ScaleDebugLabel(DebugLabel* const param_debug_label);
	void AlignDebugLabelAndPushbackToSavedLabelRects(DebugLabel* const param_debug_label);

	void UpdateDebugLabelPos(DebugLabel* const param_debug_label);
	void UpdateDebugLabelPosWithTargetPos(DebugLabel* const param_debug_label, const Point2D param_bottom_left_point);
	void BasicDrawDebugLabel(DebugLabel* const param_debug_label);

	//Basic draws a point (used mainly for DEBUG)
	void BasicDrawPoint(Point2D* param_point, Size2D param_size, SDL_Color color, Camera* camera);

	//Basic draws a texture that has been mapped onto a rectangle
	void BasicDrawTexture(const Texture* const texture, const GLColor* const color_and_alpha_mod, const Camera* const camera, const RectangleOld* const param_rectangle);

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









public: // -----------------   RECTANGLENEW FUNCTIONS   -----------------

	void DrawSDLRectWithRotation(const SDL_RectWithRotation* const rect, const SDL_Color fill_color);
	void DrawTextureWithSDLRectWithRotation(const SDL_RectWithRotation* const rect, const Texture* texture, const SDL_Rect* source_rect, const SDL_Color* color_and_alpha_mod);


	void DrawRectangleNew(const RectangleNew* const rect, const SDL_Color fill_color, Camera* const camera);
	void DrawTextureWithRectangleNew(const RectangleNew* const rect, const Texture* texture, const SDL_Rect* source_rect, const SDL_Color* color_and_alpha_mod, Camera* const camera);

	void DrawRectangleNew(const Point2DNew* const pos, const Size2DNew* const unscaled_size, const Scale2DNew* const scale, const Centering2DNew* const centering, const Rotation2DNew* const rotation, const TotalFlip* const total_flip, const SDL_Color fill_color, Camera* const camera);
	void DrawTextureWithRectangleNew(const Point2DNew* const pos, const Size2DNew* const unscaled_size, const Scale2DNew* const scale, const Centering2DNew* const centering, const Rotation2DNew* const rotation, const TotalFlip* const total_flip, const Texture* texture, const SDL_Rect* source_rect, const SDL_Color* color_and_alpha_mod, Camera* const camera);


	void DrawRefRectangleNew(const RefRectangleNew* const rect, const SDL_Color fill_color, Camera* const camera);
	void DrawTextureWithRefRectangleNew(const RefRectangleNew* const rect, const Texture* texture, const SDL_Rect* source_rect, const SDL_Color* color_and_alpha_mod, Camera* const camera);

	void DrawRefRectangleNew(const RefPoint2DNew* const pos, const Size2DNew* const unscaled_size, const RefScale2DNew* const scale, const Centering2DNew* const centering, const RefRotation2DNew* const rotation, const RefTotalFlip* const total_flip, const SDL_Color fill_color, Camera* const camera);
	void DrawTextureWithRefRectangleNew(const RefPoint2DNew* const pos, const Size2DNew* const unscaled_size, const RefScale2DNew* const scale, const Centering2DNew* const centering, const RefRotation2DNew* const rotation, const RefTotalFlip* const total_flip, const Texture* texture, const SDL_Rect* source_rect, const SDL_Color* color_and_alpha_mod, Camera* const camera);


	void DrawRefRectangleNewNew(const RefRectangleNewNew* const rect, const SDL_Color fill_color, Camera* const camera);
	void DrawTextureWithRefRectangleNewNew(const RefRectangleNewNew* const rect, const Texture* texture, const SDL_Rect* source_rect, const SDL_Color* color_and_alpha_mod, Camera* const camera);

	void DrawRefRectangleNewNew(const RefPoint2DNewNew* const pos, const RefSize2DNewNew* const unscaled_size, const RefScale2DNewNew* const scale, const Centering2DNew* const centering, const RefRotation2DNewNew* const rotation, const RefTotalFlip* const total_flip, const SDL_Color fill_color, Camera* const camera);
	void DrawTextureWithRefRectangleNewNew(const RefPoint2DNewNew* const pos, const RefSize2DNewNew* const unscaled_size, const RefScale2DNewNew* const scale, const Centering2DNew* const centering, const RefRotation2DNewNew* const rotation, const RefTotalFlip* const total_flip, const Texture* texture, const SDL_Rect* source_rect, const SDL_Color* color_and_alpha_mod, Camera* const camera);





	// ------------ RectangleNewest functions -------------

	void DrawScreenQuad(const Quad* const screen_quad, const GLColor* color, const bool align_90=1) const;
	void DrawTexturedScreenQuad(const Quad* const screen_quad, const Texture* const texture, const GLColor* color_and_alpha_mod, const bool align_90=1) const;

	void DrawQuad(const Quad* const quad, const GLColor* const color, const CameraNew* const camera);
	void DrawTexturedQuad(const Quad* const quad, const Texture* const texture, const GLColor* const color_and_alpha_mod, const CameraNew* const camera);

	void DrawTextureWithRefRectangleNewest(const RefRectangleNewest* const rect, const Texture* const texture, const SDL_Rect* const source_rect, const SDL_Color* const color_and_alpha_mod, const CameraNew* const camera);

	//void DrawTexturedRefRectangle90(const RefRectangle90* const rect, const Texture* const texture, const SDL_Rect* const source_rect, const SDL_Color* const color_and_alpha_mod, const CameraNew* const camera);








	void ModifyPixels(SDL_Texture* texture);
};