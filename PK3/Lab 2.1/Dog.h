#define _CRT_SECURE_NO_WARNINGS
#pragma once

class Dog
{
private:
	std::string name;
	std::string breed;
	int power = 0;
	int aggresion = 0;
	int age = 0;
	bool isMale = true;
	bool isAlive = true;
	char *imageData = nullptr;

	friend std::ostream& operator<< (std::ostream& os, const Dog& foo);

public:
	// konstruktory
	Dog();
	Dog(const Dog &dog);
	Dog(std::string name);
	Dog(std::string name, int age, std::string breed, int power, int aggresion, bool isMale);
	~Dog();

	// Akcesory - setters
	// Uwaga: dla bardzo obszernych p�l sk�adowych SetName(std::string&)
	void SetName(std::string);
	void SetBreed(std::string);
	void SetPower(int);
	void SetAggresion(int);
	void SetAge(int);
	void SetImage(char *imageData);

	// Akcesory - getters
	// Uwaga: dla bardzo obszernych p�l sk�adowych const std::string GetName()
	std::string GetName() const;
	std::string GetBreed() const;
	int GetPower() const;
	int GetAggresion() const;
	int GetAge() const;
	char* GetImage() const;

	// Operatory
/*	Dog& operator= (const Dog& dog); // = default;
	Dog& operator++ ();					// prefix ++Dog; postarzeje si� o rok	(to samo co dog+=1)
	Dog operator++ (int);				// postfix Dog++; postarzeje si� o rok; rezultatem operacji jest prywatna, origynalne warto�ci operandu !!!
	Dog operator+(const Dog &dog);		// je�li samiec i samica i ta sama rasa (ale != null) to powstaje rasowy szczeniak o wieku 0; 
	*/									// je�li r�ne rasy lub ojciec albo matka  nierasowi, powstaje nierasowy
	
	//Operatory
	Dog& operator= (const Dog& dog) ;
	Dog& operator++ ();
	Dog operator++ (int);
	Dog operator+(const Dog &dog);

	// Pozosta�e metody
	std::string GetInfo();
	void PrintInfo();
	Dog SimulateFightWith(Dog);
	void FightWith(Dog& dog);
};

