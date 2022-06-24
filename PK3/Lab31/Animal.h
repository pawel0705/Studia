#pragma once
#include "Console.h"

class Animal
{
public:
	float x,y;
	float dx=0.0f, dy=0.0f;
	WORD color = 0;

protected:

	std::string name;
	std::string actionText;
	int age = 0;
	bool isMale = true;
	bool isAlive = true;
	char *imageData = nullptr;

public:
	// Constructors and destructor
	Animal();
	Animal(std::string, int, bool, WORD);
	Animal(const Animal &);
	Animal(Animal &&);
	~Animal();
	
	// Akcesory - setters
	void SetName(std::string);
	void SetAge(int);
	void SetImage(char *imageData);

	// Akcesory - getters
	std::string GetName() const;
	WORD GetColor() const;
	int GetAge() const;
	char* GetImage() const;
	bool GetMale() const;

	// Operatory
	Animal& operator= (const Animal& animal); 
	Animal& operator= (Animal&& animal); 
	Animal operator+(const Animal &animal); //for new dog

	// Animal actions ta
	void DoDraw(Console &);
	std::string DoGetInfo();
};

