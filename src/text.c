#include "text.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "maths_funcs.h"

GLuint text_vao, text_vbo;

Font load_font (const char* font_img, const char* font_meta){
	Font f;
	f.size = DEFAULT_FONT_SIZE;

	// load font tex
	int x, y, n;
    unsigned char* image = stbi_load(font_img, &x, &y, &n, 0);

	glGenTextures (1, &f.texture);
	glActiveTexture (f.texture);
	glBindTexture (GL_TEXTURE_2D, f.texture);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// load font shader
	create_program_from_files ("text.vert", "text.frag", &f.shader);
	glUseProgram (f.shader.program);
	glUniformMatrix4fv (f.shader.P_loc, 1, GL_FALSE, ortho(0.0, 800.0, 0.0, 600.0, 0.05, 100.0).m);
	glUniform3f (f.shader.colour_loc, 0.0,0.0,0.0);

	// jus copied I@ll do better later so tired now
	glGenVertexArrays(1, &text_vao);
	glGenBuffers(1, &text_vbo);
	glBindVertexArray(text_vao);
	glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);     

	// will figure out size later. don't really care rn.

	// load character info from meta
	// NO META FOR THE MOMENT
	int rows = 16;
	int cols = 16;
	int char_size_px = 1024/16;
	f.chars = (Character*)malloc(sizeof(Character)*256);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++){
			f.chars[(i*cols) + j].xpos = char_size_px * j;
			f.chars[(i*cols) + j].ypos = char_size_px * i;
			f.chars[(i*cols) + j].width = char_size_px;
			f.chars[(i*cols) + j].height = char_size_px;
			f.chars[(i*cols) + j].buffer = 0;
		}

	return f;
}

void draw_text (const char* text, Font f, float x, float y){
	glUseProgram (f.shader.program);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text_vao);

	int i = 0;
	while(text[i] != '\0'){

        GLfloat xpos = x + (((int)text[i] - (int)' ')%16)*(1024/16); // tex is 16*16, first char is space, so subtract ' '
        GLfloat ypos = y - (((int)text[i] - (int)' ')/16)*(1024/16);

        GLfloat w = (1024/16);
        GLfloat h = (1024/16);
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }           
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, f.texture);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

		i++;
	}
}