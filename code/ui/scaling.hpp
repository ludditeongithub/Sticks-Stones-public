#pragma once
#include <array>
#include "fonts.hpp"

constexpr int SCALE_AMT = 10;
std::array<float, SCALE_AMT> g_ui_scales = {0.25, 0.33, 0.5, 0.67, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0};
float g_scale = 1.0;

void rescale_ui(int selection)
{
	init_fonts(g_ui_scales[selection]);
	g_scale = g_ui_scales[selection];
}

