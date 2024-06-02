#version 330 core
out vec4 fColor;
in vec3 myColor;
in vec2 coord;

uniform sampler2D texture1;

void main(){
	fColor = texture(texture1, coord);
	if (fColor.a <= 0.1)
		discard;
}