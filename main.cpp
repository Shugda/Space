#define STB_IMAGE_IMPLEMENTATION
#define GL_GLEXT_PROTOTYPES
#include "glcanvas.hpp"
#include "stb_image.h"
#include <ctime>
using namespace cnv;
using namespace std;
float alpha = 0.0;
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

const int textNumber = 11; // количество текстур

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
		data[pic] = stbi_load(files[pic].c_str(), &width[pic], &height[pic], &nrChannels[pic], STBI_rgb_alpha);

		glGenTextures(1, &id[pic]);
		glBindTexture(GL_TEXTURE_2D, id[pic]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width[pic], height[pic], 0, GL_RGBA, GL_UNSIGNED_BYTE, data[pic]);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data[pic]);
	}

	unsigned char *data[textNumber]; // картинки
	int width[textNumber], height[textNumber], nrChannels[textNumber]; // и их параметры
	string files[textNumber] = {"back.jpg","sun.jpg","mercury.jpg","venere.jpg","jj.jpg","mars.jpg","jupiter.jpg","saturn.jpg","uran.jpg","neptun.jpg","moon.jpg"}; 
};

Textures texture;
void processSpecialKeys(int key, int xx, int yy)
{
	static float angle = 0.0;
	float fraction = 0.2f;
	switch(key)
	{		
		case GLUT_KEY_LEFT :
			angle += 0.02f;
			lx = -sin(angle);
			lz = -cos(angle);
			break;	
		case GLUT_KEY_RIGHT :
			angle -= 0.02f;
			lx = -sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx*fraction;
			z += lz*fraction;
			break;
		case GLUT_KEY_DOWN :
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
	gluSphere(texture,55.0f,15,50);
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
	gluSphere(texture,1.092f,15,50);
	glPopMatrix();
}
void moon()
{
	const float r=2.7845f;
	float fraction = 0.01f;
	// y = z
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(r*sin(-alpha*fraction),r*cos(-alpha*fraction),0.0f);
	glRotatef(alpha,0.0f,0.0f,1.0f);
//	glTranslatef(0.0f,0.000f,0.0f);
	glBindTexture(GL_TEXTURE_2D, texture.id[10]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture,GL_TRUE);
	gluSphere(texture,0.002f,30,50);
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
	gluSphere(texture,size,30,50);
	glPopMatrix();
}

void Vision(void)
{
	const int r=5.0f;
	// fps
	static int timer = 0;
	static time_t now = 0;
	timer++;
	if(time(0) != now)
	{
		cout << timer << endl;
		timer = 0;
		now = time(0);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D); 

	glLoadIdentity();

	gluLookAt(x,0.0f,z, r*lx+x,0.0f,r*lz+z, 0.0f,1.0f,0.0f);

	glPushMatrix();
	Space();
	Sun();
	planet(1.6868f,0.0038f,2); // Меркурий
	planet(2.2857f,0.0095f,3); // Венера
	planet(2.7745f,0.01f,4); // Земля
	planet(3.6945f,0.0053f,5); // Марс
	planet(10.5434f,0.1097f,6); // Юпитер
	planet(17.9984f,0.0914f,7); // Сатурн
	planet(33.821f,0.0398f,8); // Уран
	planet(53.522f,0.0386f,9); // Нептун
	moon();
	glPopMatrix();

	glutSwapBuffers();
}

void tick(int)
{
	alpha += 0.01f;
	glutTimerFunc(16,tick,0);
	glutPostRedisplay();
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
	glutReshapeFunc(changeSize);
	glutSpecialFunc(processSpecialKeys);
	
	glEnable(GL_DEPTH_TEST);
	tick(0);

	glutMainLoop();
}
