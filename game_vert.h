
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
