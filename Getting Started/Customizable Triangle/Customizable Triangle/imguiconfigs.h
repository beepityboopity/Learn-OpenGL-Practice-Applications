#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class UseImGui {
public:
	void Init(GLFWwindow* window, const char* glsl_version);
	void NewFrame();
	virtual float RedUpdate();
	virtual float GreenUpdate();
	virtual float BlueUpdate();
	void Render();
	void Shutdown();
};
