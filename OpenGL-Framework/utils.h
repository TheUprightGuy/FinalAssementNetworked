#ifndef __UTILS_H__
#define __UTILS_H__

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include <WS2tcpip.h>
#include <string>
#include <strstream>

#include <vector>
#include <iostream>

enum MeshType
{
	MESH_2D_SPRITE,
	MESH_CUBE,
	MESH_SPHERE
};

enum InputState
{
	INPUT_FIRST_RELEASE,
	INPUT_RELEASE,
	INPUT_FIRST_PRESS,
	INPUT_HOLD
};

enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};

struct KeyPressInfo
{
	unsigned char cKey;
	int iX;
	int iY;
};

#define VALIDATE(a) if (!a) return (false)

namespace {
	std::string ToString(sockaddr_in _sockAddress)
	{
		//INET_ADDRSTRLEN - maximum length for IPv4 addresses
		char _pcAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &_sockAddress.sin_addr, _pcAddress, INET_ADDRSTRLEN);

		std::string _strAddress = _pcAddress;
		std::string _strPort = std::to_string(ntohs(_sockAddress.sin_port));
		std::string _strAddressPort = _strAddress + ':' + _strPort;

		return _strAddressPort;
	}
}


template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

#endif // !__UTILS_H__
