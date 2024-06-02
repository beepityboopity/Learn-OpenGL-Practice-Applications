#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vOffset;

out vec3 ourColor;
uniform float myTime;

void main()
{
    gl_Position = vec4(vPosition.x + (0.25 * sin(myTime)), vPosition.y + (0.25 * sin(myTime)), 0.0, 1.0);
    ourColor = vec3((sin(myTime + vOffset.x) * 2.0f) + 0.5f, (sin(myTime + vOffset.y) * 2.0f) + 0.5f, (sin(myTime + vOffset.z) * 2.0f) + 0.5f);
}