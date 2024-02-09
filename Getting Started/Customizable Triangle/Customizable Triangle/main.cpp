#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imguiconfigs.h"
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 Color;\n"
"void main()\n"
"{\n"
"   FragColor = Color;\n"
"}\n\0";

int main()
{
    // initialization
    glfwInit();
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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


    //vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //create vertices and buffers
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    float redValue = 0.1f;
    float greenValue = 0.1f;
    float blueValue = 0.1f;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        myimgui.NewFrame();


        //sliders for triangle vertices
        ImGui::Begin("triangle vertices");
        ImGui::Text("Corner 1");
        ImGui::SliderFloat("x1", &vertices[0], -1.0f, 1.0f);
        ImGui::SliderFloat("y1", &vertices[1], -1.0f, 1.0f);
        ImGui::Text("Corner 2");
        ImGui::SliderFloat("x2", &vertices[3], -1.0f, 1.0f);
        ImGui::SliderFloat("y2", &vertices[4], -1.0f, 1.0f);
        ImGui::Text("Corner 3");
        ImGui::SliderFloat("x3", &vertices[6], -1.0f, 1.0f);
        ImGui::SliderFloat("y3", &vertices[7], -1.0f, 1.0f);
        ImGui::End();

        //probably a bad idea but it works
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);



        //sliders for background color
        glClearColor(myimgui.RedUpdate(), myimgui.GreenUpdate(), myimgui.BlueUpdate(), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        //sliders for triangle color
        ImGui::Begin("triangle color");
        ImGui::SliderFloat("reds", &redValue, 0.0f, 1.0f);
        ImGui::SliderFloat("greens", &greenValue, 0.0f, 1.0f);
        ImGui::SliderFloat("blues", &blueValue, 0.0f, 1.0f);
        ImGui::End();

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);


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
