#include "glcanvas.hpp"
using namespace cnv;

float alpha = 0.0f;
float a;

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

	glLoadIdentity();
	
	gluLookAt(0.0f,0.0f,10.0f,
			0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f);
	
	glRotatef(alpha,1.0f,1.0f,1.0f);
	
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_POLYGON);
	{
		glVertex3f(0.0f,1.0f,1.0f);
		glVertex3f(-1.0f,0.2f,1.0f);
		glVertex3f(-0.7f,-1.0f,1.0f);
		glVertex3f(0.7f,-1.0f,1.0f);
		glVertex3f(1.0f,0.2f,1.0f);
	}	
	glEnd();

	glBegin(GL_TRIANGLES);
	{
		glVertex3f(1.0f,0.2f,1.0f);			
		glVertex3f(0.0f,1.0f,1.0f);			
		glVertex3f(1.5f,1.7f,1.0f);			
		
		glVertex3f(0.0f,1.0f,1.0f);			
		glVertex3f(-1.0f,0.2f,1.0f);			
		glVertex3f(-1.5f,1.7f,1.0f);			
		
		glVertex3f(-1.0f,0.2f,1.0f);			
		glVertex3f(-0.7f,-1.0f,1.0f);			
		glVertex3f(-1.8f,-1.0f,1.0f);			
		
		glVertex3f(0.7f,-1.0f,1.0f);			
		glVertex3f(1.0f,0.2f,1.0f);			
		glVertex3f(1.8f,-1.0f,1.0f);			
		
		glVertex3f(-0.7f,-1.0f,1.0f);			
		glVertex3f(0.7f,-1.0f,1.0f);			
		glVertex3f(0.0f,-2.5f,1.0f);			
	}
	glEnd();
	
	glColor3f(1.0f,0.0f,0.0f);

	glBegin(GL_LINES);
	{
		glVertex3f(1.5f,1.7f,1.0f);			
		glVertex3f(-1.5f,1.7f,1.0f);			
		glVertex3f(-1.5f,1.7f,1.0f);			
		glVertex3f(-1.8f,-1.0f,1.0f);			
		glVertex3f(-1.8f,-1.0f,1.0f);			
		glVertex3f(0.0f,-2.5f,1.0f);			
		glVertex3f(1.8f,-1.0f,1.0f);			
		glVertex3f(1.5f,1.7f,1.0f);			
		glVertex3f(0.0f,-2.5f,1.0f);			
		glVertex3f(1.8f,-1.0f,1.0f);			
	}
	glEnd();

	alpha+=1.0f;

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(200,100);
	glutCreateWindow("Lesson 1");

	glutDisplayFunc(Draw);
	glutReshapeFunc(changeSize);
	glutIdleFunc(Draw);
	
	glutMainLoop();
}
