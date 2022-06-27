/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp�yw�w
*/

#ifndef _ASTAR_H_
#define _ASTAR_H_

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>

#include <GL/glut.h>
#include <GL/GL.h> 
#include <GL/GLU.h>  

#include "node.h"

using namespace std;

typedef priority_queue<Node> PQN; 

const int N = 100; //maksymalna szeroko�� mapy terenu
const int M = 100; //maksymalna wysoko�� mapy terenu

using namespace std;

// rozmiar mapy
#define SIZE_H 100 
#define SIZE_W 100

class AStar
{
	static int closed_nodes_map[N][M];			// mapa terenu zaznaczaj�ca miejsca kt�re zosta�y ca�kowicie przetworzone przez algorytm A* : 1 (miejsce nale�y do w�z��w zamkni�tych A*)
	static int open_nodes_map[N][M];			// mapa terenu zaznaczaj�ca miejsca dla kt�rych zosta�y wyliczone warto�ci f. Kom�rki przechowuj� warto�� f lub 0 (w�ze� nie przetworzony lub na li�cie zamkni�tej)
	static int dir_map[N][M];					// mapa rodzic�w (pozycja rodzica okre�lona za pomoc� warto�ci (0-7):
												// -------------->x
												// |
												// | 5 6 7
												// | 4 x 0
												// | 3 2 1
												// |
												//\|/y 

														
	static PQN *DeleteNode(PQN*pq, int xdx, int ydy); //zwraca now� list� bez w�z�a o pozycji xdx,ydy

	static string generatePath(int xFinish, int yFinish, int xStart, int yStart); //generuje string z drog� z punktu startowego do punktu ko�cowego

	//Zwraca true je�eli bie��cy w�ze� nie nadaje si� do przej�cia
	//hmap - mapa wysoko�ci
	//xparent, yparent - pozycja w�z�a-rodzica
	//x,y - pozycja analizowanego w�z�a
	static inline bool przeszkoda(std::vector<unsigned char> &hmap, int xparent, int yparent, int x, int y) {
		if (hmap.size()!=0)
			return (hmap[SIZE_W* (x * 3) + (y * 3)] - hmap[SIZE_W* (xparent * 3) + (yparent * 3)] > 20);
	}

public:
	AStar(){}

	// Algorytm A*
	//  string z drog� z punktu startowego do punktu ko�cowego - dla ka�dego ruchu podaje kierunek zgodnie ze wzorem:
	// -------------->x
	// |
	// | 5 6 7
	// | 4 x 0
	// | 3 2 1
	// |
	//\|/y 
	static string pathFind( int xStart, int yStart, 
		int xFinish, int yFinish, std::vector<unsigned char> &map, std::vector<unsigned char> &hmap, float multi);

};

#endif