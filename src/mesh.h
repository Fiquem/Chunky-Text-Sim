#pragma once

#include "gl_utils.h"

typedef struct Mesh{
	GLuint vao;
	GLuint point_vbo, tex_vbo, normal_vbo; // idk why he doesn't have these so I'mma throw 'em in
	int point_count;
}Mesh;

Mesh load_cube_mesh();