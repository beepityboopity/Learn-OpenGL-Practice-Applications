#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightAmb;
uniform vec3 lightDiff;
uniform vec3 lightSpec;

uniform vec3 objAmb;
uniform vec3 objDiff;
uniform vec3 objSpec;
uniform float objShiny;

uniform vec3 viewPos;

void main() {

	// ambient
    vec3 ambient = lightAmb * objAmb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightDiff * (diff * objDiff);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objShiny);
    vec3 specular = lightSpec * (spec * objSpec);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}