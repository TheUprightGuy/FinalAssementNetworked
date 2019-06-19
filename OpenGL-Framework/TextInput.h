#pragma once
#include "button.h"
#include "TextLabel.h"
#include "object.h"

class CTextBox : public CButton
{
public:
	CTextBox(std::string _ButtonTexture, glm::vec2 _pos,std::string defaultText = "Enter text here", std::string _font = "Resources/Fonts/arial.ttf ")
		: CButton(_ButtonTexture, 0.01f)
	{
		float pixelX = (_pos.x + 1.22f) * 0.5 * glutGet(GLUT_WINDOW_WIDTH);
		float pixelY = (1.3f - _pos.y) * 0.5 * glutGet(GLUT_WINDOW_HEIGHT);

		m_restrictStart = 0;
		m_restictEnd = 180;
		m_textBoxText = new TextLabel(defaultText, _font, {pixelX, pixelY});
		m_objPosition = glm::vec3(_pos.x, _pos.y, 0.0f);
		boxInFocus = true;
		m_inputString = "";
	}

	void checkInFocus()
	{
		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD)
		{
			boxInFocus = CheckCollision();

		}
	}

	void Process()
	{
		checkInFocus();

		static float time = glutGet(GLUT_ELAPSED_TIME);
		static bool keyPressed = false;
		float timetime = glutGet(GLUT_ELAPSED_TIME) - time;

		//std::cout << timetime << std::endl;
		if (boxInFocus && CInput::GetInstance().GetCurrentState() == INPUT_FIRST_PRESS)
		{
			char lastKey = CInput::GetInstance().cLastKeyPressed;
			if (lastKey == 010 && m_inputString.length() >= 0)
			{
				m_inputString.pop_back();
			}
			else if (lastKey >= m_restrictStart && lastKey <= m_restictEnd)
			{
				m_inputString += lastKey;
			}

			time = glutGet(GLUT_ELAPSED_TIME);
			m_textBoxText->SetText(m_inputString);

			keyPressed = true;
		}
		if (CInput::GetInstance().GetCurrentState() == INPUT_RELEASE)
		{
			keyPressed = false;
		}
	}

	void Render()
	{
		CButton::Render();
		m_textBoxText->Render();
	}

	void RestrictRange(int _start, int _end)
	{
		m_restrictStart = _start;
		m_restictEnd = _end;
	}

	std::string GetText() { return(m_inputString); }

	~CTextBox();

private:
	TextLabel* m_textBoxText;

	int m_restrictStart;
	int m_restictEnd;

	std::string m_inputString;
	bool boxInFocus;
};