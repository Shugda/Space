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

const int textNumber = 7; // количество текстур

class Textures // тут хранятся текстуры
{
public:
	unsigned int id[textNumber]; // массив ID текстур

	void init() 
	{
		for (int i = 0; i < textNumber; ++i)
			load(i);
	}

private:
	void load(int pic) // загрузка текстуры
	{
		data[pic] = stbi_load(files[pic].c_str(), &width[pic], &height[pic], &nrChannels[pic], 0);

		glGenTextures(1, &id[pic]);
		glBindTexture(GL_TEXTURE_2D, id[pic]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[pic], height[pic], 0, GL_RGB, GL_UNSIGNED_BYTE, data[pic]);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data[pic]);
	}

	unsigned char *data[textNumber]; // картинки
	int width[textNumber], height[textNumber], nrChannels[textNumber]; // и их параметры
	string files[textNumber] = {"back.jpg","sun.jpg","mercury.jpg","venere.jpg","jj.jpg","mars.jpg","jupiter.jpg"}; 
};

Textures texture;

void f()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D); 
	glLoadIdentity();

	gluLookAt(0.0f,0.0f,5.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f);

	glPushMatrix(); // Фон begin
	glRotatef(90,1.0,0.0,0.0);

	glBindTexture(GL_TEXTURE_2D, texture.id[0]);
	GLUquadricObj *texture_0;
	texture_0 = gluNewQuadric();
	gluQuadricDrawStyle(texture_0, GLU_FILL);
	gluQuadricTexture(texture_0,GL_TRUE);
	gluSphere(texture_0,50,15,50);
	glPopMatrix(); // Фон end

	glPushMatrix(); // Солнце begin
	glRotatef(90,1.0,0.0,0.0);

	glBindTexture(GL_TEXTURE_2D, texture.id[1]);
	GLUquadricObj *texture_1;
	texture_1 = gluNewQuadric();
	gluQuadricDrawStyle(texture_1, GLU_FILL);
	gluQuadricTexture(texture_1,GL_TRUE);
	gluSphere(texture_1,0.4,10,50);
	glPopMatrix(); // Солнце end

	glPushMatrix(); // Меркурий begin
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(alpha,0.0,0.0,1.0);
	glTranslatef(0.0,0.5,0.0);
	glBindTexture(GL_TEXTURE_2D, texture.id[2]);

	GLUquadricObj *texture_2;
	texture_2 = gluNewQuadric();
	gluQuadricDrawStyle(texture_2, GLU_FILL);
	gluQuadricTexture(texture_2,GL_TRUE);
	gluSphere(texture_2,0.05,15,50);

	alpha+=0.1f;	
	glPopMatrix(); // Меркурий end

	glPushMatrix(); // Венера begin
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(alpha,0.0,0.0,1.0);
	glTranslatef(0.0,0.6,0.0);
	glBindTexture(GL_TEXTURE_2D, texture.id[3]);

	GLUquadricObj *texture_3;
	texture_3 = gluNewQuadric();
	gluQuadricDrawStyle(texture_3, GLU_FILL);
	gluQuadricTexture(texture_3,GL_TRUE);
	gluSphere(texture_3,0.05,15,50);

	alpha+=0.1f;	
	glPopMatrix(); // Венера end

	glPushMatrix(); // Земля begin
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(alpha,0.0,0.0,1.0);
	glTranslatef(0.0,0.7,0.0);
	glBindTexture(GL_TEXTURE_2D, texture.id[4]);

	GLUquadricObj *texture_4;
	texture_4 = gluNewQuadric();
	gluQuadricDrawStyle(texture_4, GLU_FILL);
	gluQuadricTexture(texture_4,GL_TRUE);
	gluSphere(texture_4,0.05,15,50);

	alpha+=0.1f;	
	glPopMatrix(); // Земля end

	glPushMatrix(); // Марс begin
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(alpha,0.0,0.0,1.0);
	glTranslatef(0.0,0.8,0.0);
	glBindTexture(GL_TEXTURE_2D, texture.id[5]);

	GLUquadricObj *texture_5;
	texture_5 = gluNewQuadric();
	gluQuadricDrawStyle(texture_5, GLU_FILL);
	gluQuadricTexture(texture_5,GL_TRUE);
	gluSphere(texture_5,0.05,15,50);

	alpha+=0.1f;	
	glPopMatrix(); // Марс end

	glPushMatrix(); // Юпитер begin
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(alpha,0.0,0.0,1.0);
	glTranslatef(0.0,0.9,0.0);
	glBindTexture(GL_TEXTURE_2D, texture.id[6]);

	GLUquadricObj *texture_6;
	texture_6 = gluNewQuadric();
	gluQuadricDrawStyle(texture_6, GLU_FILL);
	gluQuadricTexture(texture_6,GL_TRUE);
	gluSphere(texture_6,0.05,15,50);

	alpha+=0.1f;	
	glPopMatrix(); // Юпитер end

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(200,100);
	glutCreateWindow("Solar system");

	texture.init();

	glutDisplayFunc(f);
	glutIdleFunc(f);
	glutReshapeFunc(changeSize);

	glutMainLoop();
}
