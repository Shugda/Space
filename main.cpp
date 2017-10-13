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

const int textNumber = 2; // количество текстур
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
	string files[textNumber] = {"back.jpg", "jj.jpg"}; // имена файлов
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

	glPushMatrix(); // Земля begin

	glRotatef(90,1.0,0.0,0.0);
	glRotatef(alpha,0.0,0.0,1.0);
	glTranslatef(0.0,1.0,0.0);
	glBindTexture(GL_TEXTURE_2D, texture.id[1]);

	GLUquadricObj *gsea;
	gsea = gluNewQuadric();
	gluQuadricDrawStyle(gsea, GLU_FILL);
	gluQuadricTexture(gsea,GL_TRUE);
	gluSphere(gsea,1,15,50);
	alpha+=0.5f;	

	glPopMatrix(); // Земля end

	glPushMatrix(); // Фон begin

	glBindTexture(GL_TEXTURE_2D, texture.id[0]);
	GLUquadricObj *gea;
	gea = gluNewQuadric();
	gluQuadricDrawStyle(gea, GLU_FILL);
	gluQuadricTexture(gea,GL_TRUE);
	gluSphere(gea,50,15,50);

	glPopMatrix(); // Фон end

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(200,100);
	glutCreateWindow("Sphere");

	texture.init();

	glutDisplayFunc(f);
	glutIdleFunc(f);
	glutReshapeFunc(changeSize);

	glutMainLoop();
}
