#version 410

in vec3 textureCoords;

out vec4 fragColor;

uniform samplerCube cubeMap;
uniform samplerCube cubeMap2;

uniform float blendFactor;
uniform vec3 fogColour;

const float lowerLimit = 0.0f;
const float upperLimit = 0.5f;

void main()
{
    vec4 texColor1 = texture(cubeMap, textureCoords);
//    vec4 texColor2 = texture(cubeMap2, textureCoords);
//    vec4 finalColor = mix(cubeMap, cubeMap2, blendFactor);
    
    float factor = (textureCoords.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);
    
    fragColor = mix(vec4(fogColour, 1.0f), texColor1, factor);
}