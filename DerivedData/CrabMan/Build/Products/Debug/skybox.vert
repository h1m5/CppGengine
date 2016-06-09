#version 410

layout (location = 0)in vec3 position;

out vec3 textureCoords;

uniform mat4 pMatrix;
uniform mat4 vMatrix;
uniform mat4 mMatrix;

void main()
{
    vec4 pos = pMatrix * vMatrix * mMatrix * vec4(position, 1.0);
    gl_Position = pos.xyww;
    textureCoords = position;
}