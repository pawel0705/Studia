/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
*/

#include "enemies.h"

//read file
Enemies::Enemies(string str)
{
	std::ifstream infile(str);
	
	string line;
	int i = 0;
	while (getline(infile, line))
	{
		if(++i > 1)
			tab.push_back(Enemy(line));
	}
}

Enemies::Enemies()
{
}

Enemy::Enemy(string str)
{
	std::istringstream iss(str);
		int a, b;

		if (!(iss >> x >> y >> height >> range >> direction >> angle))
			fprintf(stderr, "failed to read data!\n");

		//n.p.:
		//pozycja wysokoœæ zasiêg ognia k¹t widzenia
		//x	y	height	range	direction	angle
		//10	78	2	14 - 5	100

}