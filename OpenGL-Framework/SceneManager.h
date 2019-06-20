#pragma once
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <vector>
#include <map>
#include <string.h>

#include "utils.h"
#include "input.h"
#include "camera.h"
#include "TextLabel.h"
#include "button.h"
#include "menu.h"
#include "light.h"
#include "AI.h"
#include "AudioManager.h"
#include "ProgramManager.h"
#include "game.h"
#include "clock.h"
#include "TextInput.h"

//Library Includes
#include <Windows.h>
#include <cassert>
//#include <vld.h>
#include <thread>

//Local Includes
//#include "consoletools.h"
#include "network.h"
#include "client.h"
#include "server.h"
#include "InputLineBuffer.h"
#include <functional>

// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")
enum MenuType
{
	MAIN,
	MULTI,
	SERVERCREATE,
	CLIENTCHOOSE,
	LOBBY,
	SETTING
};

struct ServerButtons
{
	std::string tiedToButton;
	TextLabel* m_text;
};
class CSceneManager
{
public:
	~CSceneManager();

	static CSceneManager& GetInstance();
	static void DestroyInstance();

	//Initalize any scenes in here
	void Init();

	void Render();
	void MainProcess();

	void SPProcess();

	bool MPStartUp(bool isClient);
	void MPProcess();
	
	std::string ServerPort;
	std::string ServerName;

protected:
	static CSceneManager* s_pSceneManager;

private:
	CSceneManager();
	CSceneManager(const CSceneManager& _kr) = delete;
	CSceneManager& operator= (const CSceneManager& _kr) = delete;

	//Variables
	GLuint m_program;
	GLuint G_Score;
	GLuint G_Time;

	int i_Play;
	int Select;


	//Global Camera
	CCamera* m_pCamera;

	//true == SP, false == MP
	bool bPlayMode;
	CObject* backGround;
	CObject* GObackGround;
	CObject* pauseBackGround;

	CMenu* startMenu;
	CMenu* MPMenu;
	CMenu* gameOver;
	CMenu* pauseMenu;
	CMenu* ChooseMPMenu;
	CMenu* EnterPort;
	CMenu* ServerList;
	bool NameEnter;
	CButton* m_confirm;
	CTextBox* m_ServerName;

	
	CTextBox* m_inputPort;
	MenuType mainType;
	bool bPaused;
	
	CLight* myLight;

	std::vector<ServerButtons> m_clients;
	std::vector<ServerButtons> m_servers;

	std::map<std::string, TextLabel*> m_servervec;
	//Multiplayer stuffs
	char* _pcPacketData;
	char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
										  //ZeroMemory(&_cIPAddress, strlen(_cIPAddress));
	unsigned char _ucChoice;
	EEntityType _eNetworkEntityType;
	std::thread _ClientReceiveThread, _ServerReceiveThread;
	CNetwork& _rNetwork;

	CClient* _pClient;
	CServer* _pServer;

	CClock* m_pClock;
};

#endif // !__SCENEMANAGER_H__

