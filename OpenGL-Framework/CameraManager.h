#pragma once
#ifndef __CAMERAMANAGER_H__
#define __CAMERAMANAGER_H__

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "camera.h"

class CCameraManager
{
public:
	~CCameraManager();

	void Init()
	{
	}

	static CCameraManager& GetInstance();
	static void DestroyInstance();

	//Creates a new cam and returns the index
	int AddNewCam(bool isOrtho = false) 
	{
		m_pCameras.push_back(new CCamera(isOrtho));
		return(m_pCameras.size() - 1);
	}

	void SetCurrentCam(int _i) { m_iCurrentCam = _i; }


	//"Por que no los dos?"
	CCamera* GetCam()
	{
		if (m_pCameras.empty() || m_iCurrentCam > m_pCameras.size())
		{
			return (nullptr);
		}
		else
		{
			return(m_pCameras[m_iCurrentCam]);
		}
	}
	CCamera* GetCam(int _iIndex) 
	{
		if (m_pCameras.empty() || _iIndex > m_pCameras.size())
		{
			return (nullptr);
		}
		else
		{
			return(m_pCameras[_iIndex]);
		}
	}

	CCamera* GetOrthoCam()
	{
		if (orthoCam == nullptr)
		{
			orthoCam = new CCamera(true);
		}

		return(orthoCam);
	}

protected:
	static CCameraManager* s_pCameraManager;

private:
	CCameraManager();
	CCameraManager(const CCameraManager& _kr) = delete;
	CCameraManager& operator= (const CCameraManager& _kr) = delete;

	std::vector<CCamera*> m_pCameras;
	CCamera* orthoCam;
	int m_iCurrentCam;
};
#endif
