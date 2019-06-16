#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "SceneManager.h"
#include "ProgramManager.h"
GLuint program;


void init();
void render();
void update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Mouse(int button, int glutState, int x, int y);
void PassiveMouse(int x, int y);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("The Red Room");

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glewInit();
	init();

	glutDisplayFunc(render);

	glutIdleFunc(update);

	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseFunc(Mouse); 
	glutPassiveMotionFunc(PassiveMouse);

	glutMainLoop();

	return(0);

}
void init()
{
	CSceneManager::GetInstance().Init(); //Init the scene manager
	CMeshManager::GetInstance(); //Init the mesh manager
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0, 0.0, 0.0, 1.0);

	CSceneManager::GetInstance().Render();

	glutSwapBuffers();
}

void update()
{
	CSceneManager::GetInstance().MainProcess();
	glutPostRedisplay();
}

void KeyDown(unsigned char key, int x, int y)
{
	CInput::GetInstance().KeyboardDown(key, x, y);
}

void KeyUp(unsigned char key, int x, int y)
{
	CInput::GetInstance().KeyboardUp(key, x, y);
}

void Mouse(int button, int glutState, int x, int y)
{
	CInput::GetInstance().MouseClick(button, glutState, x, y);
}

void PassiveMouse(int x, int y)
{
	CInput::GetInstance().MouseMove(x, y);
}

