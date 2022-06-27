/*
ESIwGK
Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
*/

#ifndef _NODE_H_
#define _NODE_H_


const int dir = 8; // number of possible directions to go at any position
const int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
const int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };
//		------------------------->x
//		|
//		|   5 6 7
//		|   4 x 0
//		|   3 2 1
//	   \|/
//		y


// dir==4
//const int dx[dir]={1, 0, -1, 0};
//const int dy[dir]={0, 1, 0, -1};

#define Est_EuclidianDistance 0
#define Est_ManhattanDistance 1
#define Est_ChebyshevDistance 2

class Node
{
    int xPos; // current position
    int yPos; // current position
	int dir;  // number of possible directions to go at any position
				// -------------->x
				// |
				// | 5 6 7
				// | 4 x 0
				// | 3 2 1
				// |
				//\|/y 
				//
    int g;  // total distance already travelled to reach the node
    int f;  // smaller f: higher priority
			// f=g+remaining distance estimate

	static int EstimationAlg; // estimate alg (0,1,2)

    public:
		/*
		xp, yp - pozycja wêz³a
		g
		f=g+h
		*/
        Node(int xp, int yp, int g, int f);
    
        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getg() const {return g;}
        int getf() const {return f;}
		int getdir() const { return dir; }

		static void setEstimationAlg(int v){ EstimationAlg = v; }

		/*
		Calculate f.
		xDest, yDest - target position
		infulence - from influence map
		multi
		*/
        void updatef(const int & xDest, const int & yDest, float h, float multi);

        // update g: give better g for going straight instead of diagonally
        void nextg(const int & i);
        
        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest, float h, float multi) const;
};

// Determine priority (in the f queue)
bool operator<(const Node & a, const Node & b);

#endif // !_NODE_H_