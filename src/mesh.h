#pragma once

#include "gl_utils.h"
#include "shader.h"
#include "camera.h"

#define NUM_ROWS 100
#define NUM_COLS 100

typedef struct Mesh{
	GLuint vao;
	GLuint point_vbo, tex_vbo, normal_vbo; // idk why he doesn't have these so I'mma throw 'em in
	int point_count;
}Mesh;

Mesh load_cube_mesh();
Mesh load_plane_mesh();
Mesh load_plane_mesh_given_points(float* points);
float* gen_plane_points(int rows, int cols);
float* gen_plane_normals(float* points, int num_points);
float* displace_points(float* points, int num_points);
void draw_plane(Shader_Meta s, Mesh* m, float** points, Camera c);