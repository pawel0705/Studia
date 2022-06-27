/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
*/

#ifndef _ENEMIES_H_
#define _ENEMIES_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Enemy
{
public:
	int x, y;	// enemy position
	//x	y	height	range	direction	angle
	//10	78	2	14 - 5	100

	float height;
	float range;	// zasiêg wp³ywu wroga
	float direction;
	float angle;
	Enemy(string str);
};

class Enemies 
{
public:
	vector<Enemy> tab;
public:
	Enemies(string str);
	Enemies();
};
#endif