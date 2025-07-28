
#include <SDL3/SDL.h>

#ifndef GAME_VERT_H
#define GAME_VERT_H

typedef struct GameVertInput {
    float p[3];
    float n[3];
    float u[2];
} GameVertInput;

static float v[][3] = {
    { 1.000000 , 1.000000  , -1.000000  },
    { 1.000000 , -1.000000 , -1.000000  },
    { 1.000000 , 1.000000  , 1.000000   },
    { 1.000000 , -1.000000 , 1.000000   },
    { -1.000000,  1.000000 ,  -1.000000 },
    { -1.000000,  -1.000000,  -1.000000 },
    { -1.000000,  1.000000 ,  1.000000  },
    { -1.000000,  -1.000000,  1.000000  },
};

static float normals[][3] = {
    { -0.0000,  1.0000 , -0.0000 },
    { -0.0000,  -0.0000,  1.0000 },
    { -1.0000,  -0.0000,  -0.0000},
    { -0.0000,  -1.0000,  -0.0000},
    { 1.0000 , -0.0000 , -0.0000 },
    { -0.0000,  -0.0000,  -1.0000},
};

static float uvs[][2] = {
    { 0.333333, 0.333333},
    { 0.000000, 0.000000},
    { 0.333333, 0.000000},
    { 0.000000, 0.666667},
    { 0.333333, 0.333333},
    { 0.333333, 0.666667},
    { 0.333333, 0.333333},
    { 0.666667, 0.000000},
    { 0.666667, 0.333333},
    { 0.666667, 0.666667},
    { 0.333333, 0.333333},
    { 0.666667, 0.333333},
    { 0.000000, 1.000000},
    { 0.333333, 0.666667},
    { 0.333333, 1.000000},
    { 0.333333, 1.000000},
    { 0.666667, 0.666667},
    { 0.666667, 1.000000},
    { 0.000000, 0.333333},
    { 0.000000, 0.333333},
    { 0.333333, 0.000000},
    { 0.333333, 0.666667},
    { 0.000000, 0.666667},
    { 0.333333, 0.666667},
};

typedef struct Payload {
    GameVertInput game_vert_input[36];
} Payload;

Payload get_gvi() {
    return (Payload){
        .game_vert_input = {
            // each one of these is a triangle
            // the indices here start at 1
            // so array indices will be one less
            // f 5/1/1 3/2/1 1/3/1
                (GameVertInput) {.p = {v[4][0],v[4][1],v[4][2],}, .u = {uvs[0][0],uvs[0][1],}, .n = {normals[0][0], normals[0][1], normals[0][2]}},
                (GameVertInput) {.p = {v[2][0],v[2][1],v[2][2],}, .u = {uvs[1][0],uvs[1][1],}, .n = {normals[0][0], normals[0][1], normals[0][2]}},
                (GameVertInput) {.p = {v[0][0],v[0][1],v[0][2],}, .u = {uvs[2][0],uvs[2][1],}, .n = {normals[0][0], normals[0][1], normals[0][2]}},

            // f 3/4/2 8/5/2 4/6/2
                (GameVertInput) {.p = {v[2][0],v[2][1],v[2][2],}, .u = {uvs[3][0],uvs[3][1],}, .n = {normals[1][0], normals[1][1], normals[1][2]}},
                (GameVertInput) {.p = {v[7][0],v[7][1],v[7][2],}, .u = {uvs[4][0],uvs[4][1],}, .n = {normals[1][0], normals[1][1], normals[1][2]}},
                (GameVertInput) {.p = {v[3][0],v[3][1],v[3][2],}, .u = {uvs[5][0],uvs[5][1],}, .n = {normals[1][0], normals[1][1], normals[1][2]}},

            // f 7/7/3 6/8/3 8/9/3
                (GameVertInput) {.p = {v[6][0],v[6][1],v[6][2],}, .u = {uvs[6][0],uvs[6][1],}, .n = {normals[2][0], normals[2][1], normals[2][2]}},
                (GameVertInput) {.p = {v[5][0],v[5][1],v[5][2],}, .u = {uvs[7][0],uvs[7][1],}, .n = {normals[2][0], normals[2][1], normals[2][2]}},
                (GameVertInput) {.p = {v[7][0],v[7][1],v[7][2],}, .u = {uvs[8][0],uvs[8][1],}, .n = {normals[2][0], normals[2][1], normals[2][2]}},

            // f 2/10/4 8/11/4 6/12/4
                (GameVertInput)  {.p = {v[1][0],v[1][1],v[1][2],}, .u = {uvs[9][0],uvs[9][1]},   .n = {normals[3][0], normals[3][1], normals[3][2]}},
                (GameVertInput) {.p = {v[7][0],v[7][1],v[7][2],}, .u = {uvs[10][0],uvs[10][1]}, .n = {normals[3][0], normals[3][1], normals[3][2]}},
                (GameVertInput) {.p = {v[5][0],v[5][1],v[5][2],}, .u = {uvs[11][0],uvs[11][1]}, .n = {normals[3][0], normals[3][1], normals[3][2]}},

            // f 1/13/5 4/14/5 2/15/5
                (GameVertInput) {.p = {v[0][0],v[0][1],v[0][2],}, .u = {uvs[12][0],uvs[12][1],}, .n = {normals[4][0], normals[4][1], normals[4][2]}},
                (GameVertInput) {.p = {v[3][0],v[3][1],v[3][2],}, .u = {uvs[13][0],uvs[13][1],}, .n = {normals[4][0], normals[4][1], normals[4][2]}},
                (GameVertInput) {.p = {v[1][0],v[1][1],v[1][2],}, .u = {uvs[14][0],uvs[14][1],}, .n = {normals[4][0], normals[4][1], normals[4][2]}},

            // f 5/16/6 2/17/6 6/18/6
                (GameVertInput) {.p = {v[4][0],v[4][1],v[4][2],}, .u = {uvs[15][0],uvs[15][1],}, .n = {normals[5][0], normals[5][1], normals[5][2]}},
                (GameVertInput) {.p = {v[1][0],v[1][1],v[1][2],}, .u = {uvs[16][0],uvs[16][1],}, .n = {normals[5][0], normals[5][1], normals[5][2]}},
                (GameVertInput) {.p = {v[5][0],v[5][1],v[5][2],}, .u = {uvs[17][0],uvs[17][1],}, .n = {normals[5][0], normals[5][1], normals[5][2]}},

            // f 5/1/1 7/19/1 3/2/1
                (GameVertInput) {.p = {v[4][0],v[4][1],v[4][2],}, .u = {uvs[ 0][0],uvs[ 0][1],},  .n = {normals[0][0], normals[0][1], normals[0][2]}},
                (GameVertInput) {.p = {v[6][0],v[6][1],v[6][2],}, .u = {uvs[18][0],uvs[18][1],}, .n = {normals[0][0], normals[0][1], normals[0][2]}},
                (GameVertInput) {.p = {v[2][0],v[2][1],v[2][2],}, .u = {uvs[ 1][0],uvs[ 1][1],},  .n = {normals[0][0], normals[0][1], normals[0][2]}},

            // f 3/4/2 7/20/2 8/5/2
                (GameVertInput) {.p = {v[2][0],v[2][1],v[2][2],}, .u = {uvs[ 3][0],uvs[ 3][1],},  .n = {normals[1][0], normals[1][1], normals[1][2]}},
                (GameVertInput) {.p = {v[6][0],v[6][1],v[6][2],}, .u = {uvs[19][0],uvs[19][1],}, .n = {normals[1][0], normals[1][1], normals[1][2]}},
                (GameVertInput) {.p = {v[7][0],v[7][1],v[7][2],}, .u = {uvs[ 4][0],uvs[ 4][1],},  .n = {normals[1][0], normals[1][1], normals[1][2]}},

            // f 7/7/3 5/21/3 6/8/3
                (GameVertInput) {.p = {v[6][0],v[6][1],v[6][2],}, .u = {uvs[ 6][0],uvs[ 6][1],},  .n = {normals[2][0], normals[2][1], normals[2][2]}},
                (GameVertInput) {.p = {v[4][0],v[4][1],v[4][2],}, .u = {uvs[20][0],uvs[20][1],}, .n = {normals[2][0], normals[2][1], normals[2][2]}},
                (GameVertInput) {.p = {v[5][0],v[5][1],v[5][2],}, .u = {uvs[ 7][0],uvs[ 7][1],},  .n = {normals[2][0], normals[2][1], normals[2][2]}},

            // f 2/10/4 4/22/4 8/11/4
                (GameVertInput) {.p = {v[1][0],v[1][1],v[1][2],}, .u = {uvs[ 9][0],uvs[ 9][1],},  .n = {normals[3][0], normals[3][1], normals[3][2]}},
                (GameVertInput) {.p = {v[3][0],v[3][1],v[3][2],}, .u = {uvs[21][0],uvs[21][1],}, .n = {normals[3][0], normals[3][1], normals[3][2]}},
                (GameVertInput) {.p = {v[7][0],v[7][1],v[7][2],}, .u = {uvs[10][0],uvs[10][1],}, .n = {normals[3][0], normals[3][1], normals[3][2]}},

            // f 1/13/5 3/23/5 4/14/5
                (GameVertInput) {.p = {v[0][0],v[0][1],v[0][2],}, .u = {uvs[12][0],uvs[12][1]}, .n = {normals[4][0], normals[4][1], normals[4][2]}},
                (GameVertInput) {.p = {v[2][0],v[2][1],v[2][2],}, .u = {uvs[22][0],uvs[22][1]}, .n = {normals[4][0], normals[4][1], normals[4][2]}},
                (GameVertInput) {.p = {v[3][0],v[3][1],v[3][2],}, .u = {uvs[13][0],uvs[13][1]}, .n = {normals[4][0], normals[4][1], normals[4][2]}},

            // f 5/16/6 1/24/6 2/17/6
                (GameVertInput) {.p = {v[4][0],v[4][1],v[4][2],}, .u = {uvs[15][0],uvs[15][1],}, .n = {normals[5][0], normals[5][1], normals[5][2]}},
                (GameVertInput) {.p = {v[0][0],v[0][1],v[0][2],}, .u = {uvs[23][0],uvs[23][1],}, .n = {normals[5][0], normals[5][1], normals[5][2]}},
                (GameVertInput) {.p = {v[1][0],v[1][1],v[1][2],}, .u = {uvs[16][0],uvs[16][1],}, .n = {normals[5][0], normals[5][1], normals[5][2]}},
            }
    };
}

// Matrix Math
typedef struct Matrix4x4
{
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
} Matrix4x4;

typedef struct Vector3
{
	float x, y, z;
} Vector3;

// Matrix Math

Matrix4x4 Matrix4x4_Identity() {
    return (Matrix4x4){ 
                      1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4x4 Matrix4x4_Add(Matrix4x4 a, Matrix4x4 b)
{
    Matrix4x4 result;
    result.m11 = a.m11 + b.m11;
    result.m12 = a.m12 + b.m12;
    result.m13 = a.m13 + b.m13;
    result.m14 = a.m14 + b.m14;

    result.m21 = a.m21 + b.m21;
    result.m22 = a.m22 + b.m22;
    result.m23 = a.m23 + b.m23;
    result.m24 = a.m24 + b.m24;

    result.m31 = a.m31 + b.m31;
    result.m32 = a.m32 + b.m32;
    result.m33 = a.m33 + b.m33;
    result.m34 = a.m34 + b.m34;

    result.m41 = a.m41 + b.m41;
    result.m42 = a.m42 + b.m42;
    result.m43 = a.m43 + b.m43;
    result.m44 = a.m44 + b.m44;

    return result;
}

Matrix4x4 Matrix4x4_Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2)
{
	Matrix4x4 result;

	result.m11 = (
		(matrix1.m11 * matrix2.m11) +
		(matrix1.m12 * matrix2.m21) +
		(matrix1.m13 * matrix2.m31) +
		(matrix1.m14 * matrix2.m41)
	);
	result.m12 = (
		(matrix1.m11 * matrix2.m12) +
		(matrix1.m12 * matrix2.m22) +
		(matrix1.m13 * matrix2.m32) +
		(matrix1.m14 * matrix2.m42)
	);
	result.m13 = (
		(matrix1.m11 * matrix2.m13) +
		(matrix1.m12 * matrix2.m23) +
		(matrix1.m13 * matrix2.m33) +
		(matrix1.m14 * matrix2.m43)
	);
	result.m14 = (
		(matrix1.m11 * matrix2.m14) +
		(matrix1.m12 * matrix2.m24) +
		(matrix1.m13 * matrix2.m34) +
		(matrix1.m14 * matrix2.m44)
	);
	result.m21 = (
		(matrix1.m21 * matrix2.m11) +
		(matrix1.m22 * matrix2.m21) +
		(matrix1.m23 * matrix2.m31) +
		(matrix1.m24 * matrix2.m41)
	);
	result.m22 = (
		(matrix1.m21 * matrix2.m12) +
		(matrix1.m22 * matrix2.m22) +
		(matrix1.m23 * matrix2.m32) +
		(matrix1.m24 * matrix2.m42)
	);
	result.m23 = (
		(matrix1.m21 * matrix2.m13) +
		(matrix1.m22 * matrix2.m23) +
		(matrix1.m23 * matrix2.m33) +
		(matrix1.m24 * matrix2.m43)
	);
	result.m24 = (
		(matrix1.m21 * matrix2.m14) +
		(matrix1.m22 * matrix2.m24) +
		(matrix1.m23 * matrix2.m34) +
		(matrix1.m24 * matrix2.m44)
	);
	result.m31 = (
		(matrix1.m31 * matrix2.m11) +
		(matrix1.m32 * matrix2.m21) +
		(matrix1.m33 * matrix2.m31) +
		(matrix1.m34 * matrix2.m41)
	);
	result.m32 = (
		(matrix1.m31 * matrix2.m12) +
		(matrix1.m32 * matrix2.m22) +
		(matrix1.m33 * matrix2.m32) +
		(matrix1.m34 * matrix2.m42)
	);
	result.m33 = (
		(matrix1.m31 * matrix2.m13) +
		(matrix1.m32 * matrix2.m23) +
		(matrix1.m33 * matrix2.m33) +
		(matrix1.m34 * matrix2.m43)
	);
	result.m34 = (
		(matrix1.m31 * matrix2.m14) +
		(matrix1.m32 * matrix2.m24) +
		(matrix1.m33 * matrix2.m34) +
		(matrix1.m34 * matrix2.m44)
	);
	result.m41 = (
		(matrix1.m41 * matrix2.m11) +
		(matrix1.m42 * matrix2.m21) +
		(matrix1.m43 * matrix2.m31) +
		(matrix1.m44 * matrix2.m41)
	);
	result.m42 = (
		(matrix1.m41 * matrix2.m12) +
		(matrix1.m42 * matrix2.m22) +
		(matrix1.m43 * matrix2.m32) +
		(matrix1.m44 * matrix2.m42)
	);
	result.m43 = (
		(matrix1.m41 * matrix2.m13) +
		(matrix1.m42 * matrix2.m23) +
		(matrix1.m43 * matrix2.m33) +
		(matrix1.m44 * matrix2.m43)
	);
	result.m44 = (
		(matrix1.m41 * matrix2.m14) +
		(matrix1.m42 * matrix2.m24) +
		(matrix1.m43 * matrix2.m34) +
		(matrix1.m44 * matrix2.m44)
	);

	return result;
}

Matrix4x4 Matrix4x4_CreateRotationX(float radians)
{
    return (Matrix4x4) {
        1, 0, 0, 0,
        0, SDL_cosf(radians), SDL_sinf(radians), 0,
        0, -SDL_sinf(radians), SDL_cosf(radians), 0,
        0, 0, 0, 1
    };
}

Matrix4x4 Matrix4x4_CreateRotationY(float radians)
{
    return (Matrix4x4) {
        SDL_cosf(radians), 0, -SDL_sinf(radians), 0,
        0, 1, 0, 0,
        SDL_sinf(radians), 0, SDL_cosf(radians), 0,
        0, 0, 0, 1
    };
}

Matrix4x4 Matrix4x4_CreateRotationZ(float radians)
{
	return (Matrix4x4) {
		 SDL_cosf(radians), SDL_sinf(radians), 0, 0,
		-SDL_sinf(radians), SDL_cosf(radians), 0, 0,
						 0, 				0, 1, 0,
						 0,					0, 0, 1
	};
}

Matrix4x4 Matrix4x4_CreateTranslation(float x, float y, float z)
{
	return (Matrix4x4) {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	};
}

Matrix4x4 Matrix4x4_CreateOrthographicOffCenter(
	float left,
	float right,
	float bottom,
	float top,
	float zNearPlane,
	float zFarPlane
) {
	return (Matrix4x4) {
		2.0f / (right - left), 0, 0, 0,
		0, 2.0f / (top - bottom), 0, 0,
		0, 0, 1.0f / (zNearPlane - zFarPlane), 0,
		(left + right) / (left - right), (top + bottom) / (bottom - top), zNearPlane / (zNearPlane - zFarPlane), 1
	};
}

Matrix4x4 Matrix4x4_CreatePerspectiveFieldOfView(
	float fieldOfView,
	float aspectRatio,
	float nearPlaneDistance,
	float farPlaneDistance
) {
	float num = 1.0f / ((float) SDL_tanf(fieldOfView * 0.5f));
	return (Matrix4x4) {
		num / aspectRatio, 0, 0, 0,
		0, num, 0, 0,
		0, 0, farPlaneDistance / (nearPlaneDistance - farPlaneDistance), -1,
		0, 0, (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance), 0
	};
}

Vector3 Vector3_Normalize(Vector3 vec)
{
	float magnitude = SDL_sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return (Vector3) {
		vec.x / magnitude,
		vec.y / magnitude,
		vec.z / magnitude
	};
}

float Vector3_Dot(Vector3 vecA, Vector3 vecB)
{
	return (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z);
}

Vector3 Vector3_Cross(Vector3 vecA, Vector3 vecB)
{
	return (Vector3) {
		vecA.y * vecB.z - vecB.y * vecA.z,
		-(vecA.x * vecB.z - vecB.x * vecA.z),
		vecA.x * vecB.y - vecB.x * vecA.y
	};
}

Matrix4x4 Matrix4x4_CreateLookAt(
	Vector3 cameraPosition,
	Vector3 cameraTarget,
	Vector3 cameraUpVector
) {
	Vector3 targetToPosition = {
		cameraPosition.x - cameraTarget.x,
		cameraPosition.y - cameraTarget.y,
		cameraPosition.z - cameraTarget.z
	};
	Vector3 vectorA = Vector3_Normalize(targetToPosition);
	Vector3 vectorB = Vector3_Normalize(Vector3_Cross(cameraUpVector, vectorA));
	Vector3 vectorC = Vector3_Cross(vectorA, vectorB);

	return (Matrix4x4) {
		vectorB.x, vectorC.x, vectorA.x, 0,
		vectorB.y, vectorC.y, vectorA.y, 0,
		vectorB.z, vectorC.z, vectorA.z, 0,
		-Vector3_Dot(vectorB, cameraPosition), -Vector3_Dot(vectorC, cameraPosition), -Vector3_Dot(vectorA, cameraPosition), 1
	};
}

#endif // GAME_VERT_H