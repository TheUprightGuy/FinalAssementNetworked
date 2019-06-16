#include "object.h"
#include <iostream>

CObject::CObject(ShaderSet _progtype, std::string _imgFilepath, MeshType _meshtype, CCamera* _camOveride)
	:m_MeshType(_meshtype)
{
	if (_camOveride == nullptr)
	{
		m_pCamera = CCameraManager::GetInstance().GetCam(0);
	}
	else
	{
		m_pCamera = _camOveride;
	}
	m_program = CProgrammerManager::GetInstance().GetProgram(_progtype);
	m_objPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_objScale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_texStartScale = glm::vec2(0.0f, 0.0f);
	m_texEndScale = glm::vec2(1.0f, 1.0f);
	m_RotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_RotationDegrees = 0.0f;
	/**************************************************/
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	int width, height;
	unsigned char* image = SOIL_load_image(_imgFilepath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	/*************************************************/
}

CObject::CObject()
{
}

CObject::~CObject()
{
}

//Secondary
void CObject::Init(GLuint &_program, std::string _imgFilepath, MeshType _meshtype)
{
	//m_objPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	//m_objScale = glm::vec3(1.0f, 1.0f, 1.0f);
	//m_texStartScale = glm::vec2(0.0f, 0.0f);
	//m_texEndScale = glm::vec2(1.0f, 1.0f);
	//m_RotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	//m_RotationDegrees = 0.0f;

	//m_program = _program;
	//m_MeshType = _meshtype;

	///**************************************************/
	//glGenTextures(1, &m_texture);
	//glBindTexture(GL_TEXTURE_2D, m_texture);

	//int width, height;
	//unsigned char* image = SOIL_load_image(_imgFilepath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0);
	///*************************************************/
}

void CObject::Render()
{
	//CCamera* CCamera = CCameraManager::GetInstance().GetCam();
	glUseProgram(m_program);

	glCullFace(GL_BACK); // Cull the Back faces
	glFrontFace(GL_CW); // Front face is Clockwise order

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Translate matrix
	glm::mat4 translate = glm::translate(glm::mat4(), m_objPosition); 

	/************************************///Rotation Matrix
	glm::vec3 rotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(m_RotationDegrees), m_RotAxis);

	/************************************///Scale matrix
	glm::mat4 scale = glm::scale(glm::mat4(), m_objScale); 

	/************************************///Texture Scale matrix
	glUniform1f(glGetUniformLocation(m_program, "fStartX"), m_texStartScale.x);
	glUniform1f(glGetUniformLocation(m_program, "fStartY"), m_texStartScale.y);

	glUniform1f(glGetUniformLocation(m_program, "fEndX"), m_texEndScale.x);
	glUniform1f(glGetUniformLocation(m_program, "fEndY"), m_texEndScale.y);
	/********************************/

	glm::mat4 Model = translate * rotation * scale;
	glm::mat4 MVP;
	glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(Model));
	/********************************///MVP

	if (m_MeshType != MESH_2D_SPRITE)
	{
		glm::mat4 view = m_pCamera->GetView();
		glm::mat4 proj = m_pCamera->GetProj();
		MVP = proj * view * Model;
	}
	else
	{
		glm::mat4 proj = m_pCamera->GetProj();
		MVP = proj * Model;
	}
	

	GLint MVPLoc = glGetUniformLocation(m_program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
	/***********************************/

	/***********************************/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glUniform1i(glGetUniformLocation(m_program, "tex"), 0);
	
	CMeshManager::GetInstance().RenderMesh(m_MeshType);

	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void CObject::Update()
{
}

void CObject::ChangeTexture(glm::vec2 _texStartCoords, glm::vec2 _texEndCoords)
{
	m_texStartScale = _texStartCoords;
	m_texEndScale = _texEndCoords;
}

void CObject::Translate(glm::vec3 _newPos)
{
	m_objPosition = _newPos;
}

void CObject::Scale(glm::vec3 _scale)
{
	m_objScale = _scale;
}


