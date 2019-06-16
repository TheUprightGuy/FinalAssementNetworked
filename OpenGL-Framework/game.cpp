#include "game.h"
#include <stdlib.h>
#include <time.h>

CGame* CGame::s_pGame = nullptr;

CGame::CGame()
{

}

CGame& CGame::GetInstance()
{
	if (s_pGame == nullptr)
	{
		s_pGame = new CGame();
	}

	return(*s_pGame);
}

void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = nullptr;
}

void CGame::init()
{
	//m_program = _program;

	/*
	std::vector<std::string> SkyBox
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"back.jpg",
		"front.jpg"
	};
	myCubeMap = new CCubeMap(SkyBox);
	*/
	srand(time(nullptr));

	myCubeMap = new CCubeMap();

	//Places the environment
	/*****************************************************************/
	CObject* gameFloor = new CObject(PHONGLIGHTING, "Resources/ground.jpg", MESH_CUBE);
	gameFloor->Scale(glm::vec3(200.0f, 0.5f, 200.0f));
	m_vpEnviroment.push_back(gameFloor);

	CObject* gameWall = new CObject(PHONGLIGHTING, "Resources/wall.jpg", MESH_CUBE);
	gameWall->Scale(glm::vec3(200.0f, 1.0f, 1.0f));
	gameWall->Translate(glm::vec3(0.0f, 1.0f, 199.0f));
	m_vpEnviroment.push_back(gameWall);

	gameWall = new CObject(PHONGLIGHTING, "Resources/wall.jpg", MESH_CUBE);
	gameWall->Scale(glm::vec3(200.0f, 1.0f, 1.0f));
	gameWall->Translate(glm::vec3(0.0f, 1.0f, -199.0f));
	m_vpEnviroment.push_back(gameWall);

	gameWall = new CObject(PHONGLIGHTING, "Resources/wall.jpg", MESH_CUBE);
	gameWall->Scale(glm::vec3(1.0f, 1.0f, 200.0f));
	gameWall->Translate(glm::vec3(199.0f, 1.0f, 0.0f));
	m_vpEnviroment.push_back(gameWall);

	gameWall = new CObject(PHONGLIGHTING, "Resources/wall.jpg", MESH_CUBE);
	gameWall->Scale(glm::vec3(1.0f, 1.0f, 200.0f));
	gameWall->Translate(glm::vec3(-199.0f, 1.0f, 0.0f));
	m_vpEnviroment.push_back(gameWall);

	//CCameraManager::GetInstance().GetCam()->CamTranslate(glm::vec3(0.0f, 100.0f, 40.0f));
	//CCameraManager::GetInstance().GetCam()->CamTarget(glm::vec3(0.0f, 0.0f, 5.0f));

	//Initialises the player
	/*****************************************************************/
	m_Player = new CPlayer();
	m_Player->Scale(glm::vec3(1.0f, 2.0f, 1.0f));
	m_Player->Translate(glm::vec3(0.0f, 2.5f, 0.0f));

	m_pHealthBar = new CObject(DEFAULT, "Resources/health.png", MESH_2D_SPRITE, CCameraManager::GetInstance().GetOrthoCam());
	m_pHealthBar->Scale(glm::vec3(0.2f, 0.2f, 0.0f));
	m_pHealthBar->Translate(glm::vec3(-0.85f, -0.75f, 0.0f));
	m_iHealth = 3;

	m_pScoreBack = new CObject(DEFAULT, "Resources/score.png", MESH_2D_SPRITE, CCameraManager::GetInstance().GetOrthoCam());
	m_pScoreBack->Scale(glm::vec3(0.5f, 0.2f, 0.0f));
	m_pScoreBack->Translate(glm::vec3(1.0f, -0.75f, 0.0f));

	m_pScore = new TextLabel("test", "Resources/Fonts/AGENCYR.TTF", glm::vec2(1690.0f, 115.0f));
	m_pScore->SetScale(1.5f);
	//I'm gonna make the cursor... DISSAPEAR
	/*****************************************************************/

}

void CGame::Restart()
{
	m_pSpawnedAI.clear();
	m_Player->Scale(glm::vec3(1.0f, 2.0f, 1.0f));
	m_Player->Translate(glm::vec3(0.0f, 2.5f, 0.0f));

	m_iHealth = 3;
	m_iScore = 0;
}


bool CGame::Process()
{
	if (m_gamemode)
	{
		if (m_pSpawnedAI.empty())
		{
			CEnemy* tempAI = new CEnemy();
			tempAI->Translate(glm::vec3(rand() % 200 - 200, 2.5f, rand() % 200 - 200));
			tempAI->Scale(glm::vec3(1.0f, 2.0f, 1.0f));
			m_pSpawnedAI.push_back(tempAI);
			tempAI = nullptr;
		}
		else
		{
			for (auto & i : m_pSpawnedAI)
			{
				i->Seek(m_Player->GetPos(), 0.5, 0.08);
			}
		}

		if (!m_pSpawnedAI.empty())
		{
			CheckPlayerShots();
			CheckPlayerCollisions();
		}

		std::stringstream ss;
		ss << m_iScore;
		m_pScore->SetText(ss.str());

		m_Player->process();

		switch (m_iHealth)
		{
		case 3:
			m_pHealthBar->ChangeTexture(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
			m_pHealthBar->Scale(glm::vec3(0.2f, 0.2f, 0.0f));
			m_pHealthBar->Translate(glm::vec3(-0.85f, -0.75f, 0.0f));
			break;
		case 2:
			m_pHealthBar->ChangeTexture(glm::vec2(0.0f, 0.35f), glm::vec2(1.0f, 0.6f));
			m_pHealthBar->Scale(glm::vec3(0.25f, 0.1333f, 0.0f));
			m_pHealthBar->Translate(glm::vec3(-0.85f, -0.8f, 0.0f));
			break;
		case 1:
			m_pHealthBar->ChangeTexture(glm::vec2(0.0f, 0.70f), glm::vec2(1.0f, 0.3f));
			m_pHealthBar->Scale(glm::vec3(0.3f, 0.066666f, 0.0f));
			m_pHealthBar->Translate(glm::vec3(-0.85f, -0.85f, 0.0f));
			break;
		case 0:
			return true;
			break;
		default:
			break;
		}
		//Camera Placement
		/*****************************************************************/
		glm::vec3 camVec = glm::vec3(glm::cos(-glm::radians(m_Player->GetRot())), -0.7, glm::sin(-glm::radians(m_Player->GetRot())));
		CCameraManager::GetInstance().GetCam()->CamTarget(m_Player->GetPos());
		CCameraManager::GetInstance().GetCam()->CamTranslate(m_Player->GetPos() + (-camVec * 10.0f));

	}
	else
	{
		if (m_MPtype == CLIENT)
		{
			std::stringstream ss;
			ss << m_iScore;
			m_pScore->SetText(ss.str());

			m_Player->process();

			switch (m_iHealth)
			{
			case 3:
				m_pHealthBar->ChangeTexture(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
				m_pHealthBar->Scale(glm::vec3(0.2f, 0.2f, 0.0f));
				m_pHealthBar->Translate(glm::vec3(-0.85f, -0.75f, 0.0f));
				break;
			case 2:
				m_pHealthBar->ChangeTexture(glm::vec2(0.0f, 0.35f), glm::vec2(1.0f, 0.6f));
				m_pHealthBar->Scale(glm::vec3(0.25f, 0.1333f, 0.0f));
				m_pHealthBar->Translate(glm::vec3(-0.85f, -0.8f, 0.0f));
				break;
			case 1:
				m_pHealthBar->ChangeTexture(glm::vec2(0.0f, 0.70f), glm::vec2(1.0f, 0.3f));
				m_pHealthBar->Scale(glm::vec3(0.3f, 0.066666f, 0.0f));
				m_pHealthBar->Translate(glm::vec3(-0.85f, -0.85f, 0.0f));
				break;
			case 0:
				return true;
				break;
			default:
				break;
			}

			
			//Camera Placement
			/*****************************************************************/
			glm::vec3 camVec = glm::vec3(glm::cos(-glm::radians(m_Player->GetRot())), -0.7, glm::sin(-glm::radians(m_Player->GetRot())));
			CCameraManager::GetInstance().GetCam()->CamTarget(m_Player->GetPos());
			CCameraManager::GetInstance().GetCam()->CamTranslate(m_Player->GetPos() + (-camVec * 10.0f));
		} 
		else if (m_MPtype == SERVER)
		{
			CCameraManager::GetInstance().GetCam()->CamTarget(glm::vec3(0.0f, 0.0f, 0.0f));
			CCameraManager::GetInstance().GetCam()->CamTranslate(glm::vec3(0.0f, 200.0f, -50.0f));
		}
	}
	return false;
}

void CGame::Render()
{
	myCubeMap->Render();
	for (auto & i : m_vpEnviroment)
	{
		i->Render();
	}
	
	for (auto & i : m_pSpawnedAI)
	{
		i->Render();
	}

	m_pScoreBack->Render();
	m_pHealthBar->Render();
	m_pScore->Render();

	m_Player->Render();
}

void CGame::CheckPlayerShots()
{
	for (int i = 0; i < m_pSpawnedAI.size(); i++)
	{
		for (int j = 0; j < m_Player->GetPlayerBullets().size(); j++)
		{
			//std::cout << distance(m_Player->GetPlayerBullets()[j]->GetPos(), m_pSpawnedAI[i]->GetPos()) << std::endl;
			if (distance(m_Player->GetPlayerBullets()[j]->GetPos(), m_pSpawnedAI[i]->GetPos()) < 2.0f)
			{
				m_Player->GetPlayerBullets().erase(m_Player->GetPlayerBullets().begin() + j);
				m_pSpawnedAI.erase(m_pSpawnedAI.begin() + i);
				m_iScore += 10;
				return;
				std::cout << "shoot" << std::endl;
			}
		}
	}
}

bool CGame::CheckPlayerCollisions()
{

	for (int i = 0; i < m_pSpawnedAI.size(); i++)
	{
		if (distance(m_Player->GetPos(), m_pSpawnedAI[i]->GetPos()) < 1.0f) //This method was done under time constraint. the Separating Axis Theorem was researched
		{
			std::cout << "colliding" << std::endl;
			m_pSpawnedAI.erase(m_pSpawnedAI.begin() + i);
			m_iHealth--;
			return true;
		}
	}
	return false;
}

