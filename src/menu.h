#pragma once

#include "text.h"

typedef struct Menu{
	Text* options;
	int length;
	float width, height, xpos, ypos;
	int selected;
}Menu;

Menu create_menu(Font f, const char** opts, int l, float w, float h, float x, float y);
void draw_menu(Menu m);
void increment_menu_selected(Menu* m);
void decrement_menu_selected(Menu* m);