#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "utils.h"
#include "CameraManager.h"
#include "MeshManager.h"
#include "ProgramManager.h"
#include <string>

class CObject
{
public:

	//Program with shaders || Filepath for texture || Enum for the meshtype (MESH_2D_SPRITE,MESH_CUBE,MESH_SPHERE)
	CObject(ShaderSet _progtype, std::string _imgFilepath, MeshType _meshtype, CCamera* _camOveride = nullptr);
	CObject();

	~CObject();

	//Currently defunct
	void Init(GLuint &_program, std::string _imgFilepath, MeshType _meshtype);

	void Render();
	void Update();

	void ChangeTexture(glm::vec2 _texStartCoords, glm::vec2 _texEndCoords);

	void Translate(glm::vec3 _newPos);
	void Scale(glm::vec3 _scale);
	void Rotation(float _fDeg, glm::vec3 _rotAxis) 
	{ 
		m_RotationDegrees = _fDeg;
		m_RotAxis = _rotAxis;
	}

	glm::vec3 GetPos() { return(m_objPosition); }
	glm::vec3 GetScale() { return(m_objScale); }
	float GetRot() { return(m_RotationDegrees); }

protected:
	GLuint m_program;
	//Scale
	glm::vec3 m_objScale;

	//Translate
	glm::vec3 m_objPosition;
private:
	GLuint m_texture;

	CCamera* m_pCamera;
	
	//COORD m_objPixelPos;

	

	//Rotation
	float m_RotationDegrees;
	glm::vec3 m_RotAxis;

	//Texture mapping
	glm::vec2 m_texStartScale;
	glm::vec2 m_texEndScale;

	//Mesh used
	MeshType m_MeshType;
};

#endif /*__SPRITE_H__*/