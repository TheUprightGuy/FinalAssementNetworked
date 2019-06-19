#include "input.h"


CInput* CInput::s_pInput = nullptr;

CInput::CInput()
{
	m_CurrentState = INPUT_RELEASE;
	for (int i = 0; i < 255; i++)
	{
		KeyState[i] = INPUT_RELEASE;
	}
}

CInput::~CInput()
{
	m_CurrentState = INPUT_RELEASE;
}


