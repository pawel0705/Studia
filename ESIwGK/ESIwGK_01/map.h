/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
*/

#pragma once
#include <string>
#include <math.h>
#include "astar.h"
#include "enemies.h"

//#include <allegro5/allegro_image.h>
#define PI 3.14159265

class Map 
{

	Enemies wrogowie;
	
	//frange -  przez ca³y zasiêg wp³yw=1
	//fdecline - zmniejszanie wp³ywu wraz z odleg³oœci¹ od wroga (wp³yw_1_wroga = 1.0f - odleglosc_od_wroga / 20.f;
	//fangle -ograniczenie k¹ta widzenia jednostek
	//musi byæ frange lub fdecline w³¹czony
	bool frange, fdecline, fangle;
	
	bool ffov;
	int startx, starty, endx, endy;
	int counter;
	float heuresticmulti;
	float influecemulti; //mno¿nik wp³ywu

	/*
	Zwraca true je¿eli punkt jest widoczny przez wroga (w zale¿noœci od jego ustawienia i k¹ta widzenia)
	x,y - pozycja punktu
	*/
	bool isRightAngle(Enemy & e, int x, int y);

public:
	// Mapy SIZE_WxSIZE_H opisane s¹ za pomoc¹ koloru RGB (0-255) ( rozmiar wektorów to SIZE_W*SIZE_H*3)
	// mapa wp³ywu ( wartoœæ wyp³ywu okreœla kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3))
	// mapa wysokoœci ( wartoœæ wysokoœci okreœla kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3)
	std::vector<unsigned char> Pixels;			//mapa wysokoœci
	std::vector<unsigned char> imapPixels;		//mapa wp³ywów

	Map(string strenemies, string config);
	~Map();

	void createIMap(); //Tworzy mapê wp³ywów

	string path();
	float drawPath(string str); //Rysuje drogê

	float pointIMap(int x, int y, bool truedamage); //Wylicza wp³yw dla punktu x, y

	int pathLenght(string str);

	
};