#version 330 core

out vec4 FragColor;

in vec2 positionVec;
uniform float iTime;
uniform float camHorizontal;
uniform float camVertical;
uniform vec2 mousePos;

float Sphere(vec3 p, float s)
{ // signed distance sphere
    return length(p) - s;
}

float Box(vec3 p, vec3 b)
{ // signed distance box
    vec3 q = abs(p) - b;
    return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
}

float Torus(vec3 p, vec2 t) // t.x = diameter // t.y = ring thiccness
{ // signed distance donut
    vec2 q = vec2(length(p.xz) - t.x, p.y);
    return length(q) - t.y;
}

float cappedTorus(vec3 p , vec2 sc, float ra, float rb) // i dont know how this works
// sc ranges from -1 to 1, ra and rb are thiccness related
{
    p.x = abs(p.x);
    float k = (sc.y * p.x > sc.x * p.y) ? dot(p.xy, sc) : length(p.xy);
    return sqrt(dot(p, p) + ra * ra - 2.0 * ra * k) - rb;
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
    vec3 a = vec3(0.5);
    vec3 b = vec3(0.5);
    vec3 c = vec3(1.0);
    vec3 d = vec3(0.9, 0.5, 0.6);

    return a + b*cos(7.28318*(c*t+d));
}

float map(vec3 p)
{

    vec3 q = fract(p) - 0.5; // copy for rotation
    float box = Box(p, vec3(0.1));
    float torus = Torus(q, vec2(0.1, 0.05));
    float capTorus = cappedTorus(p, vec2(sin(iTime), cos(iTime)), 1.0, 0.5);

    return capTorus;
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
    col = vec3(t * 0.2);
    //col = palette(t * 0.04);
    FragColor = vec4(col, 1.0f);
};