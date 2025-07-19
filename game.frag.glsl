#version 310 es

precision mediump float;

// input from vert
//
// uv coords
layout(location = 0) in vec2 vu;


// set = 2 for frag sampled textures
// https://wiki.libsdl.org/SDL3/SDL_CreateGPUShader
layout(set = 2, binding = 0) uniform sampler2D tex;

// // I don't know why set = 3, but it needs to.
// layout(set = 3, binding = 0) uniform UBO {
//     int lights;
// };


// output
layout(location = 0) out vec4 fragColor;

void main(void) {
    fragColor = texture(tex, vu);
    // fragColor = vec4(vu, 0,1);
}

// #version 310 es
// precision mediump float;
// precision highp int;

// uniform highp sampler2D SPIRV_Cross_CombinedTextureSampler;

// layout(location = 0) in highp vec2 in_var_TEXCOORD0;
// layout(location = 0) out highp vec4 out_var_SV_Target0;

// void main()
// {
//     out_var_SV_Target0 = texture(SPIRV_Cross_CombinedTextureSampler, in_var_TEXCOORD0);
// }
