#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <texture setup/stb_image.h>
#include <iostream>
#include <shaders/shader_class.h>

void frameCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
    // initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* myWindow = glfwCreateWindow(800, 600, "First Textures", NULL, NULL);
    glfwMakeContextCurrent(myWindow);
    glfwSetFramebufferSizeCallback(myWindow, frameCallback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // shader
    Shader myShader("vertex.vs", "frag.fs");
    myShader.use();

    // triangle vertices
    float vertices[] = {
         0.9f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        -0.9f,  0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // top left 
         0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.9f, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f  // bottom left
    };
    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    // buffers
    unsigned int vBuffer, vArray, eBuffer;
    glGenVertexArrays(1, &vArray);
    glGenBuffers(1, &vBuffer);
    glGenBuffers(1, &eBuffer);
    glBindVertexArray(vArray);
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // textures
    unsigned int texShadow;
    glGenTextures(1, &texShadow); // creatures and stores a texture into an array, similar to vertex buffers
    glBindTexture(GL_TEXTURE_2D, texShadow); // binds the texture so it can be configured
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // sets wrapping method for s axis (x axis)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // sets wrapping method for t axis (y axis)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // sets filtering method when scaling down a texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // sets filtering method when scaling up a texture

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // flips the image vertically
    unsigned char* data = stbi_load("shadow.png", &width, &height, &nrChannels, 0); // loads image data and stores its dimensions
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // generates the texture
    glGenerateMipmap(GL_TEXTURE_2D); // generates mipmaps
    stbi_image_free(data); // free memory

    unsigned int texSonic;
    glGenTextures(1, &texSonic);
    glBindTexture(GL_TEXTURE_2D, texSonic);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width1, height1, nrChannels1;
    unsigned char* data1 = stbi_load("sonic.png", &width1, &height1, &nrChannels1, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);

    myShader.setFloat("mixer", -0.5f);
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texShadow);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texSonic);

    while (!glfwWindowShouldClose(myWindow)) {
        processInput(myWindow);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(myWindow);
        glfwPollEvents();
    }
    // cleanup
    glDeleteVertexArrays(1, &vArray);
    glDeleteBuffers(1, &vBuffer);
    glDeleteBuffers(1, &eBuffer);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) { // input processing
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void frameCallback(GLFWwindow* window, int width, int height) { // window resizing
    glViewport(0, 0, width, height);
}