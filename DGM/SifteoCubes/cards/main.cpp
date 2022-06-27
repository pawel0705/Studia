#include <sifteo.h>
#include "assets.gen.h"

using namespace Sifteo;

// liczba kostek w grze
static const unsigned gNumCubes = 5;
Random gRandom;

// flaga czy jesteśmy w grze
bool inMenu = true;
bool inGame = false;

//obiekt zajmujący się wszelkimi zasobami
static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(GameAssets);

//Adnotacje
static Metadata M = Metadata()
						.title("MojaPierwszaAplikacja")
						.package("MojaPierwszaAplikacja.mobiletech.pl.polsl", "1.0")
						//1.0 to minimalna wersja SDK
						.cubeRange(gNumCubes) //zakres wymaganych kości
						.icon(Icon);		  //ikonka naszej aplikacji, koniecznie 96x96p

CubeID middleCubeID = 0; // id głównej kostki
static VideoBuffer vid[gNumCubes];

void wait(double miliseconds)
{
	TimeDelta duration(0.0);
	SystemTime start = SystemTime::now();

	duration = SystemTime::now() - start;
	while (duration.milliseconds() < miliseconds)
	{
		duration = SystemTime::now() - start;
		System::paint();
	}
}

// manager kostek
class CubeListener
{
public:
	void install()
	{
		Events::cubeTouch.set(&CubeListener::onTouch, this);
		Events::neighborAdd.set(&CubeListener::onNeighborAdd, this);
		Events::neighborRemove.set(&CubeListener::onNeighborRemove, this);
	}

private:
	struct Card
	{
		int cardId;
		const char *name;
	};

	bool lookingForPair = false; // czy szukamy pary
	int lastTouchedId = -1;		 // id ostatnio dotkniętej kostki

	bool showingCards = false;

	int centerCardUsed = 0;
	int failCount = 0;

	int maxFails = 4;
	Card cards[9] = {{1, "circle"},
					 {2, "rectangle"},
					 {3, "rectangle"},
					 {4, "circle"},
					 {5, "star"},
					 {6, "triangle"},
					 {7, "triangle"},
					 {8, "umbrella"},
					 {9, "umbrella"}};

	bool discovered[9] = {};

	//	pozycja kostki 1-9 to id karty
	int getCardId(CubeID cubeId)
	{

		if (cubeId == middleCubeID)
		{
			return 5;
		}

		Neighborhood neighbourhood(middleCubeID);
		if (neighbourhood.hasNeighborAt(LEFT)) // position: 4
		{
			CubeID id = neighbourhood.cubeAt(LEFT);
			if (cubeId == id)
			{
				return 4;
			}

			Neighborhood neighbourhood2(id);
			if (neighbourhood2.hasNeighborAt(TOP)) //position: 1
			{
				CubeID id = neighbourhood2.cubeAt(TOP);

				if (cubeId == id)
				{
					return 1;
				}
			}

			if (neighbourhood2.hasNeighborAt(BOTTOM)) //position: 3 // 7?
			{
				CubeID id = neighbourhood2.cubeAt(BOTTOM);

				if (cubeId == id)
				{
					return 7;
				}
			}
		}

		if (neighbourhood.hasNeighborAt(TOP)) // position: 2
		{
			CubeID id = neighbourhood.cubeAt(TOP);

			if (cubeId == id)
			{
				return 2;
			}

			Neighborhood neighbourhood2(id);
			if (neighbourhood2.hasNeighborAt(LEFT)) //position: 1
			{
				CubeID id = neighbourhood2.cubeAt(LEFT);

				if (cubeId == id)
				{
					return 1;
				}
			}

			if (neighbourhood2.hasNeighborAt(RIGHT)) //position: 3
			{
				CubeID id = neighbourhood2.cubeAt(RIGHT);

				if (cubeId == id)
				{
					return 3;
				}
			}
		}

		if (neighbourhood.hasNeighborAt(BOTTOM)) // position: 8
		{
			CubeID id = neighbourhood.cubeAt(BOTTOM);

			if (cubeId == id)
			{
				return 8;
			}

			Neighborhood neighbourhood2(id);
			if (neighbourhood2.hasNeighborAt(LEFT)) //position: 7
			{
				CubeID id = neighbourhood2.cubeAt(LEFT);

				if (cubeId == id)
				{
					return 7;
				}
			}

			if (neighbourhood2.hasNeighborAt(RIGHT)) //position: 9
			{
				CubeID id = neighbourhood2.cubeAt(RIGHT);

				if (cubeId == id)
				{
					return 9;
				}
			}
		}

		if (neighbourhood.hasNeighborAt(RIGHT)) // position: 6
		{
			CubeID id = neighbourhood.cubeAt(RIGHT);

			if (cubeId == id)
			{
				return 6;
			}

			Neighborhood neighbourhood2(id);
			if (neighbourhood2.hasNeighborAt(TOP)) //position: 3
			{
				CubeID id = neighbourhood2.cubeAt(TOP);

				if (cubeId == id)
				{
					return 3;
				}
			}

			if (neighbourhood2.hasNeighborAt(BOTTOM)) //position: 9
			{
				CubeID id = neighbourhood2.cubeAt(BOTTOM);

				if (cubeId == id)
				{
					return 9;
				}
			}
		}

		return -1; // poza planszą 3x3
	}

	void showCardOnCube(CubeID cubeID)
	{
		int cardID = getCardId(cubeID);
		if (discovered[cardID - 1])
		{
			vid[cubeID].bg0.image(vec(0, 0), CardDiscovered);
			return;
		}

		Card &card = cards[cardID - 1];
		//LOG("Kostka #%d\n\tkarta o ID = %d\n\tfigura - \"%s\"\n", static_cast<int>(cubeID), cardID, card.name);

		switch (card.cardId)
		{
		case 1:
		case 4:
			vid[cubeID].bg0.image(vec(0, 0), CardCircle);
			break;
		case 2:
		case 3:
			vid[cubeID].bg0.image(vec(0, 0), CardRectangle);
			break;
		case 6:
		case 7:
			vid[cubeID].bg0.image(vec(0, 0), CardTriangle);
			break;
		case 8:
		case 9:
			vid[cubeID].bg0.image(vec(0, 0), CardUmbrella);
			break;
		}
	}

	void hideCardOnCube(CubeID cubeID)
	{
		int cardID = getCardId(cubeID);
		if (discovered[cardID - 1])
		{
			vid[cubeID].bg0.image(vec(0, 0), CardDiscovered);
		}
		else
		{
			vid[cubeID].bg0.image(vec(0, 0), CardQuestion);
		}
	}

	void showDiscoveredCardOnCube(CubeID cubeID)
	{
		vid[cubeID].bg0.image(vec(0, 0), CardDiscovered);
	}

	void victory()
	{
		vid[middleCubeID].bg0.image(vec(0, 0), CardDiscovered);
	}

	void defeat()
	{
		for(int i = 0;i < gNumCubes;++i)
		{
			vid[i].bg0.image(vec(0, 0), BadLocation);
		}
	}

	void onTouch(unsigned id)
	{

		CubeID cube(id);
		LOG("Touch event on cube #%d, state=%d\n", id, cube.isTouching());

		//robimy akcję tylko przy puszczeniu?
		if (!cube.isTouching())
		{
			if (inGame)
			{
				if (id == 0) // główna kostka
				{
					//LOG("Odkryj wszystkie karty TODO\n");

					if (this->centerCardUsed < 2)
					{
						this->centerCardUsed++;
						for (CubeID i = 1; i < 5; ++i)
						{
							showCardOnCube(i);
						}

						wait(2000);

						for (CubeID i = 1; i < 5; ++i)
						{
							hideCardOnCube(i);
						}

						this->lastTouchedId = -1;
					}

					return;
				}

				if (this->lastTouchedId == id) // nie chcemy interakcji z kostką która jest już odkryta
				{
					return;
				}

				// ukazanie karty
				showCardOnCube(id);

				if (lookingForPair)
				{
					//ukazanie potencjalnej pary przez min. 1s
					wait(1000);

					Card &card1 = cards[getCardId(lastTouchedId) - 1];
					Card &card2 = cards[getCardId(id) - 1];

					String<16> str1;
					str1 << card1.name;

					String<16> str2;
					str2 << card2.name;

					if (str1 == str2)
					{
						// udalo sie
						discovered[card1.cardId - 1] = true;
						discovered[card2.cardId - 1] = true;

						showDiscoveredCardOnCube(lastTouchedId);
						showDiscoveredCardOnCube(id);

						bool victory = true;
						for(int i = 0; i < 9; ++i)
						{
							if(i == 4) //cener card
							{
								continue;
							}
							if(!discovered[i])
							{
								victory = false;
								break;
							}
						}

						if(victory)
						{
							LOG("\tWygrana!!! :D .\n");
							this->victory();
						}

					}
					else
					{
						//nie udalo sie
						
						hideCardOnCube(lastTouchedId);
						hideCardOnCube(id);

						if(++failCount == maxFails)
						{
							LOG("\tPrzegrana :(.\n");

							this->defeat();
						}

					}
					this->lookingForPair = false;
					this->lastTouchedId = -1;
				}
				else
				{
					this->lookingForPair = true;
					this->lastTouchedId = id;
				}
			}
			else if (inMenu)
			{
				LOG("Ustawiamy poziom trudnosci\n");
				if (id == 1)
				{
					//easy
					maxFails = 5;
				}
				else if (id == 0)
				{
					//medium
					maxFails = 4;
				}
				else
				{
					//hard
					maxFails = 3;
				}

				inMenu = false;
			}
		}
	}

	// odłączamy kostkę
	void onNeighborRemove(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
	{
		if (!inGame)
		{
			return;
		}

		// TODO jakiś ekran ekran na odłączonej kostce o złej pozycji
		LOG("Neighbor Remove: %02x:%d - %02x:%d\n", firstID, firstSide, secondID, secondSide);

		// id == 0 to główna kostka ona jest zawsze OK
		if (firstID != 0)
		{
			int cardIdFirst = getCardId(firstID);

			if (cardIdFirst == -1)
			{
				vid[firstID].bg1.image(vec(0, 0), Background);
				vid[firstID].bg0.image(vec(0, 0), BadLocation);
			}
		}

		if (secondID != 0)
		{
			int cardIdSecond = getCardId(secondID);

			if (cardIdSecond == -1)
			{
				vid[secondID].bg1.image(vec(0, 0), Background);
				vid[secondID].bg0.image(vec(0, 0), BadLocation);
			}
		}
	}

	// dołączamy kostkę
	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
	{
		if (!inGame)
		{
			return;
		}

		// sprawdzamy pozycję i ustawiamy karty
		LOG("Neighbor Add: %02x:%d - %02x:%d\n", firstID, firstSide, secondID, secondSide);

		if (firstID != 0)
		{
			int cardIdFirst = getCardId(firstID);
			LOG("Card ID First = %d\n", cardIdFirst);
			if (cardIdFirst != -1)
			{
				vid[firstID].bg1.image(vec(0, 0), Background);
				if (discovered[cardIdFirst - 1])
				{
					vid[firstID].bg0.image(vec(0, 0), CardDiscovered);
				}
				else
				{
					vid[firstID].bg0.image(vec(0, 0), CardQuestion);
				}
			}
		}

		if (secondID != 0)
		{
			int cardIdSecond = getCardId(secondID);
			LOG("Card ID Second = %d\n", cardIdSecond);
			if (cardIdSecond != -1)
			{
				vid[secondID].bg1.image(vec(0, 0), Background);
				if (discovered[cardIdSecond - 1])
				{
					vid[secondID].bg0.image(vec(0, 0), CardDiscovered);
				}
				else
				{
					vid[secondID].bg0.image(vec(0, 0), CardQuestion);
				}
			}
		}
	}
};

void initVid()
{
	int id;
	for (id = 0; id < gNumCubes; id++)
	{
		vid[id].initMode(BG0_SPR_BG1);
		vid[id].attach(id);
		vid[id].bg1.image(vec(0, 0), Background);
		vid[id].bg0.image(vec(0, 0), CardQuestion);
	}
}

//
//	cubes positions:
//
//	///////////			///////////			///////////
//	//       //			//       //			//       //
//	//   1   //			//   2   //			//   3   //
//	//       //			//       //			//       //
//	///////////			///////////			///////////
//
//						  center
//	///////////			///////////			///////////
//	//       //			//       //			//       //
//	//   4   //			//   5   //			//   6   //
//	//       //			//       //			//       //
//	///////////			///////////			///////////
//
//
//	///////////			///////////			///////////
//	//       //			//       //			//       //
//	//   7   //			//   8   //			//   9   //
//	//       //			//       //			//       //
//	///////////			///////////			///////////

bool checkIfCubesAreInRectangle()
{
	bool cubesOnPositions[9] = {};
	cubesOnPositions[5 - 1] = true;

	Neighborhood neighbourhood(middleCubeID);
	if (neighbourhood.hasNeighborAt(LEFT)) // position: 4
	{
		cubesOnPositions[4 - 1] = true;

		CubeID id = neighbourhood.cubeAt(LEFT);
		Neighborhood neighbourhood2(id);

		if (neighbourhood2.hasNeighborAt(TOP)) //position: 1
		{
			cubesOnPositions[1 - 1] = true;
		}
		if (neighbourhood2.hasNeighborAt(BOTTOM)) //position: 7
		{
			cubesOnPositions[7 - 1] = true;
		}
	}

	if (neighbourhood.hasNeighborAt(TOP)) // position: 2
	{
		cubesOnPositions[2 - 1] = true;

		CubeID id = neighbourhood.cubeAt(TOP);
		Neighborhood neighbourhood2(id);

		if (neighbourhood2.hasNeighborAt(LEFT)) //position: 1
		{
			cubesOnPositions[1 - 1] = true;
		}
		if (neighbourhood2.hasNeighborAt(RIGHT)) //position: 3
		{
			cubesOnPositions[3 - 1] = true;
		}
	}

	if (neighbourhood.hasNeighborAt(BOTTOM)) // position: 8
	{
		cubesOnPositions[8 - 1] = true;

		CubeID id = neighbourhood.cubeAt(BOTTOM);
		Neighborhood neighbourhood2(id);

		if (neighbourhood2.hasNeighborAt(LEFT)) //position: 7
		{
			cubesOnPositions[7 - 1] = true;
		}
		if (neighbourhood2.hasNeighborAt(RIGHT)) //position: 9
		{
			cubesOnPositions[9 - 1] = true;
		}
	}

	if (neighbourhood.hasNeighborAt(RIGHT)) // position: 6
	{
		cubesOnPositions[6 - 1] = true;

		CubeID id = neighbourhood.cubeAt(RIGHT);
		Neighborhood neighbourhood2(id);

		if (neighbourhood2.hasNeighborAt(TOP)) //position: 3
		{
			cubesOnPositions[3 - 1] = true;
		}
		if (neighbourhood2.hasNeighborAt(BOTTOM)) //position: 9
		{
			cubesOnPositions[9 - 1] = true;
		}
	}

	int connectedCubesCount = 0;
	for (int i = 0; i < 9; ++i)
	{
		if (cubesOnPositions[i])
		{
			connectedCubesCount++;
		}
	}

	return connectedCubesCount == gNumCubes ? true : false;
}

void resetCubes()
{
	// główna kostka
	vid[middleCubeID].initMode(BG0_SPR_BG1);
	vid[middleCubeID].attach(middleCubeID);
	vid[middleCubeID].bg1.image(vec(0, 0), Background);
	vid[middleCubeID].bg0.image(vec(0, 0), CardStar);
}

void showMenu()
{
	for (int id = 0; id < 3; ++id)
	{
		vid[id].initMode(BG0_ROM);
		vid[id].attach(id);
	}
	const char *str1 = "EASY";
	vid[0].bg0rom.text(vec(6, 7), str1);

	const char *str2 = "MEDIUM";
	vid[1].bg0rom.text(vec(5, 7), str2);

	const char *str3 = "HARD";
	vid[2].bg0rom.text(vec(6, 7), str3);
}

void showCenterCubeInstruction()
{
	vid[1].initMode(BG0_SPR_BG1);
	vid[1].attach(1);
	vid[1].bg1.image(vec(0, 0), Background);
	vid[1].bg0.image(vec(0, 0), CardQuestion);

	vid[2].initMode(BG0_SPR_BG1);
	vid[2].attach(2);
	vid[2].bg1.image(vec(0, 0), Background);
	vid[2].bg0.image(vec(0, 0), CardQuestion);

	const char* str = "PLACE IN CENTER";
	vid[0].bg0rom.text(vec(1, 7), str);
}

void main()
{
	initVid();

	static CubeListener cubes;

	cubes.install();

	while (1)
	{
		showMenu();
		while (inMenu)
		{
			System::paint();
		}
		
		showCenterCubeInstruction();

		while(!checkIfCubesAreInRectangle())
		{
			System::paint();
		}

		resetCubes();
		inGame = true;

		while(inGame)
		{
			System::paint();
		}
	}
}