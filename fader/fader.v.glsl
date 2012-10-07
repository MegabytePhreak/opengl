#version 110

uniform float timer;

attribute vec2 position;

varying vec2 texcoord;
varying float fade_factor;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    texcoord = position.xy * vec2(0.5) + vec2(0.5);
    fade_factor = sin(timer) * 0.5 + 0.5;
}

