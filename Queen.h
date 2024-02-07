#pragma once
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
class Queen :
    public Rook,public Bishop
{
public:
    Queen(Position _P, COLOR _C, Board* B);
    virtual void Draw() override final;
    virtual bool IsLegalMove(Position E);
    ~Queen();
};

