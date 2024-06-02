#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_class.h>
#include <algorithm>
#include <cmath>

void frameCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	glfwInit(); // initialize opengl
	// set the version of opengl being used: 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // specifies the core profile
	GLFWwindow* myWindow = glfwCreateWindow(800, 600, "yippee!", NULL, NULL); // creates the window object
	glfwMakeContextCurrent(myWindow); // sets myWindow as the current window
	glfwSetFramebufferSizeCallback(myWindow, frameCallback); // links the frameCallback function to myWindow
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // sets up pointers to opengl functions
	// sets up the vertex and fragment shaders
	Shader basicShader("vertex_shader.vs", "fragment_shader.fs");
	basicShader.use();

	// vertices of the triangle
	float triangle[] = {
		//       X       Y      Z         Offset for color
				-0.75f, -0.75f, 0.0f,    4.0f,  2.0f,  0.0f, // bottom left
				 0.75f, -0.75f, 0.0f,    2.0f,  0.0f, -2.0f, // bottom right
				0.0f,  0.75f, 0.0f,    0.0f, -2.0f, -4.0f, // top left
				 0.75f,  0.75f, 0.0f,    0.0f,  0.0f,  0.0f  // top right
	};

	// specific to EBOs, the order of vertices that will be repeated
	unsigned int indices[] = {
		0, 1, 2, // first triangle
		1, 2, 3  // second triangle
	};

	// vBuffer = storage for vertices
	// vArray = collection of vertex buffers and their corresponding attributes
	// eBuffer = storage for vertices but specific vertices can be repeated by specifying their index order
	unsigned int vBuffer, vArray, eBuffer;
	glGenVertexArrays(1, &vArray); // generates one vertex array that the buffers get stored in
	glGenBuffers(1, &vBuffer); // generates the buffer for the vertex data
	glGenBuffers(1, &eBuffer); // generates the buffer for the index data
	glBindVertexArray(vArray); // binds the vertex array so we can now modify whats in it
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer); // binds the vertex buffer to the array, specifying that it is for vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW); // binds the actual vertex data to the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eBuffer); // binds the element buffer to the array, specifying that it is for indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // binds the actual index data to the buffer
	// tells opengl how to manage and find the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// turns on the above attribute
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(myWindow)) {
		processInput(myWindow);
		float timeValue = 0.5 * glfwGetTime();
		basicShader.setFloat("myTime", timeValue);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // sets the background color
		glClear(GL_COLOR_BUFFER_BIT); // clears the color buffer so we can use other stuff there
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // draws the vertices based on the currently bound EBO

		glfwSwapBuffers(myWindow); // swaps buffers so the window renders without flickering
		glfwPollEvents(); // waits for user input before continuing
	}
	// deletes everything after its done being used
	glDeleteVertexArrays(1, &vArray);
	glDeleteBuffers(1, &vBuffer);
	glDeleteBuffers(1, &eBuffer);
	return 0;
}
// process input, only closes the window
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
// resizes the window
void frameCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}