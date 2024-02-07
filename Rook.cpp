#include "Rook.h"
Rook::Rook(Position _P, COLOR _C, Board* B) :Piece(_P, _C, B)
{
	sym = ((C == BLACK) ? 'R' : 'r');
	if (C == BLACK && P.ri == 0 && (P.ci == 0 || P.ci == 7))
	{
		moves = 0;
	}
	else if (C == WHITE && P.ri == 7 && (P.ci == 0 || P.ci == 7))
	{
		moves = 0;
	}
	else
	{
		moves = 1;
	}
}

void Rook::Draw()
{
	int RDim = B->getRDim();
	int CDim = B->getCDim();
	int R1 = P.ri * RDim;
	int C1 = P.ci * CDim;
	int R = P.ri * RDim + RDim / 2;
	int C = P.ci * CDim + CDim / 2;
	int R2 = P.ri * RDim + RDim - 1;
	int C2 = P.ci * CDim + CDim - 1;
	char f = -37;
	int a = ((this->C == BLACK) ? 0 : 15);
	for (int j = C1; j <= C2; j++)
	{
		if (j == C - 2 || j == C || j == C + 2)
		{
			gotoRowCol(R - 1, j);
			color(a);
			cout << f;
		}
	}
	for (int i = C - CDim / 5; i <= C + CDim / 5; i++)
	{
		gotoRowCol(R, i);
		color(a);
		cout << f;
	}
	for (int i = R + RDim / 6; i < R2 - RDim / 6; i++)
	{
		for (int j = C - CDim / 7; j <= C + CDim / 7; j++)
		{
			gotoRowCol(i, j);
			color(a);
			cout << f;
		}
	}
	for (int i = C1 + CDim / 4; i <= C2 - CDim / 4; i++)
	{
		gotoRowCol(R2 - RDim / 6, i);
		color(a);
		cout << f;
	}
}

bool Rook::IsLegalMove(Position E)
{
	if (isHorizontalPathClear(P, E) || isVerticalPathClear(P, E))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Rook::~Rook()
{

}