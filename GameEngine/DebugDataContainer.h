#pragma once
#include "DebugLabel.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct IndexedBool
{
	bool* data_value;
	const char* data_name;
	int index;
};
struct IndexedChar
{
	char* data_value;
	const char* data_name;
	int index;
};
struct IndexedInt
{
	int* data_value;
	const char* data_name;
	int index;
};
struct IndexedFloat
{
	float* data_value;
	const char* data_name;
	int index;
};
struct IndexedDouble
{
	double* data_value;
	const char* data_name;
	int index;
};
struct IndexedString
{
	string* data_value;
	const char* data_name;
	int index;
};
struct IndexedConstChar
{
	const char* data_value;
	const char* data_name;
	int index;
};

struct IndexedRigidCentering
{
	RigidCentering* data_value;
	const char* data_name;
	int index;
};
struct IndexedPoint2D
{
	Point2D* data_value;
	const char* data_name;
	int index;
};
struct IndexedSize2D
{
	Size2D* data_value;
	const char* data_name;
	int index;
};
struct IndexedRectangleData
{
	RectangleOld* data_value;
	const char* data_name;
	int index;
};

struct DebugDataContainer
{
	RectangleOld* clickable_rectangle;


	vector<IndexedBool> bools;
	vector<IndexedChar> chars;
	vector<IndexedInt> ints;
	vector<IndexedFloat> floats;
	vector<IndexedDouble> doubles;
	vector<IndexedConstChar> const_chars;
	vector<IndexedString> strings;

	vector<IndexedRigidCentering> rigid_centerings;
	vector<IndexedPoint2D> point_2ds;
	vector<IndexedSize2D> size_2ds;
	vector<IndexedRectangleData> rectangle_datas;


	vector<DebugDataContainer*> owned_data;
	vector<DebugDataContainer*> owners;

	bool white_list;
	vector<int> active_scenes;

	

	int current_length;



	SDL_Color fill_color;
	SDL_Color outline_color;

	bool hovering = 0;




	DebugLabel label;

	bool camera_container = 0;




	DebugDataContainer();

	~DebugDataContainer();

	void InitLeast(const vector<DebugDataContainer*> param_owners, Font* default_label_font, const char* const param_label_chars, RectangleOld* const param_clickable_rectangle, const vector<int> param_active_scenes, const bool param_white_list);
	void InitMost(const vector<DebugDataContainer*> param_owners, Font* default_label_font, const char* const param_label_chars, RectangleOld* const param_clickable_rectangle, const vector<int> param_active_scenes, const bool param_white_list, const double param_label_text_scale, const double param_label_scaled_margin_size);

	void AddBool(bool* value, const char* const value_name);
	void AddChar(char* value, const char* const value_name);
	void AddInt(int* value, const char* const value_name);
	void AddFloat(float* value, const char* const value_name);
	void AddDouble(double* value, const char* const value_name);
	void AddConstChar(const char* const value, const char* const value_name);
	void AddString(string* value, const char* const value_name);

	void AddRigidCentering(RigidCentering* value, const char* const value_name);
	void AddPoint2D(Point2D* value, const char* const value_name);
	void AddSize2D(Size2D* value, const char* const value_name);
	void AddRectangleData(RectangleOld* value, const char* const value_name);

	bool IsActive(const int current_scene);

	void ListVectorData();
};