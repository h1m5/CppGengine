#version 410
const int MAX_LIGHTS = 5;

layout(location = 0)in vec3 vert;
layout(location = 1)in vec3 normal;
layout(location = 2)in vec2 tCoord;

uniform mat4 pMatrix;
uniform mat4 vMatrix;
uniform mat4 mMatrix;

uniform vec3 lightPosition[MAX_LIGHTS];
uniform vec3 cameraPosition;

out vec2 uv;
out vec3 vertToLight[MAX_LIGHTS];
out vec3 vertToCamera;
out vec3 norm;
out float visibility;

const float density = 0.0035;
const float gradient = 5.0;

void main()
{
    vec4 worldPosition = mMatrix * vec4(vert, 1.0f);
    vec4 positionRelativeToCam = vMatrix * worldPosition;
    gl_Position = pMatrix * vMatrix * mMatrix * vec4(vert, 1.0f);
    uv = tCoord;
    
    vec4 n = mMatrix * vec4(normal, 0.0);
    norm = n.xyz;
    
    for(int i=0; i<MAX_LIGHTS; i++){
        vertToLight[i] = lightPosition[i] - worldPosition.xyz;
    }
    vertToCamera = cameraPosition - worldPosition.xyz;
    
    float distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow((distance*density),gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}
