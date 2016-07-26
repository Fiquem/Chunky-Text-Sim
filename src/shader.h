// Entirely stolen from Anton
// https://github.com/capnramses/storm_my_castle/blob/master/src/shader.h

#pragma once
#include "utils.h"

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

bool create_program_from_files(const char* vertex_shader, const char* fragment_shader, Shader_Meta* Shader_Meta);
bool compile_shader_from_file(const char* shader_file_name, GLenum shader_type, GLuint* shader);
// Anton passes in fn as name for shader_file and uses it as suffix for vertex_shader and fragment_shader. Why? What does it stand for?
// It stands for file name...