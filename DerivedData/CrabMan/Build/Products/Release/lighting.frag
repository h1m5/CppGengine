#version 410
const int MAX_LIGHTS = 5;

in vec2 uv;
in vec3 vertToLight[MAX_LIGHTS];
in vec3 vertToCamera;
in vec3 norm;
in float visibility;

out vec4 fragColor;
uniform sampler2D texDiffuse;
uniform sampler2D texSpecular;
uniform vec3 lightColor[MAX_LIGHTS];
uniform vec3 attenuation[MAX_LIGHTS];
uniform float shininess;
uniform bool hasMaterial;
uniform bool useTransparency;
uniform vec3 skyColour;

const float levels = 5.0f;

struct Material {
    vec4 diffuse;
    vec4 specular;
};
uniform Material material;
void main()
{
    vec3 diffuseContribution = vec3(0.0f);
    vec3 specularContribution = vec3(0.0f);
    
    for(int i=0; i<MAX_LIGHTS; i++){
        //calculate attenuation
        float distance = length(vertToLight[i]);
        float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z *distance *distance);
        
        //calculate diffuse
        vec3 normal = normalize(norm);
        vec3 lightDirection = normalize(vertToLight[i]);
        float NdotL = max(dot(normal, lightDirection), 0.2f);
        float level = floor(NdotL * levels);
        NdotL = level / levels;
        
        vec4 texDif = texture(texDiffuse,uv);
        
        //calculate specular
        vec3 halfVector = normalize(normalize(vertToCamera) + lightDirection);
        float NdotHV = max(dot(normal, halfVector), 0.0f);
        level = floor(NdotHV * levels);
        NdotHV = level/levels;
        float specHighlight = pow(NdotHV, shininess);
        
        vec4 texSpec = texture(texSpecular,uv);
        
        if(useTransparency){
            if(texDif.a < 0.5) discard;
            if(texSpec.a < 0.5) discard;
        }
        
        if(hasMaterial == true){
            diffuseContribution += (lightColor[i] * material.diffuse.xyz * NdotL) / attFactor;
            specularContribution += (lightColor[i] * specHighlight * material.specular.xyz) / attFactor;
        } else {
            diffuseContribution += (texDif.xyz * lightColor[i] * NdotL) / attFactor;
            specularContribution += (texSpec.xyz * lightColor[i] * specHighlight) / attFactor;
        }
    }
    
    
    
    //    fragColor = vec4(0.2f, 0.42f, 0.54f, 1.0f);
    //    fragColor = texture(texDiffuse, uv) + texture(texSpecular, uv);
    fragColor = vec4(diffuseContribution, 1.0) + vec4(specularContribution,1.0);
    fragColor = mix(vec4(skyColour,1.0f), fragColor, visibility);
}