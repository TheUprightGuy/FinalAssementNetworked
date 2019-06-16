#include "input.h"


CInput* CInput::s_pInput = nullptr;

CInput::CInput()
{

	m_CurrentState = INPUT_RELEASE;

}

CInput::~CInput()
{
	m_CurrentState = INPUT_RELEASE;
}


