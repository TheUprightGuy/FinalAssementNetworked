#include "camera.h"

CCamera::CCamera(bool isOrtho)
{
	m_CamPos = glm::vec3(0.0f, 0.0f, 1.0f);
	m_TargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_View = glm::lookAt(
		m_CamPos,
		m_TargetPos,
		glm::vec3(0.0f, 1.0f, 0.0f));

	GLfloat fWidth = (GLfloat)glutGet(GLUT_SCREEN_WIDTH);
	GLfloat fHeight = (GLfloat)glutGet(GLUT_SCREEN_HEIGHT);
	if (isOrtho)
	{
		
		glm::mat4 proj = glm::ortho(0.0f, fWidth, 0.0f, fHeight);
	}
	else
	{
		m_Proj = glm::perspectiveFov(1.309f, fWidth, fHeight, 0.1f, 10000.0f);
	}	
}

CCamera::~CCamera()
{
}

glm::mat4 CCamera::GetView()
{
	m_View = glm::lookAt(
		m_CamPos,
		m_TargetPos,
		glm::vec3(0.0f, 1.0f, 0.0f));

	return(m_View);
}
