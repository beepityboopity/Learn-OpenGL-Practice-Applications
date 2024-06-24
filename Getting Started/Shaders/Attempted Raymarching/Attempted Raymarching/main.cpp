#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_class.h>
#include <algorithm>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Yippee!", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Shader myShader("vertexShader.vs", "fragShader.fs");
    myShader.use();

    float triangle1[] = 
    {
            -1.0f, -1.0f, 0.0f,  // left  
             1.0f, -1.0f, 0.0f, // right 
             -1.0f,  1.0f, 0.0f // top   
    };

    float triangle2[] = 
    {
        1.0f, 1.0f, 0.0f,  // left  
         1.0f, -1.0f, 0.0f, // right 
         -1.0f,  1.0f, 0.0f // top   
    };

    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    double mouseX;
    double mouseY;

    while (!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();
        myShader.setFloat("iTime", timeValue);
        
        glfwGetCursorPos(window, &mouseX, &mouseY);
        myShader.setVec2("mousePos", mouseX, mouseY);

        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
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
    if (width > height) 
    {
        glViewport(0, -0.5 * (width-height), width, width);
    }
    else if(width == height)
    {
        glViewport(0, 0, width, width);
    }
    else 
    {
        glViewport(-0.5 * (height-width), 0, height, height);
    }
}


