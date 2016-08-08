#pragma once

#include "gl_utils.h"

typedef struct Character{
	float xpos, ypos;
	float width, height;
	float buffer;
}Character;

typedef struct Font{
	// uhhhhhhhhhhhhhhhhhjjhhhhhhhhhhhhh
	GLuint texture;
	GLuint shader;
	int size;
}Font;

Font load_font(const char* font_img, const char* font_meta);