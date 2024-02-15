#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

// https://www.topcoder.com/thrive/articles/Geometry Concepts part 2:%20 Line Intersection and its Applications

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float vertices[]);
void calculateLines(float vertices[]);
void collisionCheck(float triangle1[], float triangle2[]);

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
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float player[] = {
        -0.1f, -0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        0.0f, 0.1f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
        
};

float meats[] = {
        -0.9f, -0.9f, 0.0f,
        -0.7f, -0.9f, 0.0f,
        -0.8f, -0.7f, 0.0f, 

        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
};

int main() {

    calculateLines(player);
    calculateLines(meats);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle Collects Triangles", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, player);
        calculateLines(player);
        collisionCheck(player, meats);






        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(player), player, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
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

// whenever the window size changes this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void calculateLines(float vertices[]) {
    //01 34 - 9 10 11
    vertices[9] = vertices[4] - vertices[1];
    vertices[10] = vertices[0] - vertices[3];
    vertices[11] = vertices[9] * vertices[0] + vertices[10] * vertices[1];
    //01 67 - 12 13 14
    vertices[12] = vertices[7] - vertices[1];
    vertices[13] = vertices[0] - vertices[6];
    vertices[14] = vertices[12] * vertices[0] + vertices[13] * vertices[1];
    //34 67 - 15 16 17
    vertices[15] = vertices[7] - vertices[4];
    vertices[16] = vertices[3] - vertices[6];
    vertices[17] = vertices[15] * vertices[3] + vertices[16] * vertices[4];
}

void collisionCheck(float triangle1[], float triangle2[]) {
    float det = triangle1[12] * triangle2[10] - triangle2[9] * triangle1[13];
    if (det == 0) {

    }
    else {
        float x = (triangle2[10] * triangle1[14] - triangle1[13] * triangle2[11]) / det;
        float y = (triangle1[12] * triangle2[11] - triangle2[9] * triangle1[14]) / det;

        std::cout << x << " " << y << std::endl;
    }
}