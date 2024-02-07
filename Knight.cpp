#include "Knight.h"
Knight::Knight(Position _P, COLOR _C, Board* B) :Piece(_P, _C, B)
{
	sym = ((C == BLACK) ? 'H' : 'h');
	if (C == BLACK && P.ri == 0 && (P.ci == 1 || P.ci == 6))
	{
		moves = 0;
	}
	else if (C == WHITE && P.ri == 7 && (P.ci == 1 || P.ci == 6))
	{
		moves = 0;
	}
	else
	{
		moves = 1;
	}
}

void Knight::Draw()
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

	for (int i = R1 + RDim / 5; i < R1 + RDim / 3; i++)
	{
		for (int j = C - CDim / 7; j <= C + CDim / 7; j++)
		{
			gotoRowCol(i, j);
			color(a);
			cout << f;
		}
	}
	for (int i = R1 + RDim / 3; i < R; i++)
	{
		for (int j = C - CDim / 5; j <= C + CDim / 5; j++)
		{
			if (j != C)
			{
				gotoRowCol(i, j);
				color(a);
				cout << f;
			}
		}
	}
	for (int i = C - CDim / 4; i <= C + CDim / 5; i++)
	{
		if (i != C)
		{
			gotoRowCol(R, i);
			color(a);
			cout << f;
		}
	}
	for (int i = R + 1; i < R2 - 1; i++)
	{
		for (int j = C + CDim / 7; j <= C + CDim / 5; j++)
		{
			gotoRowCol(i, j);
			color(a);
			cout << f;
		}
	}
	for (int j = C - CDim / 7; j <= C + CDim / 3; j++)
	{
		gotoRowCol(R2 - 1, j);
		color(a);
		cout << f;
	}
}

bool Knight::IsLegalMove(Position E)
{
	if ((abs(P.ri - E.ri) == 2 and abs(P.ci - E.ci) == 1) || (abs(P.ri - E.ri) == 1 and abs(P.ci - E.ci) == 2))
	{
		if (B->IsApnaPiece(Position{ E.ri,E.ci }))
		{
			return false;
		}
		return true;
	}
	return false;
}

Knight::~Knight()
{

}