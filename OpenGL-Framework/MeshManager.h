#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "SpriteMesh.h"
#include "CubeMesh.h"
#include "Sphere.h"

class CMeshManager
{
public:
	~CMeshManager() {}

	static CMeshManager& GetInstance()
	{
		if (s_pMeshManager == nullptr)
		{
			s_pMeshManager = new CMeshManager();
		}

		return(*s_pMeshManager);
	}

	static void DestroyInstance()
	{
		delete s_pMeshManager;
		s_pMeshManager = nullptr;
	}

	void Init(){}

	void RenderMesh(MeshType _mesh);

protected:
	static CMeshManager* s_pMeshManager;

private:
	CMeshManager();
	CMeshManager(const CMeshManager& _kr) = delete;
	CMeshManager& operator= (const CMeshManager& _kr) = delete;

	//MeshPointers
	CSpriteMesh* m_pSpriteMesh;
	CCubeMesh* m_CubeMesh;
	Sphere* m_pSphereMesh;
};
