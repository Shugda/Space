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
	const double r = 2.7845f; // радиус орбиты Земли
	const double fraction = -3.141592/180; // перевод градусов в радианы
	const double sz = 0.002; // размер Луны
	const int speed = 60; // скорость вращения

	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);

	glTranslatef(r*sin(alpha*fraction),r*cos(alpha*fraction),0.0f);
	glRotatef(speed*alpha,0.0f,0.0f,1.0f);
	glTranslatef(0.0f,0.04,0.0f);

	glBindTexture(GL_TEXTURE_2D, texture.id[10]);
	GLUquadricObj *texture;
	texture = gluNewQuadric();
	gluQuadricDrawStyle(texture, GLU_FILL);
	gluQuadricTexture(texture,GL_TRUE);
	gluSphere(texture,sz,30,50);
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

    void text(string a)
    {
    if (a == "Sun" || a == "sun")
    cout << "Солнце - единственная звезда Солнцечной системы. Она отсносится к типу GV2 или желтый карлик.Солнце находится во внутреннем крае рукава Ориона нашей Галактики, между рукавом Персея и рукавом Стрельца, в так называемом «Местном межзвёздном облаке» — области повышенной плотности.\n Солнце состоит из водорода (~73 % от массы и ~92 % от объёма), гелия (~25 % от массы и ~7 % от объёма) и других элементов с меньшей концентрацией: железа, никеля, кислорода, азота, кремния, серы, магния, углерода, неона, кальция и хрома. На 1 млн атомов водорода приходится 98 000 атомов гелия, 851 атом кислорода, 398 атомов углерода, 123 атома неона, 100 атомов азота, 47 атомов железа, 38 атомов магния, 35 атомов кремния, 16 атомов серы, 4 атома аргона, 3 атома алюминия, по 2 атома никеля, натрия и кальция, а также малое количество прочих элементов. Масса Солнца составляет 99,866 % от суммарной массы всей Солнечной системы.\n Средний диаметр Солнца составляет 1,392*10^9 м (109 диаметров Земли), \n площадь поверхности - 6,07877·10^18 м^2 (11 917,607 площадей Земли),\n объём -\n1,40927·10^27 м^3 (1 301 019 объёмов Земли),\n масса - 1,9885·10^30 кг (332 940 масс Земли),\nтемпература короны - ~1.500.000 K,\n температура ядра - ~15.700.000 K.";

    if (a == "Mercury" || a == "mercury")
    cout << "Меркурий — ближайшая к Солнцу планета Солнечной системы, наименьшая из планет земной группы. Названа в честь древнеримского бога торговли — быстрого Меркурия, поскольку она движется по небесной сфере быстрее других планет. По своим физическим характеристикам Меркурий напоминает Луну. У него нет естественных спутников, но есть очень разреженная атмосфера.\n Планета обладает крупным железным ядром, являющимся источником магнитного поля, напряжённость которого составляет 0,01 от земного. Оно составляет 83 % от всего объёма планеты.\nТемпература на поверхности Меркурия колеблется от 80 до 700 К (от ?190 до +430 C). Солнечная сторона нагревается гораздо больше, чем полярные области и обратная сторона планеты. \n Среднее расстояние Меркурия от Солнца чуть меньше 58 млн км (57,91 млн км), планета обращается вокруг звезды за 88 земных суток.\n Средний радиус - 2439,7 +- 1,0 км (0,3829 земного),\n площадь поверхности - 7,48·10^7 км^2 (0,147 земной),\n объём - 6,083·10^10 км^3 (0,056 земного),\n средняя плотность - 5,427 г/см^3 (0,984 земной),\n масса - 3,33022*10^23 (0,055274 земной),\n период вращения - 58,646 дней (1407,5 часов).";

    if (a == "Venus" || a == "venus")
    cout << "Венера — вторая по удалённости от Солнца планета Солнечной системы, наряду с Меркурием, Землёй и Марсом принадлежит к семейству планет земной группы. Названа в честь древнеримской богини любви Венеры. Венерианский год составляет 224,7 земных суток. Она имеет самый длинный период вращения вокруг своей оси (243 земных суток) среди всех планет Солнечной системы и вращается в направлении, противоположном направлению вращения большинства планет. Венера не имеет естественных спутников. Это третий по яркости объект на небе Земли, после Солнца и Луны. Изредка Венера видна невооружённым глазом и в светлое время суток. Венера имеет плотную атмосферу, состоящую из более чем 96 % углекислого газа. Атмосферное давление на поверхности планеты в 92 раза больше, чем на поверхности Земли, и примерно равно давлению воды на глубине 900 метров. Венера, безусловно, самая горячая планета в Солнечной системе — средняя температура поверхности 735 К (462 С; 863 F), даже несмотря на то, что Меркурий находится ближе к Солнцу. Венера покрыта непрозрачным слоем облаков из серной кислоты с высокой отражающей способностью, что помимо всего прочего закрывает поверхность планеты от прямой видимости. Высокая температура поверхности обусловлена действием парникового эффекта.\n Среднее расстояние Венеры от Солнца — 108 млн км, расстояние от Венеры до Земли меняется в пределах от 38 до 261 млн км.\n Средний радиус - 6051,8 ± 1,0 км,\n Площадь поверхности - 4,60·10^8 км^2 (0,902 земных),\n Объём - 9,38·10^11 км^3 (0,857 земных),\n Масса - 4,8675·10^24 кг (0,815 земных),\n Средняя плотность - 5,24 г/см^3.";

    if (a == "Earth" || a == "earth")
    cout << " Земля - третья по удалённости от Солнца планета Солнечной системы. Пятая по диаметру, массе и плотности среди всех планет и крупнейшая среди планет земной группы, в которую входят также Меркурий, Венера и Марс. Единственное известное человеку на данный момент тело Солнечной системы в частности и Вселенной вообще, населённое живыми организмами. Внутренние области Земли достаточно активны и состоят из толстого, очень вязкого слоя, называемого мантией, которая покрывает жидкое внешнее ядро, являющееся источником магнитного поля Земли, и внутреннее твёрдое ядро, предположительно, состоящее из железа и никеля. Земля состоит в основном из железа (32,1 %), кислорода (30,1 %), кремния (15,1 %), магния (13,9 %), серы (2,9 %), никеля (1,8 %), кальция (1,5 %) и алюминия (1,4 %), на остальные элементы приходится 1,2 %. Примечательно, что углерода, являющегося основой жизни, в земной коре всего 0,1 %.\n Средний радиус - 6371,0 км, \n Площадь поверхности - 510 072 000 км^2, 148 940 000 км^2 суша (29,2 %), 361 132 000 км^2 вода (70,8 %),\n Объём - 10,8321·10^11 км^3,\n Масса - 5,9726·10^24 кг,\n Средняя плотность - 5,5153 г/см^2,\n Первая космическая скорость - 7,91 км/с,\n Вторая космическая скорость - 11,186 км/c,\n Экваториальная скорость вращения - 1674,4 км/ч (465,1 м/с),\n Период вращения 0,99726968 суток,(23ч 56м 4,100c) - сидерический период вращения,24 часа - длительность средних солнечных суток.";

    if (a == "Moon" || a == "moon")
    cout << "Луна — естественный спутник Земли. Самый близкий к Солнцу спутник планеты, так как у ближайших к Солнцу планет, Меркурия и Венеры, спутников нет.Среднее расстояние между центрами Земли и Луны — 384 467 км. Луна является единственным астрономическим объектом, на котором побывал человек. Луна состоит из коры, верхней мантии (астеносферы), средней мантии, нижней мантии и ядра. Атмосфера практически отсутствует. Поверхность Луны покрыта реголитом — смесью тонкой пыли и скалистых обломков, образующихся в результате столкновений метеоритов с лунной поверхностью. Ударно-взрывные процессы, сопровождающие метеоритную бомбардировку, способствуют взрыхлению и перемешиванию грунта, одновременно спекая и уплотняя частицы грунта. Толщина слоя реголита составляет от долей метра до десятков метров. Толщина коры Луны меняется от 0 до 105 км.\n Средний радиус - 1737,10 км (0,273 земных),\n Площадь поверхности - 3,793·10^7 км^2 (0,074 земной),\n Объём - 2,1958·10^10 км (0,020 или 1/50 земного),\n Масса - 7,3477·10^22 кг (0,0123 или 1/81 земной),\n Средняя плотность - 3,3464 г/см^3.";

    if (a == "Mars" || a == "mars")
    cout << "Марс — четвёртая по удалённости от Солнца и седьмая по размерам планета Солнечной системы. Названа в честь Марса — древнеримского бога войны, соответствующего древнегреческому Аресу. Иногда Марс называют «красной планетой» из-за красноватого оттенка поверхности, придаваемого ей оксидом железа(III). Марс — планета земной группы с разреженной атмосферой (давление у поверхности в 160 раз меньше земного). Особенностями поверхностного рельефа Марса можно считать ударные кратеры наподобие лунных, а также вулканы, долины, пустыни и полярные ледниковые шапки наподобие земных. У Марса есть два естественных спутника — Фобос и Деймос (в переводе с древнегреческого — «страх» и «ужас», имена двух сыновей Ареса, сопровождавших его в бою), которые относительно малы (Фобос — 26,8?22,4?18,4 км, Деймос — 15?12,2?10,4 км) и имеют неправильную форму. На сегодняшний день, после Земли, Марс — самая подробно изученная планета Солнечной системы. Марс имеет период вращения и смену времён года, аналогичные земным, но его климат значительно холоднее и суше земного.\n Средний радиус - 3389,5 ± 0,2 км (0,532 земного),\n Площадь поверхности - 1,4437·10^8 км^2 (0,283 земной),\n Объём - 1,6318·10^11 км^3 (0,151 земного),\n Масса - 6,4171·10^23 кг (0,107 земной),\n Средняя плотность - 3,933 г/см^3 (0,714 земной),\n Период вращения - (24 часа 37 минут 22,663 секунды, \n 24ч 39м 35,244с — длительность средних солнечных суток.";

    if (a == "Jupiter" || a == "jupiter")
    cout << "Юпитер — крупнейшая планета Солнечной системы, пятая по удалённости от Солнца. Наряду с Сатурном, Ураном и Нептуном Юпитер классифицируется как газовый гигант. Юпитер имеет, по крайней мере, 69 спутников, самые крупные из которых — Ио, Европа, Ганимед и Каллисто — были открыты Галилео Галилеем в 1610 году. Масса Юпитера в 2,47 раза превышает суммарную массу всех остальных планет Солнечной системы, вместе взятых, в 317,8 раз — массу Земли и примерно в 1000 раз меньше массы Солнца. Плотность (1326 кг/м^3) примерно равна плотности Солнца и в 4,16 раз уступает плотности Земли (5515 кг/м^3). При этом сила тяжести на его поверхности, за которую обычно принимают верхний слой облаков, более чем в 2,4 раза превосходит земную: тело, которое имеет массу, например, 100 кг, будет весить столько же, сколько весит тело массой 240 кг на поверхности Земли. Ряд атмосферных явлений на Юпитере: штормы, молнии, полярные сияния, — имеет масштабы, на порядки превосходящие земные. Примечательным образованием в атмосфере является Большое красное пятно — гигантский шторм, открытое Робертом Гуком в 1664 году. В настоящее время оно имеет размеры 15-30 тыс. км (диаметр Земли ~12,7 тыс. км), а 100 лет назад наблюдатели отмечали в 2 раза большие размеры.\n Средний радиус - 69 911 ± 6 км,\n Площадь поверхности - 6,21796·10^10 км^2,\n Объём - 1,43128·10^15 км^3,\n Масса - 1,8986·10^27 кг (317,8 земных),\n Средняя плотность - 1,326 г/см^3.";

    if (a == "Saturn" || a == "saturn")
    cout << "Сатурн — шестая планета от Солнца и вторая по размерам планета в Солнечной системе после Юпитера. Сатурн, а также Юпитер, Уран и Нептун, классифицируются как газовые гиганты. Сатурн назван в честь римского бога земледелия. В основном Сатурн состоит из водорода, с примесями гелия и следами воды, метана, аммиака и тяжёлых элементов. Внутренняя область представляет собой относительно небольшое ядро из железа, никеля и льда, покрытое тонким слоем металлического водорода и газообразным внешним слоем. Внешняя атмосфера планеты кажется из космоса спокойной и однородной, хотя иногда на ней появляются долговременные образования. Скорость ветра на Сатурне может достигать местами 1800 км/ч, что значительно больше, чем на Юпитере. Сатурн обладает заметной системой колец, состоящей главным образом из частичек льда, меньшего количества тяжёлых элементов и пыли. Вокруг планеты обращается 62 известных на данный момент спутника. Титан — самый крупный из них, а также второй по размерам спутник в Солнечной системе (после спутника Юпитера, Ганимеда), который превосходит по своим размерам Меркурий и обладает единственной среди спутников планет Солнечной системы плотной атмосферой.\n Средний радиус - 58 232 ± 6 км,\n Площадь поверхности - 4,272·10^10 км^2,\n Объём - 8,2713·10^14 км^3,\n Масса - 5,6846·10^26 кг (95 земных),\n Средняя плотность - 0,687 г/см^3";

    if (a == "Uranus" || a == "uranus")
    cout << "Уран — планета Солнечной системы, седьмая по удалённости от Солнца, третья по диаметру и четвёртая по массе. Названа в честь греческого бога неба Урана. Уран стал первой планетой, обнаруженной в Новое время и при помощи телескопа. Его открыл Уильям Гершель 13 марта 1781 года, тем самым впервые со времён античности расширив границы Солнечной системы в глазах человека. Несмотря на то, что порой Уран различим невооружённым глазом, более ранние наблюдатели принимали его за тусклую звезду. В отличие от газовых гигантов — Сатурна и Юпитера, состоящих в основном из водорода и гелия, в недрах Урана и схожего с ним Нептуна отсутствует металлический водород, но зато много льда в его высокотемпературных модификациях. По этой причине специалисты выделили эти две планеты в отдельную категорию «ледяных гигантов». Основу атмосферы Урана составляют водород и гелий. Кроме того, в ней обнаружены следы метана и других углеводородов, а также облака изо льда, твёрдого аммиака и водорода. Это самая холодная планетарная атмосфера Солнечной системы с минимальной температурой в 49 К (-224 °C). Полагают, что Уран имеет сложное слоистое строение облаков, где вода составляет нижний слой, а метан — верхний. Недра Урана состоят в основном изо льдов и горных пород. Так же, как у газовых гигантов Солнечной системы, у Урана имеется система колец и магнитосфера, а кроме того, 27 спутников. Ориентация Урана в пространстве отличается от остальных планет Солнечной системы — его ось вращения лежит как бы «на боку» относительно плоскости обращения этой планеты вокруг Солнца. Вследствие этого планета бывает обращена к Солнцу попеременно то северным полюсом, то южным, то экватором, то средними широтами. Скорость ветров на Уране может достигать 250 м/с (900 км/ч).\n Средний радиус - 25 362 ± 7 км,\n Площадь поверхности - 8,1156·10^9 км^2,\n Объём - 6,833·10^13 км^3, \n Масса - 8,6832·10^25 кг (14,6 земных),\n Средняя плотность - 1,27 г/см^3.";

    if (a == "Neptun" || a == "neptun")
    cout << "Нептун — восьмая планета Солнечной системы. Нептун также является четвёртой по диаметру и третьей по массе планетой. Масса Нептуна в 17,2 раза, а диаметр экватора в 3,9 раза больше земных. Планета была названа в честь римского бога морей. Обнаруженный 23 сентября 1846 года, Нептун стал первой планетой, открытой благодаря математическим расчётам, а не путём регулярных наблюдений. Обнаружение непредвиденных изменений в орбите Урана породило гипотезу о неизвестной планете, гравитационным возмущающим влиянием которой они и обусловлены. Нептун был найден в пределах предсказанного положения. Вскоре был открыт и его спутник Тритон, однако остальные 13 спутников, известные ныне, были неизвестны до XX века. Нептун был посещён лишь одним космическим аппаратом, «Вояджером-2», который пролетел вблизи от планеты 25 августа 1989 года. Нептун по составу близок к Урану, и обе планеты отличаются по составу от более крупных планет-гигантов — Юпитера и Сатурна. Иногда Уран и Нептун помещают в отдельную категорию «ледяных гигантов». Атмосфера Нептуна, подобно атмосфере Юпитера и Сатурна, состоит в основном из водорода и гелия, недра Нептуна, как и Урана, состоят главным образом изо льдов и горных пород. Следы метана во внешних слоях атмосферы, в частности, являются причиной синего цвета планеты. В атмосфере Нептуна бушуют самые сильные ветры среди планет Солнечной системы, по некоторым оценкам, их скорости могут достигать 2100 км/ч.\n Средний радиус -24 622 ± 19 км,\n Площадь поверхности - 7,6408·10^9 км^2,\n Объём - 6,254·10^13 км,\n Масса - 1,0243·1026 кг (17,147 земных),\n Средняя плотность - 1,638 г/см^3.";
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
//		cout << timer << endl;
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
	string b;
	getline(cin, b);
	text(b);
	tick(0);
	
	glutMainLoop();
}
