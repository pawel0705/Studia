/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
*/


#include "node.h"
#include <string>
#include <math.h>

int Node::EstimationAlg = 0;

// Determine priority (in the f queue)
bool operator<(const Node& a, const Node& b)
{
	return a.getf() > b.getf();
}

/*
xp, yp - pozycja wêz³a
g
_f= g+h
*/
Node::Node(int xp, int yp, int _g, int _f)
{
	xPos = xp;
	yPos = yp;
	g = _g;
	f = _f;

}

/*
Calculate f.
xDest, yDest - target position
infulence - from influence map
multi
*/
void Node::updatef(const int& xDest, const int& yDest, float infulence, float multi)
{
	f = g + estimate(xDest, yDest, infulence, multi) * 10; //A*
}
/*
Zwraca koszt kolejnego s¹siada/dziecka.
*/
void Node::nextg(const int& i) // i: next cell
{
	g += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

// Estimation function for the remaining distance to the goal.
// influence  - from influence map
//multi - mno¿nik
const int& Node::estimate(const int& xDest, const int& yDest, float influence, float multi) const
{

	/*******************************************************************************************************************************
	/* Laboratorium - Zadanie 1b. Obliczyæ heurystykê 2 pozosta³ymi metodami
	***************************************************************************/

	static int d = 0;

	static int xd, yd;
	xd = xDest - xPos;
	yd = yDest - yPos;


	if (EstimationAlg == Est_EuclidianDistance)
	{
		long double a = pow(xd, 2) + pow(yd, 2);
		d = static_cast<int>(sqrt(a));
	}
	else if (EstimationAlg == Est_ManhattanDistance)
	{
		// dodano
		d = abs(xd) + abs(yd);
	}
	else if (EstimationAlg == Est_ChebyshevDistance)
	{
		// dodano
		d = std::max(abs(xd), abs(yd));
	}

	d *= 1 + influence * multi;

	return d;

}
