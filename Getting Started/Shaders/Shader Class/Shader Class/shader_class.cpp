#include "shader_class.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::ifstream vShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string fragmentCode;
	std::ifstream fShaderFile;
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ya shaders fucked" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}