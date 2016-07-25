// Entirely stolen from Anton
// https://github.com/capnramses/storm_my_castle/blob/master/src/shader.c

#include "shader.h"
#include "stdio.h"

#define SHADER_PATH "shaders/"

void create_program_from_files(const char* vertex_shader, const char* fragment_shader, Shader_Meta* shadermeta)
{
	printf("Creating shader program - %s %s\n", vertex_shader, fragment_shader);
}