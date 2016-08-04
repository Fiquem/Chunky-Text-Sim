#version 450

in vec3 p;
in vec2 t;
in vec3 n;

uniform mat4 V;

out vec4 frag_colour;

float b = 0.005;
float c = 0.01;

vec3 applyFog( in vec3  rgb,      // original color of the pixel
               in float distance, // camera to point distance
               in vec3  rayOri,   // camera position
               in vec3  rayDir )  // camera to point vector
{
    float fogAmount = clamp (c * exp(-rayOri.z*b) * (1.0-exp( -distance*rayDir.z*b ))/rayDir.z, 0.0, 1.0) * 0.5;
    //vec3  fogColor  = vec3(0.5,0.6,0.7);
    vec3 fogColor = vec3(0.047, 0.067, 0.224);
    return mix( rgb, fogColor, fogAmount );
}

void main () {
	// ambient colour
	vec3 l_a = vec3 (0.8, 0.8, 0.8);
	//vec3 k_a = vec3 (0.902, 0.408, 0.573);
	vec3 k_a = vec3 (0.878, 0.89, 1.0);
	vec4 i_a = vec4 (l_a * k_a, 1.0);

	vec3 renorm = normalize (n);

	// diffuse
	vec3 l_d = vec3 (1.0, 1.0, 1.0);
	//vec3 k_d = vec3 (0.902, 0.408, 0.573);
	vec3 k_d = vec3 (0.878, 0.89, 1.0);
	vec3 light_dir = (V * normalize (vec4 (10.0,10.0,10.0,0.0))).xyz;
	vec4 i_d = vec4 (l_d * k_d * max (0.0, dot (light_dir, renorm)), 1.0);

	// specular (do I want this? don't really like it)
	vec3 l_s = vec3 (1.0, 1.0, 1.0);
	vec3 k_s = vec3 (0.047, 0.067, 0.224);
	vec3 r = normalize (reflect (-light_dir, renorm));
	vec3 v = normalize (-p);
	float spec_exp = 100;
	vec4 i_s = vec4 (l_s * k_s * max (0.0, pow (dot (v, r), spec_exp)), 1.0);

	//vec4 texel = texture (basic_texture, t);
	vec3 eye = vec3(V[0][3],V[1][3],V[2][3]);
	float dist = distance(vec3(V[0][3], V[1][3], V[2][3]), p);
	frag_colour = vec4 (applyFog (vec4 (i_a+i_d+i_s).xyz, dist, eye, p-eye), 0.0);

	//frag_colour = vec4(i_a+i_d+i_s);
}