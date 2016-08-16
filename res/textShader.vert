#version 410
layout (location = 0) in vec4 vertex;
out vec2 uv;

uniform mat4 pMatrix;

void main()
{
    gl_Position = pMatrix * vec4(vertex.xy, 0.0, 1.0);
    uv = vertex.zw;
}