// Wypisywanie iksa w konsoli.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>

using namespace std;

int n;

int main()
{
	cin >> n;
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if ((i == j) || (j == (n + 1) - i))
			{
				cout << "*";
			}
			else {
				cout << "#";
			}
		}
		cout << endl;
	}
	return 0;
}


