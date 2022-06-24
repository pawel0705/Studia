#include "stdafx.h"
#include "Playground.h"
using namespace std;

#define HITBOX 5
#define BORDERMAP 2

#pragma region Constructors
Playground::Playground(Console &console): console(console)
{}

Playground::~Playground()
{}
#pragma endregion


#pragma region Methods: Playground manipulation
void Playground::AddAnimal(AnimalSprite &animal)
{
	if (noOfAnimals < MAXANIMALS)
		animals[noOfAnimals++] = &animal;
}

void Playground::AnimalsDoDraw()
{
	for (int i = 0; i < noOfAnimals; i++)
		animals[i]->DoDraw(console);
}

void Playground::AnimalsDoAction()
{
	for (int i = 0; i<noOfAnimals; i++)
		animals[i]->DoAction(console);
}

void Playground::Simulate()
{
	DWORD currentTickCount;
	DWORD lastDrawTickCount = 0;

	while (!console.KeyPressed(VK_ESCAPE))
	{
		currentTickCount = GetTickCount();				//tickcount in ms

		if (currentTickCount - lastDrawTickCount > 20)	// 50 frames per second
		{
			AnimalsDoAction();
			console.CopyBackgroundToPlayground();
			Collision();
			AnimalsDoDraw();
			console.CopyPlaygroundToScreen();

			lastDrawTickCount = GetTickCount();
		}
	}
}
#pragma endregion

void Playground::Collision()
{
	//for (int i=0; i<noOfAnimals; i++)
	//if Collision();
	//animal->SeeOttherAnimal(AlimalisCollision);

	for (int i = 0; i < noOfAnimals; i++)
	{
		for (int j = 0; j < noOfAnimals; j++)
		{
			if (j == i) 
				break;

			if (animals[i]->DoGetInfo()[0] == animals[j]->DoGetInfo()[0]) //break if this is the same animal, for example animal[i].DoGetInfo()[0]--> 'D' ==? animal[j].DoGetInfo()[0]-->'C'
				break;

			float x1 = animals[i]->x;
			float x2 = animals[j]->x;
			float y1 = animals[i]->y;
			float y2 = animals[j]->y;

			if (BORDERMAP > x1 || BORDERMAP > x2)
				break;

			if (console.GetWidth() - BORDERMAP < x1 || console.GetWidth() - BORDERMAP < x2)
				break;

			if (BORDERMAP > y1 || BORDERMAP > y2)
				break;

			if (console.GetHeight() - BORDERMAP < y1 || console.GetHeight() - BORDERMAP < y2)
				break;


			if ((x1 - x2 > -HITBOX && x1 - x2< HITBOX) && (y1 - y2 > -HITBOX && y1 - y2 < HITBOX))
			{
				animals[i]->SeeOtherAimal(*animals[j], console.GetWidth(), console.GetHeight());
				animals[j]->SeeOtherAimal(*animals[i], console.GetWidth(), console.GetHeight());
			}

		}
	}
}