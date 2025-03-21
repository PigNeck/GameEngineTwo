#pragma once
#include "TextBox.h"
#include "Sprite.h"
#include <vector>

using namespace std;

struct Camera {
	RectangleOld rect;
	DebugDataContainer debug_data_container;
};

struct CameraNew {
	RefRectangleNewest rect;
};