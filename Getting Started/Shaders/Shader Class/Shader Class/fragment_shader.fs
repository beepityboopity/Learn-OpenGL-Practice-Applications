#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec3 colPosition;

void main(){
	FragColor = vec4(colPosition, 1.0f);
}