#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <texture setup/stb_image.h>
#include <iostream>
#include <shaders/shader_class.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

void frameCallback(GLFWwindow* window, int width, int height);
void imguiSetup(GLFWwindow* window, const char* glsl_version);

int main() {

    // **************
    // INITIALIZATION
    // **************

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1000, 750, "Linear Algebra Testing", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameCallback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    Shader textureShader("vertex.vs", "frag.fs");
    textureShader.use();

    float cubeVertices[] = {
        // green, opposite to yellow
        -0.5f, -0.5f, -0.5f,    0.0f, 0.66f,    0.0f, 0.0f, -1.0f,// bottom left
         0.5f, -0.5f, -0.5f,    0.25f, 0.66f,   0.0f, 0.0f, -1.0f,// bottom right
         0.5f,  0.5f, -0.5f,    0.25f, 0.33f,   0.0f, 0.0f, -1.0f,// top right
         0.5f,  0.5f, -0.5f,    0.25f, 0.33f,   0.0f, 0.0f, -1.0f,// top right
        -0.5f,  0.5f, -0.5f,    0.0f, 0.33f,    0.0f, 0.0f, -1.0f,// top left
        -0.5f, -0.5f, -0.5f,    0.0f, 0.66f,    0.0f, 0.0f, -1.0f,// bottom left
        // yellow, opposite to green
        -0.5f, -0.5f,  0.5f,    0.25f, 0.33f,   0.0f, 0.0f, 1.0f,// bottom left
         0.5f, -0.5f,  0.5f,    0.5f, 0.33f,    0.0f, 0.0f, 1.0f,// bottom right
         0.5f,  0.5f,  0.5f,    0.5f, 0.0f,     0.0f, 0.0f, 1.0f,// top right
         0.5f,  0.5f,  0.5f,    0.5f, 0.0f,     0.0f, 0.0f, 1.0f,// top right
        -0.5f,  0.5f,  0.5f,    0.25f, 0.0f,    0.0f, 0.0f, 1.0f,// top left
        -0.5f, -0.5f,  0.5f,    0.25f, 0.33f,   0.0f, 0.0f, 1.0f,// bottom left
        // red, opposite to white
        -0.5f, -0.5f,  0.5f,    0.25f, 0.33f,   -1.0f, 0.0f, 0.0f,// bottom left
        -0.5f,  0.5f,  0.5f,    0.5f, 0.33f,    -1.0f, 0.0f, 0.0f,// bottom right
        -0.5f,  0.5f, -0.5f,    0.5f, 0.66f,    -1.0f, 0.0f, 0.0f,// top right
        -0.5f,  0.5f, -0.5f,    0.5f, 0.66f,    -1.0f, 0.0f, 0.0f,// top right
        -0.5f, -0.5f, -0.5f,    0.25f, 0.66f,   -1.0f, 0.0f, 0.0f,// top left
        -0.5f, -0.5f,  0.5f,    0.25f, 0.33f,   -1.0f, 0.0f, 0.0f,// bottom left
        // white, opposite to red
        0.5f,  0.5f,  0.5f,     0.25f, 0.66f,   1.0f, 0.0f, 0.0f,// bottom left
        0.5f, -0.5f,  0.5f,     0.5f, 0.66f,    1.0f, 0.0f, 0.0f,// bottom right
        0.5f, -0.5f, -0.5f,     0.5f, 1.0f,     1.0f, 0.0f, 0.0f,// top right
        0.5f, -0.5f, -0.5f,     0.5f, 1.0f,     1.0f, 0.0f, 0.0f,// top right
        0.5f,  0.5f, -0.5f,     0.25f, 1.0f,    1.0f, 0.0f, 0.0f,// top left
        0.5f,  0.5f,  0.5f,     0.25f, 0.66f,   1.0f, 0.0f, 0.0f,// bottom left
        // blue, opposite to orange
        0.5f, -0.5f,  0.5f,     0.5f, 0.33f,    0.0f, -1.0f, 0.0f,// bottom left
        -0.5f, -0.5f,  0.5f,    0.75f, 0.33f,   0.0f, -1.0f, 0.0f,// bottom right
        -0.5f, -0.5f, -0.5f,    0.75f, 0.66f,   0.0f, -1.0f, 0.0f,// top right
        -0.5f, -0.5f, -0.5f,    0.75f, 0.66f,   0.0f, -1.0f, 0.0f,// top right
        0.5f, -0.5f, -0.5f,     0.5f, 0.66f,    0.0f, -1.0f, 0.0f,// top left
        0.5f, -0.5f,  0.5f,     0.5f, 0.33f,    0.0f, -1.0f, 0.0f,// bottom left
        // orange, opposite to blue
        -0.5f,  0.5f,  0.5f,    0.75f, 0.33f,   0.0f, 1.0f, 0.0f,// bottom left
        0.5f,  0.5f,  0.5f,     1.0f, 0.33f,    0.0f, 1.0f, 0.0f,// bottom right
        0.5f,  0.5f, -0.5f,     1.0f, 0.66f,    0.0f, 1.0f, 0.0f,// top right
        0.5f,  0.5f, -0.5f,     1.0f, 0.66f,    0.0f, 1.0f, 0.0f,// top right
        -0.5f,  0.5f, -0.5f,    0.75f, 0.66f,   0.0f, 1.0f, 0.0f,// top left
        -0.5f,  0.5f,  0.5f,    0.75f, 0.33f,   0.0f, 1.0f, 0.0f// bottom left
    };

    float gridVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top left
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom left
    };

    float verticesStorage[] = {
        /// for a full cube
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom left
         0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom right
         0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top right
         0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top right
        -0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top left
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom left
        ///
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,// bottom left
         0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 0.0f, 0.0f, 1.0f,// bottom right
         0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top right
         0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top right
        -0.5f,  0.5f,  0.5f,        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top left
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,// bottom left
        ///
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, -1.0f, 0.0f, 0.0f,// bottom left
        -0.5f,  0.5f,  0.5f,        1.0f, 0.0f, -1.0f, 0.0f, 0.0f,// bottom right
        -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, -1.0f, 0.0f, 0.0f,// top right
        -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, -1.0f, 0.0f, 0.0f,// top right
        -0.5f, -0.5f, -0.5f,        0.0f, 1.0f, -1.0f, 0.0f, 0.0f,// top left
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, -1.0f, 0.0f, 0.0f,// bottom left
        ///
         0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
         0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom right
         0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top right
         0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top right
         0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top left
         0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
        ///
         0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 0.0f, -1.0f, 0.0f,// bottom left
        -0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 0.0f, -1.0f, 0.0f,// bottom right
        -0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 0.0f, -1.0f, 0.0f,// top right
        -0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 0.0f, -1.0f, 0.0f,// top right
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f, 0.0f, -1.0f, 0.0f,// top left
         0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 0.0f, -1.0f, 0.0f,// bottom left
        ///
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom left
         0.5f,  0.5f,  0.5f,        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom right
         0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// top right
         0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// top right
        -0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// top left
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom left
    };

    // *******
    // BUFFERS
    // *******

    unsigned int vertexBuffer[2], vertexAttribute[2];
    glGenVertexArrays(3, vertexAttribute);
    glGenBuffers(3, vertexBuffer);
    // cube
    glBindVertexArray(vertexAttribute[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float))); // texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normal attribute
    glEnableVertexAttribArray(2);

    // grid
    glBindVertexArray(vertexAttribute[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices), gridVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normal attribute
    glEnableVertexAttribArray(2);

    // ********
    // TEXTURES
    // ********

    unsigned int gridTexture, cubeTexture, lightTexture;
    int width, height, nrChannels;
    // grid
    glGenTextures(1, &gridTexture);
    glBindTexture(GL_TEXTURE_2D, gridTexture);
    // wrapping and filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("gameBoard.png", &width, &height, &nrChannels, 0); // loads image data and stores its dimensions
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // generates the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    
    // cube
    glGenTextures(1, &cubeTexture);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    // wrapping and filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data1 = stbi_load("rubixCube.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gridTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);

    // *****
    // OTHER
    // *****

    int rotationVar1 = 20;
    int rotationVar2 = 45;
    float zoomVar = -20;

    // imgui stuff
    imguiSetup(window, "#version 130");
    float vertices[] = {
        0.1, 0.1, 0.1,
        0.1, 0.1, 0.1,
        0.1, 0.1, 0.1
    };

    glm::mat4 sandMatrix = glm::mat4(1.0f);

    // ******
    // RENDER
    // ******

    while (!glfwWindowShouldClose(window)) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Sandbox Matrix Text Input");
        ImGui::Columns(4);
        ImGui::InputFloat("00", &sandMatrix[0][0], -5.0f, 5.0f);
        ImGui::InputFloat("01", &sandMatrix[0][1], -5.0f, 5.0f);
        ImGui::InputFloat("02", &sandMatrix[0][2], -5.0f, 5.0f);
        ImGui::InputFloat("03", &sandMatrix[0][3], -5.0f, 5.0f);
        if (ImGui::Button("Reset")) sandMatrix = glm::mat4(1.0f);
        ImGui::NextColumn();
        ImGui::InputFloat("10", &sandMatrix[1][0], -5.0f, 5.0f);
        ImGui::InputFloat("11", &sandMatrix[1][1], -5.0f, 5.0f);
        ImGui::InputFloat("12", &sandMatrix[1][2], -5.0f, 5.0f);
        ImGui::InputFloat("13", &sandMatrix[1][3], -5.0f, 5.0f);
        ImGui::NextColumn();
        ImGui::InputFloat("20", &sandMatrix[2][0], -5.0f, 5.0f);
        ImGui::InputFloat("21", &sandMatrix[2][1], -5.0f, 5.0f);
        ImGui::InputFloat("22", &sandMatrix[2][2], -5.0f, 5.0f);
        ImGui::InputFloat("23", &sandMatrix[2][3], -5.0f, 5.0f);
        ImGui::NextColumn();
        ImGui::InputFloat("30", &sandMatrix[3][0], -5.0f, 5.0f);
        ImGui::InputFloat("31", &sandMatrix[3][1], -5.0f, 5.0f);
        ImGui::InputFloat("32", &sandMatrix[3][2], -5.0f, 5.0f);
        ImGui::InputFloat("33", &sandMatrix[3][3], -5.0f, 5.0f);
        ImGui::End();

        ImGui::Begin("Sandbox Matrix Slider Input");
        ImGui::Columns(4);
        ImGui::SliderFloat("00", &sandMatrix[0][0], -5.0f, 5.0f);
        ImGui::SliderFloat("01", &sandMatrix[0][1], -5.0f, 5.0f);
        ImGui::SliderFloat("02", &sandMatrix[0][2], -5.0f, 5.0f);
        ImGui::SliderFloat("03", &sandMatrix[0][3], -5.0f, 5.0f);
        if (ImGui::Button("Reset")) sandMatrix = glm::mat4(1.0f);
        ImGui::NextColumn();
        ImGui::SliderFloat("10", &sandMatrix[1][0], -5.0f, 5.0f);
        ImGui::SliderFloat("11", &sandMatrix[1][1], -5.0f, 5.0f);
        ImGui::SliderFloat("12", &sandMatrix[1][2], -5.0f, 5.0f);
        ImGui::SliderFloat("13", &sandMatrix[1][3], -5.0f, 5.0f);
        ImGui::NextColumn();
        ImGui::SliderFloat("20", &sandMatrix[2][0], -5.0f, 5.0f);
        ImGui::SliderFloat("21", &sandMatrix[2][1], -5.0f, 5.0f);
        ImGui::SliderFloat("22", &sandMatrix[2][2], -5.0f, 5.0f);
        ImGui::SliderFloat("23", &sandMatrix[2][3], -5.0f, 5.0f);
        ImGui::NextColumn();
        ImGui::SliderFloat("30", &sandMatrix[3][0], -5.0f, 5.0f);
        ImGui::SliderFloat("31", &sandMatrix[3][1], -5.0f, 5.0f);
        ImGui::SliderFloat("32", &sandMatrix[3][2], -5.0f, 5.0f);
        ImGui::SliderFloat("33", &sandMatrix[3][3], -5.0f, 5.0f);
        ImGui::End();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotationVar1 += 1;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotationVar1 -= 1;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) rotationVar2 += 1;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) rotationVar2 -= 1;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) zoomVar -= 0.5;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) zoomVar += 0.5;

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, (float)zoomVar / 3));
        view = glm::rotate(view, glm::radians((float)rotationVar1), glm::vec3(1.0, 0.0, 0.0)); // vertical x
        view = glm::rotate(view, glm::radians((float)rotationVar2), glm::vec3(0.0, 1.0, 0.0)); // horizontal y
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        textureShader.setMat4("view", view);
        textureShader.setMat4("projection", projection);

        // cube
        model = sandMatrix;
        textureShader.setMat4("model", model);
        textureShader.setInt("currentTexture", 1);

        glBindVertexArray(vertexAttribute[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ground
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(15.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.6f));
        textureShader.setMat4("model", model);
        textureShader.setInt("currentTexture", 0);

        glBindVertexArray(vertexAttribute[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, vertexAttribute);
    glDeleteBuffers(1, vertexBuffer);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void frameCallback(GLFWwindow* window, int width, int height) { // window resizing
    glViewport(0, 0, width, height);
}

void imguiSetup(GLFWwindow* window, const char* glsl_version) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsClassic();
}