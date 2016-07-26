// Entirely stolen from Anton
// https://github.com/capnramses/storm_my_castle/blob/master/src/shader.c

#include "shader.h"
#include "utils.h"

#define SHADER_PATH "shaders/"

bool compile_shader_from_file(const char* shader_file_name, GLenum shader_type, GLuint* shader)
{
	// I should probably also get into the habit of error checking...
	// Make these bools or ints or smth and print error messages everywhere
	// LATER

	printf("Loading shader file - %s\n", shader_file_name);

	char shader_string[10000]; 
	char shader_path[10000];
	sprintf(shader_path, "%s%s", SHADER_PATH, shader_file_name);
	FILE* shader_file = fopen(shader_path, "r");
	if(!shader_file) printf("ERORR loading shader");
	char line[1024];
	while(fgets(line, 1024, shader_file))
		strcat(shader_string, line);
	fclose(shader_file);

	const char* const_shader_string;
	*shader = glCreateShader(shader_type);
	glShaderSource(*shader, 1, &const_shader_string, NULL);
	glCompileShader(*shader);
	int params = -1;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &params);
	if(GL_TRUE != params) {
		printf("ERORR shader didn't compile\n");
		// I'll prob have to make this more detailed at some point but w/e
		// I'm copying by the letter enough, ignoring bits is like the least I can do to make it my own~
		return false;
	}

	return true;
}

bool create_program_from_files(const char* vertex_shader, const char* fragment_shader, Shader_Meta* Shader_Meta)
{
	printf("Creating shader program - %s %s\n", vertex_shader, fragment_shader);
	compile_shader_from_file(vertex_shader, GL_VERTEX_SHADER, &Shader_Meta->vertex_shader); // I guess -> takes precedence over & THE MORE YOU KNOW
	compile_shader_from_file(fragment_shader, GL_FRAGMENT_SHADER, &Shader_Meta->fragment_shader);
	// can't compile because doesn't recognise those SHADER enums but if I include stuff compiler goes crazy I guess becayse I already include in main.c?
	// so gonna copy more of Anton's stuff tomorrow - gl_utils!

	// the little {} around blocks of code just define a scope, right? or what?
	// why he doin' that here?
	{
		Shader_Meta->program = glCreateProgram();
		glAttachShader(Shader_Meta->program, Shader_Meta->vertex_shader);
		glAttachShader(Shader_Meta->program, Shader_Meta->fragment_shader);
		glBindAttribLocation(Shader_Meta->program, POINT, "vp");
		glBindAttribLocation(Shader_Meta->program, TEX_COORD, "vt");
		glBindAttribLocation(Shader_Meta->program, NORMAL, "vn");
		// WHY THE FUCK IS HE USING OLD SHADER CODE WHAT
	}

	return true;
}