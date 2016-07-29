#include "mesh.h"
#include "cube.h"
#include "shader.h"

Mesh load_cube_mesh(){
	Mesh cube;
	cube.point_count = 3 * 2 * 6; // 3 points * 2 triangle * 6 faces

	glGenVertexArrays (1, &cube.vao);
	glGenBuffers (1, &cube.point_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, cube.point_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * cube.point_count, cube_points, GL_STATIC_DRAW);
	//glGenBuffers (1, &cube.tex_vbo);
	//glBindBuffer (GL_ARRAY_BUFFER, cube.tex_vbo);
	//glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * cube.point_count, cube_tex_coords, GL_STATIC_DRAW);
	glGenBuffers (1, &cube.normal_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, cube.normal_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * cube.point_count, cube_normals, GL_STATIC_DRAW);

	glBindVertexArray (cube.vao);
	glEnableVertexAttribArray (POINT);
	//glEnableVertexAttribArray (TEX_COORD);
	glEnableVertexAttribArray (NORMAL);
	glVertexAttribPointer (POINT, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer (TEX_COORD, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer (NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	return cube;

	// why isn't this workingngggngg
}