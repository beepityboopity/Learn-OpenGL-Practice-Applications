#version 330 core
out vec4 FragColor;

in vec3 Light; 

void main()
{
   FragColor = vec4(Light, 1.0);
}