
#include <stdio.h>
#include <stdlib.h>
#include "gl_utils.h"
#include "cube.h"
#include "shader.h"

// window dimensions
int gl_width = 800;
int gl_height = 800;

int main()
{
    printf("\n----- Start Program -----\n\n");
    // PLAN:
    // make a game
    // GOAL #1: make OpenGL screen (COMPLETE)
    GLFWwindow* window = NULL;
    const GLubyte* renderer;
    const GLubyte* version;

    // Start OpenGL using helper libraries
    if (!glfwInit ()) {
    	fprintf (stderr, "ERROR: could not start GLFW3\n");
    	return 1;
    }

    window = glfwCreateWindow (gl_width, gl_height, "Hello Program", NULL, NULL);
    if (!window) {
    	fprintf (stderr, "ERROR: opening OS window\n");
    	return 1;
    }
    glfwMakeContextCurrent (window);

    // glewExperimental = GL_TRUE;
    glewInit ();

    /* get version info */
    renderer = glGetString (GL_RENDERER); /* get renderer string */
    version = glGetString (GL_VERSION); /* version as a string */
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);

    // GOAL #3: draw a cube
    // gonna put cube info in a header so cleaner
    // actually, gotta load shaders first, GOAL #3 PREREQ: LOAD SHADERS
    // what was that cool way with like a generic loader? let's do that
    Shader_Meta basic_shadermeta;
    create_program_from_files("basic.vert", "basic.frag", &basic_shadermeta);

    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glClearColor (.902, .408, .573, 1.0);
    //glDisable(GL_CULL_FACE);

    // draw loop
    while (!glfwWindowShouldClose (window)) {

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // just the default viewport, covering the whole render area
        glViewport (0, 0, gl_width, gl_height);
        glfwPollEvents();
        glfwSwapBuffers (window);

        // GOAL #2: make this not crash
        if (glfwGetKey (window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose (window, GL_TRUE);

    }

    printf("\n------ End Program ------\n\n");
}