// Entirely stolen from Anton
// https://github.com/capnramses/storm_my_castle/blob/master/src/shader.h

#include "GL/gl.h"

#pragma once

typedef enum Shader_Attribs{
	POINT = 0,
	TEX_COORD = 1,
	NORMAL = 2
}Shader_Attribs;

typedef struct Shader_Meta{
	GLuint program;
	GLuint vertex_shader, fragment_shader;
	GLuint M_loc, V_loc, P_loc;
}Shader_Meta;

void create_program_from_files(const char* vertex_shader, const char* fragment_shader, Shader_Meta* shadermeta);
