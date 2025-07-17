#version 310 es

precision mediump float;

// input
//
// position, normal, uv
layout(location = 0) in vec3 p;
layout(location = 1) in vec3 n;
layout(location = 2) in vec2 u;

layout(set = 0, binding = 0) uniform UBO {
    // camera pos (x, y, z) and aspect ratio (w)
    vec4 camera_pos;

    // model's matrix
    mat4 model_mat;

    // Mouse rotation yaw (x), pitch (y)
    vec2 mouse;
};

// outputs to frag
//
// uv coords
layout(location = 0) out vec2 vu;

// Generate a rotation Matrix around the x,y,z axis;
// Used for model rotation and camera yaw
mat4 rx(float r) {
    return mat4(
        1, 0, 0, 0,
        0, cos(r), sin(r), 0,
        0, -sin(r), cos(r), 0,
        0, 0, 0, 1
    );
}

mat4 ry(float r) {
    return mat4(
        cos(r), 0, -sin(r), 0,
        0, 1, 0, 0,
        sin(r), 0, cos(r), 0,
        0, 0, 0, 1
    );
}

mat4 rz(float r) {
    return mat4(
        cos(r), sin(r), 0, 0,
        -sin(r), cos(r), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

struct mat_comp {
    mat3 rotation;
    vec3 translation;
    vec3 scale;
};

mat_comp decomp_mat(mat4 matrix) {
    mat_comp components;

    components.translation = vec3(matrix[3].xyz);

    components.scale = vec3(
        length(matrix[0].xyz),
        length(matrix[1].xyz),
        length(matrix[2].xyz)
    );

    components.rotation = mat3(
        matrix[0].xyz / components.scale.x,
        matrix[1].xyz / components.scale.y,
        matrix[2].xyz / components.scale.z
    );

    return components;
}

void main(void) {

    vu = u;

    // Final vertex position is transformed by the projection matrix,
    // rotated around mouse yaw/pitch and offset by the camera position
    // We use a FOV of 90, so the matrix[0] and [5] are conveniently 1.
    // (1 / Math.tan((90/180) * Math.PI / 2) === 1)
    gl_Position = vec4(p, 1);
}
