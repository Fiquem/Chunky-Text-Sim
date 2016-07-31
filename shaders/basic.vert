#version 450

in vec3 vp;
in vec2 vt;
in vec3 vn;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 p;
out vec2 t;
out vec3 n;

void main () {
	p = (V * M * vec4 (vp, 1.0)).xyz;
	t = vt;
	n = (V * M * vec4 (vn, 0.0)).xyz;
	gl_Position = P * V * M * vec4 (vp, 1.0);
}
