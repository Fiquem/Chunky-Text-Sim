#include "camera.h"

Camera init_camera(){
	Camera c;
	c.pos = vec3(-50.0,-10.0,50.0);
	c.rot = vec3(90.0,0.0,0.0);
	return c;
}