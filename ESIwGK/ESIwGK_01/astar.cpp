/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
*/

#include "astar.h"

int AStar::closed_nodes_map[N][M];			// mapa terenu zaznaczaj¹ca miejsca które zosta³y ca³kowicie przetworzone przez algorytm A* : 
												//1(miejsce nale¿y do wêz³ów zamkniêtych A*)
int AStar::open_nodes_map[N][M];			// mapa terenu zaznaczaj¹ca miejsca dla których zosta³y wyliczone wartoœci f. 
											//Komórki przechowuj¹ wartoœæ f lub 0(wêze³ nie przetworzony lub na liœcie zamkniêtej)
int AStar::dir_map[N][M];					// mapa rodziców (pozycja rodzica okreœlona za pomoc¹ wartoœci (0-7):
											// -------------->x
											// |
											// | 5 6 7
											// | 4 x 0
											// | 3 2 1
											// |
											//\|/y 



// A-star algorithm.
// zwraca string z drog¹ z punktu startowego do punktu koñcowego - dla ka¿dego ruchu podaje kierunek
// xStar, yStar - punkt pocz¹tkowy
// xFinish, yFinish - punkt koñcowy
// Mapy SIZE_WxSIZE_H opisane s¹ za pomoc¹ koloru RGB (0-255) ( rozmiar wektorów to SIZE_W*SIZE_H*3)
// imap - mapa wp³ywu ( wartoœæ wyp³ywu okreœla kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3))
// hmap - mapa wysokoœci ( wartoœæ wysokoœci okreœla kolor czerowny: SIZE_W*(pozycja_x*3)+(pozycja_y*3)
string AStar::pathFind(int xStart, int yStart, int xFinish, int yFinish,
	std::vector<unsigned char>& imap, std::vector<unsigned char>& hmap, float multi)
{

	static int x, y;

	// Wyzerowanie tablic terenu, które przechowuj¹ informacjê o dzia³aniu algorytmu A* 
	// ( czy dane pozycje zosta³y dodane do lisyty otwartej/zamkniêtej) 
	for (y = 0; y < SIZE_W; ++y)
	{
		for (x = 0; x < SIZE_H; ++x)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	PQN* pq = new  PQN;// Utworzenie listy otwartej (lista priorytetowa : top - zwraca wêze³ o najwiêkszej wartoœci, push - dodaje, pop - usuwa) 

	// Utworzenie wêz³a pocz¹tkowego, wyliczenie dla niego f i dodanie go do listy otwartej
	static Node* n0;
	n0 = new Node(xStart, yStart, 0, 0);
	n0->updatef(xFinish, yFinish, imap[SIZE_W * (xStart * 3) + (yStart * 3)], multi); // ustawia f dla wêz³a n0
	pq->push(*n0); //dodanie wiêz³a do listy otwartej


	x = n0->getxPos();
	y = n0->getyPos();
	open_nodes_map[x][y] = n0->getf(); // zaznaczenie wêz³a pocz¹tkowego na tablicy wêz³ów otwartych

	while (!(pq->empty()))
	{
		static int counterLoop = 0;
		counterLoop++;
		if (counterLoop == 30)
		{
			std::cout << "_";
			counterLoop = 0;
		}
		//Pobranie wêz³a B z listy wêz³ów otwartych
		n0 = new Node(pq->top().getxPos(), pq->top().getyPos(), pq->top().getg(), pq->top().getf());

		x = n0->getxPos(); y = n0->getyPos();

		//Aktualizacja  open_nodes_map i   closed_nodes_map
		pq->pop();
		open_nodes_map[x][y] = 0;
		closed_nodes_map[x][y] = 1;

		//Sprawdzenie czy nie jest to wêze³ koñcowy
		if (x == xFinish && y == yFinish)
		{
			string path = generatePath(xFinish, yFinish, xStart, yStart);
			delete n0;
			while (!pq->empty()) pq->pop();
			return path;
		}

		//Dla 8 s¹siadów wêz³a B
		for (int i = 0; i < dir; i++)
		{

			// A* search
			/*******************************************************************************************************************************
			/* Laboratorium - Zadanie 1a. Zaimplementowaæ pêtle algorytmu A*

			Uwagi:
			- Przy dodawaniu wêz³ów do listy otwartej pomijane s¹ wêz³y spoza mapy, przeszkody (funkcja: przeszkoda), pozycje z mapy wêz³ów zamkniêtych) )
			- Wyliczenie kosztu bie¿¹cego wêz³a (nextg) wymaga aby zosta³ on utworzony z wartoœci¹ kosztu rodzica
			- Wartoœæ f wylicza funkcja updatef
			- Przy dodawaniu wêz³a do listy wêz³ów otwartych nale¿y tak¿e ustawiæ pozycjê rodzica bie¿¹cego wêz³a zgodnie ze wzorem:
			dir_map[pozycja_x_dziecka][pozycja_y_dziecka]=(id_dziecka+dir/2)%dir;
			gdzie dir = 8
			- Id dziecka okreœlane jest zgodnie z:
			------------------------->x
			|
			|   5 6 7
			|   4 x 0
			|   3 2 1
			\|/
			y

			Przy zmianie pozycji z bie¿¹cej na kolejne dzieci mo¿na korzystaæ z tablic okreœlaj¹cych zmianê wartoœci x,y dla poszczególnych wêz³ów potomnych
			dx[dir] i dy[dir] (node.h)

			- Je¿eli na liœcie otwartej jest ju¿ wêze³ o danej pozycji z wiêksz¹ wartoœci¹ f usuwamy wêze³ z listy za pomoc¹ metody DeleteNode, która zwraca now¹ listê wêz³ów

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
//zwraca now¹ listê bez wêz³a o pozycji xdx,ydy
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
