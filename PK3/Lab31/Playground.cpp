#include "stdafx.h"
#include "Playground.h"
using namespace std;

#define HITBOX 5

#pragma region Constructors
Playground::Playground(Console &console): console(console)
{}

Playground::~Playground()
{}
#pragma endregion


#pragma region Methods: Playground manipulation
void Playground::AddDog(Dog &dog)
{
	if (noOfDogs < MAXDOGS)
		dogs[noOfDogs++] = &dog;
}

// add methods for adding cats and rabbits
void Playground::AddRabbit(Rabbit & rabbit) //adding rabbit
{
	if (noOfRabbits < MAXRABBITS)
		rabbits[noOfRabbits++] = &rabbit;
}

void Playground::AddMole(Mole & mole) //adding mole
{
	if (noOfMoles < MAXMOLES)
		moles[noOfMoles++] = &mole;
}

void Playground::AnimalsDoDraw()
{
	//action for drawing moles
	for (int i = 0; i < noOfMoles; i++)
		moles[i]->DoDraw(console);

	//action for drawing dogs
	for (int i = 0; i < noOfDogs; i++)
		dogs[i]->DoDraw(console);

	//action for drawing rabbits
	for (int i = 0; i < noOfRabbits; i++)
		rabbits[i]->DoDraw(console);
}

void Playground::AnimalsDoAction()
{
	//action for moles
	for (int i = 0; i < noOfRabbits; i++)
		moles[i]->DoAction(console);

	//action for dogs
	for (int i = 0; i<noOfDogs; i++)
		dogs[i]->DoAction(console);

	//action for rabbits
	for (int i = 0; i < noOfRabbits; i++)
		rabbits[i]->DoAction(console);

	//check if dog is aive
	for (int i = 0; i < noOfDogs; i++)
	{
		if(dogs[i]->GetIsAlive() == false) //removing dog from array
		{
			noOfDogs--;
			int tmp = i;
			for (int j = i; j < noOfDogs; j++) 
			{
				Dog *tmp2 = dogs[j];
				dogs[j] = dogs[j + 1];
				dogs[j + 1] = tmp2;
			}
		}
	}
}

void Playground::AnimalsCOllision() //collision with dogs
{

	for (int i = 0; i < noOfDogs; i++)
	{
		for (int j = 0; j < noOfDogs; j++)
		{

			if (i == j) //this is the same dog
				break;
			
			x1 = dogs[i]->x;
			x2 = dogs[j]->x;
			y1 = dogs[i]->y;
			y2 = dogs[j]->y;

			if ((x1-x2>-HITBOX && x1-x2< HITBOX) && (y1 - y2 > -HITBOX && y1 - y2 < HITBOX)) //if collide
			{

				if (dogs[i]->GetMale() == dogs[j]->GetMale()) //fight if same gender
				{
					dogs[i]->FightWith(*dogs[j]);

					if (dogs[i]->GetPower() <= 0)
					{
						dogs[i]->SetIsAlive(false);
						console.DrawRectangleOnBackground((short)x1, (short)y1, 1, 0, BACKGROUND_RED);
					}
					else
					{
						console.DrawRectangleOnBackground((short)x2, (short)y2, 1, 0, BACKGROUND_RED);
						dogs[j]->SetIsAlive(false);
					}
				}
				/*
				else
				{
					if (dogs[i]->GetHaveChild() == true || dogs[j]->GetHaveChild() == true)
						break;
					 //Dog child = *dogs[i] + *dogs[j];

						Dog child("Small Doggy", 0, true, 0, 5);
					AddDog(child);
					dogs[i]->SetHaveChild(true);
					dogs[j]->SetHaveChild(true);
					return;
				}
				*/
			}
		}
	}
	
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

			AnimalsCOllision(); //collision

			AnimalsDoDraw();
			console.CopyPlaygroundToScreen();

		

			lastDrawTickCount = GetTickCount();
		}
	}
}
#pragma endregion

