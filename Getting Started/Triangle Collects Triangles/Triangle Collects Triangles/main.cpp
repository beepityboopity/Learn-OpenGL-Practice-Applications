#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// https://www.topcoder.com/thrive/articles/Geometry Concepts part 2:%20 Line Intersection and its Applications

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float vertices[]);
bool calculateCollision(float x1, float x2, float y1, float y2, float x3, float x4, float y3, float y4);
bool collisionCheck(float triangle1[], float triangle2[]);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.2f, 0.9f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9f, 0.0f, 0.1f, 1.0f);\n"
"}\n\0";

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float player[] = {
        -0.1f, -0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        0.0f, 0.1f, 0.0f,
};

float meats[] = {
        -0.9f, -0.9f, 0.0f,
        -0.7f, -0.9f, 0.0f,
        -0.8f, -0.7f, 0.0f,
};

int score = 0;

int main() {
    srand(static_cast <unsigned> (time(0)));
    glfwInit();
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle Cannibalism", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsClassic();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentOne = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentTwo = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderOne = glCreateProgram();
    unsigned int shaderTwo = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentOne, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentOne);
    glShaderSource(fragmentTwo, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentTwo);

    glAttachShader(shaderOne, vertexShader);
    glAttachShader(shaderOne, fragmentOne);
    glLinkProgram(shaderOne);

    glAttachShader(shaderTwo, vertexShader);
    glAttachShader(shaderTwo, fragmentTwo);
    glLinkProgram(shaderTwo);

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
   
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, player);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (collisionCheck(player, meats)) {
            float rx = -0.9f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.9f - (-0.9f))));
            float ry = -0.9f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.9f - (-0.9f))));
            meats[0] = rx - 0.1;
            meats[1] = ry - 0.1;
            meats[3] = rx + 0.1;
            meats[4] = ry - 0.1;
            meats[6] = rx;
            meats[7] = ry + 0.1; 
            score += 1;
        }

        ImGui::Begin("Cannibalized Triangles");
        ImGui::Text(std::to_string(score).c_str());
        ImGui::End();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(player), player, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(VAOs[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(meats), meats, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
       
        glUseProgram(shaderOne);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderTwo);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window, float player[])
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float moveSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && player[7] < 1.0f) {
        player[1] += moveSpeed * 0.2;
        player[4] += moveSpeed * 0.2;
        player[7] += moveSpeed * 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && player[4] > -1.0f) {
        player[1] -= moveSpeed * 0.2;
        player[4] -= moveSpeed * 0.2;
        player[7] -= moveSpeed * 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && player[0] > -1.0f) {
        player[0] -= moveSpeed * 0.2;
        player[3] -= moveSpeed * 0.2;
        player[6] -= moveSpeed * 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && player[3] < 1.0f) {
        player[0] += moveSpeed * 0.2;
        player[3] += moveSpeed * 0.2;
        player[6] += moveSpeed * 0.2;
    } 
}

bool calculateCollision(float x1, float x2, float y1, float y2, float x3, float x4, float y3, float y4) {
    float A1 = y2 - y1;
    float B1 = x1 - x2;
    float C1 = A1 * x1 + B1 * y1;

    float A2 = y4 - y3;
    float B2 = x3 - x4;
    float C2 = A2 * x3 + B2 * y3;

    float det = A1 * B2 - A2 * B1;
    float x = (B2 * C1 - B1 * C2) / det;
    float y = (A1 * C2 - A2 * C1) / det;
    
    if (std::min(x1, x2) <= x && x <= std::max(x1, x2) && 
        std::min(x3, x4) <= x && x <= std::max(x3, x4) &&
        std::min(y1, y2) <= y && y <= std::max(y1, y2) &&
        std::min(y3, y4) <= y && y <= std::max(y3, y4)) {
        return true;
    }
    else {
        return false;
    }
}

bool collisionCheck(float triangle1[], float triangle2[]) {
    bool check1 = calculateCollision(triangle1[0], triangle1[3], triangle1[1], triangle1[4],
        triangle2[0], triangle2[6], triangle2[1], triangle2[7]);
    
    bool check2 = calculateCollision(triangle1[0], triangle1[3], triangle1[1], triangle1[4],
        triangle2[3], triangle2[6], triangle2[4], triangle2[7]);

    bool check3 = calculateCollision(triangle1[0], triangle1[6], triangle1[1], triangle1[7],
        triangle2[0], triangle2[3], triangle2[1], triangle2[4]);

    bool check4 = calculateCollision(triangle1[0], triangle1[6], triangle1[1], triangle1[7],
        triangle2[3], triangle2[6], triangle2[4], triangle2[7]);

    bool check5 = calculateCollision(triangle1[3], triangle1[6], triangle1[4], triangle1[7],
        triangle2[0], triangle2[3], triangle2[1], triangle2[4]);

    bool check6 = calculateCollision(triangle1[3], triangle1[6], triangle1[4], triangle1[7],
        triangle2[0], triangle2[6], triangle2[1], triangle2[7]);
    
    if ((check1 || check2) || (check3 || check4) || (check5 || check6)) {
        return true;
    }
    else {
        return false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}