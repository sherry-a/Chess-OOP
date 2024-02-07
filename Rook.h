#pragma once
#include "Piece.h"
class Rook :
    virtual public Piece
{
public:
    Rook(Position _P, COLOR _C, Board* B);
    virtual void Draw() override;
    virtual bool IsLegalMove(Position E);
    ~Rook();
};

