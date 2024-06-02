#version 330 core
out vec4 fColor;
in vec3 myColor;
in vec2 coord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;

void main(){
	fColor = mix(texture(texture1, coord), texture(texture2, vec2(1 - coord.x, coord.y)), mixer);
	if (fColor.a < 0.1) 
		discard;
}