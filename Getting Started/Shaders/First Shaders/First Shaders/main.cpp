#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 otherColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   otherColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 otherColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(otherColor, 1.0f);\n"
"}\n\0";

int main()
{
    // initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Yippee!", NULL, NULL);
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
    glUseProgram(shaderProgram);

    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    while (!glfwWindowShouldClose(window))
    {
        float timeValue = 0.5 * glfwGetTime();
        float vertices[] = {
            -1.0f, -1.0f, 0.0f, (sin(timeValue + 4.0f) * 2.0f) + 0.5f, (sin(timeValue + 2.0f) * 2.0f) + 0.5f, (sin(timeValue) * 2.0f) + 0.5f, // left  
             1.0f, -1.0f, 0.0f, (sin(timeValue + 2.0f) * 2.0f) + 0.5f, (sin(timeValue) * 2.0f) + 0.5f, (sin(timeValue - 2.0f) * 2.0f) + 0.5f,// right 
             -1.0f,  1.0f, 0.0f, (sin(timeValue) * 2.0f) + 0.5f, (sin(timeValue - 2.0f) * 2.0f) + 0.5f, (sin(timeValue - 4.0f) * 2.0f) + 0.5f// top   
        };

        float vertices2[] = {
            1.0f, 1.0f, 0.0f, (sin(timeValue + 4.0f) * 2.0f) + 0.5f, (sin(timeValue + 2.0f) * 2.0f) + 0.5f, (sin(timeValue) * 2.0f) + 0.5f, // left  
             1.0f, -1.0f, 0.0f, (sin(timeValue + 2.0f) * 2.0f) + 0.5f, (sin(timeValue) * 2.0f) + 0.5f, (sin(timeValue - 2.0f) * 2.0f) + 0.5f,// right 
             -1.0f,  1.0f, 0.0f, (sin(timeValue) * 2.0f) + 0.5f, (sin(timeValue - 2.0f) * 2.0f) + 0.5f, (sin(timeValue - 4.0f) * 2.0f) + 0.5f// top   
        };

        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        

        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

// process input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// change window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}