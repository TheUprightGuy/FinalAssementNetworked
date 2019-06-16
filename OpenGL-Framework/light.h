#pragma once
#ifndef __LIGHT_H__

#include "utils.h"
#include "CameraManager.h"

class CLight
{
public:
	CLight(GLuint& _program);
	~CLight();

	void Render();

private:
	/*
	uniform vec3 lightColor; // = glm::vec3(1.0f, 1.0f, 1.0f);
	  uniform vec3 lightPos; // = glm::vec3(5.0f, 5.0f, 0.5f);

	uniform float lightSpecStr; // = 1.0f;
	uniform vec3 camPos; // = glm::vec3(1.0f, 1.0f, 3.0f);
	uniform float shininess; // = 32.0f;
	*/

	GLuint m_program;
	glm::vec3 m_lightColor;
	glm::vec3 m_lightPos;
	glm::vec3 m_ambientColor;

	float m_lightSpecStr;
	float m_shininess;
	float m_ambientStrength;
};
#endif // !__LIGHT_H__
