#version 410
in vec2 uv;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

const float width = 0.5;
const float edge = 0.1;

const float borderWidth = 0.7;
const float borderEdge = 0.1;

const vec2 offset = vec2(0.006, 0.006);
const vec3 outlineColour = vec3(1.0, 0.0, 0.0);

void main()
{
//    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, uv).r);
//    color = vec4(textColor, 1.0) * sampled;
    
    
    float distance = 1.0 - texture(text, uv).a;
    float alpha = 1.0 - smoothstep(width, width + edge, distance);
    
    float distance2 = 1.0 - texture(text, uv).a;
    float outlineAlpha = 1.0 - smoothstep(borderWidth, borderWidth + borderEdge, distance2);

    float overallAlpha = alpha + (1.0 - alpha) * outlineAlpha;
    vec3 overallColour = mix(outlineColour, textColor, alpha/overallAlpha);
    
    color = vec4(overallColour, overallAlpha);
}