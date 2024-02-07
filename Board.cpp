#include "Board.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include <conio.h>
#include <string>
#include <fstream>
#include <mmsystem.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
Board::Board()
{
	Dim = 8;
	RDim = 7;
	CDim = 13;
	InitNew();
}

void Board::InitNew()
{
	GameOver = false;
	Clear();
	Ps = new Piece * *[Dim];
	for (int ri = 0; ri < Dim; ri++)
	{
		Ps[ri] = new Piece * [Dim] {};
		for (int ci = 0; ci < Dim; ci++)
		{
			if (ri == 1)
			{
				Ps[ri][ci] = new Pawn(Position{ ri, ci }, BLACK, this);
			}
			else if (ri == 6)
			{
				Ps[ri][ci] = new Pawn(Position{ ri, ci }, WHITE, this);
			}
			else if (ri == 0)
			{
				if (ci == 0 || ci == 7)
				{
					Ps[ri][ci] = new Rook(Position{ ri, ci }, BLACK, this);
				}
				if (ci == 1 || ci == 6)
				{
					Ps[ri][ci] = new Knight(Position{ ri, ci }, BLACK, this);
				}
				if (ci == 2 || ci == 5)
				{
					Ps[ri][ci] = new Bishop(Position{ ri, ci }, BLACK, this);
				}
				if (ci == 3)
				{
					Ps[ri][ci] = new Queen(Position{ ri, ci }, BLACK, this);
				}
				if (ci == 4)
				{
					Ps[ri][ci] = new King(Position{ ri, ci }, BLACK, this);
				}
			}
			else if (ri == 7)
			{
				if (ci == 0 || ci == 7)
				{
					Ps[ri][ci] = new Rook(Position{ ri, ci }, WHITE, this);
				}
				if (ci == 1 || ci == 6)
				{
					Ps[ri][ci] = new Knight(Position{ ri, ci }, WHITE, this);
				}
				if (ci == 2 || ci == 5)
				{
					Ps[ri][ci] = new Bishop(Position{ ri, ci }, WHITE, this);
				}
				if (ci == 3)
				{
					Ps[ri][ci] = new Queen(Position{ ri, ci }, WHITE, this);
				}
				if (ci == 4)
				{
					Ps[ri][ci] = new King(Position{ ri, ci }, WHITE, this);
				}
			}
			else
			{
				Ps[ri][ci] = nullptr;
			}
		}
	}
	TotalMoves = 0;
	CC = WHITE;
	CM = 0;
	U.BlackTime = 600;
	U.WhiteTime = 600;
}

void Board::Draw()
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (Ps[ri][ci] == nullptr)
			{
				continue;
			}
			else
			{
				Ps[ri][ci]->Draw();
			}
		}
	}
}

void Board::DrawBoxes()
{
	HighlightedBoxWithText(Position{ Dim,0 }, 11, "Save");
	HighlightedBoxWithText(Position{ Dim,1 }, 11, "Load");
	HighlightedBoxWithText(Position{ Dim,2 }, 11, "Undo");
	HighlightedBoxWithText(Position{ Dim,3 }, 11, "Replay");
	HighlightedBoxWithText(Position{ Dim,4 }, 11, "New");
	HighlightedBoxWithText(Position{ Dim,5 }, 11, "Redo");
}

void Board::UnDrawBoxes()
{
	HighlightedBoxWithText(Position{ Dim,0 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,1 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,2 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,3 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,4 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,5 }, 0, "      ");
}

void void1() {}

void Board::UnDraw()
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (Ps[ri][ci] == nullptr)
			{
				continue;
			}
			else
			{
				Ps[ri][ci]->UnDraw();
			}
		}
	}
}

int Board::getRDim()
{
	return RDim;
}

int Board::getCDim()
{
	return CDim;
}

int Board::geta1()
{
	return a1;
}

int Board::geta2()
{
	return a2;
}

int Board::getDim()
{
	return Dim;
}

void Board::HighlightedBoxWithText(Position S, int colour, string word)
{
	int R1 = S.ri * RDim;
	int C1 = S.ci * CDim;
	int R = S.ri * RDim + RDim / 2;
	int C = S.ci * CDim + CDim / 2;
	int R2 = S.ri * RDim + RDim - 1;
	int C2 = S.ci* CDim + CDim - 1;
	char f = -37;
	color(colour);
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
	color(15);
	gotoRowCol(R, C - (word.size() / 2));
	cout << word;
}

void Board::DrawBoard()
{
	int R = RDim * Dim;
	int C = CDim * Dim;
	char f = -37;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (i % (RDim * 2) < RDim)
			{
				if (j % (CDim * 2) < CDim)
				{
					color(a1);
					gotoRowCol(i, j);
					cout << f;
				}
				else
				{
					color(a2);
					gotoRowCol(i, j);
					cout << f;
				}
			}
			else
			{
				if (j % (CDim * 2) < CDim)
				{
					color(a2);
					gotoRowCol(i, j);
					cout << f;
				}
				else
				{
					color(a1);
					gotoRowCol(i, j);
					cout << f;
				}
			}
		}
	}
}

void Board::UnDrawBoard()
{
	int R = RDim * Dim;
	int C = CDim * Dim;
	char f = -37;
	color(0);
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			gotoRowCol(i, j);
			cout << f;
		}
	}
}

void Board::SetMisc()
{
	//Showing "White Timer"
	string W = "White Timer";
	gotoRowCol(RDim / 2 - 1, (Dim + 1) * CDim - W.size() / 2);
	cout << W;
	//Showing "Black Timer"
	string B = "Black Timer";
	gotoRowCol(RDim / 2 - 1, (Dim + 2) * CDim - B.size() / 2);
	cout << B;
	//To Display W/T Time Left at Start
	U.BlackTimeRunning = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	U.BlackTimeRunning = false;
	//To Display Stats Area
	gotoRowCol(2 * RDim, (Dim + 1) * CDim);
	cout << "Stats:";
}

void Board::UnSetMisc()
{
	string W = "White Timer";
	gotoRowCol(RDim / 2 - 1, (Dim + 1) * CDim - W.size() / 2);
	cout << "           ";
	string B = "Black Timer";
	gotoRowCol(RDim / 2 - 1, (Dim + 2) * CDim - B.size() / 2);
	cout << "           ";
	gotoRowCol(RDim / 2, (Dim + 1) * CDim - 4);
	for (int i = 0; i < 8; i++)
	{
		cout << ' ';
	}
	gotoRowCol(RDim / 2, (Dim + 2) * CDim - 4);
	for (int i = 0; i < 8; i++)
	{
		cout << ' ';
	}
	gotoRowCol(2 * RDim, (Dim + 1) * CDim);
	cout << "      ";
}

void Board::ShowStats()
{
	/*for (int i = ((CM > 5) ? CM - 5 : 0); i < ((CM > 5) ? ); i++)
	{

	}*/
}

bool Board::IsLegalLeftEnemy()
{
	ChangeTurn();
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			if (Ps[i][j] != nullptr and Ps[i][j]->GetColor() == CC)
			{
				for (int x = 0; x < Dim; x++)
				{
					for (int y = 0; y < Dim; y++)
					{
						if (Ps[i][j]->IsLegalMove(Position{ x,y }) and !SearchSelfCheck(i, j, x, y))
						{
							ChangeTurn();
							return true;
						}
					}
				}
			}
		}
	}
	ChangeTurn();
	return false;
}

void Board::SearchCheckMate()
{
	if (!IsLegalLeftEnemy())
	{
		if (U.WhiteInCheck)
		{
			U.WhiteCheckMate = true;
		}
		else if (U.BlackInCheck)
		{
			U.BlackCheckMate = true;
		}
		GameOver = true;
	}
}

void Board::WhiteTimer()
{
	string mes;
	int m, s;
	while (!GameOver)
	{
		while (U.WhiteTimeRunning)
		{
			if (U.WhiteTime == 0)
			{
				GameOver = true;
				break;
			}
			color(15);
			m = U.WhiteTime / 60;
			s = U.WhiteTime % 60;
			mes = ((m < 10)? '0' + std::to_string(m) : std::to_string(m)) + ":" + ((s < 10) ? '0' + std::to_string(s) : std::to_string(s));
			gotoRowCol(RDim / 2, (Dim + 1) * CDim - mes.size() / 2);
			cout << mes;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			U.WhiteTime--;
		}
	}
}

void Board::BlackTimer()
{
	string mes;
	int m, s;
	while(!GameOver)
	{
		while (U.BlackTimeRunning)
		{
			if (U.BlackTime == 0)
			{
				GameOver = true;
				break;
			}
			color(15);
			m = U.BlackTime / 60;
			s = U.BlackTime % 60;
			mes = ((m < 10) ? '0' + std::to_string(m) : std::to_string(m)) + ":" + ((s < 10) ? '0' + std::to_string(s) : std::to_string(s));
			gotoRowCol(RDim / 2, (Dim + 2) * CDim - mes.size() / 2);
			cout << mes;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			U.BlackTime--;
		}
	}
}

void Board::StartCurrentTimer()
{
	if (CC==BLACK)
	{
		U.BlackTimeRunning = true;
	}
	else
	{
		U.WhiteTimeRunning = true;
	}
}

void Board::PauseCurrentTimer()
{
	if (CC == BLACK)
	{
		U.BlackTimeRunning = false;
	}
	else
	{
		U.WhiteTimeRunning = false;
	}
}

void Board::Play()
{
	DrawBoard();
	Draw();
	DrawBoxes();
	std::thread WT(&Board::WhiteTimer, this);
	std::thread BT(&Board::BlackTimer, this);
	SetMisc();
	while (!GameOver)
	{
		ShowTurn();
		MakeAMove();
		if (GameOver) break;
		if (SearchCheck())
		{
			((CC == BLACK) ? U.WhiteInCheck = true : U.BlackInCheck = true);
		}
		else
		{
			((CC == BLACK) ? U.WhiteInCheck = false : U.BlackInCheck = false);
		}
		SearchCheckMate();
		ChangeTurn();
	}
	UnSetMisc();
	ShowWinner();
	WT.detach();
	BT.detach();
}

void Board::HighlightEnemyKing()
{
	ChangeTurn();
	Position K = FindKingPolymorphism(CC);
	HighlightedBoxWithText(K, 13, "");
	ChangeTurn();
}

void Board::UnHighlightEnemyKing()
{
	ChangeTurn();
	Position K = FindKingPolymorphism(CC);
	Ps[K.ri][K.ci]->UnDraw();
	Ps[K.ri][K.ci]->Draw();
	ChangeTurn();
}

void Board::HighlightCurrentKing()
{
	Position K = FindKingPolymorphism(CC);
	HighlightedBoxWithText(K, 13, "");
}

void Board::UnHighlightCurrentKing()
{
	ChangeTurn();
	Position K = FindKingPolymorphism(CC);
	Ps[K.ri][K.ci]->UnDraw();
	Ps[K.ri][K.ci]->Draw();
	ChangeTurn();
}

void Board::ChangeTurn()
{
	if (CC == WHITE)
	{
		CC = BLACK;
	}
	else
	{
		CC = WHITE;
	}
}

bool Board::SearchCheck()
{
	ChangeTurn();
	Position K = FindKingPolymorphism(CC);
	ChangeTurn();
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			if (Ps[i][j] != nullptr and Ps[i][j]->GetColor() == CC and Ps[i][j]->IsLegalMove(K))
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::SearchSelfCheck(int x1, int y1, int x2, int y2)
{
	Piece* D = Ps[x2][y2];
	Ps[x2][y2] = Ps[x1][y1];
	Ps[x2][y2]->ChangePos(Position{ x2,y2 });
	Ps[x1][y1] = nullptr;
	ChangeTurn();
	bool ch = SearchCheck();
	Ps[x1][y1] = Ps[x2][y2];
	Ps[x2][y2] = D;
	Ps[x1][y1]->ChangePos(Position{ x1,y1 });
	ChangeTurn();
	return ch;
}

Piece* Board::GetPiece(int ri, int ci)
{
	return Ps[ri][ci];
}

void Board::ShowTurn()
{
	gotoRowCol(RDim , Dim * CDim + 5);
	color(15);
	cout << "It's " << ((CC == WHITE) ? "WHITE's" : "BLACK's") << " Turn!" << endl;
}

void Board::UnShowTurn()
{
	gotoRowCol(Dim, Dim * CDim + 5);
	color(0);
	char f = -37;
	for (int i = 0; i < 20; i++)
	{
		cout << f;
	}
}

void Board::ShowWinner()
{
	UnDrawBoard();
	UnDrawBoxes();
	UnShowTurn();
	changeFontSize(20);
	gotoRowCol(Dim * RDim / 2, Dim * CDim / 2);
	color(15);
	if (U.WhiteCheckMate)
	{
		cout << "BLACK Won By CheckMate!";
	}
	else if (U.BlackCheckMate)
	{
		cout << "WHITE Won By CheckMate!";
	}
	else if (U.WhiteTime == 0)
	{
		cout << "WHITE Lost By Timer!";
	}
	else if (U.BlackTime == 0)
	{
		cout << "BLACK Lost By Timer!";
	}
	else
	{
		cout << "STALEMATE. The Game Is Draw!";
	}
}

bool Board::IsApnaPiece(Position S)
{
	if (((Ps[S.ri][S.ci] != nullptr)))
	{
		return (Ps[S.ri][S.ci]->GetColor() == CC);
	}
	else
	{
		return false;
	}
}

bool Board::IsDushmanPiece(Position S)
{
	if (Ps[S.ri][S.ci] == nullptr)
	{
		return false;
	}
	else
	{
		return (Ps[S.ri][S.ci]->GetColor() != CC);
	}
}

bool Board::IsAnyPiece(Position S)
{
	return (Ps[S.ri][S.ci] != nullptr);
}

Position Board::FindKingPolymorphism(COLOR C)
{
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			if (Ps[i][j] != nullptr and Ps[i][j]->IsKing() and C==Ps[i][j]->GetColor())
			{
				return Ps[i][j]->getPos();
			}
		}
	}
}

Position Board::FindKingDynamicCasting(COLOR C)
{
	King* K;
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			K = dynamic_cast<King*>(Ps[i][j]);
			if (K != nullptr and C == Ps[i][j]->GetColor())
			{
				return K->getPos();
			}
		}
	}
}

void Board::SaveGame()
{
	color(15);
	string file;
	string S;
	do
	{
		gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
		S = "Please Enter a \".txt\" Filename to Save The Game: ";
		cout << S;
		char f;
		do
		{
			f = _getche();
			if (f == '\b')
			{
				if (!file.empty())
				{
					gotoRowCol(Dim * RDim - 5, Dim * CDim + 5 + S.size() + file.size() - 1);
					cout << ' ';
					file.pop_back();
				}
				gotoRowCol(Dim * RDim - 5, Dim * CDim + 5 + S.size() +  file.size());
			}
			else if (f != '\r')
			{
				file += f;
			}
		} while (f != '\r');
		if (file.at(file.size() - 1) != 't' || file.at(file.size() - 2) != 'x' || file.at(file.size() - 3) != 't' || file.at(file.size() - 4) != '.' || file.size() <= 4)
		{
			gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
			for (int i = 0; i < S.size() + file.size(); i++)
			{
				cout << ' ';
			}
		}
	} while (file.at(file.size() - 1) != 't' || file.at(file.size() - 2) != 'x' || file.at(file.size() - 3) != 't' || file.at(file.size() - 4) != '.' || file.size() <= 4);
	ofstream Wtr(file);
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			if (Ps[i][j] != nullptr)
			{
				Wtr << Ps[i][j]->getSym() << " ";
			}
			else
			{
				Wtr << '-' << " ";
			}
		}
		Wtr << endl;
	}
	Wtr << endl << endl << CC;
	Wtr.close();
	gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
	for (int i = 0; i < S.size() + file.size(); i++)
	{
		cout << ' ';
	}
	gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
	string T = "Board State Saved Successfully";
	cout << T;
	Sleep(1000);
	gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
	for (int i = 0; i < T.size(); i++)
	{
		cout << ' ';
	}
}

void Board::LoadGame()
{
	color(15);
	string file;
	string S;
	do
	{
		gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
		S = "Please Enter a \".txt\" File to Load The Game: ";
		cout << S;
		char f;
		do
		{
			f = _getche();
			if (f == '\b')
			{
				if (!file.empty())
				{
					gotoRowCol(Dim * RDim - 5, Dim * CDim + 5 + S.size() + file.size() - 1);
					cout << ' ';
					file.pop_back();
				}
				gotoRowCol(Dim * RDim - 5, Dim * CDim + 5 + S.size() + file.size());
			}
			else if (f != '\r')
			{
				file += f;
			}
		} while (f != '\r');
		if (file.at(file.size() - 1) != 't' || file.at(file.size() - 2) != 'x' || file.at(file.size() - 3) != 't' || file.at(file.size() - 4) != '.' || file.size() <= 4)
		{
			gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
			for (int i = 0; i < S.size() + file.size(); i++)
			{
				cout << ' ';
			}
		}
	} while (file.at(file.size() - 1) != 't' || file.at(file.size() - 2) != 'x' || file.at(file.size() - 3) != 't' || file.at(file.size() - 4) != '.' || file.size() <= 4);
	UnDraw();
	LoadFromFile(file);
	Draw();
	gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
	for (int i = 0; i < S.size() + file.size(); i++)
	{
		cout << ' ';
	}
	gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
	string T = "Board State Loaded Successfully";
	cout << T;
	Sleep(1000);
	gotoRowCol(Dim * RDim - 5, Dim * CDim + 5);
	for (int i = 0; i < T.size(); i++)
	{
		cout << ' ';
	}
}

void Board::LoadFromFile(string file)
{
	ifstream Rdr(file);
	Piece*** G;
	G = new Piece * *[Dim];
	char d;
	for (int i = 0; i < Dim; i++)
	{
		G[i] = new Piece * [Dim];
		for (int j = 0; j < Dim; j++)
		{
			Rdr >> d;
			switch (d)
			{
			case 'p':
				G[i][j] = new Pawn(Position{ i,j }, WHITE, this);
				break;
			case 'r':
				G[i][j] = new Rook(Position{ i,j }, WHITE, this);
				break;
			case 'h':
				G[i][j] = new Knight(Position{ i,j }, WHITE, this);
				break;
			case 'b':
				G[i][j] = new Bishop(Position{ i,j }, WHITE, this);
				break;
			case 'q':
				G[i][j] = new Queen(Position{ i,j }, WHITE, this);
				break;
			case 'k':
				G[i][j] = new King(Position{ i,j }, WHITE, this);
				break;


			case 'P':
				G[i][j] = new Pawn(Position{ i,j }, BLACK, this);
				break;
			case 'R':
				G[i][j] = new Rook(Position{ i,j }, BLACK, this);
				break;
			case 'H':
				G[i][j] = new Knight(Position{ i,j }, BLACK, this);
				break;
			case 'B':
				G[i][j] = new Bishop(Position{ i,j }, BLACK, this);
				break;
			case 'Q':
				G[i][j] = new Queen(Position{ i,j }, BLACK, this);
				break;
			case 'K':
				G[i][j] = new King(Position{ i,j }, BLACK, this);
				break;
			default:
				G[i][j] = nullptr;
				break;
			}
		}
	}
	int colour;
	Rdr >> colour;
	if (colour == 0)
	{
		CC = BLACK;
	}
	else
	{
		CC = WHITE;
	}
	Rdr.close();
	Clear();
	Ps = G;
	TotalMoves = 0;
	CM = 0;
	GameOver = false;
	U.BlackTime = 600;
	U.WhiteTime = 600;
}

void Board::Undo()
{
	ReverseLastMove();
	ChangeTurn();
	ShowTurn();
}

void Board::SaveGame_Complete()
{
	PauseCurrentTimer();
	HighlightedBoxWithText(Position{ Dim,0 }, 12, "");
	SaveGame();
	HighlightedBoxWithText(Position{ Dim,0 }, 11, "");
	StartCurrentTimer();
}

void Board::LoadGame_Complete()
{
	PauseCurrentTimer();
	HighlightedBoxWithText(Position{ Dim,1 }, 12, "");
	LoadGame();
	ShowTurn();
	HighlightedBoxWithText(Position{ Dim,1 }, 11, "");
	StartCurrentTimer();
}

void Board::Undo_Complete()
{
	PauseCurrentTimer();
	HighlightedBoxWithText(Position{ Dim,2 }, 12, "");
	Undo();
	Sleep(300);
	HighlightedBoxWithText(Position{ Dim,2 }, 11, "");
	StartCurrentTimer();
}

void Board::Replay_Complete()
{
	PauseCurrentTimer();
	HighlightedBoxWithText(Position{ Dim,3 }, 12, "");
	int d = TotalMoves;
	TotalMoves = CM;
	Replay();
	TotalMoves = d;
	HighlightedBoxWithText(Position{ Dim,3 }, 11, "");
	StartCurrentTimer();
}

void Board::New_Complete()
{
	PauseCurrentTimer();
	HighlightedBoxWithText(Position{ Dim,4 }, 12, "");
	UnDraw();
	InitNew();
	Draw();
	HighlightedBoxWithText(Position{ Dim,4 }, 11, "");
	StartCurrentTimer();
}

void Board::Redo_Complete()
{
	PauseCurrentTimer();
	HighlightedBoxWithText(Position{ Dim,5 }, 12, "");
	ReplayMovePiece();
	ChangeTurn();
	HighlightedBoxWithText(Position{ Dim,5 }, 11, "");
	StartCurrentTimer();
}

void Board::Replay()
{
	CM = TotalMoves;
	for (int i = TotalMoves; i > 0; i--)
	{
		if (Move.times[CM - 1] == 2)
		{
			i--;
		}
		ReverseLastMove();
		Sleep(200);
	}
	for (int i = 0; i < TotalMoves; i++)
	{
		if (Move.times[CM] == 2)
		{
			i++;
		}
		ReplayMovePiece();
	}
}

void Board::MakeAMove()
{
	int x1, y1;
	INPUT_RECORD InputRecord;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	((CC == BLACK) ? ((U.BlackInCheck) ? HighlightCurrentKing() : UnHighlightCurrentKing()) : ((U.WhiteInCheck) ? HighlightCurrentKing() : UnHighlightCurrentKing()));
	StartCurrentTimer();
	do
	{
		do
		{
			SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
			do
			{
				ReadConsoleInput(hInput, &InputRecord, 1, &Events);
				if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 19 and CM >= 1)
				{
					SaveGame_Complete();
				}
				else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 12)
				{
					LoadGame_Complete();
				}
				else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 24 and CM >= 1)
				{
					Undo_Complete();
				}
				else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 18 and CM >= 1)
				{
					Replay_Complete();
				}
				else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 14 and CM >= 1)
				{
					New_Complete();
				}
				else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 14 and CM < TotalMoves)
				{
					Redo_Complete();
				}
				else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					y1 = InputRecord.Event.MouseEvent.dwMousePosition.X;
					x1 = InputRecord.Event.MouseEvent.dwMousePosition.Y;
					break;
				}
				else if (GameOver)
				{
					return;
				}
			} while (true);
			x1 /= RDim;
			y1 /= CDim;
			if (x1 == Dim)
			{
				if (y1 == 0 and CM >= 1)
				{
					SaveGame_Complete();
				}
				else if (y1 == 1)
				{
					LoadGame_Complete();
				}
				else if (y1 == 2 and CM >= 1)
				{
					Undo_Complete();
				}
				else if (y1 == 3 and CM >= 1)
				{
					Replay_Complete();
				}
				else if (y1 == 4 and CM >= 1)
				{
					New_Complete();
				}
				else if (y1 == 5 and CM < TotalMoves)
				{
					Redo_Complete();
				}
			}
		} while (x1 > 7 || y1 > 7);
	} while (Ps[x1][y1] == nullptr || !IsApnaPiece(Position{ x1,y1 }));
	PauseCurrentTimer();
	int x2, y2;
	Ps[x1][y1]->Highlight();
	HighlightIfCastling(x1, y1);
	StartCurrentTimer();
	do
	{
		SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
		do
		{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
			if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 19 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				SaveGame_Complete();
			}
			else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 12)
			{
				Ps[x1][y1]->UnHighlight();
				LoadGame_Complete();
				MakeAMove();
				return;
			}
			else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 24 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				Undo_Complete();
			}
			else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 18 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				Replay_Complete();
			}
			else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 14 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				New_Complete();
				MakeAMove();
				return;
			}
			else if (InputRecord.Event.KeyEvent.uChar.AsciiChar == 25 and CM < TotalMoves)
			{
				Ps[x1][y1]->UnHighlight();
				Redo_Complete();
			}
			else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				y2 = InputRecord.Event.MouseEvent.dwMousePosition.X;
				x2 = InputRecord.Event.MouseEvent.dwMousePosition.Y;
				break;
			}
			else if (GameOver)
			{
				return;
			}
		} while (true);
		x2 /= RDim;
		y2 /= CDim;
		if (x2 == Dim)
		{
			if (y2 == 0 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				SaveGame_Complete();
			}
			else if (y2 == 1)
			{
				Ps[x1][y1]->UnHighlight();
				LoadGame_Complete();
				MakeAMove();
				return;
			}
			else if (y2 == 2 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				Undo_Complete();
			}
			else if (y2 == 3 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				Replay_Complete();
			}
			else if (y2 == 4 and CM >= 1)
			{
				Ps[x1][y1]->UnHighlight();
				New_Complete();
				MakeAMove();
				return;
			}
			else if (y2 == 5 and CM < TotalMoves)
			{
				Ps[x1][y1]->UnHighlight();
				Redo_Complete();
			}
		}
		if (x2 >= 8 || y2 >= 8 || x2 < 0 || y2 < 0 || IsApnaPiece(Position{ x2,y2 }) || !Ps[x1][y1]->IsLegalMove(Position{ x2,y2 }) || SearchSelfCheck(x1,y1,x2,y2))
		{
			Ps[x1][y1]->UnHighlight();
			MakeAMove();
			return;
		}
	} while (x2 >= 8 || y2 >= 8 || x2 < 0 || y2 < 0 || IsApnaPiece(Position{ x2,y2 }) || !Ps[x1][y1]->IsLegalMove(Position{ x2,y2 }) || SearchSelfCheck(x1, y1, x2, y2));
	PauseCurrentTimer();
	if (!SearchSelfCheck(x1,y1,x2,y2))
	{
		UnHighlightCurrentKing();
	}
	if (CM < TotalMoves)
	{
		for (int i = CM; i < TotalMoves; i++)
		{
			Move.x1.pop_back();
			Move.y1.pop_back();
			Move.x2.pop_back();
			Move.y2.pop_back();
			Move.P.pop_back();
		}
	}
	Move.x1.push_back(x1);
	Move.y1.push_back(y1);
	Move.x2.push_back(x2);
	Move.y2.push_back(y2);
	Move.times.push_back(0);
	if (Ps[x2][y2] != nullptr)
	{
		Move.P.push_back(Ps[x2][y2]);
	}
	else
	{
		Move.P.push_back(nullptr);
	}
	if (IsCastling(x1,y1,x2,y2))
	{
		DoCastling(x1, y1, x2, y2);
	}
	else
	{
		MovePiece(x1, y1, x2, y2);
		if (Ps[x2][y2]->IsPawnPromotion())
		{
			PromotePawn(x2, y2);
			Move.times[CM - 1]++;
			Move.x1.push_back(x2);
			Move.y1.push_back(y2);
			Move.x2.push_back(x2);
			Move.y2.push_back(y2);
			Move.P.push_back(Ps[x2][y2]);
			Move.times.push_back(Move.times[CM - 1]);
			CM++;
		}
	}
	TotalMoves = CM;
}

void Board::PromotePawn(int x, int y)
{
	UnDrawBoxes();
	DrawPPBoxes();
	HighlightedBoxWithText(Position{ x,y }, 13, "");
	gotoRowCol((Dim +1)* RDim, 0);
	string message;
	message = "Promote The Selected Pawn!";
	cout << message;
	//Getting Input From Mouse
	int x1, y1;
	do
	{
		getRowColbyLeftClick(x1, y1);
		x1 /= RDim;
		y1 /= CDim;
		if (x1 == Dim and (y1 <= 3 and x1 == Dim) and y1 >= 0)
		{
			break;
		}
	} while (true);
	//Promoting Pawn
	Position Pos = Ps[x][y]->getPos();
	COLOR col = Ps[x][y]->GetColor();
	Ps[x][y]->UnDraw();
	delete Ps[x][y];
	switch (y1)
	{
	case 0:
		Ps[x][y] = new Queen(Pos, col, this);
		break;
	case 1:
		Ps[x][y] = new Rook(Pos, col, this);
		break;
	case 2:
		Ps[x][y] = new Bishop(Pos, col, this);
		break;
	case 3:
		Ps[x][y] = new Knight(Pos, col, this);
		break;
	default:
		break;
	}
	gotoRowCol((Dim + 1) * RDim, 0);
	for (int i = 0; i < message.length(); i++)
	{
		cout << ' ';
	}
	UnDrawPPBoxes();
	DrawBoxes();
	Ps[x][y]->Draw();
}

void Board::DrawPPBoxes()
{
	HighlightedBoxWithText(Position{ Dim,0 }, 12, "Queen");
	HighlightedBoxWithText(Position{ Dim,1 }, 12, "Rook");
	HighlightedBoxWithText(Position{ Dim,2 }, 12, "Bishop");
	HighlightedBoxWithText(Position{ Dim,3 }, 12, "Knight");
}

void Board::UnDrawPPBoxes()
{
	HighlightedBoxWithText(Position{ Dim,0 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,1 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,2 }, 0, "      ");
	HighlightedBoxWithText(Position{ Dim,3 }, 0, "      ");
}

void Board::ReplayMovePiece()
{
	if (Ps[Move.x2[CM]][Move.y2[CM]] != nullptr)
	{
		Ps[Move.x2[CM]][Move.y2[CM]]->UnDraw();
	}
	Ps[Move.x1[CM]][Move.y1[CM]]->UnDraw();
	Ps[Move.x2[CM]][Move.y2[CM]] = Ps[Move.x1[CM]][Move.y1[CM]];
	Ps[Move.x1[CM]][Move.y1[CM]] = nullptr;
	Ps[Move.x2[CM]][Move.y2[CM]]->IsMoving = true;
	Ps[Move.x2[CM]][Move.y2[CM]]->ChangePos(Position{ Move.x2[CM],Move.y2[CM] });
	Ps[Move.x2[CM]][Move.y2[CM]]->IsMoving = false;
	Ps[Move.x2[CM]][Move.y2[CM]]->Draw();
	if (Move.times[CM] == 2)
	{
		if (Move.x1[CM + 1] == Move.x2[CM + 1] and Move.y1[CM + 1] == Move.y2[CM + 1])
		{
			Ps[Move.x1[CM + 1]][Move.y1[CM + 1]]->UnDraw();
			Ps[Move.x1[CM + 1]][Move.y1[CM + 1]] = Move.P[CM+1];
			Ps[Move.x1[CM + 1]][Move.y1[CM + 1]]->Draw();
			CM++;
		}
		else
		{
			CM++;
			if (Ps[Move.x2[CM]][Move.y2[CM]] != nullptr)
			{
				Ps[Move.x2[CM]][Move.y2[CM]]->UnDraw();
			}
			Ps[Move.x1[CM]][Move.y1[CM]]->UnDraw();
			Ps[Move.x2[CM]][Move.y2[CM]] = Ps[Move.x1[CM]][Move.y1[CM]];
			Ps[Move.x1[CM]][Move.y1[CM]] = nullptr;
			Ps[Move.x2[CM]][Move.y2[CM]]->IsMoving = true;
			Ps[Move.x2[CM]][Move.y2[CM]]->ChangePos(Position{ Move.x2[CM],Move.y2[CM] });
			Ps[Move.x2[CM]][Move.y2[CM]]->IsMoving = false;
			Ps[Move.x2[CM]][Move.y2[CM]]->Draw();
		}
	}
	PlaySound(TEXT("soundFX.wav"), NULL, SND_SYNC);
	CM++;
}

void Board::MovePiece(int x1, int y1, int x2, int y2)
{
	if (Ps[x2][y2] != nullptr)
	{
		Ps[x2][y2]->UnDraw();
	}
	Ps[x1][y1]->UnHighlight();
	Ps[x1][y1]->UnDraw();
	Ps[x2][y2] = Ps[x1][y1];
	Ps[x1][y1] = nullptr;
	Ps[x2][y2]->IsMoving = true;
	Ps[x2][y2]->ChangePos(Position{ x2,y2 });
	Ps[x2][y2]->IsMoving = false;
	Ps[x2][y2]->Draw();
	PlaySound(TEXT("soundFX.wav"), NULL, SND_SYNC);
	Move.times[CM]++;
	CM++;
}

void Board::ReverseLastMove()
{
	if (Move.times[CM-1] == 2)
	{
		if (Move.x1[CM - 1] == Move.x2[CM - 1] and Move.y1[CM - 1] == Move.y2[CM - 1])
		{
			Position Pos = Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->getPos();
			COLOR col = Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->GetColor();
			Ps[Move.x1[CM - 1]][Move.y1[CM - 1]];
			Ps[Move.x1[CM - 1]][Move.y1[CM - 1]] = new Pawn(Pos, col, this);
			CM--;
		}
		else
		{
			Ps[Move.x1[CM - 1]][Move.y1[CM - 1]] = Ps[Move.x2[CM - 1]][Move.y2[CM - 1]];
			if (Ps[Move.x2[CM - 1]][Move.y2[CM - 1]] != nullptr)
			{
				Ps[Move.x2[CM - 1]][Move.y2[CM - 1]]->UnDraw();
			}
			Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->ChangePos(Position{ Move.x1[CM - 1],Move.y1[CM - 1] });
			Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->moves--;
			Ps[Move.x2[CM - 1]][Move.y2[CM - 1]] = Move.P[CM - 1];
			if (Ps[Move.x2[CM - 1]][Move.y2[CM - 1]] != nullptr)
			{
				Ps[Move.x2[CM - 1]][Move.y2[CM - 1]]->Draw();
			}
			Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->Draw();
			CM--;
		}
	}
	Ps[Move.x1[CM - 1]][Move.y1[CM - 1]] = Ps[Move.x2[CM - 1]][Move.y2[CM - 1]];
	if (Ps[Move.x2[CM - 1]][Move.y2[CM - 1]] != nullptr)
	{
		Ps[Move.x2[CM - 1]][Move.y2[CM - 1]]->UnDraw();
	}
	Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->ChangePos(Position{ Move.x1[CM - 1],Move.y1[CM - 1] });
	Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->moves--;
	Ps[Move.x2[CM - 1]][Move.y2[CM - 1]] = Move.P[CM - 1];
	if (Ps[Move.x2[CM - 1]][Move.y2[CM - 1]] != nullptr)
	{
		Ps[Move.x2[CM - 1]][Move.y2[CM - 1]]->Draw();
	}
	Ps[Move.x1[CM - 1]][Move.y1[CM - 1]]->Draw();
	CM--;
}

bool Board::IsCastling(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 and !IsAnyPiece(Position{ x2,y2 }))
	{
		if (((CC==BLACK)? (!U.BlackInCheck and Ps[x1][y1]->getSym() == 'R'):(!U.WhiteInCheck and Ps[x1][y1]->getSym() == 'r')) and Ps[x1][y1]->moves == 0)
		{
			if (y1 < y2 and Ps[x2][y2 + 1] != nullptr and ((CC == BLACK) ? Ps[x2][y2 + 1]->getSym() == 'K' : Ps[x2][y2 + 1]->getSym() == 'k') and Ps[x2][y2 + 1]->moves == 0)
			{
				for (int i = y1 + 1; i <= y2; i++)
				{
					if (IsAnyPiece(Position{ x1,i }))
					{
						return false;
					}
				}
				return true;
			}
			if (y1 > y2 and Ps[x2][y2 - 1] != nullptr and ((CC == BLACK) ? Ps[x2][y2 - 1]->getSym() == 'K' : Ps[x2][y2 - 1]->getSym() == 'k') and Ps[x2][y2 - 1]->moves == 0)
			{
				for (int i = y2; i > y1; i++)
				{
					if (IsAnyPiece(Position{ x1,i }))
					{
						return false;
					}
				}
				return true;
			}
		}
		if (((CC == BLACK) ? (!U.BlackInCheck and Ps[x1][y1]->getSym() == 'K') : (!U.WhiteInCheck and Ps[x1][y1]->getSym() == 'k')) and Ps[x1][y1]->moves == 0)
		{
			if (y1 - 2 == y2 and Ps[x2][0] != nullptr and ((CC == BLACK) ? Ps[x2][0]->getSym() == 'R' : Ps[x2][0]->getSym() == 'r') and Ps[x2][0]->moves == 0)
			{
				for (int i = y2 - 1; i >= y1; i++)
				{
					if (IsAnyPiece(Position{ x1,i }))
					{
						return false;
					}
				}
				return true;
			}
			if (y1 == y2 - 2 and Ps[x2][7] != nullptr and ((CC == BLACK) ? Ps[x2][7]->getSym() == 'R' : Ps[x2][7]->getSym() == 'r') and Ps[x2][7]->moves == 0)
			{
				for (int i = y1 + 1; i <= y2; i++)
				{
					if (IsAnyPiece(Position{ x1,i }))
					{
						return false;
					}
				}
				return true;
			}
		}
	}
	return false;
}

void Board::DoCastling(int x1, int y1, int x2, int y2)
{
	Ps[x1][y1]->UnHighlight();
	Ps[x1][y1]->UnDraw();
	Ps[x2][y2] = Ps[x1][y1];
	Ps[x1][y1] = nullptr;
	Ps[x2][y2]->IsMoving = true;
	Ps[x2][y2]->ChangePos(Position{ x2,y2 });
	Ps[x2][y2]->IsMoving = false;
	Ps[x2][y2]->Draw();
	Move.times[CM]++;
	CM++;
	if ((Ps[x2][y2]->getSym() == 'R' or Ps[x2][y2]->getSym() == 'r') and y1 < y2)
	{
		Ps[x2][y2 + 1]->UnDraw();
		Ps[x2][y2 - 1] = Ps[x2][y2 + 1];
		Ps[x2][y2 + 1] = nullptr;
		Ps[x2][y2 - 1]->IsMoving = true;
		Ps[x2][y2 - 1]->ChangePos(Position{ x2,y2 - 1 });
		Ps[x2][y2 - 1]->IsMoving = false;
		Ps[x2][y2 - 1]->Draw();
		Move.x1.push_back(x2);
		Move.y1.push_back(y2 + 1);
		Move.x2.push_back(x2);
		Move.y2.push_back(y2 - 1);
		Move.P.push_back(nullptr);
		Move.times[CM - 1]++;
		Move.times.push_back(Move.times[CM - 1]);
	}
	else if ((Ps[x2][y2]->getSym() == 'R' or Ps[x2][y2]->getSym() == 'r') and y1 > y2)
	{
		Ps[x2][y2 - 1]->UnDraw();
		Ps[x2][y2 + 1] = Ps[x2][y2 - 1];
		Ps[x2][y2 - 1] = nullptr;
		Ps[x2][y2 + 1]->IsMoving = true;
		Ps[x2][y2 + 1]->ChangePos(Position{ x2,y2 + 1 });
		Ps[x2][y2 + 1]->IsMoving = false;
		Ps[x2][y2 + 1]->Draw();
		Move.x1.push_back(x2);
		Move.y1.push_back(y2 - 1);
		Move.x2.push_back(x2);
		Move.y2.push_back(y2 + 1);
		Move.P.push_back(nullptr);
		Move.times[CM - 1]++;
		Move.times.push_back(Move.times[CM - 1]);
	}
	else if ((Ps[x2][y2]->getSym() == 'K' or Ps[x2][y2]->getSym() == 'k') and y1 > y2)
	{
		Ps[x2][0]->UnDraw();
		Ps[x2][y2 + 1] = Ps[x2][0];
		Ps[x2][0] = nullptr;
		Ps[x2][y2 + 1]->IsMoving = true;
		Ps[x2][y2 + 1]->ChangePos(Position{ x2,y2 + 1 });
		Ps[x2][y2 + 1]->IsMoving = false;
		Ps[x2][y2 + 1]->Draw();
		Move.x1.push_back(x2);
		Move.y1.push_back(0);
		Move.x2.push_back(x2);
		Move.y2.push_back(y2 + 1);
		Move.P.push_back(nullptr);
		Move.times[CM - 1]++;
		Move.times.push_back(Move.times[CM - 1]);
	}
	else if ((Ps[x2][y2]->getSym() == 'K' or Ps[x2][y2]->getSym() == 'k') and y1 < y2)
	{
		Ps[x2][7]->UnDraw();
		Ps[x2][y2 - 1] = Ps[x2][7];
		Ps[x2][7] = nullptr;
		Ps[x2][y2 - 1]->IsMoving = true;
		Ps[x2][y2 - 1]->ChangePos(Position{ x2,y2 - 1 });
		Ps[x2][y2 - 1]->IsMoving = false;
		Ps[x2][y2 - 1]->Draw();
		Move.x1.push_back(x2);
		Move.y1.push_back(7);
		Move.x2.push_back(x2);
		Move.y2.push_back(y2 - 1);
		Move.P.push_back(nullptr);
		Move.times[CM - 1]++;
		Move.times.push_back(Move.times[CM - 1]);
	}
	PlaySound(TEXT("soundFX.wav"), NULL, SND_SYNC);
	CM++;
}

void Board::HighlightIfCastling(int x, int y)
{
	if (Ps[x][y]->getSym() == 'r' || Ps[x][y]->getSym() == 'R' || Ps[x][y]->getSym() == 'k' || Ps[x][y]->getSym() == 'K')
	{
		for (int i = 0; i < Dim; i++)
		{
			for (int j = 0; j < Dim; j++)
			{
				if (IsCastling(x, y, i, j))
				{
					HighlightedBoxWithText(Position{ i,j }, 14, "");
				}
			}
		}
	}
}

void Board::Clear()
{
	if (Ps != nullptr)
	{
		for (int i = 0; i < Dim; i++)
		{
			for (int j = 0; j < Dim; j++)
			{
				delete Ps[i][j];
			}
			delete[]Ps[i];
		}
		delete[]Ps;
		Ps = nullptr;
	}
	Move.x1.clear();
	Move.x2.clear();
	Move.y1.clear();
	Move.y2.clear();
	Move.P.clear();
	Move.times.clear();
}

Board::~Board()
{
	Clear();
}