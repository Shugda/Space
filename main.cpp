#define STB_IMAGE_IMPLEMENTATION
#define GL_GLEXT_PROTOTYPES
#include "glcanvas.hpp"
#include "stb_image.h"
using namespace cnv;
using namespace std;
float alpha = 0.0f;
float angel = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;
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
void processSpecialKeys(int key, int xx, int yy)
{
	float fraction = 0.1f;
	switch(key)
	{		
		case GLUT_KEY_LEFT:
			angel -= 0.01f;
			lx = sin(angel);
			lz = -cos(angel);
			break;
		case GLUT_KEY_RIGHT:
			angel += 0.01f;
			lx = sin(angel);
			lz = -cos(angel);
			break;
		case GLUT_KEY_UP:
			x += lx*fraction;
			z += lz*fraction;
			break;
		case GLUT_KEY_DOWN:
			x -= lx*fraction;
			z -= lz*fraction;
			break;
	}
}
void Space()
{
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glBindTexture(GL_TEXTURE_2D, texture.id[0]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture,GL_TRUE);
	gluSphere(texture,50.0f,15,50);
	glPopMatrix();

}
void Sun()
{
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glBindTexture(GL_TEXTURE_2D, texture.id[1]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture,GL_TRUE);
	gluSphere(texture,0.4f,15,50);
	glPopMatrix();


}
void planet(float pos, float size,int id)
{
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glRotatef(alpha,0.0f,0.0f,1.0f);
	glTranslatef(0.0f,pos,0.0f);
	glBindTexture(GL_TEXTURE_2D, texture.id[id]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture,GL_TRUE);
	gluSphere(texture,size,15,50);
	alpha += 0.1f;
	glPopMatrix();
}

void Vision(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D); 

	glLoadIdentity();

	gluLookAt(x,0.0f,z, x+lx,0.0f,x+lz, 0.0f,1.0f,0.0f);

	glPushMatrix();
	Space();
	Sun();
	planet(0.5f,0.05f,2); // Меркурий
	planet(0.6f,0.05f,3); // Венера
	planet(0.7f,0.05f,4); // Земля
	planet(0.8f,0.05f,5); // Марс
	planet(0.9f,0.05f,6);	// Юпитер
	glPopMatrix();

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
	
	glutDisplayFunc(Vision);
	glutIdleFunc(Vision);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
}
