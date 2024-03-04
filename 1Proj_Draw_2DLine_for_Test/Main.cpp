#include "../glut_lib/glut.h"
#include <iostream>

void MyDrawFunction();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("1Proj_Draw_2DLine_for_Test");
	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);

	glutDisplayFunc(MyDrawFunction);

	glutMainLoop();
	return 0;
}

void MyDrawFunction()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);

	// green color
	glColor3ub(0, 255, 0);

	// draw line (by pixel)
	for (int i = 100; i < 300; i++)
	{
		glBegin(GL_POINTS);
		glVertex2i(i, i); // x=i, y=i
		glEnd();
	}

	glFlush();
}