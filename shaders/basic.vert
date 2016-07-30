#version 450

in vec3 vp;
in vec2 vt;
in vec3 vn;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main () {
	gl_Position = P * V * M * vec4 (vp, 1.0);
}
