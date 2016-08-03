#pragma once

#include "gl_utils.h"

typedef struct Mesh{
	GLuint vao;
	GLuint point_vbo, tex_vbo, normal_vbo; // idk why he doesn't have these so I'mma throw 'em in
	int point_count;
}Mesh;

Mesh load_cube_mesh();
Mesh load_plane_mesh();
Mesh load_plane_mesh_given_points(float* points);
float* gen_plane_points(int rows, int cols, int min_off, int max_off);
float* gen_plane_normals(float* points, int num_points);
float* displace_points(float* points, int num_points);