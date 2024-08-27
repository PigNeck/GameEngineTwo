#include "DebugDataContainer.h"

DebugDataContainer::DebugDataContainer()
{
	clickable_rectangle_data = nullptr;

	bools = vector<IndexedBool>{};
	chars = vector<IndexedChar>{};
	ints = vector<IndexedInt>{};
	floats = vector<IndexedFloat>{};
	doubles = vector<IndexedDouble>{};

	point_2ds = vector<IndexedPoint2D>{};
	size_2ds = vector<IndexedSize2D>{};
	rectangle_datas = vector<IndexedRectangleData>{};


	owned_data = vector<DebugDataContainer*>{};
	owners = vector<DebugDataContainer*>{};


	white_list = 1;
	active_scenes = vector<int>{};


	current_length = 0;
}

DebugDataContainer::~DebugDataContainer()
{
	for (int i = 0; i < owned_data.size(); i++)
	{
		owned_data[i]->owners.erase(std::remove(owned_data[i]->owners.begin(), owned_data[i]->owners.end(), this), owned_data[i]->owners.end());
	}

	for (int i = 0; i < owners.size(); i++)
	{
		owners[i]->owned_data.erase(std::remove(owners[i]->owned_data.begin(), owners[i]->owned_data.end(), this), owners[i]->owned_data.end());
	}

	owned_data.clear();
	owners.clear();
}

void DebugDataContainer::Init(const vector<DebugDataContainer*> param_owners, Font* default_label_font, const char* const param_label_chars, RectangleData* const param_clickable_rectangle_data, const vector<int> param_active_scenes)
{
	owners = param_owners;

	clickable_rectangle_data = param_clickable_rectangle_data;

	active_scenes = param_active_scenes;


	for (int i = 0; i < owners.size(); i++)
	{
		owners[i]->owned_data.push_back(this);
	}


	if (default_label_font && param_label_chars && clickable_rectangle_data)
	{
		label.InitWithDescribingRectangleData(default_label_font, clickable_rectangle_data, param_label_chars, 4.0, 4.0);
	}
}

void DebugDataContainer::AddBool(bool* value, const char* const value_name)
{
	bools.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddChar(char* value, const char* const value_name)
{
	chars.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddInt(int* value, const char* const value_name)
{
	ints.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddFloat(float* value, const char* const value_name)
{
	floats.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddDouble(double* value, const char* const value_name)
{
	doubles.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddConstChar(const char* const value, const char* const value_name)
{
	const_chars.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddString(string* value, const char* const value_name)
{
	strings.push_back({ value, value_name, current_length });

	current_length++;
}

void DebugDataContainer::AddRigidCentering(RigidCentering* value, const char* const value_name)
{
	rigid_centerings.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddPoint2D(Point2D* value, const char* const value_name)
{
	point_2ds.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddSize2D(Size2D* value, const char* const value_name)
{
	size_2ds.push_back({ value, value_name, current_length });

	current_length++;
}
void DebugDataContainer::AddRectangleData(RectangleData* value, const char* const value_name)
{
	rectangle_datas.push_back({ value, value_name, current_length });

	current_length++;
}

bool DebugDataContainer::IsActive(const int current_scene)
{
	if (white_list)
	{
		return (find(active_scenes.begin(), active_scenes.end(), current_scene) != active_scenes.end());
	}
	else
	{
		return (find(active_scenes.begin(), active_scenes.end(), current_scene) == active_scenes.end());
	}
}

void DebugDataContainer::ListVectorData()
{
	for (int i = 0; i < owned_data.size(); i++)
	{
		cout << "owned_data[" << i << "]: " << "\n";
	}
	for (int i = 0; i < owners.size(); i++)
	{
		cout << "owners[" << i << "]: " << "\n";
	}
}