/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wpływów
*/


#include "map.h"


Map::Map(string strenemies, string config) : wrogowie(strenemies)
{
	std::ifstream infile(config);
	string line;
	getline(infile, line);
	getline(infile, line);
	std::istringstream iss(line);

	int EstAlg;
	if (!(iss >> frange >> fdecline >> fangle >> ffov >> EstAlg))
		fprintf(stderr, "failed to read data!\n");
	else
		Node::setEstimationAlg(EstAlg);

	getline(infile, line);
	getline(infile, line);
	std::istringstream iss2(line);

	if (!(iss2 >> startx >> starty >> endx >> endy))
		fprintf(stderr, "failed to read data!\n");
	getline(infile, line);
	getline(infile, line);
	std::istringstream iss3(line);
	//mnożnik wpływu
	if (!(iss3 >> counter >> heuresticmulti >> influecemulti))
		fprintf(stderr, "failed to read data!\n");
}

Map::~Map()
{

}

void Map::createIMap()
{
	for (int y = 0; y < (SIZE_H); ++y)
		for (int x = 0; x < (SIZE_W); ++x)
		{
			imapPixels.push_back((int)(255 * pointIMap(x, y, false)));
			imapPixels.push_back(0);
			imapPixels.push_back(0);
		}
}

//calculate influance in a single point (value from 0 to 1)
float Map::pointIMap(int x, int y, bool truedamage)
{

	/*******************************************************************************************************************************
	/* Laboratorium - Zadanie 2. Obliczyć wpływ w punkcie x,y
	***************************************************************************
	//Zwracamy wartość wpływu (0-1) - wyliczanej z odległości od wrogów. Inforamcje o wrogach przechowywane są w zmiennej: wrogowie
	Dla każdego wroga liczymy wpływ:
		- jeżeli odległość punktu od wroga jest większa od range - wróg nie ma wpływu w danym punkcie
		- jeżeli frange==true to w całym obszarze wpływu wroga wpływ=1
		- jeżeli wpływ zmniejsza się z odległością (fdecline==true)
							wpływ = 1 - odległość_punktu_do_wroga / 20

		- jeżeli uwzględniamy kont widzenia wroga (fangle==true) sprawdzamy czy punkt jest w zasięgu wzroku wroga (metoda isRightAngle). Jeżeli nie jest punkt wydoczny: wpływ=0

	********************************************************************************************************************************/

	float influance = 0.0f;


	for (auto& wrog : wrogowie.tab)
	{
		float distance2Points = sqrt(pow(wrog.x - x, 2) + pow(wrog.y - y, 2) * 1.0);


		if (distance2Points > wrog.range) {
			continue;
		}

		bool seen = isRightAngle(wrog, x, y);
		if (fangle == true && !seen) {

			influance += 0.0f;
		}
		else if (frange == true) {
			influance += 1.0f;
		}
		else if (fdecline == true) {
			influance += 1 - distance2Points / 20.0f;
		}
	}

	if (influance > 1)
		influance = 1;
	return influance;
}

//bool Map::isNotVisable(int x1, int y1, int x2, int y2, int x, int y, float h)
//{
//	float p1 = Pixels[SIZE_W*(x1*3) + (y1*3)] + h;// al_get_pixel(hmap, x1, y1).r + h;
//	float p2 = Pixels[SIZE_W*(x2*3) + (y2*3)] + h;
//	int dx1 = abs(x1-x);
//	int dy1 = abs(y1-y);
//	int dx2 = abs(x2-x);
//	int dy2 = abs(y2-y);
//	float pp1 = sqrt((float)(dx1*dx1+dy1*dy1));
//	float pp2 = sqrt((float)(dx2*dx2+dy2*dy2));
//	/*float pp1 = dx1+dy1;
//	float pp2 = dx2+dy2;*/
//	float pp = pp1 + pp2;
//	float height = (p2*pp1+p1*pp2)/pp;
//	return  (Pixels[SIZE_W*(x*3) + (y*3)]) > height;
//}

bool Map::isRightAngle(Enemy& e, int x, int y)
{
	if (!fangle) return true;
	int dx = x - e.x;
	int dy = e.y - y;
	float angle;
	if (dx >= 0 && dy > 0)
		angle = atan(dx / (float)dy) * 180 / PI;
	else if (dx > 0 && dy <= 0)
		angle = 90 + atan(abs(dy) / (float)dx) * 180 / PI;
	else if (dx <= 0 && dy < 0)
		angle = 180 + atan(abs(dx) / (float)abs(dy)) * 180 / PI;
	else
		angle = 270 + atan(dy / (float)abs(dx)) * 180 / PI;
	angle = fmod(angle + 180 - e.direction, 360);
	if (!(angle > (180) - e.angle / 2 && angle < (180) + e.angle / 2))
		return false;
	return true;

}


string Map::path()
{
	return AStar::pathFind(startx, starty, endx, endy, imapPixels, Pixels, heuresticmulti / influecemulti);
}



int Map::pathLenght(string str)
{
	int out = 0;
	int j;
	char c;
	int dx[8] = { 1, 1, 0, 1, 1, 1, 0, 1 };
	int dy[8] = { 0, 1, 1, 1, 0, 1, 1, 1 };
	for (int i = 0; i < str.length(); i++)
	{
		c = str.at(i);
		j = atoi(&c);
		if (dx[j] + dy[j] > 1)
			out += 14;
		else
			out += 10;
	}
	return out;
}

float Map::drawPath(string str)
{
	float out = 0;
	int co = counter;

	if (str.length() > 0)
	{
		int j; char c;
		int x = startx;
		int y = starty;

		for (int i = 0; i < str.length(); i++)
		{
			c = str.at(i);
			j = atoi(&c);
			x = x + dx[j];
			y = y + dy[j];
			imapPixels[SIZE_W * (x * 3) + (y * 3 + 1)] = 255;
			Pixels[SIZE_W * (x * 3) + (y * 3 + 1)] = 255;
			--co;
			if (co <= 0)
			{
				out += pointIMap(x, y, true);
				co = counter;
			}
		}

		for (int z = 0; z < 8; ++z)
		{
			imapPixels[SIZE_W * ((startx + dx[z]) * 3) + ((starty + dy[z]) * 3)] = 0;
			imapPixels[SIZE_W * ((startx + dx[z]) * 3) + ((starty + dy[z]) * 3 + 1)] = 0;
			imapPixels[SIZE_W * ((startx + dx[z]) * 3) + ((starty + dy[z]) * 3 + 2)] = 255;
		}

	}
	return out;
}