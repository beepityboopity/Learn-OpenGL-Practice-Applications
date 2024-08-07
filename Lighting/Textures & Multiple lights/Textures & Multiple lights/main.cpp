#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <texture setup/stb_image.h>
#include <shaders/shader_class.h>
#include <cameras/simpleCamera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>

void frameCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void imguiSetup(GLFWwindow* window, const char* glsl_version);
unsigned int setTexture(char const* filePath);

Camera superiorCamera(glm::vec3(-3.0f, 3.0f, -3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;



int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1000, 750, "Phong Lighting", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameCallback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    imguiSetup(window, "#version 130");

    Shader lightSourceShader("lightSource.vs", "lightSource.fs");
    Shader PhongShader("Phong.vs", "Phong.fs");

    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    unsigned int lightVAO, cubeVAO, vertexBuffer;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int diffuseMap = setTexture("box.png");
    unsigned int specMap = setTexture("boxSpec.png");
    PhongShader.use();
    PhongShader.setInt("objDiff", 0);
    PhongShader.setInt("objSpec", 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specMap);

    int rotationVar1 = 20;
    int rotationVar2 = 45;
    float zoomVar = -20;

    int shaderSelect = 1;
    int inputSelect = 1;
    int dependence = 1;
    glm::vec3 lightPos(3.0f);
    glm::vec3 objectCol(1.0f, 0.5f, 0.31f);
    glm::vec3 lightCol(1.0f);
    glm::vec3 lightDiff = lightCol;
    glm::vec3 lightAmb = lightDiff * glm::vec3(0.1f);
    glm::vec3 lightSpec(1.0f);
    float objShiny = 128.0f;

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Shader Options");
        ImGui::RadioButton("Slider Input", &inputSelect, 1);
        ImGui::SameLine();
        ImGui::RadioButton("Text Input", &inputSelect, 0);
        ImGui::RadioButton("Independent", &dependence, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Dependent", &dependence, 1);
        ImGui::Text("Object:");
        if (inputSelect) {
            ImGui::SliderFloat("Object Shininess", &objShiny, 1, 256);
            ImGui::Text("Light:");
            ImGui::SliderFloat3("Light Color", &lightCol[0], 0.0f, 1.0f);
            ImGui::SliderFloat3("Light Ambient", &lightAmb[0], 0.0f, 1.0f);
            ImGui::SliderFloat3("Light Diffuse", &lightDiff[0], 0.0f, 1.0f);
            ImGui::SliderFloat3("Light Specular", &lightSpec[0], 0.0f, 1.0f);

        }
        else {
            ImGui::InputFloat("Object Shininess", &objShiny);
            ImGui::Text("Light:");
            ImGui::InputFloat3("Light Color", &lightCol[0]);
            ImGui::InputFloat3("Light Ambient", &lightAmb[0]);
            ImGui::InputFloat3("Light Diffuse", &lightDiff[0]);
            ImGui::InputFloat3("Light Specular", &lightSpec[0]);
        }
        if (ImGui::Button("Reset")) {
            objectCol = glm::vec3(1.0f, 0.5f, 0.31f);
            lightCol = glm::vec3(1.0f);
            lightDiff = lightCol;
            lightAmb = lightDiff * glm::vec3(0.1f);
            lightSpec = glm::vec3(1.0f);
            objShiny = 128.0f;
        }
        ImGui::End();

        if (dependence) {
            lightDiff = lightCol;
            lightAmb = lightDiff * glm::vec3(0.1);
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);

        view = superiorCamera.GetViewMatrix();
        projection = glm::perspective(glm::radians(superiorCamera.Zoom), (float)1000 / (float)750, 0.1f, 100.0f);

        
        PhongShader.use();
        PhongShader.setVec3("lightPos", lightPos);
        PhongShader.setVec3("lightAmb", lightAmb);
        PhongShader.setVec3("lightDiff", lightDiff);
        PhongShader.setVec3("lightSpec", lightSpec);
        PhongShader.setFloat("objShiny", objShiny);
        PhongShader.setVec3("viewPos", superiorCamera.Position);
        PhongShader.setMat4("model", model);
        PhongShader.setMat4("view", view);
        PhongShader.setMat4("projection", projection);
        
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // light source
        lightSourceShader.use();
        model = glm::translate(model, lightPos);
        lightSourceShader.setVec3("color", lightCol);
        lightSourceShader.setMat4("model", model);
        lightSourceShader.setMat4("view", view);
        lightSourceShader.setMat4("projection", projection);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &vertexBuffer);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void frameCallback(GLFWwindow* window, int width, int height) { // window resizing
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) // input for camera, WASD rotation arrow keys movement
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) superiorCamera.Pitch += 1.0;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) superiorCamera.Pitch -= 1.0;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) superiorCamera.Yaw += 1.5;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) superiorCamera.Yaw -= 1.5;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) superiorCamera.Position.y -= 0.05;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) superiorCamera.Position.y += 0.05;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) superiorCamera.Position += superiorCamera.Front * superiorCamera.MovementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) superiorCamera.Position -= superiorCamera.Front * superiorCamera.MovementSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) superiorCamera.Position -= superiorCamera.Right * superiorCamera.MovementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) superiorCamera.Position += superiorCamera.Right * superiorCamera.MovementSpeed * deltaTime;

    superiorCamera.updateCameraVectors();
}

void imguiSetup(GLFWwindow* window, const char* glsl_version) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsClassic();
}

unsigned int setTexture(char const* filePath) {
    unsigned int ID;
    glGenTextures(1, &ID);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    GLenum format = GL_RGB;
    if (nrChannels == 1) format = GL_RED;
    else if (nrChannels == 3) format = GL_RGB;
    else if (nrChannels == 4) format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
    return ID;
}