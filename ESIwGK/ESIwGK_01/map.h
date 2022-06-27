/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp�yw�w
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
	
	//frange -  przez ca�y zasi�g wp�yw=1
	//fdecline - zmniejszanie wp�ywu wraz z odleg�o�ci� od wroga (wp�yw_1_wroga = 1.0f - odleglosc_od_wroga / 20.f;
	//fangle -ograniczenie k�ta widzenia jednostek
	//musi by� frange lub fdecline w��czony
	bool frange, fdecline, fangle;
	
	bool ffov;
	int startx, starty, endx, endy;
	int counter;
	float heuresticmulti;
	float influecemulti; //mno�nik wp�ywu

	/*
	Zwraca true je�eli punkt jest widoczny przez wroga (w zale�no�ci od jego ustawienia i k�ta widzenia)
	x,y - pozycja punktu
	*/
	bool isRightAngle(Enemy & e, int x, int y);

public:
	// Mapy SIZE_WxSIZE_H opisane s� za pomoc� koloru RGB (0-255) ( rozmiar wektor�w to SIZE_W*SIZE_H*3)
	// mapa wp�ywu ( warto�� wyp�ywu okre�la kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3))
	// mapa wysoko�ci ( warto�� wysoko�ci okre�la kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3)
	std::vector<unsigned char> Pixels;			//mapa wysoko�ci
	std::vector<unsigned char> imapPixels;		//mapa wp�yw�w

	Map(string strenemies, string config);
	~Map();

	void createIMap(); //Tworzy map� wp�yw�w

	string path();
	float drawPath(string str); //Rysuje drog�

	float pointIMap(int x, int y, bool truedamage); //Wylicza wp�yw dla punktu x, y

	int pathLenght(string str);

	
};