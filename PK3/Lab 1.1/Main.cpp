// Lab 1-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dog.h"
using namespace std;

int main()
{
	// constructor test
	Dog koka;
	Dog hugo("Hugo");
	Dog fiona("Bronek", 7, "Briard", 3, 6, true);
	Dog lara = fiona;
	cout << "Dogs created" << endl;
	
	// akcesor test
	hugo.SetBreed("Black russian terrier");
	hugo.SetPower(4);
	koka.SetName("Koka");
	koka.SetPower(-2);

	hugo.PrintInfo();
	koka.PrintInfo();
	
	return 0;
}
