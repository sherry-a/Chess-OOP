#include "Board.h"
#include <iostream>
using namespace std;


int mainss()
{
	for (int i = 0; i < 256; i++)
	{
		color(i);
		cout << i << ": Hello World" << endl;
	}
	return 0;
}

int mains()
{
	int c;
	while (true)
	{
		c = _getch();
		cout << c << endl << endl;
	}
}

int main()
{
	Board B;
	changeFontSize(10);
	B.Play();
	return 0;
}