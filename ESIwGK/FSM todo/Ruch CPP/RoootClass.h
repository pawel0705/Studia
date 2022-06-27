#pragma once


//Akcje
void  Stoj();
void  Biegnij();
void  Zmeczenie();
void  Spoczynek();

class Biegnie;
class Stoi;
class WolnyChod;
class Siedzi;
class RootClass;
class SuperStanBiegnij;
class SuperStanZatrzymajSie;

class RootClass
{

public:
	RootClass(void);
	virtual RootClass* Tick() { return this; };
	virtual RootClass* TimeOut() { return this; };

	//TODO Zdefiniowanie zdarzen
	virtual RootClass* BiegnijKlawisz() { return this; };
	virtual RootClass* ZatrzymajSieKlawisz() { return this; }
public:
	virtual ~RootClass(void);
};

class TimeManager : public RootClass
{
protected:
	int CzasTrwaniaStanu, AktualnaIloscTykniecZegara;
public:
	TimeManager(int _CzasTrwaniaStanu) : CzasTrwaniaStanu(_CzasTrwaniaStanu)
	{
		AktualnaIloscTykniecZegara = 0;
	}
	TimeManager()
	{
		AktualnaIloscTykniecZegara = 0;
	}
	virtual RootClass* Tick()
	{
		//TODO Odliczanie czasu;
		AktualnaIloscTykniecZegara++;

		if (AktualnaIloscTykniecZegara >= CzasTrwaniaStanu)
		{
			AktualnaIloscTykniecZegara = 0;
			return TimeOut();
		}
	}
};

//TODO: Zdefiniowane Stany
class SuperStanZatrzymajSie : public TimeManager {
public:
	SuperStanZatrzymajSie() {

	}

	RootClass* ZatrzymajSieKlawisz();
};

class SuperStanBiegnij : public TimeManager {

public:
	SuperStanBiegnij() {

	}

	RootClass* BiegnijKlawisz();
};

class Stoi : public SuperStanBiegnij
{
public:
	Stoi()
	{
		CzasTrwaniaStanu = 3;
		//TODO: Zdefiniowanie akcji

		Stoj();
	}
	//TODO: Zdefiniowane przejœcia dla danego stanu do innych stanów
	virtual RootClass* TimeOut();
};


class WolnyChod : public SuperStanZatrzymajSie
{
public:
	WolnyChod()
	{
		Zmeczenie();
	}

};

class Biegnie : public SuperStanZatrzymajSie
{
public:
	Biegnie()
	{
		CzasTrwaniaStanu = 5;

		Biegnij();
	}

	virtual RootClass* TimeOut();
};

class Siedzi : public SuperStanBiegnij
{
public:
	Siedzi()
	{
		Spoczynek();
	}
};

