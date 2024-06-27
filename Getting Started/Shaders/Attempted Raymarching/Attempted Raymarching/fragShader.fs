#version 330 core

out vec4 FragColor;

in vec2 positionVec;
uniform float iTime;
uniform float camHorizontal;
uniform float camVertical;
uniform vec2 mousePos;

float sdSphere(vec3 p, float s)
{ // sine distance sphere
    return length(p) - s;
}

float sdBox(vec3 p, vec3 b)
{ // sine distance box
    vec3 q = abs(p) - b;
    return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
}

float opUnion(float d1, float d2)
{ // union operator
    return min(d1, d2);
}

float opSmoothUnion(float d1, float d2, float k)
{
    float h = clamp(0.5 + 0.5*(d2 - d1)/k, 0.0, 1.0);
    return mix(d2, d1, h) - k*h*(1.0-h);
}

float opSubtraction(float d1, float d2)
{ // difference operator
    return max(-d1, d2);
}

float opSmoothSubtraction(float d1, float d2, float k)
{
    float h = clamp(0.5 + 0.5*(d2 + d1)/k, 0.0, 1.0);
    return mix(d2, -d1, h) + k*h*(1.0-h);
}

float opIntersection(float d1, float d2)
{ // intersection operator
    return max(d1, d2);
}

float opSmoothIntersection(float d1, float d2, float k)
{
    float h = clamp(0.5 + 0.5*(d2 - d1)/k, 0.0, 1.0);
    return mix(d2, d1, h) + k*h*(1.0-h);
}

float smin(float a, float b, float c)
{ // smooth minimum (very goopy)
    float h = max(c - abs(a - b), 0.0)/c;
    return min(a, b) - h*h*h*c*(1.0/6.0);
}

mat2 rot2D(float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

mat3 rot3D(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat3(
        oc*axis.x*axis.x+c, 
        oc*axis.x*axis.y-axis.z*s, 
        oc*axis.z*axis.x+axis.y*s,
        oc*axis.x*axis.y+axis.z*s, 
        oc*axis.y*axis.y+c,
        oc*axis.y*axis.z-axis.x*s,
        oc*axis.z*axis.x-axis.y*s,
        oc*axis.y*axis.z+axis.x*s,
        oc*axis.z*axis.z+c
    );
}

vec3 rodRotation(vec3 p, vec3 axis, float angle)
{
    return mix(dot(axis, p) * axis, p, cos(angle)) + cross(axis, p) * sin(angle);
}

vec3 palette(float t)
{
    vec3 a = vec3(1.0);
    vec3 b = vec3(1.0);
    vec3 c = vec3(1.0);
    vec3 d = vec3(0.5, 0.5, 0.5);

    return a + b*cos(6.28318*(c*t+d));
}

float map(vec3 p)
{
    vec3 spherePos = vec3(sin(iTime) * 3.0, 0, 0);
    float sphere = sdSphere(p - spherePos, 0.75);

    vec3 q = fract(p) - 0.5; // copy for rotation
    //q.xz *= rot2D(rotationDirection);

    float box = sdBox(q, vec3(0.1));
    float ground = p.y + 0.75;

    return min(sphere, box);
}

void main()
{ // main
    vec2 m = normalize(mousePos) * 4.0;
    vec3 ro = vec3(0, 0, -3);
    vec3 rd = normalize(vec3(positionVec, 1.0));
    vec3 col = vec3(0);

    ro.yz *= rot2D(camVertical);
    rd.yz *= rot2D(camVertical);
    ro.xz *= rot2D(camHorizontal);
    rd.xz *= rot2D(camHorizontal);
    

    float t = 0.0;

    for (int i = 0; i < 50; i++)
    {
        vec3 p = ro + rd * t;
        float d = map(p);
        t += d;
       
        col = vec3(i)/80.0;
        if (d < 0.001 || t > 100.0) break;
    }
    col = vec3(t * 0.01);
    col = palette(t * 0.04);
    FragColor = vec4(col, 1.0f);
};