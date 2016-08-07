

typedef struct Text{
	// uhhhhhhhhhhhhhhhhh
}Text;

// do I need font to be a different thing?
typedef struct Font{
	// uhhhhhhhhhhhhhhhhhjjhhhhhhhhhhhhh
	GLuint texture;
	GLuint shader;
}Font;

Font load_font(const char* font_img, const char* font_meta);