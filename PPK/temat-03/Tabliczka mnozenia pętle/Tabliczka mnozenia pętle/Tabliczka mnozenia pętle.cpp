// Tabliczka mnozenia pętle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;
int n;

int main()
{
	cout << "Program wypisze tabliczke mnozenia. Wpisz liczbe liczb: ";
	cin >> n;
	cout << "   ";
	for (int a = 1; a <= n; a++) {
		cout << a;
		if (a <= 9)
			cout << "  ";

		if (a >= 10)
			cout << " ";
	}
	cout << endl;
	for (int a = 1; a <= n; a++) {
		cout << a;
		if (a <= 9)
			cout << "  ";

		if (a >= 10)
			cout << " ";

		for (int b = 1; b <= n; b++) {
			cout << a * b;
			if ((a * b) <= 9)
				cout << "  ";

			if ((a * b) >= 10)
				cout << " ";

		}
		cout << endl;
	}



	return 0;
}


