#version 450

in vec2 t;

uniform sampler2D font_tex;
uniform vec3 colour;

out vec4 frag_colour;

void main(){
	frag_colour = vec4 (colour, 1.0) * texture(font_tex, vec2(t.x,1.0-t.y));
}