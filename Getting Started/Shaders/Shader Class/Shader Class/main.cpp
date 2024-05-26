#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_class.h"
#include <cmath>
#include <algorithm>


void resizeWindow(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* my_window = glfwCreateWindow(800, 600, "The shaders are in their own files now :3", NULL, NULL);
	glfwMakeContextCurrent(my_window);
	glfwSetFramebufferSizeCallback(my_window, resizeWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	Shader ourShader("vertex_shader.vs", "fragment_shader.fs");
	ourShader.use();
	ourShader.setFloat("offset", 0.2f);
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	

	while (!glfwWindowShouldClose(my_window)) {

		float timeValue = 0.5 * glfwGetTime();
		float vertices[] = {
		-0.75f, -0.75f, 0.0f, (sin(timeValue + 4.0f) * 2.0f) + 0.5f, (sin(timeValue + 2.0f) * 2.0f) + 0.5f, (sin(timeValue) * 2.0f) + 0.5f, // left  
		 0.75f, -0.75f, 0.0f, (sin(timeValue + 2.0f) * 2.0f) + 0.5f, (sin(timeValue) * 2.0f) + 0.5f, (sin(timeValue - 2.0f) * 2.0f) + 0.5f, // right 
		 0.0f,  0.75f, 0.0f, (sin(timeValue) * 2.0f) + 0.5f, (sin(timeValue - 2.0f) * 2.0f) + 0.5f, (sin(timeValue - 4.0f) * 2.0f) + 0.5f  // top   
		};

		processInput(my_window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(my_window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void resizeWindow(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}