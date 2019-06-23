#include "SceneManager.h"

CSceneManager* CSceneManager::s_pSceneManager = nullptr;

CSceneManager::CSceneManager()
	:_rNetwork(CNetwork::GetInstance())
{
}


CSceneManager::~CSceneManager()
{
}

CSceneManager& CSceneManager::GetInstance()
{
	if (s_pSceneManager == nullptr)
	{
		s_pSceneManager = new CSceneManager();
	}

	return(*s_pSceneManager);
}

void CSceneManager::DestroyInstance()
{
	delete s_pSceneManager;
	s_pSceneManager = nullptr;
}

void CSceneManager::Init()
{
	mainType = MAIN;

	myLight = new CLight(CProgrammerManager::GetInstance().GetProgram(PHONGLIGHTING));
	startMenu = new CMenu();
	gameOver = new CMenu();
	pauseMenu = new CMenu();
	MPMenu = new CMenu();
	ChooseMPMenu = new CMenu();
	EnterPort = new CMenu();
	ServerList = new CMenu();

	m_pClock = new CClock();
	m_pClock->Initialise();
	m_pClock->Process();

	CGame::GetInstance().init();
	i_Play = 0;
	bPaused = false;
	NameEnter = false;
	ServerPort = "";
	//GLuint UIprog = CProgrammerManager::GetInstance().GetProgram(DEFAULT);
	backGround = new CObject(DEFAULT, "Resources/menucircle.png", MESH_2D_SPRITE, CCameraManager::GetInstance().GetOrthoCam());
	backGround->Scale(glm::vec3(0.65f, 0.9f, 0.0f));
	//mySprite->Translate(glm::vec3(0.0f, 0.0f, 0.0f));

	pauseBackGround = new CObject(DEFAULT, "Resources/pausescreen.png", MESH_2D_SPRITE, CCameraManager::GetInstance().GetOrthoCam());
	pauseBackGround->Scale(glm::vec3(0.65f, 0.9f, 0.0f));

	GObackGround = new CObject(DEFAULT, "Resources/DEATHcircle.png", MESH_2D_SPRITE, CCameraManager::GetInstance().GetOrthoCam());
	GObackGround->Scale(glm::vec3(0.65f, 0.9f, 0.0f));

	//Initializing the buttons
	/******************************************************/
	CButton* startButton = new CButton("Resources/Singleplayer.png");
	startButton->Scale(glm::vec3(0.2f, 0.1f, 0.0f));
	startButton->Translate(glm::vec3(0.0f, 0.15f, 0.0f));

	CButton* multiButton = new CButton("Resources/Multiplayer.png");
	multiButton->Scale(glm::vec3(0.2f, 0.1f, 0.0f));
	multiButton->Translate(glm::vec3(0.0f, -0.15f, 0.0f));

	CButton* settingsButton = new CButton("Resources/Settings.png");
	settingsButton->Scale(glm::vec3(0.2f, 0.1f, 0.0f));
	settingsButton->Translate(glm::vec3(-0.7f, -0.8f, 0.0f));

	CButton* exitButton = new CButton("Resources/Exit.png");
	exitButton->Scale(glm::vec3(0.2f, 0.1f, 0.0f));
	exitButton->Translate(glm::vec3(0.7f, -0.8f, 0.0f));

	CButton* menuButton = new CButton("Resources/MainMenu.png");
	menuButton->Scale(glm::vec3(0.2f, 0.1f, 0.0f));
	menuButton->Translate(glm::vec3(0.0f, -0.15f, 0.0f));

	CButton* startoverButton = new CButton("Resources/StartOver.png");
	startoverButton->Scale(glm::vec3(0.2f, 0.1f, 0.0f));
	startoverButton->Translate(glm::vec3(0.0f, 0.15f, 0.0f));


	CButton* joinButton = new CButton("Resources/Join.png");
	joinButton->Scale(glm::vec3(0.15f, 0.1f, 0.0f));
	joinButton->Translate(glm::vec3(0.0f, 0.15f, 0.0f));

	CButton* hostButton = new CButton("Resources/Host.png");
	hostButton->Scale(glm::vec3(0.15f, 0.1f, 0.0f));
	hostButton->Translate(glm::vec3(0.0f, -0.17f, 0.0f));

	CButton* enterButton = new CButton("Resources/enter.png");
	enterButton->Scale(glm::vec3(0.12f, 0.07f, 0.0f));
	enterButton->Translate(glm::vec3(0.07f, -0.19f, 0.0f));

	CButton* defaultButton = new CButton("Resources/Default.png");
	defaultButton->Scale(glm::vec3(0.12f, 0.07f, 0.0f));
	defaultButton->Translate(glm::vec3(-0.15f, -0.19f, 0.0f));

	m_confirm = new CButton("Resources/enter.png");
	m_confirm->Scale(glm::vec3(0.15f, 0.07f, 0.0f));
	m_confirm->Translate(glm::vec3(0.0f, -0.19f, 0.0f));

	m_start = new CButton("Resources/enter.png");
	m_start->Scale(glm::vec3(0.15f, 0.07f, 0.0f));
	m_start->Translate(glm::vec3(0.0f, -0.21f, 0.0f));

	m_ServerName = new CTextBox("Resources/empty.png", glm::vec2(0.0f, 0.0f), "Enter Server Name");
	m_ServerName->Scale(glm::vec3(0.3f, 0.1f, 0.0f));
	
	m_inputPort = new CTextBox("Resources/empty.png", glm::vec2(0.0f, 0.0f), "Enter Port Number");
	m_inputPort->Scale(glm::vec3(0.3f, 0.1f, 0.0f));
	m_inputPort->RestrictRange(056, 072);

	//Adding the buttons to menus
	/******************************************************/
	startMenu->AddButton(startButton, "startButton");
	startMenu->AddButton(multiButton, "multiButton");
	startMenu->AddButton(settingsButton, "settingsButton");
	startMenu->AddButton(exitButton, "exitButton");

	ChooseMPMenu->AddButton(joinButton, "joinButton");
	ChooseMPMenu->AddButton(hostButton, "hostButton");
	
	EnterPort->AddButton(enterButton, "enterButton");
	EnterPort->AddButton(defaultButton, "defaultButton");
	
	gameOver->AddButton(exitButton, "exitButton");
	gameOver->AddButton(menuButton, "menuButton");
	gameOver->AddButton(startoverButton, "startoverButton");

	pauseMenu->AddButton(menuButton, "menuButton");
	pauseMenu->AddButton(startoverButton, "startoverButton");

	_pcPacketData = 0;
	_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	strcpy_s(_pcPacketData, strlen("") + 1, "");

	//A pointer to hold a client instance
	_pClient = nullptr;
	//A pointer to hold a server instance
	_pServer = nullptr;
}

void CSceneManager::Render()
{
	//main menu
	/**********************************************/
	if (i_Play == 0)
	{
		backGround->Render();

		switch (mainType)
		{
		case MAIN:
			startMenu->Render();
			break;
		case MULTI:
			ChooseMPMenu->Render();
			break;
		case SERVERCREATE:

			if (NameEnter)
			{
				m_confirm->Render();
				m_ServerName->Render();
			}
			else
			{
				EnterPort->Render();
				m_inputPort->Render();
				m_inputPort->Process();
			}

			break;
		case CLIENTCHOOSE:
			if (!NameEnter)
			{
				ServerList->Render();
				for (auto i : m_servervec)
				{
					i.second->Render();
				}
			}
			else
			{
				m_confirm->Render();
				m_ServerName->Render();
			}
			
			break;
		case LOBBY:
			ServerList->Render();
			for (auto i : m_servervec)
			{
				i.second->Render();
			}
			if (_eNetworkEntityType == SERVER)
			{
				m_start->Render();
			}
			break;
		case SETTING:
			break;
		default:
			break;
		}

	}
	//Game is processing
	/**********************************************/
	if (i_Play == 1)
	{
		CGame::GetInstance().Render();

		//Game is paused
		/**********************************************/
		if (bPaused)
		{
			pauseBackGround->Render();
			pauseMenu->Render();
		}

		myLight->Render();
	}
	//Death Screen
	/**********************************************/
	if (i_Play == 2)
	{
		GObackGround->Render();
		gameOver->Render();
	}
	/**********************************************/
}

void CSceneManager::MainProcess()
{
	static std::string selection;
	std::string tempselection;
	
	

	//main menu
	/**********************************************/
	if (i_Play == 0)
	{
		switch (mainType)
		{
		case MAIN:
			tempselection = startMenu->GetSelection();
			break;
		case MULTI:
			tempselection = ChooseMPMenu->GetSelection();
			break;
		case CLIENTCHOOSE:
		{
			static int iServerNum = 0;
			if (!NameEnter)
			{
				static float time = glutGet(GLUT_ELAPSED_TIME);
				float timetime = glutGet(GLUT_ELAPSED_TIME) - time;


				if (timetime > 100)
				{
					//mainType = CLIENTCHOOSE;
					if (_pClient->QueryServerList())
					{
						delete ServerList;
						ServerList = new CMenu();

						m_servervec.clear();
						for (int i = 0; i < _pClient->m_vecServerAddr.size(); i++)
						{
							CButton* defaultButton = new CButton("Resources/empty.png");
							defaultButton->Scale(glm::vec3(0.3f, 0.05f, 0.0f));
							defaultButton->Translate(glm::vec3(0.0f, (-(i  * 0.1f)) + 0.1f, 0.0f));

							ServerList->AddButton(defaultButton, _pClient->m_vecServerAddr[i].serverName);

							float pixelX = (0.0f + 1.22f) * 0.5 * glutGet(GLUT_WINDOW_WIDTH);
							float pixelY = ((1.45f) - i * 0.125) * 0.5 * glutGet(GLUT_WINDOW_HEIGHT);
							std::string finalOut = _pClient->m_vecServerAddr[i].serverName + " - " + ToString(_pClient->m_vecServerAddr[i].ServerAddr) + " - " + ToString(_pClient->m_vecServerAddr[i].playerNum) + "/4 players";
							TextLabel* temp = new TextLabel(finalOut, "Resources/Fonts/arial.ttf", { pixelX , pixelY });
							temp->SetScale(0.5f);

							m_servervec.insert(std::pair< std::string, TextLabel* >(_pClient->m_vecServerAddr[i].serverName, temp));
							//m_servers.push_back(temp);
						}
					}
					time = glutGet(GLUT_ELAPSED_TIME);
				}

				MPProcess();

				std::string chosen = ServerList->GetSelection();

				if (!chosen.empty() && CInput::GetInstance().GetMouseState(0) == INPUT_HOLD)
				{
					for (int i = 0; i < _pClient->m_vecServerAddr.size(); i++)
					{
						if (_pClient->m_vecServerAddr[i].serverName == chosen)
						{
							NameEnter = true;
							iServerNum = i;
						}
					}
				}
			}
			else
			{
				m_ServerName->Process();
				if (m_confirm->CheckCollision() && CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !m_ServerName->GetText().empty())
				{
					ServerName = m_ServerName->GetText();
					_pClient->SetName(ServerName);
					_pClient->SetServer(iServerNum);
					mainType = LOBBY;
				}
			}
		}
		break;

		case SERVERCREATE:
			if (NameEnter)
			{
				m_ServerName->Process();
				if (m_confirm->CheckCollision() && CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !m_ServerName->GetText().empty())
				{
					ServerName = m_ServerName->GetText();
					_pServer->SetName(ServerName);
					mainType = LOBBY;
				}
			}
			else
			{
				tempselection = EnterPort->GetSelection();
			}
			break;
		case LOBBY:
		{
			MPProcess();
		
			static float time = glutGet(GLUT_ELAPSED_TIME);
			float timetime = glutGet(GLUT_ELAPSED_TIME) - time;


			if (timetime > 250)
			{
				std::vector<std::string> m_players;
				switch (_eNetworkEntityType)
				{
				case CLIENT:
					for (auto i: _pClient->m_pConnectedPlayers)
					{
						m_players.push_back(i.first);

						m_servervec.clear();
						for (int i = 0; i < m_players.size(); i++)
						{
							float pixelX = (0.0f + 1.22f) * 0.5 * glutGet(GLUT_WINDOW_WIDTH);
							float pixelY = ((1.45f) - i * 0.125) * 0.5 * glutGet(GLUT_WINDOW_HEIGHT);
							TextLabel* temp = new TextLabel(m_players[i], "Resources/Fonts/arial.ttf", { pixelX , pixelY });
							temp->SetScale(0.5f);
							m_servervec.insert(std::pair< std::string, TextLabel* >(m_players[i], temp));
						}
					}

					if (_pClient->ServerRequestStart)
					{
						i_Play = 1;
					}

					break;
				case SERVER:
					for (auto it = _pServer->m_pConnectedClients->begin(); it != _pServer->m_pConnectedClients->end(); ++it)
					{
						m_players.push_back(it->second.m_strName);
					}

					m_servervec.clear();
					for (int i = 0; i < m_players.size(); i++)
					{
						float pixelX = (0.0f + 1.22f) * 0.5 * glutGet(GLUT_WINDOW_WIDTH);
						float pixelY = ((1.45f) - i * 0.125) * 0.5 * glutGet(GLUT_WINDOW_HEIGHT);
						TextLabel* temp = new TextLabel(m_players[i], "Resources/Fonts/arial.ttf", { pixelX , pixelY });
						temp->SetScale(0.5f);
						m_servervec.insert(std::pair< std::string, TextLabel* >(m_players[i], temp));
					}

					if (m_start->CheckCollision() && CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && _pServer->m_pConnectedClients->size() >= 2)
					{
						_pServer->SendStartSignal();
						i_Play = 1;
					}

					break;
				default:
					break;
				}
				time = glutGet(GLUT_ELAPSED_TIME);
			}
		}
		break;
		case SETTING:
			break;
		default:
			break;
		}

		
	}
	//Game is paused
	/**********************************************/
	else if (i_Play == 1)
	{
		if (bPlayMode)
		{
			//SinglePlayer
			/********************************************************/
			//Keypress to pause the game
			static bool bEsc = false;
			if (CInput::GetInstance().GetKeyState(27) == INPUT_HOLD && bEsc == false)
			{
				bEsc = true;
				bPaused = !bPaused;
			}
			else if (CInput::GetInstance().GetCurrentState() == INPUT_RELEASE)
			{
				bEsc = false;
			}

			//Game is unpaused
			/**********************************************/
			if (!bPaused)
			{
				glutSetCursor(GLUT_CURSOR_NONE);
				if (CGame::GetInstance().Process())
				{
					i_Play = 2;
				}
			}
			//Game is paused
			/**********************************************/
			else
			{
				glutSetCursor(GLUT_CURSOR_INHERIT);
				tempselection = pauseMenu->GetSelection();

			}
		}
		else
		{
			/********************************************************/
			MPProcess();
			CGame::GetInstance().Process();
		}
	}
	//Death Screen
	/**********************************************/
	else if (i_Play == 2)
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
		tempselection = gameOver->GetSelection();
	}
	/**********************************************/

	static bool bTap = false;

	//Deciding what each button does
	/**********************************************/
	if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !bTap)
	{
		bTap = true;
		if (tempselection == "startButton")
		{
			std::cout << "Singleplayer" << std::endl;
			i_Play = 1;
			bPlayMode = true;
			CGame::GetInstance().SetGameMode(bPlayMode);

			selection.clear();
			tempselection.clear();
		}
		else if (tempselection == "multiButton")
		{
			std::cout << "Multiplayer" << std::endl;
			mainType = MULTI;

			selection.clear();
			tempselection.clear();

			bPlayMode = false;
		}
		else if (tempselection == "settingsButton")
		{
			std::cout << "Settings" << std::endl;
		}
		else if (tempselection == "exitButton")
		{
			exit(EXIT_SUCCESS);
		}
		else if (tempselection == "menuButton")
		{
			tempselection = "startButton";
			bPaused = false;
			i_Play = 0;
		}
		else if (tempselection == "startoverButton")
		{
			G_Score = 0;
			G_Time = 0;
			i_Play = 1;
			bPaused = false;
			CGame::GetInstance().Restart();
		}
		else if (tempselection == "hostButton")
		{
			mainType = SERVERCREATE;
		}
		else if (tempselection == "joinButton")
		{
			NameEnter = false;
			static bool isStarted = false;
			if (!isStarted)
			{
				MPStartUp(true);
				isStarted = true;
			}
			
			int numOfTries = 5;
			for (int i = 0; i < numOfTries; i++)
			{
				mainType = CLIENTCHOOSE;
				if (_pClient->QueryServerList())
				{
					
					for (int i = 0; i < _pClient->m_vecServerAddr.size(); i++)
					{
						CButton* defaultButton = new CButton("Resources/empty.png");
						defaultButton->Scale(glm::vec3(0.3f, 0.05f, 0.0f));
						defaultButton->Translate(glm::vec3(0.0f, (i  * 0.1) + 0.1f, 0.0f));

						ServerList->AddButton(defaultButton, _pClient->m_vecServerAddr[i].serverName);

						float pixelX = (0.0f + 1.22f) * 0.5 * glutGet(GLUT_WINDOW_WIDTH);
						float pixelY = ((1.45f) - i * 0.125) * 0.5 * glutGet(GLUT_WINDOW_HEIGHT);

						std::string finalOut = _pClient->m_vecServerAddr[i].serverName + " - " + ToString(_pClient->m_vecServerAddr[i].ServerAddr) + " - " + ToString(_pClient->m_vecServerAddr[i].playerNum) + "/4 players";
						TextLabel* temp = new TextLabel(finalOut, "Resources/Fonts/arial.ttf", { pixelX , pixelY });
						temp->SetScale(0.5f);

						m_servervec.insert(std::pair< std::string, TextLabel* >(_pClient->m_vecServerAddr[i].serverName, temp));

						//m_servers.push_back({ _pClient->m_vecServerAddr[i].serverName, temp});
					}
					break;
				}
				Sleep(50);
			}
			

		}
		else if (tempselection == "enterButton")
		{
			NameEnter = true;
			ServerPort = m_inputPort->GetText();
			MPStartUp(false);
		}
		else if (tempselection == "defaultButton")
		{
			ServerPort = "";
			NameEnter = true;
			MPStartUp(false);
		}

	}
	else if (CInput::GetInstance().GetMouseState(0) == INPUT_RELEASE)
	{
		bTap = false;
	}
	/**********************************************/
	if (!tempselection.empty() )
	{
		selection = tempselection;
	}
	
}

void CSceneManager::SPProcess()
{
}

bool CSceneManager::MPStartUp(bool isClient)
{
	_rNetwork.StartUp();

	if (isClient)
	{
		_eNetworkEntityType = CLIENT;
		CGame::GetInstance().SetGameMode(bPlayMode, CLIENT);
	}
	else
	{
		_eNetworkEntityType = SERVER;
		CGame::GetInstance().SetGameMode(bPlayMode, SERVER);
	}

	if (!_rNetwork.GetInstance().Initialise(_eNetworkEntityType) )
	{
		std::cout << "Unable to initialise the Network........Press any key to continue......";
		//_getch();
		
		return false;
	}

	//Run receive on a separate thread so that it does not block the main client thread.
	if (_eNetworkEntityType == CLIENT) //if network entity is a client
	{
		_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));
	}

	//Run receive of server also on a separate thread 
	else if (_eNetworkEntityType == SERVER) //if network entity is a server
	{

		_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));

	}
	return true;
}

void CSceneManager::MPProcess()
{	
	CInputLineBuffer _InputBuffer(MAX_MESSAGE_LENGTH);
	
	//Get the instance of the network
	
	// query, is this to be a client or a server?
	
	if (_rNetwork.IsOnline())
	{
		if (_eNetworkEntityType == CLIENT) //if network entity is a client
		{
			_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());

			//Prepare for reading input from the user
			//_InputBuffer.PrintToScreenTop();

			static float fTime = 0.0f;
			static float  fCount = 0.0f;
			fCount += m_pClock->GetDeltaTick();

			//On server tick
			if (fCount > fTime + 0.1666f)
			{

				//Put the message into a packet structure
				TPacket _packet;
				//_packet.Serialize(PLAYER_UPDATE, const_cast<char*>(_pcToSend)); //Hardcoded username; change to name as taken in via user input.
				//_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData); //Send game data to server

				////Clear the Input Buffer
				//_InputBuffer.ClearString();
				////Print To Screen Top
				//_InputBuffer.PrintToScreenTop();
				
				fTime = fCount;
			}
			m_pClock->Process();

			if (_pClient != nullptr)
			{
				//If the message queue is empty 
				if (_pClient->GetWorkQueue()->empty())
				{
					//Don't do anything
				}
				else
				{
					//Retrieve off a message from the queue and process it
					std::string temp;
					_pClient->GetWorkQueue()->pop(temp);
					_pClient->ProcessData(const_cast<char*>(temp.c_str()));
				}
			}

		}
		else //if you are running a server instance
		{
			
			if (_pServer != nullptr)
			{
				static float fTime = 0.0f;
				static float  fCount = 0.0f;
				fCount += m_pClock->GetDeltaTick();
				//On server tick

				if (fCount > fTime + 0.1666f)
				{
					//_pServer->CheckAlive();
					//_pServer->UpdateWorld();

					fTime = fCount;
				}

				
				m_pClock->Process();

				if (!_pServer->GetWorkQueue()->empty())
				{
					_rNetwork.GetInstance().GetNetworkEntity()->GetRemoteIPAddress(_cIPAddress);
					//std::cout << _cIPAddress
					//<< ":" << _rNetwork.GetInstance().GetNetworkEntity()->GetRemotePort() << "> " << _pcPacketData << std::endl;

					//Retrieve off a message from the queue and process it
					_pServer->GetWorkQueue()->pop(_pcPacketData);
					_pServer->ProcessData(_pcPacketData);
				}
				
			}
		}


	} //End of while network is Online
	else
	{
		_ClientReceiveThread.join();
	_ServerReceiveThread.join();

	//Shut Down the Network
	_rNetwork.ShutDown();
	_rNetwork.DestroyInstance();

	delete[] _pcPacketData;
	}
	
	return;
}
