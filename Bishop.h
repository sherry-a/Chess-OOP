#pragma once
#include "Piece.h"
class Bishop :
    virtual public Piece
{
public:
    Bishop(Position _P, COLOR _C, Board* B);
    virtual void Draw() override;
    virtual bool IsLegalMove(Position E);
    ~Bishop();
};

