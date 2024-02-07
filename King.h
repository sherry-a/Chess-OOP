#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(Position _P, COLOR _C, Board* B);
    virtual void Draw() override final;
    virtual bool IsKing() override final;
    bool IsLegalMove(Position E);
    ~King();
};

