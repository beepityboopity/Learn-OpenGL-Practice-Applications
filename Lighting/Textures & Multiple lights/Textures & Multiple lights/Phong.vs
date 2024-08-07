#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	FragPos = vec3(model * vec4(vPosition, 1.0));
	Normal = vNormal;
	texCoords = vTexCoords;
	gl_Position = projection * view * vec4(FragPos, 1.0);
}