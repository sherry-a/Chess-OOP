#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
    Knight(Position _P, COLOR _C, Board* B);
    virtual void Draw() override final;
    bool IsLegalMove(Position E);
    ~Knight();
};

