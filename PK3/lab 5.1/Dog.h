#pragma once
#include "AnimalSprite.h"
#include "Console.h"

class Dog : public AnimalSprite
{
private:
	const Action actionInfo[5] = {
		{ 1, "thinking", 1, &AnimalSprite::ActionThinking },
		{ 60, "running", 200, &AnimalSprite::ActionMoving },
		{ 20, "pissing", 100, &AnimalSprite::ActionSpecial },
		{ 19, "sleeping", 100, &AnimalSprite::ActionSleeping },
	};
public:
	// konstruktory
	Dog();
	Dog(const Dog &dog);
	Dog(Dog &&dog);
	Dog(std::string name);
	Dog(std::string name, int age, bool isMale, WORD color);
	~Dog();

	// Operatory
	Dog& operator= (const Dog &dog);
	Dog& operator= (Dog &&dog); 

	void SeeOtherAimal(const AnimalSprite& dog, float width, float heigth);
		
	// Dog virtual actions
	virtual std::string DoGetInfo();

	// Action implementation
	Action ActionInfo(int);
	void ActionThinking(Console &console);
	void ActionMoving(Console &console);
	void ActionSpecial(Console &console);
	void ActionSleeping(Console &console);
};

