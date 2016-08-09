#pragma once

#include "gl_utils.h"
#include "shader.h"

#define DEFAULT_FONT_SIZE 14

typedef struct Character{
	int xpos, ypos;
	int width, height;
	int buffer;
}Character;

typedef struct Font{
	// uhhhhhhhhhhhhhhhhhjjhhhhhhhhhhhhh
	GLuint texture;
	Shader_Meta shader;
	int size;
	Character* chars;
}Font;

Font load_font(const char* font_img, const char* font_meta);
void draw_text(const char* text, Font f, float x, float y);