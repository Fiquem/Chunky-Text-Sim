// Entirely stolen from Anton
// https://github.com/capnramses/storm_my_castle/blob/master/src/shader.c

#include "shader.h"

#define SHADER_PATH "shaders/"

bool compile_shader_from_file(const char* shader_file_name, GLenum shader_type, GLuint* shader)
{
	// I should probably also get into the habit of error checking...
	// Make these bools or ints or smth and print error messages everywhere
	// LATER

	printf("Loading shader file - %s\n", shader_file_name);

	char shader_string[10000];
	shader_string[0] = '\0';
	char shader_path[10000];
	sprintf(shader_path, "%s%s", SHADER_PATH, shader_file_name);
	FILE* shader_file = fopen(shader_path, "r");
	if(!shader_file) printf("ERORR loading shader");
	char line[1024];
	while(fgets(line, 1024, shader_file))
		strcat(shader_string, line);
	fclose(shader_file);

	const char* const_shader_string = shader_string;
	*shader = glCreateShader(shader_type);
	glShaderSource(*shader, 1, &const_shader_string, NULL);
	glCompileShader(*shader);
	int params = -1;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &params);
	if(GL_TRUE != params) {
		fprintf(stderr,"ERROR: shader did not compile\n");
		int max_length = 2048;
		int actual_length = 0;
		char slog[2048];
		glGetShaderInfoLog(*shader, max_length, &actual_length, slog);
		fprintf(stderr,"shader info log for GL index %u:\n%s\n", *shader, slog);
		return false;
	}

	return true;
}

bool create_program_from_files(const char* vertex_shader, const char* fragment_shader, Shader_Meta* Shader_Meta)
{
	printf("Creating shader program - %s %s\n", vertex_shader, fragment_shader);
	if(!compile_shader_from_file(vertex_shader, GL_VERTEX_SHADER, &Shader_Meta->vertex_shader)) // I guess -> takes precedence over & THE MORE YOU KNOW
		fprintf(stderr,"ERROR: compiling vertex shader\n");
	if(!compile_shader_from_file(fragment_shader, GL_FRAGMENT_SHADER, &Shader_Meta->fragment_shader))
		fprintf(stderr,"ERROR: compiling fragment shader\n");
	// can't compile because doesn't recognise those SHADER enums but if I include stuff compiler goes crazy I guess becayse I already include in main.c?
	// so gonna copy more of Anton's stuff tomorrow - gl_utils!
	// FIXED

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
		// lol okay that confused me for too long
		// so those lines just mean I don't need to put the (location = 0) in the shader
		// I am literally so dumb I should have noticed that from the funciton name
		// just looked at http://gamedev.stackexchange.com/questions/29672/in-out-keywords-in-glsl to confirm suspicions about attrib/varying
		// wait so will this still work if I call them 'in' instead of 'attribute' ???
		glLinkProgram(Shader_Meta->program);
		int params = -1;
		glGetProgramiv(Shader_Meta->program, GL_LINK_STATUS, &params);
		if(GL_TRUE != params) {
			fprintf(stderr,"ERORR shader program didn't compile\n");
			int max_length = 2048;
			int actual_length = 0;
			char plog[2048];
			// I thought slog and plog were cute names but I get it now
			// shader log program log
			glGetProgramInfoLog(Shader_Meta->program, max_length, &actual_length, plog);
			printf ("program info log for GL index %u:\n%s", Shader_Meta->program, plog);
			return false;
		}
		Shader_Meta->M_loc = glGetUniformLocation(Shader_Meta->program, "M");
		Shader_Meta->V_loc = glGetUniformLocation(Shader_Meta->program, "V");
		Shader_Meta->P_loc = glGetUniformLocation(Shader_Meta->program, "P");
	}
	printf("Created shader program\n");
	return true;
}