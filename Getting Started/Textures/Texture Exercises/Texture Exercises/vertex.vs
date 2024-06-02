#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTextureCoord;

out vec3 myColor;
out vec2 coord;

void main(){
	gl_Position = vec4(vPosition, 1.0);
	myColor = vColor;
	coord = vTextureCoord;
}
