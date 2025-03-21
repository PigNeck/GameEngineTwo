#include "Program.h"

#define PI 3.14159265

#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080

#define NEW_LINE_WAIT_MULTIPLIER 0.15

#define NUMBER_OF_CHANNELS 16

const double EASE_PARAMETER = 1000.0;
const double EASE_DIVISOR = 2.0 * log(EASE_PARAMETER);
const double FIRST_Y_SHIFT = (1.0 / EASE_PARAMETER) / EASE_DIVISOR;
const double SECOND_Y_SHIFT = (2.0 / EASE_DIVISOR) - FIRST_Y_SHIFT;
const double Y_STRETCH_FACTOR = 1.0 / (SECOND_Y_SHIFT - FIRST_Y_SHIFT);


void TextLink::InitLeast(const size_t param_linked_path_index, const size_t param_linked_portion_index, const size_t param_begin_char, const size_t param_end_char, const char param_link_type)
{
	linked_path_index = param_linked_path_index;
	linked_portion_index = param_linked_portion_index;
	begin_char = param_begin_char;
	end_char = param_end_char;
	link_type = param_link_type;
}



void Bar::SetTargetWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar)
{
	SetTargetWidth(100.0 * (double)discrete_progress / (double)discrete_capacity, light_bar);
}
void Bar::SetTargetWidth(const double percent, const bool light_bar)
{
	target_width = progress_back_rect_pointer->size.width * (percent / 100.0);

	if (light_bar)
	{
		lighting_level = 101.0;
	}
}

void Bar::SetActualWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar)
{
	SetActualWidth(100.0 * (double)discrete_progress / (double)discrete_capacity, light_bar);
}
void Bar::SetActualWidth(const double percent, const bool light_bar)
{
	target_width = progress_back_rect_pointer->size.width * (percent / 100.0);
	progress_rect.size.width = target_width;
	progress_rect.pos.x = (progress_back_rect_pointer->size.width / -2.0) + (progress_rect.size.width / 2.0);

	if (light_bar)
	{
		lighting_level = 101.0;
	}
}


void ProgressBar::SetTargetWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar)
{
	if (bars.size() > size_t(0))
	{
		bars[0]->SetTargetWidth(discrete_progress, discrete_capacity, light_bar);
	}
	else
	{
		cout << "Failed because bars.size() == 0. Try calling BasicInit(...) to fix this issue. Sent by ProgressBar::SetTargetWidth(...)." << endl;
	}
}
void ProgressBar::SetTargetWidth(const double percent, const bool light_bar)
{
	if (bars.size() > size_t(0))
	{
		bars[0]->SetTargetWidth(percent, light_bar);
	}
	else
	{
		cout << "Failed because bars.size() == 0. Try calling BasicInit(...) to fix this issue. Sent by ProgressBar::SetTargetWidth(...)." << endl;
	}
}

void ProgressBar::SetTargetWidthWithIndex(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar, const size_t bar_index)
{
	if (bar_index < bars.size())
	{
		bars[bar_index]->SetTargetWidth(discrete_progress, discrete_capacity, light_bar);
	}
	else
	{
		cout << "bar_index out of range :(. Sent by ProgressBar::SetTargetWidthWithIndex(...)." << endl;
	}
}
void ProgressBar::SetTargetWidthWithIndex(const double percent, const bool light_bar, const size_t bar_index)
{
	if (bar_index < bars.size())
	{
		bars[bar_index]->SetTargetWidth(percent, light_bar);
	}
	else
	{
		cout << "bar_index out of range :(. Sent by ProgressBar::SetTargetWidthWithIndex(...)." << endl;
	}
}

void ProgressBar::SetActualWidth(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar)
{
	if (bars.size() > size_t(0))
	{
		bars[0]->SetActualWidth(discrete_progress, discrete_capacity, light_bar);
	}
	else
	{
		cout << "Failed because bars.size() == 0. Try calling BasicInit(...) to fix this issue. Sent by ProgressBar::SetActualWidth(...)." << endl;
	}
}
void ProgressBar::SetActualWidth(const double percent, const bool light_bar)
{
	if (bars.size() > size_t(0))
	{
		bars[0]->SetActualWidth(percent, light_bar);
	}
	else
	{
		cout << "Failed because bars.size() == 0. Try calling BasicInit(...) to fix this issue. Sent by ProgressBar::SetActualWidth(...)." << endl;
	}
}

void ProgressBar::SetActualWidthWithIndex(const size_t discrete_progress, const size_t discrete_capacity, const bool light_bar, const size_t bar_index)
{
	if (bar_index < bars.size())
	{
		bars[bar_index]->SetActualWidth(discrete_progress, discrete_capacity, light_bar);
	}
	else
	{
		cout << "bar_index out of range :(. Sent by ProgressBar::SetActualWidthWithIndex(...)." << endl;
	}
}
void ProgressBar::SetActualWidthWithIndex(const double percent, const bool light_bar, const size_t bar_index)
{
	if (bar_index < bars.size())
	{
		bars[bar_index]->SetActualWidth(percent, light_bar);
	}
	else
	{
		cout << "bar_index out of range :(. Sent by ProgressBar::SetActualWidthWithIndex(...)." << endl;
	}
}

void ProgressBar::InitLeast()
{
	//Do nothing lamo (you)
}
void ProgressBar::InitMost(const vector<Bar*> param_bars, const RectangleOld param_back_rect, const SDL_Color param_back_color, const RectangleOld param_progress_back_rect, const SDL_Color param_progress_back_color)
{
	bars = param_bars;
	back_rect = param_back_rect;
	back_color = param_back_color;
	progress_back_rect = param_progress_back_rect;
	progress_back_color = param_progress_back_color;
}
void ProgressBar::InitBasic(const Point2D position, const Size2D back_rect_size, const double outline_thickness, const size_t discrete_progress, const size_t discrete_capacity)
{
	back_rect.pos = position;
	back_rect.size = back_rect_size;
	back_rect.base_size = back_rect_size;

	progress_back_rect.size = { back_rect_size.width - (outline_thickness * 2.0), back_rect_size.height - (outline_thickness * 2.0) };

	AddBar(discrete_progress, discrete_capacity);
}
void ProgressBar::InitBasic(const Point2D position, const Size2D back_rect_size, const double outline_thickness, const double percent)
{
	back_rect.pos = position;
	back_rect.size = back_rect_size;
	back_rect.base_size = back_rect_size;

	progress_back_rect.size = { back_rect_size.width - (outline_thickness * 2.0), back_rect_size.height - (outline_thickness * 2.0) };

	AddBar(percent);
}

void ProgressBar::SetDefaultBarColor(const size_t index)
{
	switch (bars.size())
	{
	case 1:
		bars[index]->progress_color = { 0, 200, 0, 255 };
		bars[index]->secondary_progress_color = { 50, 255, 50, 255 };
		break;
	case 2:
		bars[index]->progress_color = { 0, 0, 200, 255 };
		bars[index]->secondary_progress_color = { 50, 50, 255, 255 };
		break;
	case 3:
		bars[index]->progress_color = { 200, 0, 0, 255 };
		bars[index]->secondary_progress_color = { 255, 50, 50, 255 };
		break;
	default:
		bars[index]->progress_color = { 100, 100, 100, 255 };
		bars[index]->secondary_progress_color = { 200, 200, 200, 255 };
	}
}

void ProgressBar::AddBar(const size_t discrete_progress, const size_t discrete_capacity)
{
	bars.push_back(new Bar());
	bars.back()->progress_rect.size.height = progress_back_rect.size.height;
	bars.back()->progress_rect.reference_rectangle = &back_rect;
	bars.back()->progress_back_rect_pointer = &progress_back_rect;

	bars.back()->SetTargetWidth(discrete_progress, discrete_capacity, 0);
	bars.back()->progress_rect.size.width = bars.back()->target_width;

	bars.back()->progress_rect.pos.x = (bars.back()->progress_rect.size.width / 2.0) - (progress_back_rect.size.width / 2.0);

	SetDefaultBarColor(bars.size() - size_t(1));
}
void ProgressBar::AddBar(const double percent)
{
	bars.push_back(new Bar());
	bars.back()->progress_rect.size.height = progress_back_rect.size.height;
	bars.back()->progress_rect.reference_rectangle = &back_rect;
	bars.back()->progress_back_rect_pointer = &progress_back_rect;

	bars.back()->SetTargetWidth(percent, 0);
	bars.back()->progress_rect.size.width = bars.back()->target_width;

	bars.back()->progress_rect.pos.x = (bars.back()->progress_rect.size.width / 2.0) - (progress_back_rect.size.width / 2.0);

	SetDefaultBarColor(bars.size() - size_t(1));
}

ProgressBar::ProgressBar()
{
	back_rect.base_size = { 100.0, 50.0 };
	back_rect.size = { 100.0, 50.0 };

	progress_back_rect.size = { 92.0, 42.0 };
	progress_back_rect.reference_rectangle = &back_rect;
}



void TextPortion::InitLeast(const char* const param_text, const char default_sound_id)
{
	text.clear();
	for (const char* ptr = param_text; *ptr != '\0'; ++ptr) {
		double wait_multiplier = 1.0;
		char sound_id = default_sound_id;
		switch (*ptr)
		{
		case '\n':
			wait_multiplier = NEW_LINE_WAIT_MULTIPLIER;
			sound_id = 0;
			break;
		case ' ':
			wait_multiplier = 1.0;
			sound_id = 0;
			break;
		case '.':
			wait_multiplier = 0.1;
			break;
		case ',':
			wait_multiplier = 0.3;
			break;
		}
		text.push_back({ *ptr, sound_id, wait_multiplier });
	}
}
void TextPortion::InitBack(const char* const param_text, const char default_sound_id, const size_t param_back_path_index, const bool param_back_lesson_select)
{
	InitLeast(param_text, default_sound_id);

	back_path_index = param_back_path_index;
	back_lesson_select = param_back_lesson_select;
}
void TextPortion::InitNext(const char* const param_text, const char default_sound_id, const size_t param_next_path_index, const bool param_next_lesson_select)
{
	InitLeast(param_text, default_sound_id);
	
	next_path_index = param_next_path_index;
	next_lesson_select = param_next_lesson_select;
}
void TextPortion::InitMost(const char* const param_text, const char default_sound_id, const size_t param_back_path_index, const bool param_back_lesson_select, const size_t param_next_path_index, const bool param_next_lesson_select)
{
	InitLeast(param_text, default_sound_id);

	back_path_index = param_back_path_index;
	back_lesson_select = param_back_lesson_select;

	next_path_index = param_next_path_index;
	next_lesson_select = param_next_lesson_select;
}

size_t TextPortion::CharPartOfLink(const size_t char_index)
{
	for (size_t i = 0; i < links.size(); i++)
	{
		if ((char_index >= links[i].begin_char) && (char_index <= links[i].end_char))
		{
			return i;
		}
	}

	return numeric_limits<size_t>::max();
}

TextPortion* CoursePath::GetCurrentPortion()
{
	return portions[current_portion_index];
}



void Program::SetCurrentTextPortionTextBoxProgression(const double target_visable_char_progression)
{
	current_visable_char_progression = target_visable_char_progression;

	//Send warning if current_visable_char_progression is set out of range.
	if (current_visable_char_progression > (double)current_text_portion_text_box.chars.size())
	{
		cout << "Set current_visable_char_progression ABOVE MAX (current_text_portion_text_box.chars.size()). Sent from SetCurrentTextPortionTextBoxProgression(...)" << endl;
	}

	if (current_visable_char_progression >= 0.0)
	{
		const size_t trunc_index = (size_t)current_visable_char_progression;

		for (size_t i = 0; (i <= trunc_index) && (i < current_text_portion_text_box.chars.size()); i++)
		{
			current_text_portion_text_box.chars[i]->a_mod = 255;

		}
	}
}


size_t Program::GetCurrentCoursePathPathDataIndex()
{
	const size_t cpps = course_path_path.size();

	if (removing_progress_bar)
	{
		if (cpps > size_t(1))
		{
			return cpps - size_t(2);
		}
		else
		{
			cout << "course_path_path.size() was 0 or 1 and removing_progress_bar was 1 :(. Sent by Program::GetCurrentCoursePathPathDataIndex()" << endl;
			return numeric_limits<size_t>::max();
		}
	}
	else
	{
		if (cpps > size_t(0))
		{
			return cpps - size_t(1);
		}
		else
		{
			cout << "course_path_path.size() was 0 :(. Sent by Program::GetCurrentCoursePathPathDataIndex()" << endl;
			return numeric_limits<size_t>::max();
		}
	}
}
CoursePathPathData* Program::GetCurrentCoursePathPathData()
{
	const size_t cpps = course_path_path.size();

	if (removing_progress_bar)
	{
		if (cpps > size_t(1))
		{
			return course_path_path[cpps - size_t(2)];
		}
		else
		{
			cout << "course_path_path.size() was 0 or 1 and removing_progress_bar was 1 :(. Sent by Program::GetCurrentCoursePathPathData()" << endl;
			return nullptr;
		}
	}
	else
	{
		if (cpps > size_t(0))
		{
			return course_path_path[cpps - size_t(1)];
		}
		else
		{
			cout << "course_path_path.size() was 0 :(. Sent by Program::GetCurrentCoursePathPathData()" << endl;
			return nullptr;
		}
	}
}
CoursePath* Program::GetCurrentCoursePath()
{
	CoursePathPathData* const current_course_path_path_data = GetCurrentCoursePathPathData();

	if (current_course_path_path_data)
	{
		return current_course_path_path_data->path_pointer;
	}
	else
	{
		cout << "current_course_path_path_data was nullptr :(. Sent by Program::GetCurrentCoursePath()" << endl;
		return nullptr;
	}
}
ProgressBar* Program::GetCurrentCourseProgressBar()
{
	CoursePathPathData* const current_course_path_path_data = GetCurrentCoursePathPathData();

	if (current_course_path_path_data)
	{
		return &current_course_path_path_data->progress_bar;
	}
	else
	{
		cout << "current_course_path_path_data was nullptr :(. Sent by Program::GetCurrentCourseProgressBar()" << endl;
		return nullptr;
	}
}
TextBox* Program::GetCurrentCourseTextBox()
{
	CoursePathPathData* const current_course_path_path_data = GetCurrentCoursePathPathData();

	if (current_course_path_path_data)
	{
		return &current_course_path_path_data->text_box;
	}
	else
	{
		cout << "current_course_path_path_data was nullptr :(. Sent by Program::GetCurrentCourseTextBar()" << endl;
		return nullptr;
	}
}

void Program::UpdateCoursePathTextBox()
{
	course_path_text_box.Clear();
	course_path_text_box.AddCharPtr("Path: ");

	size_t upper_bound;
	if (removing_progress_bar)
	{
		upper_bound = course_path_path.size() - size_t(1);
	}
	else
	{
		upper_bound = course_path_path.size();
	}

	for (size_t i = 0; i < upper_bound; i++)
	{
		if (i != 0)
		{
			course_path_text_box.AddCharPtr(" -> ");
		}

		const char* current_path_name = course_path_path[i]->path_pointer->path_name;

		//Accounting for current_path_name being undefined or nothing
		if (current_path_name)
		{
			if (strlen(current_path_name) == 0)
			{
				current_path_name = "???";
			}
		}
		else
		{
			current_path_name = "???";
		}

		course_path_text_box.AddCharPtr(current_path_name);
	}

	course_path_text_box.UpdateCharPos();
}

void Program::UpdateConfetti()
{
	for (size_t i = 0; i < confetti.size(); i++)
	{
		confetti[i].velocity.x *= pow(0.98, e->frame_factor_inverse);

		confetti[i].velocity.y -= 0.1 * e->frame_factor_inverse;
		confetti[i].velocity.y *= pow(0.98, e->frame_factor_inverse);

		confetti[i].position.x += confetti[i].velocity.x;
		confetti[i].position.y += confetti[i].velocity.y;

		confetti[i].rotation += 1.0;
	}
}
void Program::DrawConfetti(Camera* const camera)
{
	RectangleOld conf_rect;
	conf_rect.size.width = 20.0;
	conf_rect.size.height = 10.0;
	SDL_Color conf_color = { 0, 0, 0, 255 };
	const unsigned char conf_alpha = (unsigned char)round((1.0 - (complete_lesson_cutscene_timer / 2.3)) * 255.0) * (unsigned char)(complete_lesson_cutscene_timer <= 2.3);

	for (size_t i = 0; i < confetti.size(); i++)
	{
		conf_rect.pos = confetti[i].position;
		conf_rect.rotation = confetti[i].rotation;

		switch (confetti[i].color_id)
		{
		case 0:
			conf_color = { 255, 0, 0, conf_alpha };
			break;
		case 1:
			conf_color = { 0, 255, 0, conf_alpha };
			break;
		case 2:
			conf_color = { 0, 0, 255, conf_alpha };
			break;
		case 3:
			conf_color = { 255, 255, 0, conf_alpha };
			break;
		case 4:
			conf_color = { 255, 0, 255, conf_alpha };
			break;
		case 5:
			conf_color = { 0, 255, 255, conf_alpha };
			break;
		}

		e->DrawRectangle(&conf_rect, conf_color, camera);
	}
}

void Program::UpdateProgressBar(ProgressBar* const progress_bar)
{
	for (size_t i = 0; i < progress_bar->bars.size(); i++)
	{
		Bar* const current_bar = progress_bar->bars[i];


		const double diff = current_bar->target_width - current_bar->progress_rect.size.width;
		if (diff != 0.0)
		{
			//Set bar width
			current_bar->progress_rect.size.width += diff * (1.0 - pow((100.0 - current_bar->bar_advance_rate) / 100.0, e->frame_factor_inverse));
			//Set bar x
			current_bar->progress_rect.pos.x = (progress_bar->progress_back_rect.size.width / -2.0) + (current_bar->progress_rect.size.width / 2.0);

			//If diff is negligable, finish the job >:)
			if ((abs(current_bar->target_width - current_bar->progress_rect.size.width) / progress_bar->progress_back_rect.size.width) < 0.0001)
			{
				//Set bar width
				current_bar->progress_rect.size.width = current_bar->target_width;
				//Set bar x
				current_bar->progress_rect.pos.x = (progress_bar->progress_back_rect.size.width / -2.0) + (current_bar->progress_rect.size.width / 2.0);
			}
		}

		if (current_bar->lighting_level != 0.0)
		{
			if (current_bar->lighting_level > 100.0)
			{
				current_bar->lighting_level = 100.0;
			}
			else
			{
				current_bar->lighting_level *= pow((100.0 - current_bar->lighting_advance_rate) / 100.0, e->frame_factor_inverse);

				if (current_bar->lighting_level < 0.01)
				{
					current_bar->lighting_level = 0.0;
				}
			}
		}
	}
}
void Program::DrawProgressBar(ProgressBar* const progress_bar, Camera* const camera)
{
	e->DrawRectangle(&progress_bar->back_rect, progress_bar->back_color, camera);
	e->DrawRectangle(&progress_bar->progress_back_rect, progress_bar->progress_back_color, camera);

	SDL_Color calculated_color;
	for (size_t i = 0; i < progress_bar->bars.size(); i++)
	{
		Bar* const current_bar = progress_bar->bars[i];

		const double lighting_propotion = current_bar->lighting_level / 100.0;
		const double inverse_lighting_proportion = (100.0 - current_bar->lighting_level) / 100.0;

		calculated_color.r = (unsigned char)round(((double)current_bar->secondary_progress_color.r * lighting_propotion) + ((double)current_bar->progress_color.r * inverse_lighting_proportion));
		calculated_color.g = (unsigned char)round(((double)current_bar->secondary_progress_color.g * lighting_propotion) + ((double)current_bar->progress_color.g * inverse_lighting_proportion));
		calculated_color.b = (unsigned char)round(((double)current_bar->secondary_progress_color.b * lighting_propotion) + ((double)current_bar->progress_color.b * inverse_lighting_proportion));
		calculated_color.a = (unsigned char)round(((double)current_bar->secondary_progress_color.a * lighting_propotion) + ((double)current_bar->progress_color.a * inverse_lighting_proportion));

		e->DrawRectangle(&current_bar->progress_rect, calculated_color, camera);
	}
}

void Program::SetHeightsOfCoursePathPathProgressBars()
{
	const double temp_sum_h = (previous_portion_button.parent_rect.size.height + (4.0 * (double)(course_path_path.size() - size_t(1))));
	const double temp_equal_h = temp_sum_h / (double)course_path_path.size();
	const double temp_smol_h = ((temp_equal_h - 4.0) * (percent_progress_bar_animation_complete / 100.0)) + 4.0;
	double temp_big_h = 0.0;
	if (course_path_path.size() > size_t(1))
	{
		temp_big_h = (temp_sum_h - temp_smol_h) / (double)(course_path_path.size() - size_t(1));
	}
	
	
	double consistent_big_progress_rect_height = temp_big_h - 8.0;
	if (consistent_big_progress_rect_height < 0.0)
	{
		consistent_big_progress_rect_height = 0.0;
	}
	double consistent_smol_progress_rect_height = temp_smol_h - 8.0;
	if (consistent_smol_progress_rect_height < 0.0)
	{
		consistent_smol_progress_rect_height = 0.0;
	}
	

	ProgressBar* temp_pb = nullptr;
	TextBox* temp_tb = nullptr;
	for (size_t i = 0; i < course_path_path.size(); i++)
	{
		double applicable_temp_h;
		double applicable_consistent_progress_rect_height;
		if (i == (course_path_path.size() - size_t(1)))
		{
			applicable_temp_h = temp_smol_h;
			applicable_consistent_progress_rect_height = consistent_smol_progress_rect_height;
		}
		else
		{
			applicable_temp_h = temp_big_h;
			applicable_consistent_progress_rect_height = consistent_big_progress_rect_height;
		}


		temp_pb = &course_path_path[i]->progress_bar;
		temp_tb = &course_path_path[i]->text_box;

		//course_path_path[i]->target_scaled_height = temp_h;
		temp_pb->back_rect.base_size.height = applicable_temp_h;
		temp_pb->back_rect.size.height = applicable_temp_h;

		temp_pb->progress_back_rect.size.height = applicable_consistent_progress_rect_height;

		for (size_t j = 0; j < temp_pb->bars.size(); j++)
		{
			temp_pb->bars[j]->progress_rect.size.height = applicable_consistent_progress_rect_height;
		}

		temp_pb->back_rect.pos.y = (e->blank_camera->rect.size.height / -2.0) + (applicable_temp_h / 2.0) + ((temp_big_h - 4.0) * (double)i);

		temp_tb->parent_rect.pos.y = temp_pb->back_rect.pos.y;

		if (applicable_consistent_progress_rect_height != 0.0)
		{
			course_path_path[i]->text_box_visable = 1;
			temp_tb->parent_rect.size.height = applicable_consistent_progress_rect_height;
			temp_tb->parent_rect.SetBaseWidthWithWidthScale(temp_tb->parent_rect.GetHeightScale());
		}
		else
		{
			course_path_path[i]->text_box_visable = 0;
		}
	}
}

void Program::UpdateCoursePathPathProgressBars()
{
	if (progress_bar_animation_direction)
	{
		if (percent_progress_bar_animation_complete != 100.0)
		{
			progress_bar_animation_counter += e->frame_factor_inverse;
			const double x = (progress_bar_animation_counter / 90.0);

			if (x >= 1.0)
			{
				progress_bar_animation_counter = 90.0;
				percent_progress_bar_animation_complete = 100.0;
			}
			else
			{
				percent_progress_bar_animation_complete = (100.0 * (-pow(0.0002, x))) + 100.0;
			}
			SetHeightsOfCoursePathPathProgressBars();
		}
	}
	else
	{
		if (percent_progress_bar_animation_complete != 0.0)
		{
			progress_bar_animation_counter += e->frame_factor_inverse;
			const double x = (progress_bar_animation_counter / 90.0);

			if (x >= 1.0)
			{
				delete course_path_path.back();
				course_path_path.pop_back();

				removing_progress_bar = 0;

				progress_bar_animation_counter = 90.0;

				progress_bar_animation_direction = 1;
				percent_progress_bar_animation_complete = 100.0;
			}
			else
			{
				if (x < 0.5)
				{
					percent_progress_bar_animation_complete = (1.0 - (((pow(EASE_PARAMETER, (2.0 * x) - 1.0) / EASE_DIVISOR) - FIRST_Y_SHIFT) * Y_STRETCH_FACTOR)) * 100.0;
				}
				else
				{
					percent_progress_bar_animation_complete = (1.0 - ((-(pow(EASE_PARAMETER, 1.0 - (2.0 * x)) / EASE_DIVISOR) + SECOND_Y_SHIFT) * Y_STRETCH_FACTOR)) * 100.0;
				}
			}

			SetHeightsOfCoursePathPathProgressBars();
		}
	}

	for (size_t i = 0; i < course_path_path.size(); i++)
	{
		UpdateProgressBar(&course_path_path[i]->progress_bar);
	}
}
void Program::DrawCoursePathPathProgressBars()
{
	for (size_t i = 0; i < course_path_path.size(); i++)
	{
		DrawProgressBar(&course_path_path[i]->progress_bar, e->blank_camera);

		const Point2D temp_blank_mouse = e->GetMousePos(e->blank_camera);
		RectangleOld temp_overlap_rect = course_path_path[i]->progress_bar.progress_back_rect;
		temp_overlap_rect.size.height += 4.0;
		if (i == 0)
		{
			temp_overlap_rect.size.height += 2.0;
			temp_overlap_rect.pos.y -= 1.0;
		}
		if (i == (course_path_path.size() - size_t(1)))
		{
			temp_overlap_rect.size.height += 2.0;
			temp_overlap_rect.pos.y += 1.0;
		}

		bool condition;
		if (i == 0)
		{
			condition = OverlapPoint2DWithRectangleEx(&temp_blank_mouse, &temp_overlap_rect, 0, 1, 0, 1);
		}
		else
		{
			condition = OverlapPoint2DWithRectangleEx(&temp_blank_mouse, &temp_overlap_rect, 0, 0, 0, 1);
		}

		if (condition)
		{
			if (course_path_path[i]->text_box_visable)
			{
				e->DrawTextBox(&course_path_path[i]->text_box, e->blank_camera);
			}
		}
	}
}

bool Program::CheckForLinkClicksAndGenerateSavedLinkRects(const double rate, const Size2D stretch_multiplier, const int text_sound_channel_num, const int link_click_channel_num)
{
	bool found_overlapping_link = 0;
	bool part_of_overlapping_link = 0;
	bool found_clicked_link = 0;

	saved_link_rects.clear();

	const vector<TextLink>* current_links = &GetCurrentCoursePath()->GetCurrentPortion()->links;
	for (size_t i = 0; i < current_links->size(); i++)
	{
		part_of_overlapping_link = 0;

		if (current_visable_char_progression >= (double)current_links->at(i).begin_char)
		{
			const size_t temp_begin_index = current_links->at(i).begin_char;

			size_t temp_end_index;
			if (current_visable_char_progression >= (double)current_links->at(i).end_char)
			{
				temp_end_index = current_links->at(i).end_char;
			}
			else
			{
				temp_end_index = (size_t)current_visable_char_progression;
			}

			vector<RectStructOne>* const temp_hitboxes = current_text_portion_text_box.GetSegmentHitbox(temp_begin_index, temp_end_index);

			for (size_t j = 0; j < temp_hitboxes->size(); j++)
			{
				Size2D temp_text_box_uni_size_scale = current_text_portion_text_box.parent_rect.GetUniSizeScale();
				temp_hitboxes->at(j).uni_right_edge += temp_text_box_uni_size_scale.width;
				temp_hitboxes->at(j).uni_bottom_edge -= temp_text_box_uni_size_scale.height;
				temp_hitboxes->at(j).uni_left_edge -= temp_text_box_uni_size_scale.width;
				temp_hitboxes->at(j).uni_top_edge += temp_text_box_uni_size_scale.height;

				saved_link_rects.push_back({ temp_hitboxes->at(j), 0, 0 });

				if (part_of_overlapping_link)
				{
					saved_link_rects.back().hovering = 1;
					saved_link_rects.back().pressed = e->input.mouse_left.pressed;
				}

				if (!found_overlapping_link)
				{
					const Point2D mouse_pos = e->GetMousePos(e->blank_camera);
					if (OverlapPoint2DWithRectStructOne(&mouse_pos, &temp_hitboxes->at(j), 1))
					{
						part_of_overlapping_link = 1;

						for (size_t k = 0; k <= j; k++)
						{
							size_t temp_index = saved_link_rects.size() - size_t(1) - k;

							saved_link_rects[temp_index].hovering = 1;
							saved_link_rects[temp_index].pressed = e->input.mouse_left.pressed;
						}

						found_overlapping_link = 1;

						if (e->input.mouse_left.first_frame_pressed)
						{
							Mix_PlayChannel(link_click_channel_num, e->click_press_sound, 0);
						}
						if (e->input.mouse_left.first_frame_released)
						{
							Mix_PlayChannel(link_click_channel_num, e->click_release_sound, 0);

							SetCurrentPathAndPortionIndexes(current_links->at(i).linked_path_index, current_links->at(i).linked_portion_index, 0, 1);
							AdvanceCurrentTextPortionTextBox(rate, stretch_multiplier, text_sound_channel_num);
							found_clicked_link = 1;
						}
						else
						{
							if (current_link_type != current_links->at(i).link_type)
							{
								switch (current_links->at(i).link_type)
								{
								case 1:
									link_tool_tip.SetText("Who?");
									current_link_type = 1;
									break;
								case 2:
									link_tool_tip.SetText("What?");
									current_link_type = 1;
									break;
								case 3:
									link_tool_tip.SetText("When?");
									current_link_type = 1;
									break;
								case 4:
									link_tool_tip.SetText("Why?");
									current_link_type = 1;
									break;
								case 5:
									link_tool_tip.SetText("How?");
									current_link_type = 1;
									break;
								}
							}

							if (current_link_type != 0)
							{
								update_and_draw_tool_tip_this_frame = 1;
							}
						}
					}
				}
			}
		}
	}

	return found_clicked_link;
}
void Program::AdvanceCurrentTextPortionTextBox(const double rate, const Size2D stretch_multiplier, const int channel_num)
{
	double remaining_wait = rate * e->frame_factor_inverse;
	TextPortion* const current_text_portion = GetCurrentCoursePath()->GetCurrentPortion();
	
	char sound_effect_id = 0;

	while ((remaining_wait > 0.0) && (current_visable_char_progression < (double)current_text_portion->text.size()))
	{
		size_t current_visable_char;
		double current_visable_char_wait_multiplier;
		if (current_visable_char_progression >= 0.0)
		{
			current_visable_char = (size_t)current_visable_char_progression;
			current_visable_char_wait_multiplier = current_text_portion->text[current_visable_char].wait_multiplier;
		}
		else
		{
			current_visable_char = numeric_limits<size_t>::max();
			current_visable_char_wait_multiplier = 1.0;
		}

		const double next_visable_char_progression = (double)(current_visable_char + size_t(1));
		const double next_visable_char_wait_diff = next_visable_char_progression - current_visable_char_progression;
		const double multiplied_remaining_wait = remaining_wait * current_visable_char_wait_multiplier;
		if ((current_visable_char_progression + multiplied_remaining_wait) >= next_visable_char_progression)
		{
			current_visable_char_progression = next_visable_char_progression;
			remaining_wait = (multiplied_remaining_wait - next_visable_char_wait_diff) / current_visable_char_wait_multiplier;

			const size_t trunc_current_visable_char_progression = (size_t)current_visable_char_progression;
			if (trunc_current_visable_char_progression < current_text_portion_text_box.chars.size())
			{
				current_text_portion_text_box.chars[trunc_current_visable_char_progression]->a_mod = 255;
				current_text_portion_text_box.chars[trunc_current_visable_char_progression]->rect.size.width = saved_char_sizes[trunc_current_visable_char_progression].width * stretch_multiplier.width;
				current_text_portion_text_box.chars[trunc_current_visable_char_progression]->rect.size.height = saved_char_sizes[trunc_current_visable_char_progression].height * stretch_multiplier.height;
			}
			if (trunc_current_visable_char_progression < current_text_portion->text.size())
			{
				if (current_text_portion->text[trunc_current_visable_char_progression].sound_id != 0)
				{
					sound_effect_id = current_text_portion->text[trunc_current_visable_char_progression].sound_id;
				}
			}
		}
		else
		{
			current_visable_char_progression += multiplied_remaining_wait;
			remaining_wait = 0.0;
		}
	}

	//Update the appropriate saved_visable_char_progression value
	if (GetCurrentCoursePath()->current_portion_index >= GetCurrentCoursePath()->progress)
	{
		GetCurrentCoursePath()->saved_visable_char_progression = current_visable_char_progression;
	}


	if (sound_effect_id != 0)
	{
		switch (sound_effect_id)
		{
		case 1:
			Mix_PlayChannel(channel_num, text_sound_1, 0);
			break;
		case 2:
			Mix_PlayChannel(channel_num, text_sound_2, 0);
			break;
		case 3:
			Mix_PlayChannel(channel_num, text_sound_3, 0);
			break;
		case 4:
			Mix_PlayChannel(channel_num, text_sound_4, 0);
			break;
		}
	}
}
void Program::ReduceStretchInCurrentTextPortionTextBox(const double rate)
{
	//Loop through all visable chars and reduce height modifier
	bool done = 0;
	for (size_t i = 0; (i < current_text_portion_text_box.lines.size()) && (!done); i++)
	{
		for (size_t j = current_text_portion_text_box.lines[i]->first_index; j <= current_text_portion_text_box.lines[i]->last_index; j++)
		{
			if (j <= trunc(current_visable_char_progression))
			{
				const Size2D current_size = current_text_portion_text_box.chars[j]->rect.size;
				const Size2D current_saved_size = saved_char_sizes[j];
				if (current_size.height > (current_saved_size.height + 0.001))
				{
					current_text_portion_text_box.chars[j]->rect.size.width -= (current_size.width - current_saved_size.width) * rate;
					current_text_portion_text_box.chars[j]->rect.size.height -= (current_size.height - current_saved_size.height) * rate;
				}
				else
				{
					current_text_portion_text_box.chars[j]->rect.size = saved_char_sizes[j];
				}
			}
			else
			{
				done = 1;
				break;
			}
		}
	}
}

void Program::UpdateGooberPos()
{
	if (!(((size_t)current_visable_char_progression == GetCurrentCoursePath()->GetCurrentPortion()->text.size()) && (goober_anim_counter == 0)))
	{
		goober_anim_counter++;
		if (goober_anim_counter > goober_max_anim_counter)
		{
			goober_anim_counter = 0;
		}
	}

	goober_rectangle.pos.y = (-pow((2.0 * (double)goober_anim_counter / (double)(goober_max_anim_counter + 1)) - 1.0, 2.0) + 1.0) * 30.0;

}

void Program::AddLesson(const char* lesson_name, const unsigned int param_hour_estimate, const unsigned int param_minute_estimate, const size_t param_main_path_index)
{
	const size_t lessons_size = lessons.size();

	lessons.push_back(new Lesson());
	SimpleTextButton* const button = &lessons.back()->button;
	ProgressBar* const p_bar = &lessons.back()->progress_bar;


	button->InitWithBaseSize({ 4.0, 4.0 }, lesson_name, &e->default_font, { 100.0, 24.0 }, 4.0, 4.0, { 0.0, 0.0 }, 0);
	button->parent_rect.pos = { -540.0, ((double)lessons_size * -160.0) + 400.0 };
	button->sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

	p_bar->InitBasic({ button->parent_rect.pos.x, button->parent_rect.pos.y - (button->parent_rect.size.height / 2.0) - 12.0 }, { button->parent_rect.size.width, 16.0 }, 4.0, 0.0);
	p_bar->bars[0]->bar_advance_rate = 100.0;

	lessons.back()->main_path_index = param_main_path_index;
	lessons.back()->hour_estimate = param_hour_estimate;
	lessons.back()->minute_estimate = param_minute_estimate;
}
bool Program::UpdateLessons()
{
	const size_t lessons_size = lessons.size();

	for (size_t i = 0; i < lessons_size; i++)
	{
		lessons[i]->button.parent_rect.pos.y = ((double)i * -160.0) + 400.0 + lessons_scroll_bar.scroll_value;
		lessons[i]->progress_bar.back_rect.pos.y = lessons[i]->button.parent_rect.pos.y - (lessons[i]->button.parent_rect.size.height / 2.0) - 12.0;

		e->UpdateSimpleTextButton(&lessons[i]->button, e->blank_camera, &main_layer, 1, {});
		if (lessons[i]->button.press_data.first_frame_released)
		{
			if (lessons[i]->main_path_index < course_paths.size())
			{
				SetCurrentPathAndPortionIndexesEx(lessons[i]->main_path_index, course_paths[lessons[i]->main_path_index]->current_portion_index, 1, 1, 0);
			}
			else
			{
				cout << "lessons[i]->main_path_index OUT OF RANGE!!!11!1 Set by UpdateLessons()." << endl;
			}
			SetScene(4, 0);
			return 1;
		}
	}

	return 0;
}
void Program::DrawLessons()
{
	for (size_t i = 0; i < lessons.size(); i++)
	{
		e->DrawSimpleTextButton(&lessons[i]->button, e->blank_camera);
		DrawProgressBar(&lessons[i]->progress_bar, e->blank_camera);
	}
}

void Program::InitSounds()
{
	Mix_AllocateChannels(NUMBER_OF_CHANNELS);

	Mix_Volume(-1, 64);

	text_sound_1 = Mix_LoadWAV("sounds/text_sound_1.wav");
	Mix_VolumeChunk(text_sound_1, 64);
	text_sound_2 = Mix_LoadWAV("sounds/text_sound_2.wav");
	Mix_VolumeChunk(text_sound_2, 64);
	text_sound_3 = Mix_LoadWAV("sounds/text_sound_3.wav");
	Mix_VolumeChunk(text_sound_3, 64);

	confetti_sound = Mix_LoadWAV("sounds/confetti_sound.wav");
	Mix_VolumeChunk(confetti_sound, 128);
}
void Program::DestroySounds()
{
	Mix_FreeChunk(text_sound_1);
	text_sound_1 = nullptr;
	Mix_FreeChunk(text_sound_2);
	text_sound_2 = nullptr;
	Mix_FreeChunk(text_sound_3);
	text_sound_3 = nullptr;

	Mix_FreeChunk(confetti_sound);
	confetti_sound = nullptr;
}


void Program::UpdatePlayer(Player* param_player)
{
	param_player->previous_frame_running = param_player->running;
	param_player->running = 0;

	if (e->input.a.pressed)
	{
		param_player->hitbox.pos.x -= 2.0;
		param_player->running = 1;

		param_player->sprite.rect.flip.value = 1;
	}
	if (e->input.d.pressed)
	{
		param_player->hitbox.pos.x += 2.0;
		param_player->running = 1;

		param_player->sprite.rect.flip.value = 0;
	}
	if (e->input.s.pressed)
	{
		param_player->hitbox.pos.y -= 2.0;
		param_player->running = 1;
	}
	if (e->input.w.pressed)
	{
		param_player->hitbox.pos.y += 2.0;
		param_player->running = 1;
	}

	param_player->first_frame_running = 0;
	if (param_player->running && (!param_player->previous_frame_running)) { param_player->first_frame_running = 1; }

	param_player->first_frame_idle = 0;
	if (param_player->previous_frame_running && (!param_player->running)) { param_player->first_frame_idle = 1; }

	if (param_player->first_frame_running)
	{
		param_player->sprite.LoadAnimation(&run_anim);
	}

	if (param_player->first_frame_idle)
	{
		param_player->sprite.LoadAnimation(&idle_anim);
	}

	if (e->input.t.pressed && e->input.r.first_frame_pressed)
	{
		param_player->sprite.LoadAnimation(&pride_anim);
	}

	param_player->sprite.rect.pos = param_player->hitbox.pos;
}

void Program::UpdateMainCamera()
{
	Point2D player_pos = player.hitbox.GetUniPos();
	Point2D cam_pos = main_camera->rect.GetUniPos();
	main_camera->rect.pos.x += (player_pos.x - cam_pos.x) * 0.1 * e->frame_factor_inverse;
	main_camera->rect.pos.y += (player_pos.y - cam_pos.y) * 0.1 * e->frame_factor_inverse;
}

void Program::DrawGround(Ground* param_ground, Camera* camera)
{
	RectangleOld tile_rectangle_data;
	tile_rectangle_data.base_size = { 64.0, 24.0 };
	tile_rectangle_data.SetSizeWithSizeScale({ 4.0, 4.0 });

	//RectangleOld accessory_rect;
	//accessory_rect.base_size = tree.size;
	//accessory_rect.SetSizeScale({ 4.0, 4.0 });

	int tile_counter = 0;

	for (int y = 49; y >= 0; y--)
	{
		for (int x = 0; x < 50; x++)
		{
			if (param_ground->tile_data[x][y] != NULL)
			{
				const double tile_rise_time = (param_ground->rise_time / 1.6) - ((double)tile_counter * 0.01);

				if (tile_rise_time > 0.0)
				{
					tile_rectangle_data.pos.x = (x * 180.0) + (y * 72.0);

					if (tile_rise_time < 1.0)
					{
						tile_rectangle_data.pos.y = (y * 72.0) + (1000.0 * sin(tile_rise_time * PI / 2.0)) - 1000.0;
					}
					else
					{
						tile_rectangle_data.pos.y = (y * 72.0);
					}



					double TIME_FOR_SINGLE_CYCLE;
					double MIN_HIGHLIGHT_VALUE;
					double MAX_HIGHLIGHT_VALUE;

					double cycle_time;
					double sin_time;
					double double_alpha;


					switch (param_ground->tile_data[x][y])
					{
					case 1:
						e->DrawTexture(light_ground, camera, &tile_rectangle_data);
						break;
					case 2:
						e->DrawTexture(dark_ground, camera, &tile_rectangle_data);
						break;
					case 3:
						e->DrawTexture(grassy_ground, camera, &tile_rectangle_data);
						break;
					case 4:
						e->DrawTexture(cobble_ground, camera, &tile_rectangle_data);
						break;
					case 5:
						e->DrawTexture(grassy_ground, camera, &tile_rectangle_data);

						TIME_FOR_SINGLE_CYCLE = 2.0;
						MIN_HIGHLIGHT_VALUE = 20.0;
						MAX_HIGHLIGHT_VALUE = 100.0;

						cycle_time = fmod(param_ground->rise_time, TIME_FOR_SINGLE_CYCLE) / TIME_FOR_SINGLE_CYCLE;

						sin_time = sin(cycle_time * 2.0 * PI);

						double_alpha = MIN_HIGHLIGHT_VALUE + (((sin_time + 1.0) / 2.0) * (MAX_HIGHLIGHT_VALUE - MIN_HIGHLIGHT_VALUE));

						//SDL_SetTextureAlphaMod(ground_highlight.sdl_texture, (int)round(double_alpha)); REMOVED CAUSE RENDERER GOT YEETED
						//e->DrawTexture(&ground_highlight, camera, &tile_rectangle_data); REMOVED CAUSE RENDERER GOT YEETED
						//SDL_SetTextureAlphaMod(ground_highlight.sdl_texture, 255); REMOVED CAUSE RENDERER GOT YEETED
						break;
					case 6:
						e->DrawTexture(water_ground.GetCurrentFrame()->texture, camera, &tile_rectangle_data);
						break;
					}
				}

				tile_counter++;
			}
		}
	}

	param_ground->rise_time += e->frame_factor_inverse / 60.0;

	water_ground.Update(e->frame_factor_inverse);
}

//Clicks should be done BEFORE this function is called
void Program::UpdateCellSet(CellSet* const param_cell_set)
{
	for (size_t i = 0; i < param_cell_set->set.size(); i++)
	{
		param_cell_set->set[i]->Update(e->frame_factor_inverse);
	}

	const RectangleOld temp_full_hitbox = param_cell_set->GenerateFullHitbox();
	const Point2D temp_mouse_pos = e->GetMousePos(e->blank_camera);

	hovering_over_tset = 0;
	if (OverlapPoint2DWithRectangle(&temp_mouse_pos, &temp_full_hitbox, 1))
	{
		size_t selected_index = 0;
		RectangleOld temp_cell_cropped_hitbox;
		for (size_t i = 0; i < param_cell_set->set.size(); i++)
		{
			temp_cell_cropped_hitbox = param_cell_set->GenerateHitboxCropped(i);
			if (OverlapPoint2DWithRectangle(&temp_mouse_pos, &temp_cell_cropped_hitbox, 1))
			{
				selected_index = i;
			}
		}
		param_cell_set->UpdateNumberDisplay(selected_index);
		hovering_over_tset = 1;
	}
}
void Program::DrawCellSet(CellSet* const param_cell_set, Camera* const camera)
{
	for (size_t i = 0; i < param_cell_set->set.size(); i++)
	{
		RectangleOld outer_hitbox = param_cell_set->GenerateHitbox(i);
		RectangleOld inner_hitbox = param_cell_set->GenerateInnerHitbox(i);

		SDL_Color cell_color = { 0, 0, 0, 255 };
		const double delta_y = param_cell_set->GetTrueScale().height * param_cell_set->set[i]->animation_movement_percent / 100.0;
		if (param_cell_set->set[i]->state == 1)
		{
			cell_color.r = 255;
			cell_color.g = 255;
			cell_color.b = (char)round(255.0 * param_cell_set->set[i]->animation_color_percent / 100.0);

			outer_hitbox.pos.y += delta_y;
			inner_hitbox.pos.y += delta_y;
		}
		else
		{
			const char rg = (char)50 + (char)round(78.0 * param_cell_set->set[i]->animation_color_percent / 100.0);
			cell_color.r = rg;
			cell_color.g = rg;
			cell_color.b = (char)50 - (char)round(50.0 * param_cell_set->set[i]->animation_color_percent / 100.0);

			//const char uni_val = (char)50 - (char)round(50.0 * param_transistor_set->set[i]->animation_color_percent / 100.0);
			//cell_color.r = uni_val;
			//cell_color.g = uni_val;
			//cell_color.b = uni_val;

			outer_hitbox.pos.y -= delta_y;
			inner_hitbox.pos.y -= delta_y;
		}

		e->DrawRectangle(&outer_hitbox, { 0, 0, 0, 255 }, camera);
		e->DrawRectangle(&inner_hitbox, cell_color, camera);
	}

	if (hovering_over_tset)
	{
		e->DrawTextBox(&param_cell_set->number_display, camera);
	}
}

void Program::ResetCurrentVisableCharProgression(const double new_char_progression_value)
{
	current_visable_char_progression = new_char_progression_value;

	const bool trunc_visable_char_progression_valid = (current_visable_char_progression >= 0.0);
	size_t trunc_visable_char_progression = (size_t)current_visable_char_progression;
	for (size_t i = 0; i < current_text_portion_text_box.chars.size(); i++)
	{
		//Determine visibility of chars based on param_visable_char_progression
		if (trunc_visable_char_progression_valid)
		{
			if (i > trunc_visable_char_progression)
			{
				current_text_portion_text_box.chars[i]->a_mod = 0;
			}
			else
			{
				current_text_portion_text_box.chars[i]->a_mod = 255;
			}
		}
		else
		{
			current_text_portion_text_box.chars[i]->a_mod = 0;
		}
	}
}
void Program::SetCurrentPathAndPortionIndexesEx(const size_t param_path_index, size_t param_portion_index, const bool reset_course_path_path, const bool move_bars_instantly, const bool allow_semicomplete_portions)
{
	bool changed_path_index = 0;

	if (param_path_index != numeric_limits<size_t>::max())
	{
		if ((param_path_index >= 0) && (param_path_index < course_paths.size()))
		{
			bool condition;
			if (course_path_path.size() > 0)
			{
				condition = GetCurrentCoursePath() != course_paths[param_path_index];
			}
			else
			{
				condition = 1;
			}

			if (condition)
			{
				changed_path_index = 1;

				if (reset_course_path_path)
				{
					course_path_path.clear();
				}

				bool condition_2 = 0;
				if (course_path_path.size() >= 2)
				{
					CoursePath* const back_thing = course_path_path[course_path_path.size() - size_t(2)]->path_pointer;

					if (back_thing == course_paths[param_path_index])
					{
						if (removing_progress_bar)
						{
							delete course_path_path.back();
							course_path_path.pop_back();

							removing_progress_bar = 0;
						}

						removing_progress_bar = 1;
						progress_bar_animation_counter = 0.0;
						percent_progress_bar_animation_complete = 100.0;
						progress_bar_animation_direction = 0;
					}
					else
					{
						condition_2 = 1;
					}
				}
				else
				{
					condition_2 = 1;
				}

				if (condition_2)
				{
					if (removing_progress_bar)
					{
						delete course_path_path.back();
						course_path_path.pop_back();

						removing_progress_bar = 0;
					}


					course_path_path.push_back(new CoursePathPathData);
					course_path_path.back()->path_pointer = course_paths[param_path_index];

					Size2D temp_size = { next_portion_button.parent_rect.GetUniEdge({ 2 }) - previous_portion_button.parent_rect.GetUniEdge({ 0 }) + 8.0, (previous_portion_button.parent_rect.size.height + (4.0 * (double)(course_path_path.size() - size_t(1)))) / (double)course_path_path.size()};

					course_path_path.back()->progress_bar.InitBasic(
						{ 0.0, 0.0 },
						temp_size,
						4.0,
						0.0
					);

					//Setting new progress bar back bar color
					switch(course_path_path.size())
					{
					case 1:
						course_path_path.back()->progress_bar.bars.back()->progress_color = { 0, 180, 0, 255 };
						course_path_path.back()->progress_bar.bars.back()->secondary_progress_color = { 0, 230, 0, 255 };
						break;
					case 2:
						course_path_path.back()->progress_bar.bars.back()->progress_color = { 0, 140, 156, 255 };
						course_path_path.back()->progress_bar.bars.back()->secondary_progress_color = { 0, 167, 187, 255 };
						break;
					}

					course_path_path.back()->progress_bar.AddBar(0.0);

					//Setting new progress bar front bar color
					switch (course_path_path.size())
					{
					case 1:
						course_path_path.back()->progress_bar.bars.back()->progress_color = { 0, 220, 0, 255 };
						course_path_path.back()->progress_bar.bars.back()->secondary_progress_color = { 20, 255, 20, 255 };
						break;
					case 2:
						course_path_path.back()->progress_bar.bars.back()->progress_color = { 0, 180, 200, 255 };
						course_path_path.back()->progress_bar.bars.back()->secondary_progress_color = { 0, 217, 240, 255 };
						break;
					}

					course_path_path.back()->text_box.InitLeast(&e->default_font);
					course_path_path.back()->text_box.parent_rect.size.width = temp_size.width - 8.0;
					course_path_path.back()->text_box.parent_rect.size.height = previous_portion_button.parent_rect.size.height - 8.0;
					course_path_path.back()->text_box.parent_rect.SetBaseSizeWithSizeScale({ 4.0, 4.0 });
					course_path_path.back()->text_box.horizontal_text_centering = { 1 };
					course_path_path.back()->text_box.vertical_text_centering = { 1 };

					if (reset_course_path_path)
					{
						progress_bar_animation_direction = 1;
						progress_bar_animation_counter = 90.0;
						percent_progress_bar_animation_complete = 100.0;

						SetHeightsOfCoursePathPathProgressBars();
					}
					else
					{
						progress_bar_animation_direction = 1;
						progress_bar_animation_counter = 0.0;
						percent_progress_bar_animation_complete = 0.0;
					}
				}

				UpdateCoursePathTextBox();
			}
		}
		else
		{
			cout << "param_path_index out of range, so function quit. Sent from SetCurrentTextPortionIndex(...)" << endl;
			return;
		}
	}

	const size_t course_text_size = GetCurrentCoursePath()->portions.size();
	if (course_text_size > 0)
	{
		bool changed_portion_index = 0;
		bool changed_progress = 0;
		bool finished_portion = 0;



		//Set current_portion_index, changed_portion_index, and (progress, changed_progress, and finished_portion if finished_portion) appropriately
		size_t* const current_portion_index = &GetCurrentCoursePath()->current_portion_index;
		size_t* const progress = &GetCurrentCoursePath()->progress;

		if (param_portion_index != numeric_limits<size_t>::max())
		{
			if (param_portion_index == course_text_size)
			{
				if (*progress != course_text_size)
				{
					*progress = course_text_size;
					changed_progress = 1;
				}

				param_portion_index = course_text_size - size_t(1);
				finished_portion = 1;
			}
			if (param_portion_index > course_text_size)
			{
				if (*progress != course_text_size)
				{
					*progress = course_text_size;
					changed_progress = 1;
				}

				param_portion_index = course_text_size - size_t(1);
				cout << "param_text_portion_index TOO HIGH. Set current_text_portion_index to last course_text index instead. Sent from SetCurrentTextPortionIndex(...)" << endl;
			}

			if (*current_portion_index != param_portion_index)
			{
				*current_portion_index = param_portion_index;
				changed_portion_index = 1;
			}
		}

		changed_portion_index = changed_portion_index || changed_path_index;
		changed_progress = changed_progress || changed_path_index;





		//Add all the chars from current_portion to current_text_portion_text_box (blue if part of a link).
		TextPortion* const current_portion = GetCurrentCoursePath()->GetCurrentPortion();

		current_text_portion_text_box.Clear();
		for (size_t i = 0; i < current_portion->text.size(); i++)
		{
			if (current_portion->CharPartOfLink(i) == numeric_limits<size_t>::max())
			{
				current_text_portion_text_box.AddChar(current_portion->text[i].value);
			}
			else
			{
				current_text_portion_text_box.AddChar(current_portion->text[i].value, 0, 0, 200, 255);
			}
		}
		current_text_portion_text_box.UpdateCharPos();





		//Set current_visable_char_progression and progress
		const size_t current_portion_text_size = current_text_portion_text_box.chars.size();
		if (!finished_portion)
		{
			if (*current_portion_index > *progress)
			{
				*progress = *current_portion_index;
				changed_progress = 1;

				current_visable_char_progression = -1.0;
			}
			else
			{
				if (*current_portion_index == *progress)
				{
					const double VISIBLE_CHAR_REDUCTION = 30.0;
					const double VISIBLE_CHAR_FINISH_LENIENCY = 12.0;

					current_visable_char_progression = GetCurrentCoursePath()->saved_visable_char_progression - VISIBLE_CHAR_REDUCTION;
					if (current_visable_char_progression <= -1.0)
					{
						current_visable_char_progression = -1.0;
					}
					else
					{
						if ((current_visable_char_progression + VISIBLE_CHAR_REDUCTION) >= ((double)current_portion_text_size - VISIBLE_CHAR_FINISH_LENIENCY))
						{
							current_visable_char_progression = (double)current_portion_text_size;
						}
						else
						{
							if (changed_path_index || !allow_semicomplete_portions)
							{
								current_visable_char_progression = -1.0;
							}
						}
					}
				}
				else
				{
					current_visable_char_progression = (double)current_portion_text_size;
				}
			}
		}



		ResetCurrentVisableCharProgression(current_visable_char_progression);



		//Add to saved_char_sizes
		saved_char_sizes.clear();
		for (size_t i = 0; i < current_text_portion_text_box.chars.size(); i++)
		{
			saved_char_sizes.push_back(current_text_portion_text_box.chars[i]->rect.size);
		}



		//Set front progress bar length
		if (finished_portion)
		{
			if (move_bars_instantly)
			{
				GetCurrentCourseProgressBar()->SetActualWidthWithIndex(100.0, 1, 1);
			}
			else
			{
				GetCurrentCourseProgressBar()->SetTargetWidthWithIndex(100.0, 1, 1);
			}
		}
		else
		{
			if (changed_portion_index)
			{
				if (move_bars_instantly)
				{
					GetCurrentCourseProgressBar()->SetActualWidthWithIndex(GetCurrentCoursePath()->current_portion_index, GetCurrentCoursePath()->portions.size(), 1, 1);
				}
				else
				{
					GetCurrentCourseProgressBar()->SetTargetWidthWithIndex(GetCurrentCoursePath()->current_portion_index, GetCurrentCoursePath()->portions.size(), 1, 1);
				}
			}
		}





		if (changed_progress)
		{
			const size_t path_progress = GetCurrentCoursePath()->progress;

			//Set back progress bar length
			if (move_bars_instantly)
			{
				GetCurrentCourseProgressBar()->SetActualWidthWithIndex(path_progress, GetCurrentCoursePath()->portions.size(), 1, 0);
			}
			else
			{
				GetCurrentCourseProgressBar()->SetTargetWidthWithIndex(path_progress, GetCurrentCoursePath()->portions.size(), 1, 0);
			}

			//Set progress_bar_text_box.chars
			GetCurrentCourseTextBox()->Clear();
			GetCurrentCourseTextBox()->AddCharPtr(to_string(path_progress).c_str());
			GetCurrentCourseTextBox()->AddChar('/');
			GetCurrentCourseTextBox()->AddCharPtr(to_string(course_text_size).c_str());
			GetCurrentCourseTextBox()->AddCharPtr(" completed");
			GetCurrentCourseTextBox()->UpdateCharPos();
		}
	}
	else
	{
		cout << "course_text_size == 0, so function quit. Sent from SetCurrentTextPortionIndex(...)" << endl;
	}
}
void Program::SetCurrentPathAndPortionIndexes(const size_t param_path_index, size_t param_portion_index, const bool reset_course_path_path, const bool move_bars_instantly)
{
	SetCurrentPathAndPortionIndexesEx(param_path_index, param_portion_index, reset_course_path_path, move_bars_instantly, 1);
}
void Program::SetCurrentTextPortionIndex(size_t param_portion_index, const bool reset_course_path_path, const bool move_bar_instantly)
{
	SetCurrentPathAndPortionIndexes(numeric_limits<size_t>::max(), param_portion_index, reset_course_path_path, move_bar_instantly);
}

void Program::Run()
{
	NumSwitchScene();

	switch (e->scene)
	{
	case 1:
		RunScene1();
		break;
	case 2:
		RunScene2();
		break;
	case 3:
		RunScene3();
		break;
	case 4:
		RunScene4();
		break;
	case 5:
		RunScene5();
		break;
	case 6:
		RunScene6();
		break;
	case 7:
		RunScene7();
		break;
	case 8:
		RunScene8();
		break;
	case 9:
		RunScene9();
		break;
	}
}
void Program::Draw()
{
	switch (e->scene)
	{
	case 1:
		DrawScene1();
		break;
	case 2:
		DrawScene2();
		break;
	case 3:
		DrawScene3();
		break;
	case 4:
		DrawScene4();
		break;
	case 5:
		DrawScene5();
		break;
	case 6:
		DrawScene6();
		break;
	case 7:
		DrawScene7();
		break;
	case 8:
		DrawScene8();
		break;
	case 9:
		DrawScene9();
		break;
	}
}
void Program::PostDrawRun()
{
	switch (e->scene)
	{
	case 1:
		PostDrawRunScene1();
		break;
	case 2:
		PostDrawRunScene2();
		break;
	case 3:
		PostDrawRunScene3();
		break;
	case 4:
		PostDrawRunScene4();
		break;
	case 5:
		PostDrawRunScene5();
		break;
	case 6:
		PostDrawRunScene6();
		break;
	case 7:
		PostDrawRunScene7();
		break;
	case 8:
		PostDrawRunScene8();
		break;
	case 9:
		PostDrawRunScene9();
		break;
	}
}

void Program::SetScene1()
{
	main_camera->rect.pos = { 0.0, 0.0 };
}
void Program::EndScene1()
{

}
void Program::RunScene1()
{
	e->UpdateSimpleTextButton(&run_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&code_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&images_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&sounds_button, main_camera, &main_layer, 1, {});
	e->UpdateSimpleTextButton(&other_files_button, main_camera, &main_layer, 1, {});

	if (run_button.press_data.first_frame_released)
	{
		SetScene(2, 0);
		return;
	}

	if (code_button.press_data.first_frame_released || images_button.press_data.first_frame_released || sounds_button.press_data.first_frame_released || other_files_button.press_data.first_frame_released)
	{
		SetScene(3, 0);
		return;
	}

	if (e->input.g.pressed)
	{
		Size2D temp_current_size = test_box.parent_rect.size;

		test_box.parent_rect.size = { temp_current_size.width + 1.0, temp_current_size.height + 0.5 };
	}
}
void Program::DrawScene1()
{
	e->DrawSimpleTextButton(&run_button, main_camera);
	e->DrawSimpleTextButton(&code_button, main_camera);
	e->DrawSimpleTextButton(&images_button, main_camera);
	e->DrawSimpleTextButton(&sounds_button, main_camera);
	e->DrawSimpleTextButton(&other_files_button, main_camera);


	e->DrawRectangle(&test_rect, { 255, 0, 0, 255 }, main_camera);

	//e->DrawTextBox(&test_box, main_camera);
}
void Program::PostDrawRunScene1()
{

}

void Program::SetScene2()
{
	ground.rise_time = 0.0;
}
void Program::EndScene2()
{

}
void Program::RunScene2()
{
	UpdatePlayer(&player);

	UpdateMainCamera();
}
void Program::DrawScene2()
{
	DrawGround(&ground, main_camera);

	e->DrawSprite(&player.sprite, main_camera);
}
void Program::PostDrawRunScene2()
{
	player.sprite.animation->Update(e->frame_factor_inverse);
}

void Program::SetScene3()
{
	main_camera->rect.pos = { 0.0, 0.0 };
}
void Program::EndScene3()
{

}
void Program::RunScene3()
{
	e->UpdateSimpleTextButton(&back_button, main_camera, &main_layer, 1, {});

	if (back_button.press_data.first_frame_released)
	{
		SetScene(1, 0);
		return;
	}
}
void Program::DrawScene3()
{
	e->DrawSimpleTextButton(&back_button, main_camera);

	e->DrawRectangleScaledBorderScaledShadow(&test_rect, { 255, 0, 0, 100 }, 4.0, { 2 }, { 0, 0, 0, 100 }, { -4.0, -4.0 }, { 0, 0, 0, 70 }, main_camera);
}
void Program::PostDrawRunScene3()
{

}

void Program::SetScene4()
{
	previous_portion_button.press_data.Reset();
	next_portion_button.press_data.Reset();
	previous_return_portion_button.press_data.Reset();
	next_return_portion_button.press_data.Reset();
	finish_portion_button.press_data.Reset();

	previous_next_portion_button_accessibility = 0;
	previous_previous_portion_button_accessibility = 0;
	previous_finish_portion_button_accessibility = 0;
	previous_previous_return_button_accessibility = 0;
	previous_next_return_button_accessibility = 0;

	complete_lesson_cutscene_timer = -1.0;
}
void Program::EndScene4()
{
	update_and_draw_tool_tip_this_frame = 0;

	confetti.clear();
}
void Program::RunScene4()
{
	//Update the accessibility of the previous, next, return, and finish portion buttons
	const bool at_first_portion = GetCurrentCoursePath()->current_portion_index == size_t(0);
	const bool at_last_portion = (GetCurrentCoursePath()->current_portion_index + size_t(1)) >= GetCurrentCoursePath()->portions.size();
	const bool all_portion_chars_visable = current_visable_char_progression >= (double)(current_text_portion_text_box.chars.size() - size_t(1));
	const bool has_return_path_index = (GetCurrentCoursePath()->return_path_index != numeric_limits<size_t>::max());

	

	const bool next_portion_button_accessibility = all_portion_chars_visable && !at_last_portion;
	next_portion_button.press_data.pressable = next_portion_button_accessibility;
	next_portion_button.press_data.hoverable = next_portion_button_accessibility;
	const bool previous_portion_button_accessibility = !at_first_portion;
	previous_portion_button.press_data.pressable = previous_portion_button_accessibility;
	previous_portion_button.press_data.hoverable = previous_portion_button_accessibility;
	const bool finish_portion_button_accessibility = all_portion_chars_visable && at_last_portion && !has_return_path_index;
	finish_portion_button.press_data.pressable = finish_portion_button_accessibility;
	finish_portion_button.press_data.hoverable = finish_portion_button_accessibility;
	const bool previous_return_button_accessibility = at_first_portion && has_return_path_index;
	previous_return_portion_button.press_data.pressable = previous_return_button_accessibility;
	previous_return_portion_button.press_data.hoverable = previous_return_button_accessibility;
	const bool next_return_button_accessibility = all_portion_chars_visable && at_last_portion && has_return_path_index;
	next_return_portion_button.press_data.pressable = next_return_button_accessibility;
	next_return_portion_button.press_data.hoverable = next_return_button_accessibility;

	if (next_portion_button_accessibility)
	{
		e->UpdateSimpleTextButton(&next_portion_button, e->blank_camera, &main_layer, 0, {});
	}
	else
	{
		if (previous_next_portion_button_accessibility)
		{
			next_portion_button.press_data.Reset();
		}
	}

	if (previous_portion_button_accessibility)
	{
		e->UpdateSimpleTextButton(&previous_portion_button, e->blank_camera, &main_layer, 0, {});
	}
	else
	{
		if (previous_previous_portion_button_accessibility)
		{
			previous_portion_button.press_data.Reset();
		}
	}

	if (previous_return_button_accessibility)
	{
		e->UpdateSimpleTextButton(&previous_return_portion_button, e->blank_camera, &main_layer, 0, {});
	}
	else
	{
		if (previous_previous_return_button_accessibility)
		{
			previous_return_portion_button.press_data.Reset();
		}
	}

	if (next_return_button_accessibility)
	{
		e->UpdateSimpleTextButton(&next_return_portion_button, e->blank_camera, &main_layer, 0, {});
	}
	else
	{
		if (previous_next_return_button_accessibility)
		{
			next_portion_button.press_data.Reset();
		}
	}

	if (finish_portion_button_accessibility)
	{
		e->UpdateSimpleTextButton(&finish_portion_button, e->blank_camera, &main_layer, 0, {});
	}
	else
	{
		if (previous_finish_portion_button_accessibility)
		{
			finish_portion_button.press_data.Reset();
		}
	}

	previous_next_portion_button_accessibility = next_portion_button_accessibility;
	previous_previous_portion_button_accessibility = previous_portion_button_accessibility;
	previous_finish_portion_button_accessibility = finish_portion_button_accessibility;
	previous_previous_return_button_accessibility = previous_return_button_accessibility;
	previous_next_return_button_accessibility = next_return_button_accessibility;


	e->UpdateSimpleTextButton(&skedaddle_button, e->blank_camera, &main_layer, 0, {});
	if (skedaddle_button.press_data.first_frame_released)
	{
		SetScene(5, 0);
		return;
	}



	if (complete_lesson_cutscene_timer == -1.0)
	{
		if (next_portion_button.press_data.first_frame_released || e->input.j.first_frame_pressed)
		{
			SetCurrentTextPortionIndex(GetCurrentCoursePath()->current_portion_index + size_t(1), 0, 0);
		}
		if (previous_portion_button.press_data.first_frame_released)
		{
			SetCurrentTextPortionIndex(GetCurrentCoursePath()->current_portion_index - size_t(1), 0, 0);
		}


		if (finish_portion_button.press_data.first_frame_released)
		{
			SetCurrentTextPortionIndex(GetCurrentCoursePath()->portions.size(), 0, 0);
			complete_lesson_cutscene_timer = 0.0;

			Mix_PlayChannel(2, confetti_sound, 0);
			for (size_t i = 0; i < size_t(50); i++)
			{
				confetti.push_back({ (unsigned char)e->GetRandInt(0, 5), {0.0, finish_portion_button.parent_rect.GetUniEdge({3})}, {e->GetRandDouble(-8.0, 8.0), e->GetRandDouble(5.0, 15.0)}, 0.0});
			}
		}


		if (previous_return_portion_button.press_data.first_frame_released)
		{
			SetCurrentPathAndPortionIndexes(GetCurrentCoursePath()->return_path_index, numeric_limits<size_t>::max(), 0, 1);
		}
		
		if (next_return_portion_button.press_data.first_frame_released)
		{
			SetCurrentTextPortionIndex(GetCurrentCoursePath()->portions.size(), 0, 0);
			SetCurrentPathAndPortionIndexes(GetCurrentCoursePath()->return_path_index, numeric_limits<size_t>::max(), 0, 1);
		}



		AdvanceCurrentTextPortionTextBox(0.64, { 0.66667, 1.5 }, 1);
		CheckForLinkClicksAndGenerateSavedLinkRects(0.8, { 0.66667, 1.5 }, 1, 0);
	}



	// COURSE SPECIFIC UPDATING

	const CoursePath* current_course_path = GetCurrentCoursePath();
	const size_t current_portion_index = current_course_path->current_portion_index;

	if (current_course_path)
	{
		if (current_course_path == &intro_main)
		{
			UpdateGooberPos();

			switch (current_portion_index)
			{
			case 0:
				break;
			}
		}
	}





	if (complete_lesson_cutscene_timer != -1.0)
	{
		if (complete_lesson_cutscene_timer >= 2.3)
		{
			SetScene(5, 0);
			return;
		}

		UpdateConfetti();


		complete_lesson_cutscene_timer += 1.0 / e->frame_rate;
	}


	//Update visual-related member variables
	ReduceStretchInCurrentTextPortionTextBox(0.2);

	UpdateCoursePathPathProgressBars();
}
void Program::DrawScene4()
{
	e->DrawTextBox(&current_text_portion_text_box, e->blank_camera);

	for (size_t i = 0; i < saved_link_rects.size(); i++)
	{
		if (saved_link_rects[i].hovering)
		{
			if (saved_link_rects[i].pressed)
			{
				e->DrawRectStructOne(&saved_link_rects[i].rect, { 0, 0, 200, 60 }, e->blank_camera);
			}
			else
			{
				e->DrawRectStructOne(&saved_link_rects[i].rect, { 0, 0, 200, 40 }, e->blank_camera);
			}
		}
		else
		{
			e->DrawRectStructOne(&saved_link_rects[i].rect, { 0, 0, 200, 20 }, e->blank_camera);
		}
	}

	/*
	for (size_t i = 0; i < course_text[current_text_portion_index]->links.size(); i++)
	{
		const TextLink current_link = course_text[current_text_portion_index]->links[i];
		vector<RectStructOne>* temp_rects = current_text_portion_text_box.GetSegmentHitbox(current_link.begin_char, current_link.end_char);
		for (size_t j = 0; j < temp_rects->size(); j++)
		{
			e->DrawRectStructOne(&temp_rects->at(j), { 0, 0, 200, 50 }, e->blank_camera);
		}
	}
	*/

	if (course_path_text_box.chars.size() > 0)
	{
		//e->DrawRectangle(&course_path_rectangle, { 220, 220, 220, 255 }, e->blank_camera);
		e->DrawTextBox(&course_path_text_box, e->blank_camera);
	}

	DrawCoursePathPathProgressBars();
	const Point2D mouse_blank = e->GetMousePos(e->blank_camera);
	//if (OverlapPoint2DWithRectangle(&mouse_blank, &path_progress_bar.back_rect, 1))
	//{
	//	e->DrawTextBox(&progress_bar_text_box, e->blank_camera);
	//}


	//Draw the previous, next, return, and finish buttons
	const bool at_first_portion = GetCurrentCoursePath()->current_portion_index == size_t(0);
	const bool at_last_portion = (GetCurrentCoursePath()->current_portion_index + size_t(1)) >= GetCurrentCoursePath()->portions.size();
	const bool has_return_path_index = (GetCurrentCoursePath()->return_path_index != numeric_limits<size_t>::max());



	if (has_return_path_index)
	{
		if (at_last_portion)
		{
			e->DrawSimpleTextButton(&next_return_portion_button, e->blank_camera);
		}
		else
		{
			e->DrawSimpleTextButton(&next_portion_button, e->blank_camera);
		}
	}
	else
	{
		if (at_last_portion)
		{
			e->DrawSimpleTextButton(&finish_portion_button, e->blank_camera);
		}
		else
		{
			e->DrawSimpleTextButton(&next_portion_button, e->blank_camera);
		}
	}

	if (at_first_portion)
	{
		if (has_return_path_index)
		{
			e->DrawSimpleTextButton(&previous_return_portion_button, e->blank_camera);
		}
		else
		{
			e->DrawSimpleTextButton(&previous_portion_button, e->blank_camera);
		}
	}
	else
	{
		e->DrawSimpleTextButton(&previous_portion_button, e->blank_camera);
	}

	e->DrawSimpleTextButton(&skedaddle_button, e->blank_camera);


	// COURSE SPECIFIC DRAWING

	const CoursePath* current_course_path = GetCurrentCoursePath();
	const size_t current_portion_index = current_course_path->current_portion_index;

	if (current_course_path)
	{
		if (current_course_path == &intro_main)
		{
			e->DrawTexture(goober_texture, e->blank_camera, &goober_rectangle);

			switch (current_portion_index)
			{
			case 0:
				break;
			}
		}
	}







	//Draw Confetti
	DrawConfetti(e->blank_camera);

	if (update_and_draw_tool_tip_this_frame)
	{
		e->UpdateToolTip(&link_tool_tip, e->blank_camera);
		e->DrawToolTip(&link_tool_tip, e->blank_camera);

		update_and_draw_tool_tip_this_frame = 0;
	}
}
void Program::PostDrawRunScene4()
{
	//Nothin
}

void Program::SetScene5()
{
	for (size_t i = 0; i < lessons.size(); i++)
	{
		lessons[i]->button.press_data.Reset();

		if (lessons[i]->main_path_index < course_paths.size())
		{
			lessons[i]->progress_bar.SetActualWidth(course_paths[lessons[i]->main_path_index]->progress, course_paths[lessons[i]->main_path_index]->portions.size(), 0);
		}
		else
		{
			lessons[i]->progress_bar.SetActualWidth(200.0, 0);

			cout << "lessons[i]->main_path_index out of range bozo!!@!!1! Sent from SetScene5()" << endl;
		}
	}
}
void Program::EndScene5()
{

}
void Program::RunScene5()
{
	e->UpdateScrollBar(&lessons_scroll_bar, e->blank_camera, &main_layer, 0, { &main_layer });
	if (UpdateLessons())
	{
		return;
	}
}
void Program::DrawScene5()
{
	e->DrawScrollBar(&lessons_scroll_bar, e->blank_camera);
	DrawLessons();
}
void Program::PostDrawRunScene5()
{

}

void Program::SetScene6()
{

}
void Program::EndScene6()
{

}
void Program::RunScene6()
{
	if (e->input.j.pressed)
	{
		//val_1_1.v[0] -= 1.0;
		//val_1_1.v[1] -= 0.5;

		test_rect_new.pos.x -= 1.0;
		test_rect_new.pos.y -= 0.5;
	}
	if (e->input.k.pressed)
	{
		//val_1_1.v[0] += 1.0;
		//val_1_1.v[1] += 0.5;

		test_rect_new.pos.x += 1.0;
		test_rect_new.pos.y += 0.5;
	}

	if (e->input.n.pressed)
	{
		//val_1_2.v[0] *= 0.8;
		//val_1_2.v[1] *= 0.8;

		test_rect_new.transformations.scale.width_scale *= 0.95;
		test_rect_new.transformations.scale.height_scale *= 0.95;
	}
	if (e->input.m.pressed)
	{
		//val_1_2.v[0] *= 1.25;
		//val_1_2.v[1] *= 1.25;

		test_rect_new.transformations.scale.width_scale /= 0.95;
		test_rect_new.transformations.scale.height_scale /= 0.95;
	}

	if (e->input.b.pressed)
	{
		test_rect_new.transformations.rotation.radians += 0.01;

		//test_90_rect.transformations.RotateCounterclockwise(1);
	}

	//val_1_3.v[0] += 0.02;

	if (e->input.v.first_frame_pressed)
	{
		//test_rect_new_two.pos.SetValueToFitUniValue({ test_point.x, test_point.y });
		//test_rect_new_two.pos.v[0] += 5.0;

		//test_rect_new_two.transformations.rotation.radians += 0.01;

		//test_90_rect_two.transformations.RotateCounterclockwise(1);
	}

	if (e->input.g.pressed)
	{
		test_rect_new.transformations.scale.width_scale -= 0.02;

		//test_rect_new_two.transformations.total_flip.flip_horizontally = !test_rect_new_two.rotate_scale_flip.total_flip.flip_horizontally;
	}
	if (e->input.h.pressed)
	{
		test_rect_new.transformations.scale.width_scale += 0.02;

		//test_rect_new_two.transformations.total_flip.flip_vertically = !test_rect_new_two.rotate_scale_flip.total_flip.flip_vertically;
	}

	if (e->input.u.first_frame_pressed)
	{
		//test_rect_new_two.SetUniCorner({ test_point.x, test_point.y }, CornerEnum::TOP_RIGHT);
		//test_rect_new_two.pos.SetValueToFitUniValue({ test_point.x, test_point.y });
	}

	if (e->input.p.first_frame_pressed)
	{
		RectangleNewest temp_rect;
		temp_rect.pos = Point2DNew(test_rect_new.pos.x, test_rect_new.pos.y);
		temp_rect.unscaled_size = test_rect_new.unscaled_size;
		temp_rect.centering = test_rect_new.centering;
		temp_rect.transformations = Transformations(test_rect_new.transformations.rotation, test_rect_new.transformations.scale, test_rect_new.transformations.total_flip);

		ListProperties(temp_rect);
	}
}
void Program::DrawScene6()
{
	//const vector<double> temp_1 = val_1_1.GetUniValue();
	//const vector<double> temp_2 = val_2.GetUniValue();

	//Point2D p1 = { temp_1[0], temp_1[1] };
	//Point2D p2 = { temp_2[0], temp_2[1] };

	//e->DrawPoint(&p1, { 8.0, 8.0 }, { 0, 0, 0, 255 }, e->blank_camera);
	//e->DrawPoint(&p2, { 8.0, 8.0 }, { 0, 0, 0, 255 }, e->blank_camera);

	e->DrawTextureWithRefRectangleNewest(&test_rect_new, nullptr, nullptr, nullptr, nullptr);
	e->DrawTextureWithRefRectangleNewest(&test_rect_new_two, nullptr, nullptr, nullptr, nullptr);
	//e->DrawTextureWithRefRectangleNewest(&test_rect_new_three, nullptr, nullptr, nullptr, nullptr);

	//e->DrawTexturedRefRectangle90(&test_90_rect, nullptr, nullptr, nullptr, nullptr);
	//e->DrawTexturedRefRectangle90(&test_90_rect_two, nullptr, nullptr, nullptr, nullptr);

	//Point2D p3 = { test_point.x, test_point.y };

	//e->DrawPoint(&p3, { 8.0, 8.0 }, { 0, 0, 0, 255 }, e->blank_camera);
}
void Program::PostDrawRunScene6()
{

}

void Program::SetScene7()
{
	example1_text_box.GenerateFull();

	cout << example1_text_box.lines.size() << endl;
}
void Program::EndScene7()
{

}
void Program::RunScene7()
{

}
void Program::DrawScene7()
{
	const Quad temp_quad = example1_text_box.rect.GetUniQuad();
	const GLColor temp_color(0.f, 0.f, 0.f, 0.2f);

	e->DrawQuad(&temp_quad, &temp_color, nullptr);

	const Quad temp_quad2 = example1_text_box.lines[0].rect.GetUniQuad();
	e->DrawQuad(&temp_quad2, &temp_color, nullptr);

	e->DrawBasicTextBox(&example1_text_box, nullptr);
}
void Program::PostDrawRunScene7()
{

}

void Program::SetScene8()
{

}
void Program::EndScene8()
{

}
void Program::RunScene8()
{

}
void Program::DrawScene8()
{

}
void Program::PostDrawRunScene8()
{

}

void Program::SetScene9()
{

}
void Program::EndScene9()
{

}
void Program::RunScene9()
{

}
void Program::DrawScene9()
{

}
void Program::PostDrawRunScene9()
{

}

Program::Program() : e(nullptr), example1_font("default_white_basic", "png", LineParameters(7.0, 1.0, 1.0, numeric_limits<double>::max(), { 0.0, 0.0 }, false, true)), example1_text_box(&example1_font, RefRectangleNewest({ 0.0, 0.0 }, RefTransformations(Rotation2DNew(), Scale2DNew(4.0, 4.0), TotalFlip()), { 100.0, 25.0 }, { 0.0, 0.0 }))
{
	e = new Engine();

	main_camera = e->NewCamera("Main");

	const double blank_camera_right_edge = e->blank_camera->rect.GetUniEdge({ 0 });
	const double blank_camera_bottom_edge = e->blank_camera->rect.GetUniEdge({ 1 });
	const double blank_camera_left_edge = e->blank_camera->rect.GetUniEdge({ 2 });
	const double blank_camera_top_edge = e->blank_camera->rect.GetUniEdge({ 3 });






	//-----------------   COURSE STUFFS SCENE 4   -----------------

	{
		test_cset.InitLeast(&e->default_font);
		test_cset.number_display.CreateDebugData({ &e->engine_debug_data_container }, &e->default_font, "number_display", { 2 }, 1);
		test_cset.set.push_back(new Cell());
		test_cset.set.push_back(new Cell());
		test_cset.set.push_back(new Cell());



		//Initialze portion_text_box
		current_text_portion_text_box.InitLeast(&e->default_font);
		current_text_portion_text_box.text_wrap = 1;
		current_text_portion_text_box.parent_rect.size.width = e->blank_camera->rect.size.width;
		current_text_portion_text_box.parent_rect.size.height = e->blank_camera->rect.size.height / 3.0;
		current_text_portion_text_box.parent_rect.SetBaseSizeWithSizeScale({ 4.0, 4.0 });
		current_text_portion_text_box.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });



		//Initialize the next, previous, return, and finish buttons
		Size2D course_button_size = { 50.0, 13.0 };

		next_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Next", &e->default_font, course_button_size, 4.0, 4.0, { 0.0, 0.0 }, 0);
		next_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_right_edge, { 0 });
		next_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
		next_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

		previous_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Prev", &e->default_font, course_button_size, 4.0, 4.0, { 0.0, 0.0 }, 0);
		previous_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_left_edge, { 2 });
		previous_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
		previous_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

		previous_return_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Return", &e->default_font, course_button_size, 4.0, 4.0, { 0.0, 0.0 }, 0);
		previous_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_left_edge, { 2 });
		previous_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
		previous_return_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };
		previous_return_portion_button.press_data.hoverable = 0;
		previous_return_portion_button.press_data.pressable = 0;

		//Maybe call "done"?

		next_return_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Return", &e->default_font, course_button_size, 4.0, 4.0, { 0.0, 0.0 }, 0);
		next_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_right_edge, { 0 });
		next_return_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
		next_return_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };
		next_return_portion_button.press_data.hoverable = 0;
		next_return_portion_button.press_data.pressable = 0;

		finish_portion_button.InitWithBaseSize({ 4.0, 4.0 }, "Finish", &e->default_font, course_button_size, 4.0, 4.0, { 0.0, 0.0 }, 0);
		finish_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_right_edge, { 0 });
		finish_portion_button.parent_rect.SetPosWithUniEdge(blank_camera_bottom_edge, { 1 });
		finish_portion_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };
		finish_portion_button.press_data.hoverable = 0;
		finish_portion_button.press_data.pressable = 0;


		skedaddle_button.InitWithMargin({ 4.0, 4.0 }, "Skeddadle", &e->default_font, { 24.0, 12.0 }, 4.0, 4.0);
		skedaddle_button.parent_rect.SetPosWithUniEdge(blank_camera_left_edge, { 2 });
		skedaddle_button.parent_rect.SetPosWithUniEdge(blank_camera_top_edge, { 3 });
		skedaddle_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };






		course_path_rectangle.size.width = e->blank_camera->rect.size.width;
		course_path_rectangle.size.height = 26.0;
		course_path_rectangle.SetBaseSizeWithSizeScale({ 2.0, 2.0 });
		course_path_rectangle.SetPosWithUniEdge(previous_portion_button.parent_rect.GetUniEdge({ 3 }), { 1 });
		course_path_rectangle.SetPosWithUniEdge(e->blank_camera->rect.GetUniEdge({ 2 }), { 2 });
		course_path_rectangle.pos.x += 6.0;
		course_path_rectangle.pos.y += 6.0;

		course_path_text_box.InitMost(&e->default_font, course_path_rectangle, "Path: main", { 0 }, { 0 }, 0);

		course_path_rectangle.base_size = { 1.0, 1.0 };
		course_path_rectangle.pos.x -= 6.0;
		course_path_rectangle.pos.y -= 6.0;


		link_tool_tip.InitLeast(&e->default_font);
	}
	





	// ---------- COURSE SPECIFIC DATA ----------

	{
		goober_texture->LoadTexture("images/program/little_fellow_fade_out_fix.png");
		goober_max_anim_counter = (unsigned int)round(e->frame_factor * 16.0);
		if (goober_max_anim_counter == 0)
		{
			goober_max_anim_counter = 1;
		}
		goober_anim_counter = 0;
		goober_rectangle.size = { 216.0, 208.0 };
		goober_rectangle.pos = { 0.0, 0.0 };


		intro_main.path_name = "Intro";

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("Ello, it's me, lead developer of PLACEHOLDER!", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("I\'m going to assume that you wish to learn how to develop games, seeing as you clicked the \"how to develop games\" button.", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("If not, you can always skedaddle by clicking the aptly named \"skedaddle\" button.", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("For those of you who do wish to learn game development though, I should give you some information before we start the course.", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("First of all, game development takes a LOT of effort. Video games incorporate computer programming, digital art, and sound design all into one package.", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("Even simple-looking games like Undertale or Omori can easily take upwards of 5 years to complete!", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("Essentially, this is my reminder to be patient.", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("This course should only take around 20 hours to complete though (hopefully not 5 years).", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("And if you finish, you should be ready to start developing your first (or maybe not first) game!", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("You don\'t need to know anything about computer programming to take this course, but if you do, you can skip things you already know.", 1);

		intro_main.portions.push_back(new TextPortion());
		intro_main.portions.back()->InitLeast("Okay, that\'s it for the intro, good luck!", 1);

		course_paths.push_back(&intro_main);



		lesson_1_main.path_name = "Lesson 1";

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("As I previously mentioned, a lot of parts go into making a video game, so let's simply try to recreate one part first.", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("The part we are trying to recreate is going to be the score from \"Scooby-Doo\" for the ZX Spectrum, which we will finish in a couple of lessons.", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("Look at those GRAPHICS", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("Anyways, this score is a numerical value that is displayed on the screen and increments when the player defeats enemies, which are these little ghouls here.", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("Seems pretty simple, right? (say yes please)", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("As it turns out, not really.", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("Like, how does the computer \"know\" what the number is at all times?", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("How is it able to add a certain number of points to the number?", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("How can it display this number on the screen?", 1);

		lesson_1_main.portions.push_back(new TextPortion());
		lesson_1_main.portions.back()->InitLeast("However, before we can even start to answer these questions, we need to learn about a core computer science concept: abstraction!", 1);
		lesson_1_main.portions.back()->links.push_back(TextLink());
		lesson_1_main.portions.back()->links.back().InitLeast(2, 0, 61, 128, 4);

		course_paths.push_back(&lesson_1_main);



		lesson_1_abstraction_justification.path_name = "Abstraction Justification";
		lesson_1_abstraction_justification.return_path_index = 1;

		lesson_1_abstraction_justification.portions.push_back(new TextPortion());
		lesson_1_abstraction_justification.portions.back()->InitLeast("The rest of the course will not make sense if you are not aware of this concept, unfortunately. I would love it if you could get right into it, but this is quite necessary information as it turns out. Plus, abstraction is cool! (according to me)", 1);

		course_paths.push_back(&lesson_1_abstraction_justification);





		SetCurrentPathAndPortionIndexes(0, 0, 1, 1); //This tecnically isn't course specific. However, it needs to be called after the courses are created (I think)

	}
	





	//-----------------   COURSE STUFFS SCENE 5   -----------------

	lessons_scroll_bar.InitBasic(20.0 * 160.0, e->blank_camera->rect.size.height, e->blank_camera->rect, 32.0, 0);
	AddLesson("Intro", 0, 10, 0);
	AddLesson("Lesson 1", 0, 15, 1);






	// -----------------   SOUNDS   -----------------

	InitSounds();






	// -----------------   INITIALIZE MOUSE LAYERS   -----------------

	main_layer.Init(&e->mouse_layers);






	// -----------------   INITIALIZE GAME HOME SCREEN   -----------------

	{
		const double window_width_scaling = (double)e->window_width / (double)DEFAULT_WINDOW_WIDTH;
		const double window_height_scaling = (double)e->window_height / (double)DEFAULT_WINDOW_HEIGHT;

		double lesser_scale;
		if (window_width_scaling <= window_height_scaling)
		{
			lesser_scale = window_width_scaling;
		}
		else
		{
			lesser_scale = window_height_scaling;
		}
		const double five_lesser_scale = lesser_scale * 5.0;

		Size2D editing_button_size = { 100.0, 24.0 };
		const double editing_button_list_x = 600.0;
		const double editing_button_list_y = 400.0;
		const double editing_button_spacing_y = 180.0;

		code_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Code", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
		//code_button.CreateDebugData({ &e->engine_debug_data_container }, "Code Button", { 1 });
		code_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 0.0)) / window_height_scaling };
		code_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

		images_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Images", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
		images_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 1.0)) / window_height_scaling };
		images_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

		sounds_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Sounds", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
		sounds_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 2.0)) / window_height_scaling };
		sounds_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

		other_files_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Other Files", &e->default_font, editing_button_size, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
		other_files_button.parent_rect.pos = { editing_button_list_x / window_width_scaling, (editing_button_list_y - (editing_button_spacing_y * 3.0)) / window_height_scaling };
		other_files_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };

		run_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Run", &e->default_font, { 200.0, 24.0 }, five_lesser_scale, five_lesser_scale, { 0.0, 0.0 }, 0);
		run_button.parent_rect.pos.x = -300.0 / window_width_scaling;
		run_button.parent_rect.SetPosWithUniEdge(other_files_button.parent_rect.GetUniEdge({ 1 }), { 1 });
		run_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };


		back_button.InitWithBaseSize({ five_lesser_scale, five_lesser_scale }, "Back", &e->default_font, { 14.0, e->window_height / five_lesser_scale }, five_lesser_scale, five_lesser_scale, { 14.0 * five_lesser_scale, 0.0 }, 1);
		//back_button.CreateDebugData({ &e->engine_debug_data_container }, "Back Button", {});
		back_button.parent_rect.SetPosWithUniEdge(main_camera->rect.GetUniEdge({ 2 }), { 2 });
		back_button.text_box.text_wrap = 1;
		back_button.text_box.parent_rect.base_size.width = 4.0;
		back_button.text_box.parent_rect.size.width = 4.0;
		back_button.sounds = { nullptr, nullptr, e->click_press_sound, e->click_release_sound, 0 };
	}
	




	// -----------------   INITIALIZE ANIMATIONS?   -----------------

	{
		run_anim.LoadFrames("images/program/player/run_anim", 8, 10.0);

		idle_anim.LoadFrames("images/program/player/idle_anim", 3, 2.0);
		idle_anim.frames.back().frame_length = 0.1;

		swim_anim.LoadFrames("images/program/player/swim_anim", 5, 10.0);

		pride_anim.LoadFrames("images/program/player/pride_anim", 6, 10.0);
		pride_anim.offset.x = 4.5;

		player.hitbox.base_size = idle_anim.dimentions;
		player.hitbox.SetSizeWithSizeScale(Size2D{ 4.0, 4.0 });
		player.hitbox.base_size = player.hitbox.size;

		player.sprite.rect = player.hitbox;
		player.sprite.rect.SetBaseSizeWithSizeScale({ 4.0, 4.0 });
		player.sprite.LoadAnimation(&idle_anim);

		light_ground->LoadTexture("images/program/ground_tiles/light_ground.png");
		dark_ground->LoadTexture("images/program/ground_tiles/dark_ground.png");
		grassy_ground->LoadTexture("images/program/ground_tiles/grass.png");
		cobble_ground->LoadTexture("images/program/ground_tiles/cobble.png");
		ground_highlight->LoadTexture("images/program/ground_tiles/ground_highlight.png");
		water_ground.LoadFrames("images/program/ground_tiles/water", 38, 5.0);

		tree->LoadTexture("images/program/ground_accessories/tree.png");
	}
	

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			ground.tile_data[x][y] = 3;
		}
	}

	ground.tile_data[0][0] = 1;
	ground.tile_data[1][0] = 2;
	ground.tile_data[2][0] = 4;
	ground.tile_data[3][0] = 5;
	ground.tile_data[4][0] = 6;

	test_box.InitLeast(&e->default_font);
	test_box.CreateDebugData({ &e->engine_debug_data_container }, &e->default_font, "Test Box", { 1 }, 1);
	test_box.parent_rect.base_size = { 100.0, 50.0 };
	test_box.parent_rect.SetSizeWithSizeScale({ 1.0, 1.0 });
	test_box.AddCharPtr("Here are words that \nare cool");
	test_box.UpdateCharPos();


	test_rect.pos = { 100.0, 100.0 };
	test_rect.base_size = { 80.0, 80.0 };
	test_rect.SetSizeWithSizeScale({ 1.0, 1.0 });


	/*
	test_box_two.InitLeast(&e->default_font);
	test_box_two.CreateDebugData({ &e->engine_debug_data_container }, "Test Box Two", { 1 });
	test_box_two.debug_data_container.debug_id = 4;
	test_box_two.parent_rect.base_size = { 100.0, 50.0 };
	test_box_two.parent_rect.SetSizeWithSizeScale({ 1.0, 1.0 });
	//test_box->AddCharPtr("Here are words that \nare cool");
	test_box_two.AddCharPtr("Skibidi");
	test_box_two.UpdateCharPos();
	*/

	test_container.InitLeast({}, &e->default_font, "Test Container", nullptr, {}, 1);





	// ----------- TEST RECTANGLE ROTATION -----------

	//val_2.reference_point = &val_1_1;
	//val_2.reference_scale = &val_1_2;
	//val_2.reference_rotation = &val_1_3;
	//val_2.v[0] = 20.0;
	//val_2.v[1] = 40.0;

	test_rect_new.centering = { 1.0, -1.0 };

	test_rect_new_two.pos = { -100.0, 50.0 };
	test_rect_new_two.unscaled_size = { 50.0, 25.0 };
	test_rect_new_two.transformations.rotation = { 0.5 };
	test_rect_new_two.SetReference(&test_rect_new);

	//test_rect_new_three.pos = { 80.0, 60.0 };
	//test_rect_new_three.unscaled_size = { 25.0, 50.0 };
	//test_rect_new_three.transformations.rotation = { 0.5 };
	//test_rect_new_three.SetReference(&test_rect_new_two);



	//test_90_rect.pos = { -200.0, -50.0 };

	//test_90_rect_two.pos = { 100.0, 50.0 };
	//test_90_rect_two.unscaled_size = { 50.0, 50.0 };
	//test_90_rect_two.SetReference(&test_90_rect);







	example1_font.LoadCharTextures();
	example1_text_box.AddCharPtr("abcdefghijklmnopqrstuvwxyz");
	//example1_text_box.Init(&example1_font, "chicken nuggies", RefRectangleNewest({ 0.0, 0.0 }, RefTransformations(Rotation2DNew(), Scale2DNew(4.0, 4.0), TotalFlip()), Size2DNew(100.0, 25.0), Centering2DNew()), { 0.0, 0.0 });

	/*
	cout << "text_box.chars.size(): " << example1_text_box.chars.size() << endl;

	cout << "font char color mod: " << example1_font.c.template_color_mod.r << ", " << example1_font.c.template_color_mod.g << ", " << example1_font.c.template_color_mod.b << ", " << example1_font.c.template_color_mod.a << endl;

	if (example1_text_box.chars.size() != 0)
	{
		cout << "first char value: " << example1_text_box.chars[0].char_value << endl;
		cout << "first char color mod: " << example1_text_box.chars[0].color_mod.r << ", " << example1_text_box.chars[0].color_mod.g << ", " << example1_text_box.chars[0].color_mod.b << ", " << example1_text_box.chars[0].color_mod.a << endl;
	}

	cout << "example1_text_box.default_font->c.char_value: " << example1_text_box.default_font->c.char_value << endl;
	cout << "example1_text_box.default_font->GetFontCharConst('c')->char_value: " << example1_text_box.default_font->GetFontCharConst('c')->char_value << endl;
	*/
}
Program::~Program()
{
	delete e;

	DestroySounds();
}

// -----------------   SET SCENE FUNCTIONS   -----------------

void Program::NumSwitchScene()
{
	if (e->input.one.first_frame_pressed)
	{
		SetScene(1, 0);
		return;
	}
	if (e->input.two.first_frame_pressed)
	{
		SetScene(2, 0);
		return;
	}
	if (e->input.three.first_frame_pressed)
	{
		SetScene(3, 0);
		return;
	}
	if (e->input.four.first_frame_pressed)
	{
		SetScene(4, 0);
		return;
	}
	if (e->input.five.first_frame_pressed)
	{
		SetScene(5, 0);
		return;
	}
	if (e->input.six.first_frame_pressed)
	{
		SetScene(6, 0);
		return;
	}
	if (e->input.seven.first_frame_pressed)
	{
		SetScene(7, 0);
		return;
	}
	if (e->input.eight.first_frame_pressed)
	{
		SetScene(8, 0);
		return;
	}
	if (e->input.nine.first_frame_pressed)
	{
		SetScene(9, 0);
		return;
	}
}
void Program::SetScene(const int param_scene, const bool run_new_scene)
{
	EndScene();

	e->scene = param_scene;
	switch (param_scene)
	{
	case 1:
		SetScene1();
		break;
	case 2:
		SetScene2();
		break;
	case 3:
		SetScene3();
		break;
	case 4:
		SetScene4();
		break;
	case 5:
		SetScene5();
		break;
	case 6:
		SetScene6();
		break;
	case 7:
		SetScene7();
		break;
	case 8:
		SetScene8();
		break;
	case 9:
		SetScene9();
		break;
	}

	if (run_new_scene)
	{
		Run();
	}
}
void Program::EndScene()
{
	switch (e->scene)
	{
	case 1:
		EndScene1();
		break;
	case 2:
		EndScene2();
		break;
	case 3:
		EndScene3();
		break;
	case 4:
		EndScene4();
		break;
	case 5:
		EndScene5();
		break;
	case 6:
		EndScene6();
		break;
	case 7:
		EndScene7();
		break;
	case 8:
		EndScene8();
		break;
	case 9:
		EndScene9();
		break;
	}
}