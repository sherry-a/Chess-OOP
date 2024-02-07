#pragma once
#include "Head.h"
#include "Board.h"
class Board;
class Piece
{
protected:
	Board* B;
	Position P;
	char sym;
	COLOR C;
public:
	bool IsMoving;
	int moves;
	Piece(Position _P, COLOR _C, Board* _B);
	virtual void Draw();
	void UnDraw();
	bool IsPawnPromotion();
	void ChangePos(Position _P);
	void UnHighlight();
	void UnHighlightSelf();
	void UnHighlightLegal();
	void Highlight();
	void HighlightSelf();
	void HighlightLegal();
	char getSym();
	Position getPos();
	virtual bool IsKing();
	COLOR GetColor();
	bool isHorizontal(Position S, Position E);
	bool isVertical(Position S, Position E);
	bool isDiagonal(Position S, Position E);
	bool isHorizontalPathClear(Position S, Position E);
	bool isVerticalPathClear(Position S, Position E);
	bool isDiagonalPathClear(Position S, Position E);
	virtual bool IsLegalMove(Position E);
	virtual ~Piece();
};

