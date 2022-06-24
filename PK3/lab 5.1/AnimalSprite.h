#pragma once
#include "stdafx.h"
#include "Console.h"
#include "Animal.h"
#include "Sprite.h"
#include <string>

class AnimalSprite : public Animal, public Sprite //C5 Multi-inheritance Animal+Sprite
{
public:
	AnimalSprite();
	AnimalSprite(std::string, int, bool, WORD);
	AnimalSprite(const AnimalSprite &);
	AnimalSprite(AnimalSprite &&);
	~AnimalSprite();

	AnimalSprite& operator= (const AnimalSprite& animal);
	AnimalSprite& operator= (AnimalSprite&& animal);

	virtual void DoDraw(Console &);
	virtual void DoAction(Console &);
	virtual void SeeOtherAimal(const AnimalSprite& animal, float width, float height) = 0;
};