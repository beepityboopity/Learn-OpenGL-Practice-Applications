#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <imgui.h>
#include "useimgui.h"
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    UseImGui myimgui;
    myimgui.Init(window, glsl_version);
    static float red, green, blue;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        myimgui.NewFrame();
        glClearColor(myimgui.RedUpdate(), myimgui.GreenUpdate(), myimgui.BlueUpdate(), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        
        myimgui.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    myimgui.Shutdown();
    glfwTerminate();
    return 0;
}



void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
