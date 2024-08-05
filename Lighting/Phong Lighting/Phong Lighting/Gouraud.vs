#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

out vec3 Light;

uniform vec3 lightPos;
uniform vec3 lightAmb;
uniform vec3 lightDiff;
uniform vec3 lightSpec;

uniform vec3 objAmb;
uniform vec3 objDiff;
uniform vec3 objSpec;
uniform float objShiny;

uniform vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vPosition, 1.0);
    vec3 Position = vec3(model * vec4(vPosition, 1.0));
    vec3 Normal = normalize(vNormal);
    
    // ambient
    vec3 ambient = lightAmb * objAmb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightDiff * (diff * objDiff);
    
    // specular
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objShiny);
    vec3 specular = lightSpec * (spec * objSpec);    

    Light = ambient + diffuse + specular;
}