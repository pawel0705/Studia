/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
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

const int N = 100; //maksymalna szerokoœæ mapy terenu
const int M = 100; //maksymalna wysokoœæ mapy terenu

using namespace std;

// rozmiar mapy
#define SIZE_H 100 
#define SIZE_W 100

class AStar
{
	static int closed_nodes_map[N][M];			// mapa terenu zaznaczaj¹ca miejsca które zosta³y ca³kowicie przetworzone przez algorytm A* : 1 (miejsce nale¿y do wêz³ów zamkniêtych A*)
	static int open_nodes_map[N][M];			// mapa terenu zaznaczaj¹ca miejsca dla których zosta³y wyliczone wartoœci f. Komórki przechowuj¹ wartoœæ f lub 0 (wêze³ nie przetworzony lub na liœcie zamkniêtej)
	static int dir_map[N][M];					// mapa rodziców (pozycja rodzica okreœlona za pomoc¹ wartoœci (0-7):
												// -------------->x
												// |
												// | 5 6 7
												// | 4 x 0
												// | 3 2 1
												// |
												//\|/y 

														
	static PQN *DeleteNode(PQN*pq, int xdx, int ydy); //zwraca now¹ listê bez wêz³a o pozycji xdx,ydy

	static string generatePath(int xFinish, int yFinish, int xStart, int yStart); //generuje string z drog¹ z punktu startowego do punktu koñcowego

	//Zwraca true je¿eli bie¿¹cy wêze³ nie nadaje siê do przejœcia
	//hmap - mapa wysokoœci
	//xparent, yparent - pozycja wêz³a-rodzica
	//x,y - pozycja analizowanego wêz³a
	static inline bool przeszkoda(std::vector<unsigned char> &hmap, int xparent, int yparent, int x, int y) {
		if (hmap.size()!=0)
			return (hmap[SIZE_W* (x * 3) + (y * 3)] - hmap[SIZE_W* (xparent * 3) + (yparent * 3)] > 20);
	}

public:
	AStar(){}

	// Algorytm A*
	//  string z drog¹ z punktu startowego do punktu koñcowego - dla ka¿dego ruchu podaje kierunek zgodnie ze wzorem:
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