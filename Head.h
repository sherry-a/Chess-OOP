#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;
using std::endl;

struct Position
{
	int ri;
	int ci;
};

enum COLOR
{
	BLACK, WHITE
};

void getRowColbyLeftClick(int& rpos, int& cpos);

void gotoRowCol(int rpos, int cpos);

void changeFontSize(int fontsize);

void color(int k);
