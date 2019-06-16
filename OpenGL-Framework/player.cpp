#include "player.h"


CPlayer::CPlayer()
	: CObject::CObject(PHONGLIGHTING, "Resources/Rayman.jpg", MESH_CUBE)
{

}
void CPlayer::init()
{

}

void CPlayer::process()
{

	glm::vec3 PlayerPos = GetPos();

	static float fAccel = 0.4f;

	static bool bTap = false;
	static int iCounter = 0;

	static bool bShoot = false;

	float rads = glm::radians(GetRot());
	if (CInput::GetInstance().GetCurrentState() == INPUT_RELEASE)
	{
		fAccel = 0.4f;
		bTap = false;
		
	}

	//Moves the player according to its current rotation
	/*****************************************************************/
	if (CInput::GetInstance().GetKeyState('w') == INPUT_HOLD)
	{
		glm::vec3 forwardVec = glm::vec3(glm::cos(-rads), 0.0, glm::sin(-rads)); //I'm gonna be honest, I don't understand why this works, but it does, so I'm happy with it
		glm::vec3 newvec = PlayerPos + forwardVec;
		if (newvec.x < 199.0f && newvec.x > -199.0f && newvec.z < 199.0f && newvec.z > -199.0f)
		{
			PlayerPos = PlayerPos + forwardVec;
		}
		
	}

	if (CInput::GetInstance().GetKeyState('s') == INPUT_HOLD)
	{
		glm::vec3 backVec = glm::vec3(glm::cos(-rads), 0.0, glm::sin(-rads));
		glm::vec3 newvec = PlayerPos - backVec;
		if (newvec.x < 199.0f && newvec.x > -199.0f && newvec.z < 199.0f && newvec.z > -199.0f)
		{
			PlayerPos = newvec;
		}
		
	}

	if (CInput::GetInstance().GetKeyState('a') == INPUT_HOLD)
	{
		glm::vec3 leftVec = glm::vec3(glm::cos(-glm::radians(GetRot() - 90)), 0.0, glm::sin(-glm::radians(GetRot() - 90)));
		glm::vec3 newvec = PlayerPos - leftVec;
		if (newvec.x < 199.0f && newvec.x > -199.0f && newvec.z < 199.0f && newvec.z > -199.0f)
		{
			PlayerPos = newvec;
		}
		
	}

	if (CInput::GetInstance().GetKeyState('d') == INPUT_HOLD)
	{
		glm::vec3 rightVec = glm::vec3(glm::cos(-glm::radians(GetRot() + 90)), 0.0, glm::sin(-glm::radians(GetRot() + 90)));
		glm::vec3 newvec = PlayerPos - rightVec;
		if (newvec.x < 199.0f && newvec.x > -199.0f && newvec.z < 199.0f && newvec.z > -199.0f)
		{
			PlayerPos = newvec;
		}
	}
	if (fAccel < 0.4f)
	{
		fAccel += 0.2f;
	}


	//Locks the mouse To the centre and hides it
	/*****************************************************************/
	//Deadzone size is 2
	if (CInput::GetInstance().GetMousePos().x < glutGet(GLUT_WINDOW_WIDTH) / 2 + 2)
	{
		Rotation(GetRot() + 5, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (CInput::GetInstance().GetMousePos().x > glutGet(GLUT_WINDOW_WIDTH) / 2 - 2)
	{
		Rotation(GetRot() - 5, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	//Debug
	static bool bLockMouse = true;
	if (CInput::GetInstance().GetKeyState('`') == INPUT_HOLD && bTap == false)
	{

		bLockMouse = !bLockMouse;
		bTap = true;
	}
	if (bLockMouse)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
	/*****************************************************************/

	//Move player
	/*****************************************************************/
	Translate(PlayerPos);

	if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && bShoot == false)
	{
		bShoot = true;
		Shoot();
	}
	else if (CInput::GetInstance().GetMouseState(0) == INPUT_RELEASE)
	{
		bShoot = false;
	}

	for (int i = 0; i < m_pBullets.size(); i++)
	{
		m_pBullets[i]->Process();
	}

	for (int i = 0; i < m_pBullets.size(); i++)
	{
		if (distance(m_pBullets[i]->GetPos(), GetPos()) > 200)
		{
			m_pBullets.erase(m_pBullets.begin() + i);
		}
	}
}

void CPlayer::Render()
{
	for (int i = 0; i < m_pBullets.size(); i++)
	{
		m_pBullets[i]->Render();
	}
	CObject::Render();
}

void CPlayer::Shoot()
{
	glm::vec3 forwardVec = glm::vec3(glm::cos(-glm::radians(CObject::GetRot())), 0.0, glm::sin(-glm::radians(CObject::GetRot())));
	m_pBullets.push_back(new CBullet(m_program, CObject::GetPos(), forwardVec));
}
