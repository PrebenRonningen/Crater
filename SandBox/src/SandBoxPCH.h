#pragma once
#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")
#pragma comment(lib,"SDL2_ttf.lib")

#pragma comment(lib,"xinput.lib")

// SDL Headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>

// Imgui
#include <imgui.h>
#include "Crater/ImGui/imgui_impl_sdl.h"
#include "Crater/ImGui/imgui_impl_opengl2.h"

// std
#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream

#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef _DEBUG
#include "vld.h"
#endif