// Entirely stolen from Anton
// https://github.com/capnramses/storm_my_castle/blob/master/src/shader.c

#include "shader.h"
#include "stdio.h"
#include "gl_utils.h"

#define SHADER_PATH "shaders/"

bool compile_shader_from_file(const char* shader_file, GLenum shader_type, GLuint* shader)
{
	// I should probably also get into the habit of error checking...
	// Make these bools or ints or smth and print error messages everywhere
	// LATER
	return 1;
}

bool create_program_from_files(const char* vertex_shader, const char* fragment_shader, Shader_Meta* Shader_Meta)
{
	printf("Creating shader program - %s %s\n", vertex_shader, fragment_shader);
	compile_shader_from_file(vertex_shader, GL_VERTEX_SHADER, &Shader_Meta->vertex_shader); // I guess -> takes precedence over & THE MORE YOU KNOW
	compile_shader_from_file(fragment_shader, GL_FRAGMENT_SHADER, &Shader_Meta->fragment_shader);
	// can't compile because doesn't recognise those SHADER enums but if I include stuff compiler goes crazy I guess becayse I already include in main.c?
	// so gonna copy more of Anton's stuff tomorrow - gl_utils!

	return 1;
}