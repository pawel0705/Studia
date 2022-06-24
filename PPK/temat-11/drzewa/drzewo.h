

#ifndef DRZEWO_H    // Jezeli plik nie byl dolaczony, ...
#define DRZEWO_H    // ... to zostanie dolaczony. 
                    // Dzieki temu plik bedzie dolaczony tylko raz.


typedef int T;

/** Deklaracja wezla drzewa.
    @author Ambrozy Kleks
    @date   2018-02-31
*/
struct wezel
{
   T wartosc;
   wezel * pLewy, * pPrawy;
};


// skomentowane deklaracje funkcji:

/** Funkcja wypisujaca na standardowe wyjscie napis "Hello, world!".
    @author Ambrozy Kleks
    @date   2018-02-31
    @params bez parametrow
    @return niczego nie zwraca 
*/
int V = 0;
void helloWorld ();
void dodajRek(wezel*& pRoot, T liczba);
void wypisz(wezel * pRoot,int V);
void usun(wezel *&pRoot);

#endif
