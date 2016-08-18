#include "menu.h"

Menu create_menu(Font f, const char** opts, int length, float w, float h, float x, float y){
	Menu m;
	Text t;
	m.options = (MenuOption*)malloc(sizeof(MenuOption)*length);
	m.width = w;
	m.height = h;
	m.xpos = x;
	m.ypos = y;
	m.length = length;
	m.selected = 0;

	for (int i = 0; i < length; i++){
		t = set_text(f, opts[i], w, h, 0.0, 0.0);
		set_text_pos(&t, CENTRE);
		set_text_pos(&t, t.xpos+x, ((length-1-i)*(m.height-f.size)/(length-1))+y);
		m.options[i].text = t;
	}

	m.options[0].text.selected = true;

	return m;
}

void draw_menu(Menu m){
	for (int i = 0; i < m.length; i++)
		draw_text(m.options[i].text);
}

void increment_menu_selected(Menu* m){
	if (m->selected < m->length-1){
		m->options[m->selected].text.selected = false;
		m->selected++;
		m->options[m->selected].text.selected = true;
	}
}

void decrement_menu_selected(Menu* m){
	if (m->selected > 0) {
		m->options[m->selected].text.selected = false;
		m->selected--;
		m->options[m->selected].text.selected = true;
	}
}

void select_menu_item(Menu* m){
	m->options[m->selected].function(m->selected);
}