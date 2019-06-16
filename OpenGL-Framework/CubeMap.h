#pragma once
#ifndef __CUBEMAP_H__
#define __CUBEMAP_H__

#include "CameraManager.h"
#include "utils.h"
#include <string.h>

class CCubeMap
{
public:
	CCubeMap(std::vector<std::string> _textures);
	~CCubeMap();

	void init();
	void render();
private:
	//GLfloat m_cubemapvertices;
	//GLuint m_cubemapindices;

	GLuint m_ebo;
	GLuint m_vao;
	GLuint m_vbo;

	GLuint m_texture;

	GLuint m_program;
};

#endif