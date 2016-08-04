#include "mesh.h"
#include "cube.h"
#include "shader.h"
#include "maths_funcs.h"
#include "time.h"

Mesh load_cube_mesh(){
	Mesh cube;
	cube.point_count = 3 * 2 * 6; // 3 points * 2 triangle * 6 faces
	printf("loading cube\n");

	glGenBuffers (1, &cube.point_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, cube.point_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * cube.point_count, cube_points, GL_STATIC_DRAW);
	//glGenBuffers (1, &cube.tex_vbo);
	//glBindBuffer (GL_ARRAY_BUFFER, cube.tex_vbo);
	//glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * cube.point_count, cube_tex_coords, GL_STATIC_DRAW);
	glGenBuffers (1, &cube.normal_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, cube.normal_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * cube.point_count, cube_normals, GL_STATIC_DRAW);

	glGenVertexArrays (1, &cube.vao);
	glBindVertexArray (cube.vao);
	glEnableVertexAttribArray (POINT);
	//glEnableVertexAttribArray (TEX_COORD);
	glEnableVertexAttribArray (NORMAL);
	glBindBuffer (GL_ARRAY_BUFFER, cube.point_vbo);
	glVertexAttribPointer (POINT, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer (TEX_COORD, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, cube.normal_vbo);
	glVertexAttribPointer (NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	printf("cube loaded\n");
	return cube;
	// why isn't this workingngggngg
}

float* gen_plane_points(int rows, int cols){

	float* plane_points_quads = (float*)malloc(sizeof(float)*3*rows*cols);
	// Create an array of size num rows * num cols * 3 points
	// x = row num, y = col num, z = 0 - flat
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < 3*cols; j+=3){
			plane_points_quads[(3*cols*i) + j] = (float)(j/3);
			plane_points_quads[(3*cols*i) + j + 1] = 0.0f;
			plane_points_quads[(3*cols*i) + j + 2] = (float)-i;
		}

		// do a little offset each way
	srand(time(NULL));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < 3*cols; j++){
			plane_points_quads[(3*cols*i) + j] += -0.5f + (rand() % 10)/10.0f;
		}

	// Change quads to tris
	// 4 -> 6? noo
	// think we're gonna do this in steps. bare number of points -> points with repetition as if we were to draw quads -> tris
	// ooh, what's the rule for the number of points I need here
	// 2 rows 2 cols -> 4, 2 rows 3 cols -> 8, 2,4 = 12, so 4*n-1 where n = cols
	// 3 rows 2 cols -> 8, 3 rows 3 cols -> 16, 4*n-1*m-1, n=cols, m=rows LEGGO
	float* plane_points_quads_with_repetition = (float*)malloc(sizeof(float)*3*(rows-1)*(cols-1)*4);
	int index = 0;
	for (int i = 0; i < rows - 1; i++)
		for (int j = 0; j < 3*(cols - 1); j+=3){
			plane_points_quads_with_repetition[index] = plane_points_quads[(3*cols*i) + j];
			plane_points_quads_with_repetition[index + 1] = plane_points_quads[(3*cols*i) + j + 1];
			plane_points_quads_with_repetition[index + 2] = plane_points_quads[(3*cols*i) + j + 2];

			plane_points_quads_with_repetition[index + 3] = plane_points_quads[(3*cols*(i+1)) + j];
			plane_points_quads_with_repetition[index + 4] = plane_points_quads[(3*cols*(i+1)) + j + 1];
			plane_points_quads_with_repetition[index + 5] = plane_points_quads[(3*cols*(i+1)) + j + 2];

			plane_points_quads_with_repetition[index + 6] = plane_points_quads[(3*cols*(i+1)) + j + 3];
			plane_points_quads_with_repetition[index + 7] = plane_points_quads[(3*cols*(i+1)) + j + 4];
			plane_points_quads_with_repetition[index + 8] = plane_points_quads[(3*cols*(i+1)) + j + 5];

			plane_points_quads_with_repetition[index + 9] = plane_points_quads[(3*cols*i) + j + 3];
			plane_points_quads_with_repetition[index + 10] = plane_points_quads[(3*cols*i) + j + 4];
			plane_points_quads_with_repetition[index + 11] = plane_points_quads[(3*cols*i) + j + 5];

			index += 12;
		}

	// Okay, now we can 4 -> 6 I think
	// work with 4 points at a time, 3 floats per point, increments of 3*4
	float* plane_points = (float*)malloc(sizeof(float)*3*(rows-1)*(cols-1)*6);
	index = 0;
	for (int i = 0; i < 3*(rows-1)*(cols-1)*4; i+=12){
		plane_points[index] = plane_points_quads_with_repetition[i];
		plane_points[index + 1] = plane_points_quads_with_repetition[i + 1];
		plane_points[index + 2] = plane_points_quads_with_repetition[i + 2];

		plane_points[index + 3] = plane_points_quads_with_repetition[i + 9];
		plane_points[index + 4] = plane_points_quads_with_repetition[i + 10];
		plane_points[index + 5] = plane_points_quads_with_repetition[i + 11];

		plane_points[index + 6] = plane_points_quads_with_repetition[i + 3];
		plane_points[index + 7] = plane_points_quads_with_repetition[i + 4];
		plane_points[index + 8] = plane_points_quads_with_repetition[i + 5];

		plane_points[index + 9] = plane_points_quads_with_repetition[i + 3];
		plane_points[index + 10] = plane_points_quads_with_repetition[i + 4];
		plane_points[index + 11] = plane_points_quads_with_repetition[i + 5];

		plane_points[index + 12] = plane_points_quads_with_repetition[i + 9];
		plane_points[index + 13] = plane_points_quads_with_repetition[i + 10];
		plane_points[index + 14] = plane_points_quads_with_repetition[i + 11];

		plane_points[index + 15] = plane_points_quads_with_repetition[i + 6];
		plane_points[index + 16] = plane_points_quads_with_repetition[i + 7];
		plane_points[index + 17] = plane_points_quads_with_repetition[i + 8];
		index += 18;
	}

	delete (plane_points_quads);
	delete (plane_points_quads_with_repetition);

	return plane_points;
}

float* gen_plane_normals(float* points, int num_points){
	float* normals = (float*)malloc(sizeof(float)*3*num_points);
	for (int i = 0; i < 3*num_points; i+=3)
	{
		normals[i] = 0.0;
		normals[i + 1] = 1.0;
		normals[i + 2] = 0.0;
	}

	// simple enough
	// for every three points, get 2 vectors and cross product
	// I did 'em backwards the first time OOPS
	// the cross product is order dependent yo

	// oh dear there's some weird stuff happening
	// Normals not right on the first row of trangles (well, half the dfirst row)

	for (int i = 0; i < 3*num_points; i+=9)
	{
		vec3 p0 = vec3(points[i],points[i+1],points[i+2]);
		vec3 p1 = vec3(points[i+3],points[i+4],points[i+5]);
		vec3 p2 = vec3(points[i+6],points[i+7],points[i+8]);
		// I was just using the points, not the vectors.............
		vec3 v0 = p1 - p0;
		vec3 v1 = p2 - p1;
		vec3 c = cross(v0,v1);

		normals[i] = c.v[0];
		normals[i + 1] = c.v[1];
		normals[i + 2] = c.v[2];
		normals[i + 3] = c.v[0];
		normals[i + 4] = c.v[1];
		normals[i + 5] = c.v[2];
		normals[i + 6] = c.v[0];
		normals[i + 7] = c.v[1];
		normals[i + 8] = c.v[2];
	}

	return normals;
}

Mesh load_plane_mesh(){
	Mesh plane;
	plane.point_count = (NUM_ROWS-1)*(NUM_COLS-1)*6;
	printf("loading plane\n");

	float* plane_points = gen_plane_points(NUM_ROWS, NUM_COLS);
	float* plane_normals = gen_plane_normals(plane_points, plane.point_count);
	float plane_tex_coords[] = {};

	glGenBuffers (1, &plane.point_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, plane.point_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * plane.point_count, plane_points, GL_STATIC_DRAW);
	//glGenBuffers (1, &plane.tex_vbo);
	//glBindBuffer (GL_ARRAY_BUFFER, plane.tex_vbo);
	//glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * plane.point_count, plane_tex_coords, GL_STATIC_DRAW);
	glGenBuffers (1, &plane.normal_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, plane.normal_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * plane.point_count, plane_normals, GL_STATIC_DRAW);

	glGenVertexArrays (1, &plane.vao);
	glBindVertexArray (plane.vao);
	glEnableVertexAttribArray (POINT);
	//glEnableVertexAttribArray (TEX_COORD);
	glEnableVertexAttribArray (NORMAL);
	glBindBuffer (GL_ARRAY_BUFFER, plane.point_vbo);
	glVertexAttribPointer (POINT, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer (TEX_COORD, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, plane.normal_vbo);
	glVertexAttribPointer (NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	printf("plane loaded\n");
	return plane;
}

Mesh load_plane_mesh_given_points(float* plane_points){
	Mesh plane;
	plane.point_count = (NUM_ROWS-1)*(NUM_COLS-1)*6;
	//printf("loading plane\n");

	float* plane_normals = gen_plane_normals(plane_points, plane.point_count);
	float plane_tex_coords[] = {};
	
	glGenBuffers (1, &plane.point_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, plane.point_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * plane.point_count, plane_points, GL_STATIC_DRAW);
	//glGenBuffers (1, &plane.tex_vbo);
	//glBindBuffer (GL_ARRAY_BUFFER, plane.tex_vbo);
	//glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * plane.point_count, plane_tex_coords, GL_STATIC_DRAW);
	glGenBuffers (1, &plane.normal_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, plane.normal_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * plane.point_count, plane_normals, GL_STATIC_DRAW);

	glGenVertexArrays (1, &plane.vao);
	glBindVertexArray (plane.vao);
	glEnableVertexAttribArray (POINT);
	//glEnableVertexAttribArray (TEX_COORD);
	glEnableVertexAttribArray (NORMAL);
	glBindBuffer (GL_ARRAY_BUFFER, plane.point_vbo);
	glVertexAttribPointer (POINT, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer (TEX_COORD, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, plane.normal_vbo);
	glVertexAttribPointer (NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	delete (plane_normals);

	//printf("plane loaded\n");
	return plane;
}

float* displace_points(float* points, int num_points){
	for (int i = 0; i < 3*num_points; i+=3)
		points[i + 1] += sin(time(NULL)+(points[i]*points[i+2]))/100.0;
	return points;
}