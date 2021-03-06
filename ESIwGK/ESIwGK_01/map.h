/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp造w闚
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
	
	//frange -  przez ca造 zasi璕 wp造w=1
	//fdecline - zmniejszanie wp造wu wraz z odleg這?ci? od wroga (wp造w_1_wroga = 1.0f - odleglosc_od_wroga / 20.f;
	//fangle -ograniczenie k靖a widzenia jednostek
	//musi by? frange lub fdecline w章czony
	bool frange, fdecline, fangle;
	
	bool ffov;
	int startx, starty, endx, endy;
	int counter;
	float heuresticmulti;
	float influecemulti; //mno積ik wp造wu

	/*
	Zwraca true je瞠li punkt jest widoczny przez wroga (w zale積o?ci od jego ustawienia i k靖a widzenia)
	x,y - pozycja punktu
	*/
	bool isRightAngle(Enemy & e, int x, int y);

public:
	// Mapy SIZE_WxSIZE_H opisane s? za pomoc? koloru RGB (0-255) ( rozmiar wektor闚 to SIZE_W*SIZE_H*3)
	// mapa wp造wu ( warto?? wyp造wu okre?la kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3))
	// mapa wysoko?ci ( warto?? wysoko?ci okre?la kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3)
	std::vector<unsigned char> Pixels;			//mapa wysoko?ci
	std::vector<unsigned char> imapPixels;		//mapa wp造w闚

	Map(string strenemies, string config);
	~Map();

	void createIMap(); //Tworzy map? wp造w闚

	string path();
	float drawPath(string str); //Rysuje drog?

	float pointIMap(int x, int y, bool truedamage); //Wylicza wp造w dla punktu x, y

	int pathLenght(string str);

	
};