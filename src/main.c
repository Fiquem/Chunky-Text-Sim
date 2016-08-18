
#include "gl_utils.h"
#include "shader.h"
#include "mesh.h"
#include "maths_funcs.h"
#include "text.h"
#include "menu.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

vec3 cam_pos = vec3(-50.0,-10.0,50.0);
vec3 cam_rot = vec3(90.0,0.0,0.0);
Text test_text;
Menu test_menu;

int main()
{
    printf("\n----- Start Program -----\n\n");
    init_gl();
    glfwSetKeyCallback(g_gfx.window, key_callback);

    // GOAL #3: draw a cube (COMPLETE)
    // gonna put cube info in a header so cleaner
    // actually, gotta load shaders first, GOAL #3 PREREQ: LOAD SHADERS
    // what was that cool way with like a generic loader? let's do that
    Shader_Meta basic_shadermeta;
    create_program_from_files("basic.vert", "basic.frag", &basic_shadermeta);

    // GOAL #4: draw a plane with points with sorta randomised offsets
    // GOAL #5: make the plane kinda wobbly
    float* plane_points = gen_plane_points(NUM_ROWS, NUM_COLS);
    Mesh plane = load_plane_mesh_given_points(plane_points);

    // GOAL # I LOST COUNT. 18?: TEXT
    Font test_font = load_font("font/testfont.png", "font/testfont_highlight.png", "font/testfont.meta");
    test_text = set_text(test_font, "fada test: áéíóúÁÉÍÓÚ", INIT_WIN_WIDTH, INIT_WIN_HEIGHT, 100.0, 50.0);

    // I stopped doing goals and just kept going
    // goal a billion make a mnau
    const char* opts[] = {"HEY","L:OOK","IT'S","A","MENUI"};
    test_menu = create_menu(test_font, opts, 5, INIT_WIN_WIDTH, INIT_WIN_HEIGHT/2.0, 0.0, 150.0);

    // draw loop
    double prev = glfwGetTime();
    while (!glfwWindowShouldClose (g_gfx.window)) {
        double curr = glfwGetTime();
        double elapsed_time = curr - prev;
        prev = curr;

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport (0, 0, INIT_WIN_WIDTH, INIT_WIN_HEIGHT);

        // displace points, redo mesh
        plane_points = displace_points(plane_points, plane.point_count);
        plane = load_plane_mesh_given_points(plane_points);

        glUseProgram (basic_shadermeta.program);
        glBindVertexArray (plane.vao);
        glUniformMatrix4fv (basic_shadermeta.M_loc, 1, GL_FALSE, identity_mat4().m);
        glUniformMatrix4fv (basic_shadermeta.V_loc, 1, GL_FALSE, rotate_x_deg(rotate_y_deg(translate(identity_mat4(), cam_pos), cam_rot.v[1]), cam_rot.v[0]).m);
        glUniformMatrix4fv (basic_shadermeta.P_loc, 1, GL_FALSE, perspective(90, 800.0/600.0, 0.01, 1000.0).m);
        glDrawArrays (GL_TRIANGLES, 0, plane.point_count);

        //draw_text (test_text);
        draw_menu (test_menu);

        // GOAL #2: make this not crash (COMPLETE)
        // will uncomment this when I add in forward and right vecs
        if (glfwGetKey (g_gfx.window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose (g_gfx.window, GL_TRUE);
        if (glfwGetKey (g_gfx.window, GLFW_KEY_UP))
            if(cam_rot.v[0] < 90) cam_rot.v[0] += 50 * elapsed_time;
        if (glfwGetKey (g_gfx.window, GLFW_KEY_DOWN))
            if(cam_rot.v[0] > 70) cam_rot.v[0] -= 50 * elapsed_time;
        if (glfwGetKey (g_gfx.window, GLFW_KEY_LEFT))
            cam_rot.v[1] -= 50 * elapsed_time;
        if (glfwGetKey (g_gfx.window, GLFW_KEY_RIGHT))
            cam_rot.v[1] += 50 * elapsed_time;

        glfwPollEvents();
        // I swear to god if this is why
        // OH MY GOD THIS WAS WHY
        glfwSwapBuffers (g_gfx.window);
    }

    printf("\n------ End Program ------\n\n");
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        decrement_menu_selected(&test_menu);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        increment_menu_selected(&test_menu);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        select_menu_item(&test_menu);
}