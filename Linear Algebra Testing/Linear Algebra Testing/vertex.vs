#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TextureCoord;
layout (location = 2) in vec3 Normal;

out vec2 coord;
out vec3 Norm;
out vec3 fPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	fPos = vec3(model * vec4(Position, 1.0));
	gl_Position = projection * view * vec4(fPos, 1.0);
	coord = TextureCoord;
	Norm = Normal;
}