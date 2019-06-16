#include "CameraManager.h"

CCameraManager* CCameraManager::s_pCameraManager = nullptr;

CCameraManager::CCameraManager()
{
	m_iCurrentCam = 0;
	m_pCameras.push_back(new CCamera(false));
}


CCameraManager::~CCameraManager()
{
}

CCameraManager& CCameraManager::GetInstance()
{
	if (s_pCameraManager == nullptr)
	{
		s_pCameraManager = new CCameraManager();
	}

	return(*s_pCameraManager);
}

void CCameraManager::DestroyInstance()
{
	delete s_pCameraManager;
	s_pCameraManager = nullptr;
}
