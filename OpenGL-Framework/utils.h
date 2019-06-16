#ifndef __UTILS_H__
#define __UTILS_H__

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


#include <vector>


enum MeshType
{
	MESH_2D_SPRITE,
	MESH_CUBE,
	MESH_SPHERE
};

enum InputState
{
	INPUT_FIRST_RELEASE,
	INPUT_RELEASE,
	INPUT_FIRST_PRESS,
	INPUT_HOLD
};

enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};

struct KeyPressInfo
{
	unsigned char cKey;
	int iX;
	int iY;
};


#endif // !__UTILS_H__
