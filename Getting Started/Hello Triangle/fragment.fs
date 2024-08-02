#version 330 core

out vec4 FragColor;
in vec3 colPosition;

uniform int color;

void main()
{
	if(color == 0) FragColor = vec4(0.2656f, 0.2226f, 0.3398f, 1.0f);
	else if(color == 1) FragColor = vec4(0.5078f, 0.3516f, 0.5352f, 1.0f);
	else if(color == 2) FragColor = vec4(0.7343f, 0.4804f, 0.6172f, 1.0f);
	else if(color == 3) FragColor = vec4(0.9297f, 0.6094f, 0.6406f, 1.0f);
	else FragColor = vec4(colPosition, 1.0f);
}