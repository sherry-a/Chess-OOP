#include "Bishop.h"
Bishop::Bishop(Position _P, COLOR _C, Board* B) :Piece(_P, _C, B)
{
	sym = ((C == BLACK) ? 'B' : 'b');
	if (C == BLACK && P.ri == 0 && (P.ci == 2 || P.ci == 5))
	{
		moves = 0;
	}
	else if (C == WHITE && P.ri == 7 && (P.ci == 2 || P.ci == 5))
	{
		moves = 0;
	}
	else
	{
		moves = 1;
	}
}

void Bishop::Draw()
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
	gotoRowCol(R - RDim / 3, C);
	color(a);
	cout << f;
	for (int i = C - CDim / 4; i <= C + CDim / 4; i++)
	{
		gotoRowCol(R - RDim / 6, i);
		color(a);
		cout << f;
	}
	for (int i = R - RDim / 5; i < R2 - RDim / 6; i++)
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

bool Bishop::IsLegalMove(Position E)
{
	if (isDiagonalPathClear(P, E))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Bishop::~Bishop()
{

}