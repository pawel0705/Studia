/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp�yw�w
*/

#include "astar.h"

int AStar::closed_nodes_map[N][M];			// mapa terenu zaznaczaj�ca miejsca kt�re zosta�y ca�kowicie przetworzone przez algorytm A* : 
												//1(miejsce nale�y do w�z��w zamkni�tych A*)
int AStar::open_nodes_map[N][M];			// mapa terenu zaznaczaj�ca miejsca dla kt�rych zosta�y wyliczone warto�ci f. 
											//Kom�rki przechowuj� warto�� f lub 0(w�ze� nie przetworzony lub na li�cie zamkni�tej)
int AStar::dir_map[N][M];					// mapa rodzic�w (pozycja rodzica okre�lona za pomoc� warto�ci (0-7):
											// -------------->x
											// |
											// | 5 6 7
											// | 4 x 0
											// | 3 2 1
											// |
											//\|/y 



// A-star algorithm.
// zwraca string z drog� z punktu startowego do punktu ko�cowego - dla ka�dego ruchu podaje kierunek
// xStar, yStar - punkt pocz�tkowy
// xFinish, yFinish - punkt ko�cowy
// Mapy SIZE_WxSIZE_H opisane s� za pomoc� koloru RGB (0-255) ( rozmiar wektor�w to SIZE_W*SIZE_H*3)
// imap - mapa wp�ywu ( warto�� wyp�ywu okre�la kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3))
// hmap - mapa wysoko�ci ( warto�� wysoko�ci okre�la kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3)
string AStar::pathFind(int xStart, int yStart, int xFinish, int yFinish,
	std::vector<unsigned char>& imap, std::vector<unsigned char>& hmap, float multi)
{

	static int x, y;

	// Wyzerowanie tablic terenu, kt�re przechowuj� informacj� o dzia�aniu algorytmu A* 
	// ( czy dane pozycje zosta�y dodane do lisyty otwartej/zamkni�tej) 
	for (y = 0; y < SIZE_W; ++y)
	{
		for (x = 0; x < SIZE_H; ++x)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	PQN* pq = new  PQN;// Utworzenie listy otwartej (lista priorytetowa : top - zwraca w�ze� o najwi�kszej warto�ci, push - dodaje, pop - usuwa) 

	// Utworzenie w�z�a pocz�tkowego, wyliczenie dla niego f i dodanie go do listy otwartej
	static Node* n0;
	n0 = new Node(xStart, yStart, 0, 0);
	n0->updatef(xFinish, yFinish, imap[SIZE_W * (xStart * 3) + (yStart * 3)], multi); // ustawia f dla w�z�a n0
	pq->push(*n0); //dodanie wi�z�a do listy otwartej


	x = n0->getxPos();
	y = n0->getyPos();
	open_nodes_map[x][y] = n0->getf(); // zaznaczenie w�z�a pocz�tkowego na tablicy w�z��w otwartych

	while (!(pq->empty()))
	{
		static int counterLoop = 0;
		counterLoop++;
		if (counterLoop == 30)
		{
			std::cout << "_";
			counterLoop = 0;
		}
		//Pobranie w�z�a B z listy w�z��w otwartych
		n0 = new Node(pq->top().getxPos(), pq->top().getyPos(), pq->top().getg(), pq->top().getf());

		x = n0->getxPos(); y = n0->getyPos();

		//Aktualizacja  open_nodes_map i   closed_nodes_map
		pq->pop();
		open_nodes_map[x][y] = 0;
		closed_nodes_map[x][y] = 1;

		//Sprawdzenie czy nie jest to w�ze� ko�cowy
		if (x == xFinish && y == yFinish)
		{
			string path = generatePath(xFinish, yFinish, xStart, yStart);
			delete n0;
			while (!pq->empty()) pq->pop();
			return path;
		}

		//Dla 8 s�siad�w w�z�a B
		for (int i = 0; i < dir; i++)
		{

			// A* search
			/*******************************************************************************************************************************
			/* Laboratorium - Zadanie 1a. Zaimplementowa� p�tle algorytmu A*

			Uwagi:
			- Przy dodawaniu w�z��w do listy otwartej pomijane s� w�z�y spoza mapy, przeszkody (funkcja: przeszkoda), pozycje z mapy w�z��w zamkni�tych) )
			- Wyliczenie kosztu bie��cego w�z�a (nextg) wymaga aby zosta� on utworzony z warto�ci� kosztu rodzica
			- Warto�� f wylicza funkcja updatef
			- Przy dodawaniu w�z�a do listy w�z��w otwartych nale�y tak�e ustawi� pozycj� rodzica bie��cego w�z�a zgodnie ze wzorem:
			dir_map[pozycja_x_dziecka][pozycja_y_dziecka]=(id_dziecka+dir/2)%dir;
			gdzie dir = 8
			- Id dziecka okre�lane jest zgodnie z:
			------------------------->x
			|
			|   5 6 7
			|   4 x 0
			|   3 2 1
			\|/
			y

			Przy zmianie pozycji z bie��cej na kolejne dzieci mo�na korzysta� z tablic okre�laj�cych zmian� warto�ci x,y dla poszczeg�lnych w�z��w potomnych
			dx[dir] i dy[dir] (node.h)

			- Je�eli na li�cie otwartej jest ju� w�ze� o danej pozycji z wi�ksz� warto�ci� f usuwamy w�ze� z listy za pomoc� metody DeleteNode, kt�ra zwraca now� list� w�z��w

			***************************************************************************/

			//**********************************************************************************

			int xdx = x + dx[i];
			int xdy = y + dy[i];

			if (xdx >= 0 && xdx < SIZE_W && xdy >= 0 && xdy < SIZE_H && !closed_nodes_map[xdx][xdy] && !przeszkoda(imap, x, y, xdx, xdy) && !przeszkoda(hmap, x, y, xdx, xdy))
			{
				Node m0(xdx, xdy, n0->getg(), n0->getf());
				m0.nextg(i);
				auto ch = m0.estimate(xFinish, yFinish, imap[xdx, xdy], 1.0f);
				m0.updatef(xdx, xdy, ch, 1.0f);


				if (open_nodes_map[xdx][xdy] == 0)
				{
					pq->push(m0);
					open_nodes_map[xdx][xdy] = m0.getf();
					dir_map[xdx][xdy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][xdy] > m0.getf())
				{
					pq = DeleteNode(pq, xdx, xdy);
				}
			}
		}

		closed_nodes_map[x][y] = 1;
		open_nodes_map[x][y] = 0;
		delete n0;
	}

	return ""; // no route found
}

/*
//zwraca now� list� bez w�z�a o pozycji xdx,ydy
*/
PQN* AStar::DeleteNode(PQN* pq, int xdx, int ydy)
{
	PQN* pq2 = new PQN;

	while ((pq->size() != 0) && (!(pq->top().getxPos() == xdx && pq->top().getyPos() == ydy)))
	{
		pq2->push(pq->top());
		pq->pop();
	}

	pq->pop(); // remove the wanted node


	if (pq->size() < pq2->size())
	{
		PQN* tmp = pq;
		pq = pq2;
		pq2 = tmp;
	}

	// empty the larger size pq to the smaller one
	while (!pq2->empty())
	{
		pq->push(pq2->top());
		pq2->pop();
	}
	delete pq2;
	return pq;
}


// generate the path from finish to start
// by following the directions
string AStar::generatePath(int xFinish, int yFinish, int xStart, int yStart)
{
	string path = "";
	static int j;
	string c;
	while (!(xFinish == xStart && yFinish == yStart))
	{
		j = dir_map[xFinish][yFinish];
		c = '0' + (j + dir / 2) % dir;
		path = c + path;
		xFinish += dx[j];
		yFinish += dy[j];
	}
	return path;
}
