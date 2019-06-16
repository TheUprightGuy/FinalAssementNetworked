#ifndef __PROGRAMMANAGER_H__
#define __PROGRAMMANAGER_H__

#include "utils.h"
#include "ShaderLoader.h"

enum ShaderSet
{
	DEFAULT,
	PHONGLIGHTING
};

class CProgrammerManager
{
public:
	~CProgrammerManager();

	GLuint& GetProgram(ShaderSet getShaderProg)
	{
		ShaderLoader shaderLoader;

		switch (getShaderProg)
		{
		case DEFAULT:
			if (defaultProg == 0)
			{
				defaultProg = shaderLoader.CreateProgram("Shaders/VertexShader.vs", "Shaders/FragmentShader.fs");
			}
			return(defaultProg);
			break;
		case PHONGLIGHTING:
			if (phongProg == 0)
			{
				phongProg = shaderLoader.CreateProgram("Shaders/PhongLightingVS.vs", "Shaders/PhongLightingFS.fs");
			}
			return(phongProg);
			break;
		default:
			break;
		}

	}
	static CProgrammerManager& GetInstance()
	{
		if (s_pProgrammerManager == nullptr)
		{
			s_pProgrammerManager = new CProgrammerManager();
		}

		return(*s_pProgrammerManager);
	}

	static void DestroyInstance()
	{
		delete s_pProgrammerManager;
		s_pProgrammerManager = nullptr;
	}

	//Singleton setup
	/*********************************************/
protected:
	static CProgrammerManager* s_pProgrammerManager;

private:
	CProgrammerManager()
	{
		defaultProg = 0;
		phongProg = 0;
	}
	CProgrammerManager(const CProgrammerManager& _kr) = delete;
	CProgrammerManager& operator= (const CProgrammerManager& _kr) = delete;
	/*********************************************/


	GLuint defaultProg;
	GLuint phongProg;
};


#endif