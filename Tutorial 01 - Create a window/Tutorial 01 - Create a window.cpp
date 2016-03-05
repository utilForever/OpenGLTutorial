#include <GL/freeglut.h>

static void InitializeGlutCallbacks();
static void RenderScene();

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01 - Create a window");

	InitializeGlutCallbacks();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
	glutSwapBuffers();
}