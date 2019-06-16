#include "button.h"
#include <iostream>


CButton::CButton(std::string _ButtonTexture)
	:CObject::CObject(DEFAULT, _ButtonTexture, MESH_2D_SPRITE, CCameraManager::GetInstance().GetOrthoCam())
{

}


bool CButton::CheckCollision()
{
	glm::vec3 objPos = GetPos();
	glm::vec3 objScale = GetScale();

	float fMouseCalcX = ((CInput::GetInstance().GetMousePos().x / glutGet(GLUT_WINDOW_WIDTH)) * 2) - 1.0f; //This was done under heavy sleep deprivation. I have already confessed my sins
	float fMouseCalcY = -(((CInput::GetInstance().GetMousePos().y / glutGet(GLUT_WINDOW_HEIGHT)) * 2) - 1.0f);

	float objTop = objPos.y - (objScale.y);
	float objBot = objPos.y + (objScale.y);

	glm::vec2 mouseCoords = glm::vec2(fMouseCalcX, fMouseCalcY);
	if ((mouseCoords.x > (objPos.x - objScale.x)) && (mouseCoords.x < (objPos.x + objScale.x)) &&
		(mouseCoords.y > (objTop)) && (mouseCoords.y < (objBot) ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
