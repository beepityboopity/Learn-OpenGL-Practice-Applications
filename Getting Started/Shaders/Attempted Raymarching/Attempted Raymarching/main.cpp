#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec2 positionVec;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   positionVec = aPos.xy;\n"
"}\0";

// shamelessly yoinked from a youtube video
const char* fragmentShaderSource = "#version 330 core\n"

"out vec4 FragColor;\n"

"in vec2 positionVec;\n"
"uniform float iTime;\n"

"float sdSphere(vec3 p, float s){\n" // sine distance sphere
    "return length(p) - s;\n"
"}\n"

"float sdBox(vec3 p, vec3 b){\n" // sine distance box
    "vec3 q = abs(p) - b;\n"
    "return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.y)), 0.0);\n"
"}\n"

"float opUnion(float d1, float d2){\n" // union operator
"return min(d1, d2);\n"
"}\n"

"float opSmoothUnion(float d1, float d2, float k){\n"
    "float h = clamp(0.5 + 0.5*(d2 - d1)/k, 0.0, 1.0);\n"
    "return mix(d2, d1, h) - k*h*(1.0-h);\n"
"}\n"

"float opSubtraction(float d1, float d2){\n" // difference operator
"return max(-d1, d2);\n"
"}\n"

"float opSmoothSubtraction(float d1, float d2, float k){\n"
"float h = clamp(0.5 + 0.5*(d2 + d1)/k, 0.0, 1.0);\n"
"return mix(d2, -d1, h) + k*h*(1.0-h);\n"
"}\n"

"float opIntersection(float d1, float d2){\n" // intersection operator
"return max(d1, d2);\n"
"}\n"

"float opSmoothIntersection(float d1, float d2, float k){\n"
"float h = clamp(0.5 + 0.5*(d2 - d1)/k, 0.0, 1.0);\n"
"return mix(d2, d1, h) + k*h*(1.0-h);\n"
"}\n"

"float smin(float a, float b, float c){\n" // smooth minimum (very goopy)
    "float h = max(c - abs(a - b), 0.0)/c;\n"
    "return min(a, b) - h*h*h*c*(1.0/6.0);\n"
"}\n"

"float map(vec3 p){\n"
    "vec3 spherePos = vec3(sin(iTime) * 2.0, 0, 0);\n"
    "float sphere = sdSphere(p - spherePos, 1.0);\n"

    "float box = sdBox(p * 4.0, vec3(0.75)) / 4.0;\n"
    "float ground = p.y + 0.75;\n"

    "return min(ground, smin(sphere, box, 2.0));\n"
"}\n"

"void main(){\n" // main

    "vec3 ro = vec3(0, 0, -2);\n"
    "vec3 rd = normalize(vec3(positionVec, 0.5));\n"
    "vec3 col = vec3(0);\n"

    "float t = 0.0;\n"

    "for (int i = 0; i < 80; i++){\n"

        "vec3 p = ro + rd * t;\n"
        "float d = map(p);\n"
        "t += d;\n"
        
        "col = vec3(i)/80.0;\n"
        "if (d < 0.001 || t > 100.0) break;\n"

    "}\n"

    "col = vec3(t * 0.2);\n"

    "FragColor = vec4(col.x, 0.0, col.z, 1.0f);\n"

"}\n\0";

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
        float timeValue = glfwGetTime();
        int uniformLocation = glGetUniformLocation(shaderProgram, "iTime");
        glUseProgram(shaderProgram);
        glUniform1f(uniformLocation, timeValue);

        float triangle1[] = {
            -1.0f, -1.0f, 0.0f,  // left  
             1.0f, -1.0f, 0.0f, // right 
             -1.0f,  1.0f, 0.0f // top   
        };

        float triangle2[] = {
            1.0f, 1.0f, 0.0f,  // left  
             1.0f, -1.0f, 0.0f, // right 
             -1.0f,  1.0f, 0.0f // top   
        };

        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
        glEnableVertexAttribArray(0);




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

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (width > height) {
        glViewport(0, -0.5 * (width-height), width, width);
    }
    else if(width == height){
        glViewport(0, 0, width, width);
    }
    else {
        glViewport(-0.5 * (height-width), 0, height, height);
    }
}