#include "CubeMap.h"

GLfloat m_cubemapvertices[] =
{
	// Positions    
	// Front Face             
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	// Right Face             
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,

	// Back Face             
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	// Left Face             
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,

	// Top Face                 
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,

	// Bottom Face             
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
};

/*
-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //0.0f,
1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
// Right Face
1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
// Back Face
1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
// Left Face
-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
// Top Face
-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
// Bottom Face
-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
*/
GLuint m_cubemapindices[] =
{
	// Front Face
	0, 1, 2,
	0, 2, 3,

	// Right Face
	4, 5, 6,
	4, 6, 7,

	// Back Face
	8, 9, 10,
	8, 10, 11,

	// Left Face
	12, 13, 14,
	12, 14, 15,

	// Top Face
	16, 17, 18,
	16, 18, 19,

	// Bottom Face
	20, 21, 22,
	20, 22, 23,
};

CCubeMap::CCubeMap(std::vector<std::string> _textures)
{
	ShaderLoader ShaderLoader;
	m_program = ShaderLoader.CreateProgram("Shaders/CubeMapVS.vs", "Shaders/CubeMapFS.fs");
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cubemapvertices), m_cubemapvertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(m_cubemapindices),
		m_cubemapindices,
		GL_STATIC_DRAW);

	//Shape
	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		3 * sizeof(GLfloat), // Stride of the entire single vertex
		(GLvoid*)0); // Offset
	glEnableVertexAttribArray(0);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	int width, height;
	unsigned char* image;

	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resources/Textures/";
		fullPathName.append(_textures[i]);

		image = SOIL_load_image(fullPathName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	
}

void CCubeMap::render()
{
	glUseProgram(m_program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisable(GL_CULL_FACE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glUniform1i(glGetUniformLocation(m_program, "cubeSampler"), 0);

	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(1000.0f, 1000.0f, 1000.0f));
	glm::mat4 MVP = CCameraManager::GetInstance().GetCam()->GetProj() * CCameraManager::GetInstance().GetCam()->GetView() * model;

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	
	glBindVertexArray(0); //This is the culprit
	glUseProgram(0);
	

	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_CULL_FACE);
}
