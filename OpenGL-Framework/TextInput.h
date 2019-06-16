#pragma once
#include "button.h"
#include "TextLabel.h"
#include "object.h"

class CTextBox : public CButton
{
public:
	CTextBox(std::string _ButtonTexture, glm::vec2 _pos, std::string _font = "Resources/Fonts/arial.ttf ", std::string defaultText = "Enter text here")
		: CButton(_ButtonTexture)
	{
		m_textBoxText = new TextLabel(defaultText, _font, _pos);
		m_objPosition = glm::vec3(_pos.x, _pos.y, 0.0f);
		boxInFocus = false;
	}

	void checkInFocus()
	{

	}

	void Process()
	{
		checkInFocus();

		if (boxInFocus)
		{
		}

	}


	~CTextBox();

private:
	TextLabel* m_textBoxText;

	bool boxInFocus;
};