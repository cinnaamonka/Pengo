#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <iostream>

#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#include "./Minigin/Singleton.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "3rdParty/imgui.h"
#include "3rdParty/imgui_impl_opengl3.h"
#include "3rdParty/imgui_impl_sdl2.h"
#include "3rdParty/imgui_internal.h"
#include "3rdParty/imgui_plot.h"
#include <stdio.h>
#include <SDL.h>

