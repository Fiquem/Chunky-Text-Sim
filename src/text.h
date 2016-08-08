#pragma once

#include "gl_utils.h"
#include "shader.h"

#define DEFAULT_FONT_SIZE 14

typedef struct Character{
	float xpos, ypos;
	float width, height;
	float buffer;
}Character;

typedef struct Font{
	// uhhhhhhhhhhhhhhhhhjjhhhhhhhhhhhhh
	GLuint texture;
	Shader_Meta shader;
	int size;
	Character* chars;
}Font;

Font load_font(const char* font_img, const char* font_meta);