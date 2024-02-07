#pragma once
#include "Piece.h"
#include <vector>
using std::vector;
class Piece;
class Board
{
    int Dim;
    Piece*** Ps = nullptr;
    COLOR CC;
    int RDim, CDim;
    int a1 = 7;
    int a2 = 8;
    int TotalMoves;
    int CM;
    bool GameOver = false;
    struct Moves
    {
        vector<int>x1;
        vector<int>y1;
        vector<int>x2;
        vector<int>y2;
        vector<Piece*>P;
        vector<int> times;
    }Move;
    struct players
    {
        bool WhiteInCheck = false;
        bool BlackInCheck = false;
        bool WhiteCheckMate = false;
        bool BlackCheckMate = false;
        bool WhiteTimeRunning = false;
        bool BlackTimeRunning = false;
        int WhiteTime;
        int BlackTime;
    }U;
    void WhiteTimer();
    void BlackTimer();
    void StartCurrentTimer();
    void PauseCurrentTimer();
    void DoCastling(int x1, int y1, int x2, int y2);
    void HighlightedBoxWithText(Position S, int colour, string word);
    void ShowTurn();
    void UnShowTurn();
    void SetMisc();
    void UnSetMisc();
    void ShowStats();
    void ShowWinner();
    void MakeAMove();
    void PromotePawn(int x,int y);
    void ChangeTurn();
    bool SearchCheck();
    void SearchCheckMate();
    void HighlightEnemyKing();
    void UnHighlightEnemyKing();
    void HighlightCurrentKing();
    void UnHighlightCurrentKing();
    void HighlightIfCastling(int x,int y);
    void Clear();
    void Undo();
    void MovePiece(int x1,int y1,int x2,int y2);
    void ReplayMovePiece();
    void ReverseLastMove();
    void Draw();
    void UnDraw();
    void DrawBoxes();
    void UnDrawBoxes();
    void DrawBoard();
    void UnDrawBoard();
    void Replay();
    void SaveGame();
    void LoadGame();
    void LoadFromFile(string file);
    void SaveGame_Complete();
    void LoadGame_Complete();
    void Undo_Complete();
    void Replay_Complete();
    void New_Complete();
    void Redo_Complete();
    void DrawPPBoxes();
    void UnDrawPPBoxes();
    bool IsLegalLeftEnemy();
public:
    Board();
    bool IsCastling(int x1, int y1, int x2, int y2);
    void InitNew();
    int geta1();
    int geta2();
    int getRDim();
    int getCDim();
    int getDim();
    void Play();
    bool SearchSelfCheck(int x1, int y1, int x2, int y2);
    Position FindKingPolymorphism(COLOR C);
    Position FindKingDynamicCasting(COLOR C);
    bool IsApnaPiece(Position S);
    bool IsDushmanPiece(Position S);
    bool IsAnyPiece(Position S);
    Piece* GetPiece(int ri, int ci);
    ~Board();
};