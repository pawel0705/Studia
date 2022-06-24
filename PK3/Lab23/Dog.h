#pragma once
#include "Breed.h"
class Dog
{
private:
	std::string name;
	Breed &breed; //C3 // add breed field referencing Breed
	
	int age = 0;
	int power = 0;
	bool isMale = true;
	bool isAlive = true;
	char *imageData = nullptr;

	friend std::ostream& operator<< (std::ostream& os, const Dog& foo);

public:
	// konstruktory
	Dog();
	Dog(const Dog &dog);
	Dog(Dog &&dog); //C3 //do zrobienia (konstruektor kradnacy/przenoszacy [move]) 
	Dog(std::string name);
	Dog(std::string name, int age, bool isMale, Breed &breed);
	~Dog();

	// Akcesory - setters
	// Uwaga: dla bardzo obszernych pól sk³adowych SetName(std::string&)
	void SetName(std::string);
	void SetBreed(Breed &breed);
	void SetAge(int);
	void SetImage(char *imageData);

	// Akcesory - getters
	// Uwaga: dla bardzo obszernych pól sk³adowych const std::string GetName()
	std::string GetName() const;
	Breed& GetBreed() const;
	int GetPower() const;
	int GetAggresion() const;
	int GetAge() const;
	char* GetImage() const;

	// Operatory
	Dog& operator= (const Dog& dog); // = default;
	Dog& operator= (Dog&& dog) noexcept; //C3 // = default; 

	Dog& operator++ ();					
	Dog operator++(int);				
	Dog operator+(const Dog &dog); // jeœli samiec i samica i ta sama rasa (ale != null) to powstaje rasowy szczeniak o wieku 0; 
	
	// Pozosta³e metody
	std::string GetInfo();
	void PrintInfo();
	Dog SimulateFightWith(Dog);
	void FightWith(Dog& dog); 
};

