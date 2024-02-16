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
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.5f, 0.6f, 1.0f);\n"
"}\n\0";

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float player[] = {
        -0.1f, -0.1f, 0.0f, // 0 1 2
        0.1f, -0.1f, 0.0f,  // 3 4 5
        0.0f, 0.1f, 0.0f,   // 6 7 8

        0.0f, 0.0f, 0.0f,   // 9 10 11
        0.0f, 0.0f, 0.0f,   // 12 13 14
        0.0f, 0.0f, 0.0f    // 15 16 17
        
};

float meats[] = {
        -0.9f, -0.9f, 0.0f, // 0 1 2
        -0.7f, -0.9f, 0.0f, // 3 4 5
        -0.8f, -0.7f, 0.0f, // 6 7 8

        0.0f, 0.0f, 0.0f,   // 9 10 11
        0.0f, 0.0f, 0.0f,   // 12 13 14
        0.0f, 0.0f, 0.0f    // 15 16 17
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

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentOne = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentTwo = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderOne = glCreateProgram();
    unsigned int shaderTwo = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentOne, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentTwo);
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
        calculateLines(player);
        collisionCheck(player, meats);



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
/*
float player[] = {
        -0.1f, -0.1f, 0.0f, // 0 1 2
        0.1f, -0.1f, 0.0f,  // 3 4 5
        0.0f, 0.1f, 0.0f,   // 6 7 8

        0.0f, 0.0f, 0.0f,   // 9 10 11
        0.0f, 0.0f, 0.0f,   // 12 13 14
        0.0f, 0.0f, 0.0f    // 15 16 17

};

float meats[] = {
        -0.9f, -0.9f, 0.0f, // 0 1 2
        -0.7f, -0.9f, 0.0f, // 3 4 5
        -0.8f, -0.7f, 0.0f, // 6 7 8

        0.0f, 0.0f, 0.0f,   // 9 10 11
        0.0f, 0.0f, 0.0f,   // 12 13 14
        0.0f, 0.0f, 0.0f    // 15 16 17
};
*/
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

bool collisionCheck(float triangle1[], float triangle2[]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            float det = (triangle1[9 + i*3] * triangle2[10 + j*3]) - (triangle2[9 + j*3] * triangle1[10 + i*3]);
            if (det != 0 && i!=j) {

                float x = (triangle2[10 + j*3] * triangle1[11 + i*3] - triangle1[10 + i*3] * triangle2[11 + j*3]) / det;
                float y = (triangle1[9 + i*3] * triangle2[11 + j*3] - triangle2[9 + j*3] * triangle1[11 + i*3]) / det;
                
                std::cout << i << " " << j << std::endl;
                std::cout << "test " << x << " " << y << " det: " << det << std::endl;
                std::cout << triangle2[j * 3] << std::endl;
                std::cout << triangle2[3 + j * 3] << std::endl;
                
                if ((std::min(triangle2[j * 3], triangle2[j * 3 + 3]) <= x <= std::max(triangle2[j * 3], triangle2[j * 3 + 3])) && 
                    (std::min(triangle2[1 + (j * 3)], triangle2[4 + (j * 3)]) <= y <= std::max(triangle2[1 + (j * 3)], triangle2[4 + (j * 3)]))) {
                    
                    
                    
                    //return true;
                }
                
            }

            

        }
    }

    return false;




    float det = triangle1[12] * triangle2[10] - triangle2[9] * triangle1[13];
    float x = (triangle2[10] * triangle1[14] - triangle1[13] * triangle2[11]) / det;
    float y = (triangle1[12] * triangle2[11] - triangle2[9] * triangle1[14]) / det;

    std::cout << x << " " << y << std::endl;
    
}

// whenever the window size changes this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}