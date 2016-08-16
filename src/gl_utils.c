#include "gl_utils.h"

Gfx g_gfx;

bool init_gl(){
	// PLAN:
	// make a game
	// GOAL #1: make OpenGL screen (COMPLETE)

    // Start OpenGL using helper libraries
    if (!glfwInit ()) { fprintf (stderr, "ERROR: could not start GLFW3\n"); return false;}
    g_gfx.window = glfwCreateWindow (INIT_WIN_WIDTH, INIT_WIN_HEIGHT, "Chunky Text Sim", NULL, NULL);
    if (!g_gfx.window) { fprintf (stderr, "ERROR: opening OS window\n"); return false;}
    glfwMakeContextCurrent (g_gfx.window);
    glewExperimental = GL_TRUE;

    // :/
    if (glewInit ()) { fprintf (stderr, "ERROR: could not start GLEW\n"); return false;}

    // version info
    g_gfx.renderer = glGetString (GL_RENDERER);
    g_gfx.version = glGetString (GL_VERSION);
    printf ("Renderer: %s\n", g_gfx.renderer);
    printf ("OpenGL version supported %s\n", g_gfx.version);

    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glClearColor (0.902, 0.408, 0.573, 1.0);
    glDisable (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace (GL_CCW);
}