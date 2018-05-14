#define STB_IMAGE_IMPLEMENTATION
#define GL_GLEXT_PROTOTYPES
#include "glcanvas.hpp"
#include "stb_image.h"
#include <ctime>
using namespace cnv;
using namespace std;

enum Name {mercury, venus, earth, mars, jupiter, saturn, uranus, neptune};

struct Planet {
	void load(float dst, float sz, float sp)
	{
		distance = dst;
		size = sz;
		speed = sp;
	}

	void tick()
	{
		alpha += speed;
	}

	float distance;
	float size;
	float speed;
	float alpha = 0;
};

Planet planets[8];

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
		data[pic] = stbi_load((dir + files[pic] + ext).c_str(), &width[pic], &height[pic], &nrChannels[pic], STBI_rgb_alpha);

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
	const string files[textNumber] = {"mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune", "back", "sun", "moon"}; 
	const string dir = "img/";
	const string ext = ".jpg";
};

Textures texture;
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

void processSpecialKeys(int key, int, int)
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
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture.id[8]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture, GL_TRUE);
	gluSphere(texture,55.0f, 15, 50);
	glPopMatrix();
}

void Sun()
{
	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture.id[9]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture, GL_TRUE);
	gluSphere(texture, 1.092f, 15, 50);
	glPopMatrix();
}

void satellite(double r, double sz, int speed, int id)
{
//	const double r = 2.7845f; // радиус орбиты планеты вокруг которой движется спутник 
	const double fraction = -3.141592/180; // перевод градусов в радианы
//	const double sz = 0.002; // размер Спутника
//	const int speed = 60; // скорость вращения

	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	glTranslatef(r*sin(alpha*fraction), r*cos(alpha*fraction), 0.0f);
	glRotatef(speed*alpha, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.04, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture.id[id]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture, GL_TRUE);
	gluSphere(texture, sz, 30, 50);
	glPopMatrix();
}

void planet(Name name)
{
	glPushMatrix();
	glRotatef(90,1.0f, 0.0f, 0.0f);

	glRotatef(planets[name].alpha, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, planets[name].distance, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture.id[name]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture, GL_TRUE);
	gluSphere(texture, planets[name].size, 30, 50);
	glPopMatrix();
}

void text(string name)
{
	ifstream input("text.txt");
	vector<string> txt;
	for (string s; getline(input, s); txt.push_back(s));
	input.close();

	int offset;

    if (name == "Mercury" || name == "mercury")
		offset = 0;
    if (name == "Venus" || name == "venus")
		offset = 8;
    if (name == "Earth" || name == "earth")
		offset = 16;
    if (name == "Mars" || name == "mars")
		offset = 24;
    if (name == "Jupiter" || name == "jupiter")
		offset = 32;
    if (name == "Saturn" || name == "saturn")
		offset = 40;
    if (name == "Uranus" || name == "uranus")
		offset = 48;
    if (name == "Neptune" || name == "neptune")
		offset = 56;
    if (name == "Sun" || name == "sun")
		offset = 64;
    if (name == "Moon" || name == "moon")
		offset = 72;

	for (int i = 0; i < 8; ++i)
		cout << txt[offset+i] << endl;
}

void loadSatellites()
{
	satellite(2.7845f, 0.002, 60, 10); //Луна

}

void Vision()
{
	const int r=5.0f;
	// fps
	static int timer = 0;
	static time_t now = 0;
	timer++;
	if(time(0) != now)
	{
//		cout << timer << endl;
		timer = 0;
		now = time(0);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D); 

	glLoadIdentity();

	gluLookAt(x, 0.0f,z, r*lx+x, 0.0f,r*lz+z, 0.0f,1.0f, 0.0f);

	glPushMatrix();
	Space();
	Sun();

	for (int i = 0; i < 8; ++i)
		planet((Name)i);

	loadSatellites();
	glPopMatrix();
	glutSwapBuffers();
}

void loadPlanets()
{
	planets[mercury].load(1.6868f, 0.0038f, 0.01);
	planets[venus].load(2.2857f, 0.0095f, 0.01);
	planets[earth].load(2.7745f, 0.01f, 0.01);
	planets[mars].load(3.6945f, 0.0053f, 0.01);
	planets[jupiter].load(10.5434f, 0.1097f, 0.01);
	planets[saturn].load(17.9984f, 0.0914f, 0.01);
	planets[uranus].load(33.821f, 0.0398f, 0.01);
	planets[neptune].load(53.522f, 0.0386f, 0.01);
}

void tick(int)
{
	alpha += 0.01f;
	for (int i = 0; i < 8; ++i)
		planets[i].tick();

	glutTimerFunc(16,tick, 0);
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
	loadPlanets();
	
	glutDisplayFunc(Vision);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(processSpecialKeys);
	
	glEnable(GL_DEPTH_TEST);
	string name;
	getline(cin, name);
	text(name);
	tick(0);
	
	glutMainLoop();
}
