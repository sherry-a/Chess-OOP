#include "Piece.h"
Piece::Piece(Position _P, COLOR _C, Board* _B)
{
	P = _P;
	C = _C;
	B = _B;
	IsMoving = false;
}

bool Piece::IsPawnPromotion()
{
	if (C == BLACK and P.ri == 7 and sym == 'P')
	{
		return true;
	}
	else if (C == WHITE and P.ri == 0 and sym == 'p')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Piece::Draw()
{
}

void Piece::ChangePos(Position _P)
{
	P = _P;
	if (IsMoving)
	{
		moves++;
	}
}

COLOR Piece::GetColor()
{
	return C;
}

char Piece::getSym()
{
	return sym;
}

bool Piece::isHorizontal(Position S, Position E)
{
	return (S.ri == E.ri and (abs(S.ci - E.ci) != 0));
}

bool Piece::isVertical(Position S, Position E)
{
	return (S.ci == E.ci and (abs(S.ri - E.ri) != 0));
}

bool Piece::isDiagonal(Position S, Position E)
{
	return ((abs(S.ri - E.ri) == abs(S.ci - E.ci)) and (abs(S.ri - E.ri) != 0) and (abs(S.ci - E.ci) != 0));
}

bool Piece::isHorizontalPathClear(Position S, Position E)
{
	if (isHorizontal(S, E) == true)
	{
		if (S.ci < E.ci)
		{
			for (int C = S.ci + 1; C <= E.ci; C++)
			{
				if (S.ri == E.ri && C == E.ci && B->IsDushmanPiece(Position{ S.ri,C }))
				{
					return true;
				}
				if (B->GetPiece(S.ri, C) != nullptr)
				{
					return false;
				}
			}
		}
		else
		{
			for (int C = S.ci - 1; C >= E.ci; C--)
			{
				if (S.ri == E.ri && C == E.ci && B->IsDushmanPiece(Position{ S.ri,C }))
				{
					return true;
				}
				if (B->GetPiece(S.ri, C) != nullptr)
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}

}

bool Piece::isVerticalPathClear(Position S, Position E)
{
	if (isVertical(S, E) == true)
	{
		if (S.ri < E.ri)
		{
			for (int R = S.ri + 1; R <= E.ri; R++)
			{
				if (R == E.ri && S.ci == E.ci && B->IsDushmanPiece(Position{ R,S.ci }))
				{
					return true;
				}
				if (B->GetPiece(R, S.ci) != nullptr)
				{
					return false;
				}
			}
		}
		else
		{
			for (int R = S.ri - 1; R >= E.ri; R--)
			{
				if (R == E.ri && S.ci == E.ci && B->IsDushmanPiece(Position{ R,S.ci }))
				{
					return true;
				}
				if (B->GetPiece(R, S.ci) != nullptr)
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Piece::isDiagonalPathClear(Position S, Position E)
{
	if (isDiagonal(S, E) == true)
	{
		if (S.ri < E.ri && S.ci < E.ci)
		{
			for (int R = S.ri + 1, C = S.ci + 1; R <= E.ri and C <= E.ci; R++, C++)
			{
				if (R == E.ri && C == E.ci && B->IsDushmanPiece(Position{ R,C }))
				{
					return true;
				}
				if (B->GetPiece(R, C) != nullptr)
				{
					return false;
				}
			}
		}
		else if (S.ri < E.ri && S.ci > E.ci)
		{
			for (int R = S.ri + 1, C = S.ci - 1; R <= E.ri and C >= E.ci; R++, C--)
			{
				if (R == E.ri && C == E.ci && B->IsDushmanPiece(Position{ R,C }))
				{
					return true;
				}
				if (B->GetPiece(R, C) != nullptr)
				{
					return false;
				}
			}
		}
		else if (S.ri > E.ri && S.ci < E.ci)
		{
			for (int R = S.ri - 1, C = S.ci + 1; R >= E.ri and C <= E.ci; R--, C++)
			{
				if (R == E.ri && C == E.ci && B->IsDushmanPiece(Position{ R,C }))
				{
					return true;
				}
				if (B->GetPiece(R, C) != nullptr)
				{
					return false;
				}
			}
		}
		else if ((S.ri > E.ri && S.ci > E.ci))
		{
			for (int R = S.ri - 1, C = S.ci - 1; R >= E.ri and C >= E.ci; R--, C--)
			{
				if (R == E.ri && C == E.ci && B->IsDushmanPiece(Position{ R,C }))
				{
					return true;
				}
				if (B->GetPiece(R, C) != nullptr)
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool Piece::IsKing()
{
	return false;
}

Position Piece::getPos()
{
	return P;
}

bool Piece::IsLegalMove(Position E)
{
	return true;
}

void Piece::UnHighlight()
{
	UnHighlightSelf();
	UnHighlightLegal();
}

void Piece::UnHighlightSelf()
{
	int RDim = B->getRDim();
	int CDim = B->getCDim();
	int Dim = B->getDim();
	int R1 = P.ri * RDim;
	int C1 = P.ci * CDim;
	int R2 = P.ri * RDim + RDim - 1;
	int C2 = P.ci * CDim + CDim - 1;
	char f = -37;
	int a;
	if (P.ri % 2 == 0)
	{
		if (P.ci % 2 == 0)
		{
			a = B->geta1();
		}
		else
		{
			a = B->geta2();
		}
	}
	else
	{
		if (P.ci % 2 == 0)
		{
			a = B->geta2();
		}
		else
		{
			a = B->geta1();
		}
	}
	color(a);
	for (int i = R1; i <= R2; i++)
	{
		gotoRowCol(i, C1);
		cout << f;
		gotoRowCol(i, C2);
		cout << f;
	}
	for (int i = C1; i <= C2; i++)
	{
		gotoRowCol(R1, i);
		cout << f;
		gotoRowCol(R2, i);
		cout << f;
	}
}

void Piece::UnHighlightLegal()
{
	int RDim = B->getRDim();
	int CDim = B->getCDim();
	int Dim = B->getDim();
	char f = -37;
	int a;

	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			if (IsLegalMove(Position{ i,j }) and B->IsDushmanPiece(Position{ i,j }))
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
					{
						a = B->geta1();
					}
					else
					{
						a = B->geta2();
					}
				}
				else
				{
					if (j % 2 == 0)
					{
						a = B->geta2();
					}
					else
					{
						a = B->geta1();
					}
				}
				color(a);
				int R1 = i * RDim;
				int C1 = j * CDim;
				int R2 = i * RDim + RDim - 1;
				int C2 = j * CDim + CDim - 1;
				for (int i = R1; i <= R2; i++)
				{
					gotoRowCol(i, C1);
					cout << f;
					gotoRowCol(i, C2);
					cout << f;
				}
				for (int i = C1; i <= C2; i++)
				{
					gotoRowCol(R1, i);
					cout << f;
					gotoRowCol(R2, i);
					cout << f;
				}
			}
			else if (IsLegalMove(Position{ i,j }))
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
					{
						a = B->geta1();
					}
					else
					{
						a = B->geta2();
					}
				}
				else
				{
					if (j % 2 == 0)
					{
						a = B->geta2();
					}
					else
					{
						a = B->geta1();
					}
				}
				color(a);
				int R1 = i * RDim;
				int C1 = j * CDim;
				int R2 = i * RDim + RDim - 1;
				int C2 = j * CDim + CDim - 1;
				for (int i = R1; i <= R2; i++)
				{
					gotoRowCol(i, C1);
					cout << f;
					gotoRowCol(i, C2);
					cout << f;
				}
				for (int i = C1; i <= C2; i++)
				{
					gotoRowCol(R1, i);
					cout << f;
					gotoRowCol(R2, i);
					cout << f;
				}
			}
		}
	}
}

void Piece::Highlight()
{
	HighlightSelf();
	HighlightLegal();
}

void Piece::HighlightSelf()
{
	int RDim = B->getRDim();
	int CDim = B->getCDim();
	int Dim = B->getDim();
	int R1 = P.ri * RDim;
	int C1 = P.ci * CDim;
	int R2 = P.ri * RDim + RDim - 1;
	int C2 = P.ci * CDim + CDim - 1;
	char f = -37;
	int a = 3;
	color(a);
	for (int i = R1; i <= R2; i++)
	{
		gotoRowCol(i, C1);
		cout << f;
		gotoRowCol(i, C2);
		cout << f;
	}
	for (int i = C1; i <= C2; i++)
	{
		gotoRowCol(R1, i);
		cout << f;
		gotoRowCol(R2, i);
		cout << f;
	}
}

void Piece::HighlightLegal()
{
	int RDim = B->getRDim();
	int CDim = B->getCDim();
	int Dim = B->getDim();
	char f = -37;
	int a1 = 10;
	int a2 = 4;
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			if (IsLegalMove(Position{ i,j }) and B->IsDushmanPiece(Position{ i,j }))
			{
				if (B->SearchSelfCheck(P.ri, P.ci, i, j))
				{
					continue;
				}
				color(a2);
				int R1 = i * RDim;
				int C1 = j * CDim;
				int R2 = i * RDim + RDim - 1;
				int C2 = j * CDim + CDim - 1;
				for (int i = R1; i <= R2; i++)
				{
					gotoRowCol(i, C1);
					cout << f;
					gotoRowCol(i, C2);
					cout << f;
				}
				for (int i = C1; i <= C2; i++)
				{
					gotoRowCol(R1, i);
					cout << f;
					gotoRowCol(R2, i);
					cout << f;
				}
			}
			else if (IsLegalMove(Position{ i,j }))
			{
				if (B->SearchSelfCheck(P.ri, P.ci, i, j))
				{
					continue;
				}
				color(a1);
				int R1 = i * RDim;
				int C1 = j * CDim;
				int R2 = i * RDim + RDim - 1;
				int C2 = j * CDim + CDim - 1;
				for (int i = R1; i <= R2; i++)
				{
					gotoRowCol(i, C1);
					cout << f;
					gotoRowCol(i, C2);
					cout << f;
				}
				for (int i = C1; i <= C2; i++)
				{
					gotoRowCol(R1, i);
					cout << f;
					gotoRowCol(R2, i);
					cout << f;
				}
			}
		}
	}
}

void Piece::UnDraw()
{
	int RDim = B->getRDim();
	int CDim = B->getCDim();
	int Dim = B->getDim();
	int R1 = P.ri * RDim;
	int C1 = P.ci * CDim;
	int R2 = P.ri * RDim + RDim - 1;
	int C2 = P.ci * CDim + CDim - 1;
	char f = -37;
	int a;
	if (P.ri % 2 == 0)
	{
		if (P.ci % 2 == 0)
		{
			a = B->geta1();
		}
		else
		{
			a = B->geta2();
		}
	}
	else
	{
		if (P.ci % 2 == 0)
		{
			a = B->geta2();
		}
		else
		{
			a = B->geta1();
		}
	}
	color(a);
	for (int i = R1; i <= R2; i++)
	{
		for (int j = C1; j <= C2; j++)
		{
			gotoRowCol(i, j);
			cout << f;
		}
	}

}

Piece::~Piece()
{

}