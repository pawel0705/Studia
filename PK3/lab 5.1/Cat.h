
#pragma once
#include "AnimalSprite.h"
#include "Console.h"
#include <string>

class Cat : public AnimalSprite
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
	Cat();
	Cat(const Cat &cat);
	Cat(Cat &&cat);
	Cat(std::string name);
	Cat(std::string name, int age, bool isMale, WORD color);
	~Cat();

	// Operatory
	Cat& operator= (const Cat &cat);
	Cat& operator= (Cat &&cat);

	// Cat virtual actions
	virtual std::string DoGetInfo();

	// Action implementation
	Action ActionInfo(int);
	void ActionThinking(Console &console);
	void ActionMoving(Console &console);
	void ActionSpecial(Console &console);
	void ActionSleeping(Console &console);

	void SeeOtherAimal(const AnimalSprite& animal, float width, float heigth); 
};

