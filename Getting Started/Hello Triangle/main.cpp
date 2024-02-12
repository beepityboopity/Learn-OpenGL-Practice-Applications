#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2656f, 0.2226f, 0.3398f, 1.0f);\n"
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.5078f, 0.3516f, 0.5352f, 1.0f);\n"
"}\n\0";

const char* fragmentShader3Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.7343f, 0.4804f, 0.6172f, 1.0f);\n"
"}\n\0";

const char* fragmentShader4Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9297f, 0.6094f, 0.6406f, 1.0f);\n"
"}\n\0";


int main()
{
    //initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // create vertex shader and four fragment shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShader4 = glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int shaderProgram1 = glCreateProgram();
    unsigned int shaderProgram2 = glCreateProgram();
    unsigned int shaderProgram3 = glCreateProgram();
    unsigned int shaderProgram4 = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShader1);
    glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShader2);
    glShaderSource(fragmentShader3, 1, &fragmentShader3Source, NULL);
    glCompileShader(fragmentShader3);
    glShaderSource(fragmentShader4, 1, &fragmentShader4Source, NULL);
    glCompileShader(fragmentShader4);

    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glAttachShader(shaderProgram3, vertexShader);
    glAttachShader(shaderProgram3, fragmentShader3);
    glLinkProgram(shaderProgram3);
    glAttachShader(shaderProgram4, vertexShader);
    glAttachShader(shaderProgram4, fragmentShader4);
    glLinkProgram(shaderProgram4);

    //triangle vertices grouped by color
    float Hello1[] = {
        -0.9f, 0.55f, 0.0f, // H
        -0.85f, 0.55f, 0.0f,
        -0.85f, 0.30f, 0.0f,

        -0.85f, 0.4f, 0.0f,
        -0.7f, 0.45f, 0.0f,
        -0.7f, 0.4f, 0.0f,

        -0.7f, 0.55f, 0.0f,
        -0.65f, 0.55f, 0.0f,
        -0.65f, 0.30f, 0.0f,

        -0.6f, 0.55f, 0.0f, // E
        -0.55f, 0.55f, 0.0f,
        -0.55f, 0.30f, 0.0f,

        -0.55f, 0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f,
        -0.45f, 0.55f, 0.0f,

        -0.55f, 0.4f, 0.0f,
        -0.45f, 0.4f, 0.0f,
        -0.45f, 0.45f, 0.0f,

        -0.55f, 0.3f, 0.0f,
        -0.45f, 0.3f, 0.0f,
        -0.45f, 0.35f, 0.0f,

        -0.4f, 0.55f, 0.0f, // L1
        -0.35f, 0.55f, 0.0f,
        -0.35f, 0.30f, 0.0f,

        -0.35f, 0.3f, 0.0f,
        -0.25f, 0.3f, 0.0f,
        -0.25f, 0.35f, 0.0f,

        -0.2f, 0.55f, 0.0f, // L2
        -0.15f, 0.55f, 0.0f,
        -0.15f, 0.30f, 0.0f,

        -0.15f, 0.3f, 0.0f,
        -0.05f, 0.3f, 0.0f,
        -0.05f, 0.35f, 0.0f,

        0.0f, 0.55f, 0.0f, // O
        0.05f, 0.55f, 0.0f,
        0.05f, 0.30f, 0.0f,

        0.05f, 0.3f, 0.0f,
        0.15f, 0.3f, 0.0f,
        0.15f, 0.35f, 0.0f,

        0.05f, 0.5f, 0.0f,
        0.15f, 0.5f, 0.0f,
        0.15f, 0.55f, 0.0f,

        0.15f, 0.55f, 0.0f,
        0.20f, 0.55f, 0.0f,
        0.20f, 0.30f, 0.0f
    };
    float Hello2[] = {
        -0.9f, 0.55f, 0.0f, // H
        -0.9f, 0.3f, 0.0f,
        -0.85f, 0.30f, 0.0f,

        -0.85f, 0.4f, 0.0f,
        -0.7f, 0.45f, 0.0f,
        -0.85f, 0.45f, 0.0f,

        -0.7f, 0.55f, 0.0f,
        -0.7f, 0.3f, 0.0f,
        -0.65f, 0.30f, 0.0f,

        -0.6f, 0.55f, 0.0f, // E
        -0.6f, 0.3f, 0.0f,
        -0.55f, 0.30f, 0.0f,

        -0.55f, 0.5f, 0.0f,
        -0.55f, 0.55f, 0.0f,
        -0.45f, 0.55f, 0.0f,

        -0.55f, 0.4f, 0.0f,
        -0.55f, 0.45f, 0.0f,
        -0.45f, 0.45f, 0.0f,

        -0.55f, 0.3f, 0.0f,
        -0.55f, 0.35f, 0.0f,
        -0.45f, 0.35f, 0.0f,

        -0.4f, 0.55f, 0.0f, // L1
        -0.4f, 0.3f, 0.0f,
        -0.35f, 0.30f, 0.0f,

        -0.35f, 0.3f, 0.0f,
        -0.35f, 0.35f, 0.0f,
        -0.25f, 0.35f, 0.0f,

        -0.2f, 0.55f, 0.0f, // L2
        -0.2f, 0.3f, 0.0f,
        -0.15f, 0.30f, 0.0f,

        -0.15f, 0.3f, 0.0f,
        -0.15f, 0.35f, 0.0f,
        -0.05f, 0.35f, 0.0f,

        0.0f, 0.55f, 0.0f, // O
        0.0f, 0.3f, 0.0f,
        0.05f, 0.30f, 0.0f,

        0.05f, 0.3f, 0.0f,
        0.05f, 0.35f, 0.0f,
        0.15f, 0.35f, 0.0f,

        0.05f, 0.5f, 0.0f,
        0.05f, 0.55f, 0.0f,
        0.15f, 0.55f, 0.0f,

        0.15f, 0.55f, 0.0f,
        0.15f, 0.3f, 0.0f,
        0.20f, 0.30f, 0.0f
    };

    float Triangle1[] = {
        -0.90f, 0.15f, 0.0f, // T
        -0.90f, 0.20f, 0.0f,
        -0.65f, 0.20f, 0.0f,

        -0.80f, 0.15f, 0.0f,
        -0.80f, -0.05f, 0.0f,
        -0.75f, -0.05f, 0.0f,

        -0.60f, 0.2f, 0.0f, // R
        -0.60f, -0.05f, 0.0f,
        -0.55f, -0.05f, 0.0f,

        -0.55f, 0.15f, 0.0f,
        -0.55f, 0.20f, 0.0f,
        -0.45f, 0.2f, 0.0f,

        -0.50f, 0.10f, 0.0f,
        -0.45f, 0.10f, 0.0f,
        -0.50f, 0.15f, 0.0f,

        -0.55f, 0.05f, 0.0f,
        -0.55f, 0.10f, 0.0f,
        -0.45f, 0.10f, 0.0f,

        -0.55f, 0.05f, 0.0f,
        -0.50f, -0.05f, 0.0f,
        -0.45f, -0.05f, 0.0f,

        -0.40f, 0.2f, 0.0f, //I
        -0.40f, -0.05f, 0.0f,
        -0.35f, -0.05f, 0.0f,

        -0.15f, 0.15f, 0.0f, //A
        -0.25f, -0.05f, 0.0f,
        -0.15f, 0.20f, 0.0f,

        -0.15f, 0.15f, 0.0f,
        -0.05f, -0.05f, 0.0f,
        -0.15f, 0.20f, 0.0f,

        -0.20f, 0.05f, 0.0f,
        -0.10f, 0.05f, 0.0f,
        -0.15f, 0.075f, 0.0f,

        0.05f, 0.2f, 0.0f, //N
        0.05f, -0.05f, 0.0f,
        0.10f, -0.05f, 0.0f,

        0.20f, 0.2f, 0.0f,
        0.20f, -0.05f, 0.0f,
        0.25f, -0.05f, 0.0f,

        0.10f, 0.2f, 0.0f,
        0.15f, -0.05f, 0.0f,
        0.20f, -0.05f, 0.0f,

        0.30f, 0.2f, 0.0f, //G
        0.30f, -0.05f, 0.0f,
        0.35f, -0.05f, 0.0f,

        0.35f, 0.15f, 0.0f,
        0.35f, 0.20f, 0.0f,
        0.50f, 0.20f, 0.0f,

        0.35f, -0.05f, 0.0f,
        0.35f, 0.0f, 0.0f,
        0.50f, 0.0f, 0.0f,

        0.40f, 0.05f, 0.0f,
        0.40f, 0.10f, 0.0f,
        0.50f, 0.10f, 0.0f,

        0.50f, 0.0f, 0.0f,
        0.45f, 0.05f, 0.0f,
        0.45f, 0.0f, 0.0f,

        0.55f, 0.2f, 0.0f, //L
        0.55f, -0.05f, 0.0f,
        0.60f, -0.05f, 0.0f,

        0.60f, -0.05f, 0.0f,
        0.60f, 0.0f, 0.0f,
        0.70f, 0.0f, 0.0f,

        0.75f, 0.2f, 0.0f, //E
        0.75f, -0.05f, 0.0f,
        0.80f, -0.05f, 0.0f,

        0.80f, -0.05f, 0.0f,
        0.80f, 0.0f, 0.0f,
        0.90f, 0.0f, 0.0f,

        0.80f, 0.05f, 0.0f,
        0.80f, 0.10f, 0.0f,
        0.90f, 0.10f, 0.0f,

        0.80f, 0.15f, 0.0f,
        0.80f, 0.20f, 0.0f,
        0.90f, 0.20f, 0.0f,
    };

    float Triangle2[] = {
        -0.90f, 0.15f, 0.0f, // T
        -0.65f, 0.15f, 0.0f,
        -0.65f, 0.20f, 0.0f,

        -0.80f, 0.15f, 0.0f,
        -0.75f, 0.15f, 0.0f,
        -0.75f, -0.05f, 0.0f,

        -0.60f, 0.2f, 0.0f, // R
        -0.55f, 0.2f, 0.0f,
        -0.55f, -0.05f, 0.0f,

        -0.55f, 0.15f, 0.0f,
        -0.45f, 0.15f, 0.0f,
        -0.45f, 0.2f, 0.0f,

        -0.45f, 0.15f, 0.0f,
        -0.45f, 0.10f, 0.0f,
        -0.50f, 0.15f, 0.0f,

        -0.55f, 0.05f, 0.0f,
        -0.45f, 0.05f, 0.0f,
        -0.45f, 0.10f, 0.0f,

        -0.40f, 0.2f, 0.0f, //I
        -0.35f, 0.2f, 0.0f,
        -0.35f, -0.05f, 0.0f,

        -0.30f, -0.05f, 0.0f, //A
        -0.25f, -0.05f, 0.0f,
        -0.15f, 0.20f, 0.0f,

        0.0f, -0.05f, 0.0f,
        -0.05f, -0.05f, 0.0f,
        -0.15f, 0.20f, 0.0f,

        -0.20f, 0.05f, 0.0f,
        -0.10f, 0.05f, 0.0f,
        -0.15f, 0.075f, 0.0f,

        0.05f, 0.2f, 0.0f, //N
        0.10f, 0.2f, 0.0f,
        0.10f, -0.05f, 0.0f,

        0.20f, 0.2f, 0.0f,
        0.25f, 0.2f, 0.0f,
        0.25f, -0.05f, 0.0f,

        0.10f, 0.2f, 0.0f,
        0.15f, -0.05f, 0.0f,
        0.20f, -0.05f, 0.0f,

        0.30f, 0.2f, 0.0f, //G
        0.35f, 0.2f, 0.0f,
        0.35f, -0.05f, 0.0f,

        0.35f, 0.15f, 0.0f,
        0.50f, 0.15f, 0.0f,
        0.50f, 0.20f, 0.0f,

        0.35f, -0.05f, 0.0f,
        0.50f, -0.05f, 0.0f,
        0.50f, 0.0f, 0.0f,

        0.40f, 0.05f, 0.0f,
        0.50f, 0.05f, 0.0f,
        0.50f, 0.10f, 0.0f,

        0.45f, 0.05f, 0.0f,
        0.50f, 0.0f, 0.0f,
        0.50f, 0.05f, 0.0f,

        0.55f, 0.2f, 0.0f, //L
        0.60f, 0.2f, 0.0f,
        0.60f, -0.05f, 0.0f,

        0.60f, -0.05f, 0.0f,
        0.70f, -0.05f, 0.0f,
        0.70f, 0.0f, 0.0f,

        0.75f, 0.2f, 0.0f, //E
        0.80f, 0.2f, 0.0f,
        0.80f, -0.05f, 0.0f,

        0.80f, -0.05f, 0.0f,
        0.90f, -0.05f, 0.0f,
        0.90f, 0.0f, 0.0f,

        0.80f, 0.05f, 0.0f,
        0.90f, 0.05f, 0.0f,
        0.90f, 0.10f, 0.0f,

        0.80f, 0.15f, 0.0f,
        0.90f, 0.15f, 0.0f,
        0.90f, 0.20f, 0.0f,
    };

    // vertex buffers and attributes for each color
    unsigned int VBOs[4], VAOs[4];
    glGenVertexArrays(4, VAOs);
    glGenBuffers(4, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Hello1), Hello1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(Hello2), Hello2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1), Triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);	
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2), Triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.1054f, 0.1210f, 0.1992f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 81);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 81);

        glUseProgram(shaderProgram3);
        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLES, 0, 81);

        glUseProgram(shaderProgram4);
        glBindVertexArray(VAOs[3]);
        glDrawArrays(GL_TRIANGLES, 0, 81);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
    // delete programs and terminate
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);
    glDeleteProgram(shaderProgram3);
    glDeleteProgram(shaderProgram4);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}