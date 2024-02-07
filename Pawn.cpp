#include "Pawn.h"
Pawn::Pawn(Position _P, COLOR _C, Board* B) :Piece(_P, _C, B)
{
	sym = ((C == BLACK) ? 'P' : 'p');
	if (C == BLACK && P.ri == 1)
	{
		moves = 0;
	}
	else if (C == WHITE && P.ri == 6)
	{
		moves = 0;
	}
	else
	{
		moves = 1;
	}
}

void Pawn::Draw()
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
	gotoRowCol(R - RDim / 6, C);
	color(a);
	cout << f;
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

bool Pawn::IsLegalMove(Position E)
{
	if (C == WHITE)
	{
		if ((P.ri - E.ri == 1) && abs(P.ci - E.ci) == 1 && B->IsDushmanPiece(Position{ E.ri,E.ci }))
		{
			return true;
		}
		if (P.ri == 6)
		{
			if (((P.ri - E.ri) <= 2 and (P.ri - E.ri) > 0) and (P.ci == E.ci))
			{
				if (B->IsAnyPiece(Position{ E.ri, E.ci }) || B->IsAnyPiece(Position{ ((P.ri - E.ri == 1) ? E.ri : E.ri + 1),E.ci }))
				{
					return false;
				}
				return true;
			}
		}
		else
		{
			if (((P.ri - E.ri) == 1 and (P.ci == E.ci)))
			{
				if (B->IsAnyPiece(Position{ E.ri, E.ci }))
				{
					return false;
				}
				return true;
			}
		}
	}
	else if (C == BLACK)
	{
		if ((E.ri - P.ri == 1) && abs(E.ci - P.ci) == 1 && B->IsDushmanPiece(Position{ E.ri,E.ci }))
		{
			return true;
		}
		if (P.ri == 1)
		{
			if (((E.ri - P.ri) <= 2 and (E.ri - P.ri) > 0) and (E.ci == P.ci))
			{
				if (B->IsAnyPiece(Position{ E.ri, E.ci }) || B->IsAnyPiece(Position{ ((E.ri - P.ri == 1) ? E.ri : E.ri - 1),E.ci }))
				{
					return false;
				}
				return true;
			}
		}
		else
		{
			if (((E.ri - P.ri) == 1 and (P.ci == E.ci)))
			{
				if (B->IsAnyPiece(Position{ E.ri, E.ci }))
				{
					return false;
				}
				return true;
			}
		}
	}
	return false;
}

Pawn::~Pawn()
{

}