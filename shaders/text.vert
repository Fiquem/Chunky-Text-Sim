#version 450

in vec2 vp;
in vec2 vt;

uniform mat4 P;

out vec2 t;

void main(){
	t = vt;
	gl_Position = vec4(vp, 0.0, 1.0);
}