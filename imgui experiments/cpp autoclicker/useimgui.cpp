#include "useimgui.h"

void UseImGui::Init(GLFWwindow* window, const char* glsl_version)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsClassic();
}

void UseImGui::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

float UseImGui::RedUpdate() {
	static float red = 0.0f;
	ImGui::Begin("background color");
	ImGui::SliderFloat("red", &red, 0.0f, 1.0f);
	ImGui::End();
	return red;
}

float UseImGui::GreenUpdate() {
	static float green = 0.0f;
	ImGui::Begin("background color");
	ImGui::SliderFloat("green", &green, 0.0f, 1.0f);
	ImGui::End();
	return green;
}

float UseImGui::BlueUpdate() {
	static float blue = 0.0f;
	ImGui::Begin("background color");
	ImGui::SliderFloat("blue", &blue, 0.0f, 1.0f);
	ImGui::End();
	return blue;
}

void UseImGui::Render() {
	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UseImGui::Shutdown() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
