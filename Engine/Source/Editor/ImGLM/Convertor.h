#pragma once

#include "EngineMacros.h"
#include "..\..\Libraries\ImGui\imgui.h"
namespace ImGui {
	void DragVec2(const char* label, vec2 *v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	void DragVec3(const char* label, vec3* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	void DragVec4(const char* label, vec4* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
}
