#include "glcanvas.hpp"
using namespace cnv;

float windowwidth = 400;
float windowhigh = 400;

void changeSize(int w, int h)
{
	if (!h) h = 1;
	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	{
		glVertex3f(25.0f,25.0,-25.0);
		glVertex3f(-25.0f,25.0,-25.0);
		glVertex3f(-25.0f,-25.0,-25.0);
		glVertex3f(25.0f,-25.0,-25.0);

		glColor3f(0,1,0);
		glVertex3f(25.0f,25.0,25.0);
		glVertex3f(-25.0f,25.0,25.0);
		glVertex3f(-25.0f,-25.0,25.0);
		glVertex3f(25.0f,-25.0,25.0);

		glColor3f(0,0,1);
		glVertex3f(-25.0f,25.0,25.0);
		glVertex3f(-25.0f,25.0,-25.0);
		glVertex3f(-25.0f,-25.0,-25.0);
		glVertex3f(-25.0f,-25.0,25.0);

		glColor3f(1,1,0);
		glVertex3f(-25.0f,25.0,-25.0);
		glVertex3f(-25.0f,25.0,25.0);
		glVertex3f(25.0f,25.0,25.0);
		glVertex3f(25.0f,25.0,-25.0);

		glColor3f(1,0,1);
		glVertex3f(25.0f,25.0,-25.0);
		glVertex3f(25.0f,25.0,25.0);
		glVertex3f(25.0f,-25.0,25.0);
		glVertex3f(25.0f,-25.0,-25.0);

		glColor3f(0,1,1);
		glVertex3f(25.0f,-25.0,-25.0);
		glVertex3f(-25.0f,-25.0,-25.0);
		glVertex3f(-25.0f,-25.0,25.0);
		glVertex3f(25.0f,-25.0,25.0);

	}
	glEnd();

	glutSwapBuffers();
}	

void Timer(int)
{
	glRotatef(1,1.0,1.0,1.0);
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 0);
}

void Initialize()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-windowwidth/2, windowwidth/2, -windowhigh/2,windowhigh/2,-200.0,200.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0,0.0,0.0);
	glScalef(1.0,1.0,1.0);
	glRotatef(0,0.0,0.0,0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowwidth,windowhigh);
	glutInitWindowPosition(200,0);
	glutCreateWindow("Lesson 1");

	glutDisplayFunc(Draw);
	Initialize();
	Timer(0);
	glutMainLoop();
}
