#define STB_IMAGE_IMPLEMENTATION
#define GL_GLEXT_PROTOTYPES
#include "glcanvas.hpp"
#include "stb_image.h"
using namespace cnv;
using namespace std;
float alpha = 0.0f;

void changeSize(int w, int h)
{
	if (!h) h = 1;
	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void load()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("jj.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
}

void f()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D); 
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_ALPHA_TEST);
	glLoadIdentity();

	gluLookAt(0.0f,0.0f,70.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f);

	glRotatef(90,1.0,0.0,0.0);
	glRotatef(alpha,0.0,0.0,1.0);

	glTranslatef(20.0,0.0,0.0);

	GLUquadricObj *gsea;
	gsea = gluNewQuadric();
	gluQuadricDrawStyle(gsea, GLU_FILL);
	gluQuadricTexture(gsea,GL_TRUE);
	gluSphere(gsea,10,10,10);

	alpha+=0.5f;	

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(200,100);
	glutCreateWindow("Sphere");

	load();

	glutDisplayFunc(f);
	glutIdleFunc(f);
	glutReshapeFunc(changeSize);

	glutMainLoop();
}
