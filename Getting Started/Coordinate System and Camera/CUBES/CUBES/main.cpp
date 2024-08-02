#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <texture setup/stb_image.h>
#include <iostream>
#include <shaders/shader_class.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void frameCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
    // initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* myWindow = glfwCreateWindow(600, 600, "First Textures", NULL, NULL);
    glfwMakeContextCurrent(myWindow);
    glfwSetFramebufferSizeCallback(myWindow, frameCallback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    // shader
    Shader myShader("vertex.vs", "frag.fs");
    myShader.use();

    // triangle vertices
    float vertices[] = {
        /* for a full cube
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        */
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        ///
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         
        ///
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -10.0f),
        glm::vec3(1.5f, 2.2f, -2.5f),
        glm::vec3(-2.8f, -1.0f, -4.3f),
        glm::vec3(2.4f, -0.4f, 3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, 2.0f, 2.5f),
        glm::vec3(1.5f,  -2.0f, 2.5f),
        glm::vec3(-1.5f,  0.2f, -1.5f),
        glm::vec3(1.3f,  1.0f, -1.5f),

        glm::vec3(-4.37280f, -7.08650f, -2.27383f),
        glm::vec3(6.34176f, -0.28484f, -1.31389f),
        glm::vec3(8.06901f, 3.29675f, -1.40341f),
        glm::vec3(-0.74458f, 4.75098f, -4.05354f),
        glm::vec3(-6.90236f, -7.49466f, 3.81857f),
        glm::vec3(7.95293f, 4.54460f, 8.66313f),
        glm::vec3(-4.92975f, 9.91673f, -7.52481f),
        glm::vec3(7.73915f, -4.81632f, 5.12715f),
        glm::vec3(-0.05296f, 8.98912f, -8.41480f),
        glm::vec3(-2.16567f, -6.99086f, 1.23991f)
    };

    // buffers
    unsigned int vBuffer, vArray;
    glGenVertexArrays(1, &vArray);
    glGenBuffers(1, &vBuffer);
    glBindVertexArray(vArray);
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // textures
    unsigned int texShadow;
    glGenTextures(1, &texShadow); // creatures and stores a texture into an array, similar to vertex buffers
    glBindTexture(GL_TEXTURE_2D, texShadow); // binds the texture so it can be configured
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // sets wrapping method for s axis (x axis)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // sets wrapping method for t axis (y axis)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // sets filtering method when scaling down a texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // sets filtering method when scaling up a texture

    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // flips the image vertically
    unsigned char* data = stbi_load("Snail.png", &width, &height, &nrChannels, 0); // loads image data and stores its dimensions
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // generates the texture
    glGenerateMipmap(GL_TEXTURE_2D); // generates mipmaps
    stbi_image_free(data); // free memory

    myShader.setInt("texture1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texShadow);

    glm::mat4 projection = glm::mat4(1.0f); // projection matrix adds perspective so things get smaller as they get farther away
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f); // sets the perspective/FOV
    myShader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(myWindow)) {
        processInput(myWindow);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f); // view matrix shifts where the camera looks by everything but the camera
        float camX = (sin(glfwGetTime()) * 15.0f) + 10.0f;
        float camZ = (cos(glfwGetTime()) * 15.0f) + 10.0f;
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, 5.0f)); // move snail backwards so we can see it
        view = view * glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        myShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f); // model matrix contains translations, scaling, and rotation
        for (unsigned int i = 0; i < 20; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate it so the snail lays on the x axis
            
            if (i == 3 || i == 5 || i == 7 || i == 9)
                model = model * glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * (0.0f - i), glm::vec3(0.0, 0.0, -1.0));
            else
                model = model * glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * (i + 1.0f), glm::vec3(0.0, 0.0, -1.0));
            if (i%3 == 0)
                model = model * glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(-1.0, 0.0, 0.0));
            if (i % 5 == 0)
                model = model * glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(-1.0, -1.0, 0.0));
            myShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 24);
        }
        glfwSwapBuffers(myWindow);
        glfwPollEvents();
    }
    // cleanup
    glDeleteVertexArrays(1, &vArray);
    glDeleteBuffers(1, &vBuffer);
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