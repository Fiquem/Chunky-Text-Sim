
#include "gl_utils.h"
#include "shader.h"
#include "mesh.h"
#include "maths_funcs.h"
#include "text.h"
#include "menu.h"
#include "camera.h"
#include "game_utils.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Text test_text;
Menu test_menu;

void test(){
    printf("test\n");
}

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
    MenuFunction funcs[] = {test, test, test, test, test};
    test_menu = create_menu(test_font, opts, funcs, 5, INIT_WIN_WIDTH, INIT_WIN_HEIGHT/2.0, 0.0, 150.0);

    Camera cam = init_camera();

    GameState game_state = MENU;

    // draw loop
    double prev = glfwGetTime();
    while (!glfwWindowShouldClose (g_gfx.window)) {
        double curr = glfwGetTime();
        double elapsed_time = curr - prev;
        prev = curr;

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport (0, 0, INIT_WIN_WIDTH, INIT_WIN_HEIGHT);

        switch(game_state){
            case MENU:
                draw_plane (basic_shadermeta, &plane, &plane_points, cam);
                draw_menu (test_menu);

                // GOAL #2: make this not crash (COMPLETE)
                // will uncomment this when I add in forward and right vecs
                if (glfwGetKey (g_gfx.window, GLFW_KEY_ESCAPE))
                    glfwSetWindowShouldClose (g_gfx.window, GL_TRUE);
                if (glfwGetKey (g_gfx.window, GLFW_KEY_W))
                    if(cam.rot.v[0] < 90) cam.rot.v[0] += 50 * elapsed_time;
                if (glfwGetKey (g_gfx.window, GLFW_KEY_S))
                    if(cam.rot.v[0] > 70) cam.rot.v[0] -= 50 * elapsed_time;
                if (glfwGetKey (g_gfx.window, GLFW_KEY_A))
                    cam.rot.v[1] -= 50 * elapsed_time;
                if (glfwGetKey (g_gfx.window, GLFW_KEY_D))
                    cam.rot.v[1] += 50 * elapsed_time;

                break;

            case TEST:
                printf("I deid it\n");
                break;

            default:
                printf("Unhandled game state.\n");
                exit(1);
        }

        glfwPollEvents();
        // I swear to god if this is why
        // OH MY GOD THIS WAS WHY
        glfwSwapBuffers (g_gfx.window);
    }

    printf("\n------ End Program ------\n\n");
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        decrement_menu_selected(&test_menu);
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        increment_menu_selected(&test_menu);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        select_menu_item(&test_menu);
}