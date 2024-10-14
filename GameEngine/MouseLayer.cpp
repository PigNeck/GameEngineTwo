#include "MouseLayer.h"

void MouseLayer::Init(vector<MouseLayer*>* param_engine_mouse_layer_vector)
{
	param_engine_mouse_layer_vector->push_back(this);
}