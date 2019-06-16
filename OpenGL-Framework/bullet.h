#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "utils.h"
#include "object.h"

class CBullet : public CObject
{
public:
	CBullet(GLuint _program, glm::vec3 _placement, glm::vec3 _direction);
	~CBullet();

	
	void Process();
private:
	glm::vec3 m_direction;
};
#endif