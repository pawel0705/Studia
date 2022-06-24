


#include <iostream>
#include <vector>

#include "../../memory-leaks/debug_new.h"
#include "drzewo.h"

int main (int ile, char ** params)
{
	wezel * pKorzen = 0;
	dodajRek(pKorzen, 10);
	dodajRek(pKorzen, 2);
	dodajRek(pKorzen, 18);
	dodajRek(pKorzen, 12);
	wypisz(pKorzen, V);
	usun(pKorzen);
//helloWorld(); 
   
   // wyciek pamieci na probe:
   
 
   
   return 0;
} 


