#include "Queen.h"
Queen::Queen(Position _P, COLOR _C, Board* B) : Rook(_P, _C, B), Bishop(_P, _C, B), Piece(_P, _C, B)
{
	sym = ((C == BLACK) ? 'Q' : 'q');
	if (C == BLACK && P.ri == 0 && P.ci == 3)
	{
		moves = 0;
	}
	else if (C == WHITE && P.ri == 7 && P.ci == 3)
	{
		moves = 0;
	}
	else
	{
		moves = 1;
	}
}

void Queen::Draw()
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
	for (int j = C - CDim / 4; j <= C + CDim / 4; j++)
	{
		if (j != C - 1 and j != C + 1)
		{
			gotoRowCol(R - RDim / 3, j);
			color(a);
			cout << f;
		}
	}
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

bool Queen::IsLegalMove(Position E)
{
	if (Rook::IsLegalMove(E) || Bishop::IsLegalMove(E))
	{
		return true;
	}
	return false;
}

Queen::~Queen()
{

}