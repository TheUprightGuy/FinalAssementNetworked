#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include "input.h"
#include "utils.h"
#include "object.h"
#include "CameraManager.h";
#include "player.h"
#include "bullet.h"
#include "CCubeMap.h"
#include "AI.h"
#include "TextLabel.h"
#include "network.h"

#include <sstream>

class CGame
{
public:
	~CGame(){}

	static CGame& GetInstance();
	static void DestroyInstance();

	void init();
	
	bool Process();
	void Render();
	void Restart();

	void CheckPlayerShots();
	bool CheckPlayerCollisions();

	int GetCam() { return(m_Cam); }

	void SetGameMode(bool bIsSinglePlayer, EEntityType _newmode = CLIENT)
	{ 
		m_gamemode = bIsSinglePlayer;
		m_MPtype = _newmode;
	}

	void GetPlayerData(glm::vec3& _playerPos, float& _playerRot) 
	{
		_playerPos = m_Player->GetPos();
		_playerRot = m_Player->GetRot();
	}

	std::map<std::string, CObject*>& GetPlayers() { return(m_Players); }

protected:
	static CGame* s_pGame;

private:
	CGame();
	CGame(const CGame& _kr) = delete;
	CGame& operator= (const CGame& _kr) = delete;

	int m_Cam;
	CCubeMap* myCubeMap;

	std::vector<CObject*> m_vpEnviroment;

	CEnemy* m_pAI;
	std::vector<CEnemy*> m_pSpawnedAI;

	CPlayer* m_Player;
	CObject* m_pHealthBar;
	CObject* m_pScoreBack;
	TextLabel* m_pScore;
	int m_iScore;
	int m_iHealth;

	std::map<std::string, CObject*> m_Players;

	EEntityType m_MPtype;
	bool m_gamemode;
};


#endif