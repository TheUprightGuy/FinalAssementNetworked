#ifndef __CUBEMAP_H__
#define __CUBEMAP_H__

#include "glew.h"
#include "freeglut.h"
#include "ShaderLoader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "fmod.hpp"
#include "TextLabel.h"
#include "CameraManager.h"

#include <vector>

//#include "Camera.h"

class CCubeMap
{
public:
	CCubeMap();
	~CCubeMap();

	void Render();

private:
	GLfloat verticesCM;
	GLuint indicesCM;

	ShaderLoader ShaderLoaderCM;
	GLuint Program;
	GLuint CMVBO;
	GLuint CMVAO;
	GLuint CMEBO;
	GLuint CMtextureID;

	//CCamera* CameraInstance;

};

#endif //__CUBEMAP_H__