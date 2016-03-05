#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

GLuint VBO;

static void InitializeGlutCallbacks();
static void RenderScene();
static void CreateVertexBuffer();

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 02 - Hello Dot!");

	InitializeGlutCallbacks();

	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cerr << "Error: " << glewGetErrorString(result) << std::endl;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();

	glutMainLoop();

	return 0;
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderScene);
}

static void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void CreateVertexBuffer()
{
	
}