 //
// (c) 2015 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

//Library Includes
#include <WS2tcpip.h>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>


//Local Includes
#include "mputils.h"
#include "network.h"
#include "consoletools.h"
#include "socket.h"


//Local Includes
#include "server.h"

CServer::CServer()
	:m_pcPacketData(0),
	m_pServerSocket(0)
{
	ZeroMemory(&m_ClientAddress, sizeof(m_ClientAddress));
}

CServer::~CServer()
{
	delete m_pConnectedClients;
	m_pConnectedClients = 0;

	delete m_pServerSocket;
	m_pServerSocket = 0;

	delete m_pWorkQueue;
	m_pWorkQueue = 0;
	
	delete[] m_pcPacketData;
	m_pcPacketData = 0;
}

bool CServer::Initialise()
{
	m_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	
	//Create a work queue to distribute messages between the main  thread and the receive thread.
	m_pWorkQueue = new CWorkQueue<char*>();

	//Create a socket object
	m_pServerSocket = new CSocket();

	//Get the port number to bind the socket to
	unsigned short _usServerPort = QueryPortNumber(DEFAULT_SERVER_PORT);

	//Initialise the socket to the local loop back address and port number
	if (!m_pServerSocket->Initialise(_usServerPort))
	{
		return false;
	}

	//Qs 2: Create the map to hold details of all connected clients
	m_pConnectedClients = new std::map < std::string, TClientDetails >() ;

	return true;
}

bool CServer::AddClient(std::string _strClientName)
{
	//TO DO : Add the code to add a client to the map here...
	
	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		//Check to see that the client to be added does not already exist in the map, 
		if(it->first == ToString(m_ClientAddress))
		{
			return false;
		}
		//also check for the existence of the username
		else if (it->second.m_strName == _strClientName)
		{
			return false;
		}
	}
	//Add the client to the map.
	TClientDetails _clientToAdd;
	_clientToAdd.m_strName = _strClientName;
	_clientToAdd.m_ClientAddress = this->m_ClientAddress;

	std::string _strAddress = ToString(m_ClientAddress);
	m_pConnectedClients->insert(std::pair < std::string, TClientDetails > (_strAddress, _clientToAdd));
	return true;
}

bool CServer::SendData(char* _pcDataToSend)
{
	int _iBytesToSend = (int)strlen(_pcDataToSend) + 1;
	
	int iNumBytes = sendto(
		m_pServerSocket->GetSocketHandle(),				// socket to send through.
		_pcDataToSend,									// data to send
		_iBytesToSend,									// number of bytes to send
		0,												// flags
		reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet target
		sizeof(m_ClientAddress)							// size of the above address struct.
		);
	//iNumBytes;
	if (_iBytesToSend != iNumBytes)
	{
		std::cout << "There was an error in sending data from client to server" << std::endl;
		return false;
	}
	return true;
}

bool CServer::SendToAll(char* _pcDataToSend)
{
	int _iBytesToSend = (int)strlen(_pcDataToSend) + 1;
	
	int iNumBytes;

	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		iNumBytes = sendto(
			m_pServerSocket->GetSocketHandle(),				// socket to send through.
			_pcDataToSend,									// data to send
			_iBytesToSend,									// number of bytes to send
			0,												// flags
			reinterpret_cast<sockaddr*>(&it->second.m_ClientAddress),	// address to be filled with packet target
			sizeof(it->second.m_ClientAddress)							// size of the above address struct.
		);
		//iNumBytes;
	}

	//iNumBytes;
	if (_iBytesToSend != iNumBytes)
	{
		//std::cout << "There was an error in sending data from client to server" << std::endl;
		return false;
	}
	return true;
}

void CServer::CheckAlive()
{
	TPacket _packetToSend;
	_packetToSend.Serialize(KEEPALIVE, "RUALIVE");
	SendToAll(_packetToSend.PacketData);
}

void CServer::UpdateWorld()
{

	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		std::ostringstream oss;
		oss << it->second.m_strName;
		oss << " ";
		oss << it->second.m_ClientData;

		std::cout << oss.str() << std::endl;

		std::string _strToSend = oss.str();
		const char* _pcToSend = _strToSend.c_str();

		int _iMessageSize = static_cast<int>(strlen(_pcToSend));

		//Put the message into a packet structure
		TPacket _packet;
		_packet.Serialize(WORLD_UPDATE, const_cast<char*>(_pcToSend)); //Hardcoded username; change to name as taken in via user input.
		SendToAll(_packet.PacketData); //Send game data to server
	}
	
	
	

}

void CServer::ReceiveData(char* _pcBufferToReceiveData)
{
	
	int iSizeOfAdd = sizeof(m_ClientAddress);
	int _iNumOfBytesReceived;
	int _iPacketSize;

	//Make a thread local buffer to receive data into
	char _buffer[MAX_MESSAGE_LENGTH];

	while (true)
	{
		// pull off the packet(s) using recvfrom()
		_iNumOfBytesReceived = recvfrom(			// pulls a packet from a single source...
			m_pServerSocket->GetSocketHandle(),						// client-end socket being used to read from
			_buffer,							// incoming packet to be filled
			MAX_MESSAGE_LENGTH,					   // length of incoming packet to be filled
			0,										// flags
			reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet source
			&iSizeOfAdd								// size of the above address struct.
		);
		if (_iNumOfBytesReceived < 0)
		{
			int _iError = WSAGetLastError();
			ErrorRoutines::PrintWSAErrorInfo(_iError);
			//return false;
		}
		else
		{
			_iPacketSize = static_cast<int>(strlen(_buffer)) + 1;
			strcpy_s(_pcBufferToReceiveData, _iPacketSize, _buffer);
			char _IPAddress[100];
			inet_ntop(AF_INET, &m_ClientAddress.sin_addr, _IPAddress, sizeof(_IPAddress));
			
			/*std::cout << "Server Received \"" << _pcBufferToReceiveData << "\" from " <<
				_IPAddress << ":" << ntohs(m_ClientAddress.sin_port) << std::endl;*/
			//Push this packet data into the WorkQ
			m_pWorkQueue->push(_pcBufferToReceiveData);
		}
		//std::this_thread::yield();
		
	} //End of while (true)
}

void CServer::GetRemoteIPAddress(char *_pcSendersIP)
{
	char _temp[MAX_ADDRESS_LENGTH];
	int _iAddressLength;
	inet_ntop(AF_INET, &(m_ClientAddress.sin_addr), _temp, sizeof(_temp));
	_iAddressLength = static_cast<int>(strlen(_temp)) + 1;
	strcpy_s(_pcSendersIP, _iAddressLength, _temp);
}

unsigned short CServer::GetRemotePort()
{
	return ntohs(m_ClientAddress.sin_port);
}

void CServer::ProcessData(char* _pcDataReceived)
{
	TPacket _packetRecvd, _packetToSend;
	_packetRecvd = _packetRecvd.Deserialize(_pcDataReceived);
	switch (_packetRecvd.MessageType)
	{
	case HANDSHAKE:
	{
		std::cout << "Server received a handshake message " << std::endl;

		_packetToSend.Serialize(HANDSHAKE, _packetRecvd.MessageContent);
		SendToAll(_packetToSend.PacketData);

		if (AddClient(_packetRecvd.MessageContent))
		{
			TPacket _Accepted;
			//_Accepted.Serialize(DATA, "Joined Successfully. Currently Online:");
			//SendData(_Accepted.PacketData);

			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				_Accepted.Serialize(HANDSHAKE, const_cast<char*>(it->second.m_strName.c_str() ) );
				SendData(_Accepted.PacketData);
			}

			//_Accepted.Serialize(DATA, "\n");
			//SendData(_Accepted.PacketData);

			
		}
		break;
	}
	case DATA:
	{

		//_packetToSend.Serialize(DATA, _packetRecvd.MessageContent);
		//SendToAll(_packetToSend.PacketData);
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));

		//_packetToSend.Serialize(DATA, "TEST MESSAGE");
		//SendToAll(_packetToSend.PacketData);
		break;
	}

	case BROADCAST:
	{
		std::cout << "Received a broadcast packet" << std::endl;
		//Just send out a packet to the back to the client again which will have the server's IP and port in it's sender fields
		std::string serverInfo = ToString(m_pConnectedClients->size());
		serverInfo += '/';
		serverInfo += m_name;
		_packetToSend.Serialize(BROADCAST, const_cast<char*>(serverInfo.c_str()));
		SendData(_packetToSend.PacketData);

		break;
	}
	case KEEPALIVE:
		m_pConnectedClients->at(ToString(m_ClientAddress)).m_bIsActive = true;
		//std::cout << m_pConnectedClients->at(ToString(m_ClientAddress)).m_strName << " checked in." << std::endl;
		break;
	case PLAYER_UPDATE:
	{
		std::string str(_packetRecvd.MessageContent);
		
		std::string _clientAdress = ToString(m_ClientAddress);
		m_pConnectedClients->at(_clientAdress).m_ClientData = str;

		break;
	}
	default:
		break;

	}
}

CWorkQueue<char*>* CServer::GetWorkQueue()
{
	return m_pWorkQueue;
}
