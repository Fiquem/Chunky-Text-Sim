// guess I need a camera class

#pragma once
#include "maths_funcs.h"

typedef struct Camera{
	vec3 pos, rot;
}Camera;

Camera init_camera();