#version 310 es

precision mediump float;

// input from vert
//
// uv coords
layout(location = 0) in vec2 vu;

// input from uniforms
layout(binding = 0) uniform sampler2D s;

// output
layout(location = 0) out vec4 fragColor;

void main(void) {
    fragColor = vec4(vu, 1,1);
}