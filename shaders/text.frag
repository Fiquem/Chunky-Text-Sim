#version 450

in vec2 t;

uniform sampler2D font_tex;
uniform vec3 colour;

out vec4 frag_colour;

void main(){
	vec4 character_mask = vec4 (1.0, 1.0, 1.0, 1.0-texture(font_tex, vec2(t.x,1.0-t.y)).r); // what are the swizzlers with an r? tusr? idk
	frag_colour = vec4 (colour, 1.0) * character_mask;
}