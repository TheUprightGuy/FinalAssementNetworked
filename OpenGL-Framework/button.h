#pragma once
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <string.h>

#include "utils.h"
#include "object.h"
#include "TextLabel.h"
#include "input.h"

//okay okay, I know your gonna read this eventually callan, but the textlabel positioning function is retarded. Hence why it's not being used here
class CButton : public CObject
{
public:
	CButton(std::string _ButtonTexture = "Resources/Rayman.jpg", float _increase = 0.02f);
	~CButton() {}

	bool CheckCollision();
private:
	glm::vec3 defaultScale;
	bool default;
	float buttonIncrease;
};

#endif // !__BUTTON_H__
