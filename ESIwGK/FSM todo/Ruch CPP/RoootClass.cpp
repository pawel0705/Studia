#include "StdAfx.h"
#include "RoootClass.h"

RootClass::RootClass(void)
{
}

RootClass::~RootClass(void)
{
}


RootClass* Stoi::TimeOut()
{
	//TODO: Przejscie do stanu po upynieciu czasu
	delete this;

	return new Siedzi();
};

RootClass* Biegnie::TimeOut()
{
	delete this;

	return new WolnyChod();
};

RootClass* SuperStanZatrzymajSie::ZatrzymajSieKlawisz() {
	delete this;

	return new Stoi();
}

RootClass* SuperStanBiegnij::BiegnijKlawisz() {
	delete this;

	return new Biegnie();
};
