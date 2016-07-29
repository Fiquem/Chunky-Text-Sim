// need to make a stupid utils file because I need to add the same stupid GL header in multiple places and the stupid compiler stupid freaks out about that

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// yeah okay whatever I'll just copy straight
// it's just it's neat and makes sense
#define INIT_WIN_WIDTH 800
#define INIT_WIN_HEIGHT 600

typedef struct Gfx{
	GLFWwindow* window;
    const GLubyte* renderer;
    const GLubyte* version;
    int win_width, win_height;
}Gfx;

bool init_gl();

// I didn't know what this was but I know what this is now I need it
extern Gfx g_gfx;