#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoords;

uniform vec3 lightPos;
uniform vec3 lightAmb;
uniform vec3 lightDiff;
uniform vec3 lightSpec;

uniform sampler2D objDiff;
uniform sampler2D objSpec;
uniform float objShiny;

uniform vec3 viewPos;

vec3 directionLightCalc(dirLight light, vec3 normal, vec3 viewDir);
vec3 pointLightCalc(pointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 spotLightCalc(spotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {

	// ambient
    vec3 ambient = lightAmb * vec3(texture(objDiff, texCoords));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightDiff * diff * vec3(texture(objDiff, texCoords));
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objShiny);
    vec3 specular = lightSpec * spec * vec3(texture(objSpec, texCoords));  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}