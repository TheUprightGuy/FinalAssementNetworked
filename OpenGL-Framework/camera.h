#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "utils.h"

#include <string>

class CCamera
{
public:
	CCamera(bool isOrtho);
	~CCamera();

	glm::vec3 GetCamPos() { return(m_CamPos); }
	void SetCamPos(glm::vec3 _NewPos)
	{
		m_CamPos = _NewPos;
	}

	glm::mat4 GetView();
	glm::mat4 GetProj() { return(m_Proj); }

	void CamTranslate(glm::vec3 _newPos) { m_CamPos = glm::vec3(_newPos.x, _newPos.y, _newPos.z); }
	void CamTarget(glm::vec3 _newPos) { m_TargetPos = glm::vec3(_newPos.x, _newPos.y, _newPos.z); }
private:
	glm::vec3 m_CamPos;
	glm::vec3 m_TargetPos;

	glm::mat4 m_View;
	glm::mat4 m_Proj;
};
#endif // !__CAMERA_H__
