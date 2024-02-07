#pragma once
#include "Piece.h"
class Pawn :
    public Piece
{
public:
    Pawn(Position _P, COLOR _C, Board* B);
    virtual void Draw() override final;
    bool IsLegalMove(Position E);
    ~Pawn();
};

