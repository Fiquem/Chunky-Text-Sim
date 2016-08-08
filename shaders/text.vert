#version 450

in vec3 vp;
in vec2 vt;

uniform mat4 P;

out vec2 t;

void main(){
	t = vt;
	gl_Position = P * vec4(vp.xy, 0.0, 1.0);
}