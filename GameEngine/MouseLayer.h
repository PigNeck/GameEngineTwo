#pragma once
#include <vector>

using namespace std;

struct MouseLayer
{
	//Is set to 1 at the start of each run cycle
	bool active = 0;

	//Find the engine_mouse_layer_vector at e->mouse_layers. This function adds the mouse layer to the engine_mouse_layer_vector. All the members of this vector are set to active at the beginning of each run cycle.
	void Init(vector<MouseLayer*>* param_engine_mouse_layer_vector);
};

