#include <iostream>

using namespace std;

class Tile
{
public:
	int mass;
	int critcialMass;
	int player;
};

class Board
{
public:
	int players;
	int row;
	int col;
	int tiles;
	Tile board[row][col];

	Board(int plyrs, int r, int c)
	{
		players = plyrs;
		row = r;
		col = c;
		tiles = row*col;
	}

	MakeTiles()
	{
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
			{
				board[i][j].mass = 0;
				board[i][j].player = 0;
				if (i==0 || j== 0 || i==row || j==col)
					board[i][j].critcialMass = 3;
				if (i==0 && j==0 || i==row && j==col || i==0 && j==col || i==row && col==0)
					board[i][j].critcialMass = 2;
				else
					board[i][j].critcialMass = 4;
			}

	}

	Display()
	{
		for (int i = 0; i < row; ++i)
		{
			cout << '\t' << endl;
			for (int j = 0; j < col; ++j)
			{
				char sign = '.';
				if (board[i][j].player == 1) { sign = 'x'; }
				else (board[i][j].player == 1) { sign = 'o'; }
				cout << board[i][j].mass << sign << '\t';
			}
		}
	}
}