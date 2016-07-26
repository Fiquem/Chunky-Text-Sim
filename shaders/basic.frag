#version 450

in vec3 p;
in vec2 t;
in vec3 n;

uniform mat4 V;

out vec4 frag_colour;

void main () {
	vec3 l_a = vec3 (0.2, 0.2, 0.2);
	vec3 k_a = vec3 (0.2, 0.2, 0.2);
	vec4 i_a = vec4 (l_a * k_a, 0.0);

	vec3 renorm = normalize (n);

	vec3 l_d = vec3 (0.3, 0.3, 0.3);
	vec3 k_d = vec3 (0.3, 0.3, 0.7);
	vec3 light_dir = (V * normalize (vec4 (1.0,1.0,1.0,0.0))).xyz;
	vec4 i_d = vec4 (l_d * k_d * max (0.0, dot (light_dir, renorm)), 0.0);

	vec3 l_s = vec3 (1.0, 1.0, 1.0);
	vec3 k_s = vec3 (1.0, 1.0, 1.0);
	vec3 r = normalize (reflect (-light_dir, renorm));
	vec3 v = normalize (-p);
	float spec_exp = 100;
	vec4 i_s = vec4 (l_s * k_s * max (0.0, pow (dot (v, r), spec_exp)), 0.0);

	frag_colour = vec4(i_a+i_d+i_s);
}