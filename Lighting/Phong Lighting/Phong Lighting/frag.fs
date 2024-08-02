#version 330 core
out vec4 fColor;
in vec2 coord;
in vec3 Norm;

uniform sampler2D currentTexture;

void main(){
	fColor = texture(currentTexture, coord);
	if (fColor.a <= 0.1)
		discard;
}