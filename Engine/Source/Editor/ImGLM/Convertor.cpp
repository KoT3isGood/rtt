#include "Convertor.h"

void ImGui::DragVec2(const char* label, vec2* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	float vector[2] = { v->x,v->y};
	ImGui::DragFloat2(label, vector, v_speed, v_min, v_max, format, flags);
	v->x = vector[0]; v->y = vector[1];
}

void ImGui::DragVec3(const char* label, vec3* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	float vector[3] = {v->x,v->y,v->z};
	ImGui::DragFloat3(label, vector, v_speed, v_min, v_max, format, flags);
	v->x = vector[0]; v->y = vector[1]; v->z = vector[2];
}


void ImGui::DragVec4(const char* label, vec4* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	float vector[4] = { v->x,v->y,v->z,v->w};
	ImGui::DragFloat4(label, vector, v_speed, v_min, v_max, format, flags);
	v->x = vector[0]; v->y = vector[1]; v->z = vector[2]; v->w = vector[3];
}