#include "text.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Font load_font(const char* font_img, const char* font_meta){
	Font f;
	f.size = DEFAULT_FONT_SIZE;

	// load font tex
	int x, y, n;
    unsigned char* image = stbi_load(font_img, &x, &y, &n, 0);

	glGenTextures (1, &(f.texture));
	glActiveTexture (f.texture);
	glBindTexture (GL_TEXTURE_2D, f.texture);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// load font shader

	// will figure out size later. don't really care rn.

	// load character info from meta
	// NO META FOR THE MOMENT
	int rows = 16;
	int cols = 16;
	int char_size_px = 1024/16;
	f.chars = (Character*)malloc(sizeof(Character)*256);
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++){
			f.chars[(i*cols) + j].xpos = char_size_px * j;
			f.chars[(i*cols) + j].ypos = char_size_px * i;
			f.chars[(i*cols) + j].width = char_size_px;
			f.chars[(i*cols) + j].height = char_size_px;
			f.chars[(i*cols) + j].buffer = 0;
		}

	return f;
}