
#include "gl_utils.h"
#include "shader.h"
#include "mesh.h"

int main()
{
    printf("\n----- Start Program -----\n\n");
    init_gl();

    // GOAL #3: draw a cube
    // gonna put cube info in a header so cleaner
    // actually, gotta load shaders first, GOAL #3 PREREQ: LOAD SHADERS
    // what was that cool way with like a generic loader? let's do that
    Shader_Meta basic_shadermeta;
    create_program_from_files("basic.vert", "basic.frag", &basic_shadermeta);

    Mesh cube = load_cube_mesh();

    // draw loop
    while (!glfwWindowShouldClose (g_gfx.window)) {

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // just the default viewport, covering the whole render area
        glViewport (0, 0, INIT_WIN_WIDTH, INIT_WIN_HEIGHT);
        glfwPollEvents();
        glfwSwapBuffers (g_gfx.window);

        glUseProgram (basic_shadermeta.program);
        glBindVertexArray (cube.vao);
        glDrawArrays (GL_TRIANGLES, 0, cube.point_count);

        // GOAL #2: make this not crash
        if (glfwGetKey (g_gfx.window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose (g_gfx.window, GL_TRUE);

    }

    printf("\n------ End Program ------\n\n");
}