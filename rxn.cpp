#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Tile
{
	int mass;
	int critcialMass;
	int OwnedBy;
}Tile;

class Board
{
public:
	int players;
	int row;
	int col;
	int tiles;
	int turn;
	int win;
	char sign[2];
	Tile board[10][10];

	Board(int plyrs, int r, int c)
	{
		players = plyrs;
		sign[0] = '@';
		sign[1] = '#';
		row = r;
		col = c;
		tiles = row*col;
		Tile board[row][col];
		turn = 0;
		win = 0;
	}

	void MakeTiles()
	{
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
			{
				board[i][j].mass = 0;
				board[i][j].OwnedBy = 0;

				if (i==0 && j==0 || i==row-1 && j==col-1 || i==0 && j==col-1 || i==row-1 && j==0)
					board[i][j].critcialMass = 2;
				else if (i==0 || j== 0 || i==row-1 || j==col-1)
					board[i][j].critcialMass = 3;
				else
					board[i][j].critcialMass = 4;
			}

	}

	void Display()
	{
		for (int i = 0; i < col; ++i)
		{
			cout  << '\t' << i;
		}
		cout << endl << endl;

		for (int i = 0; i < row; ++i)
		{
			cout << i << "\t";
			for (int j = 0; j < col; ++j)
			{
				
				if (board[i][j].mass != 0) { cout << board[i][j].mass << sign[board[i][j].OwnedBy - 1] << '\t'; }
				else { cout << '.' << '\t'; }
			}
			cout << "\n" << endl;
		}
		cout << "\n" << endl;
	}

	void Input()
	{
		int player = turn%2 + 1;
		int moveRow;
		int moveCol;
		char sign = (player == 1) ? '@' : '#';

		cout << sign << " Player Move: ";
		cin >>  moveRow >> moveCol;
		//if ((moveRow > 0 && moveRow < row-1) || (moveCol > 0 && moveCol < col-1))
		//	Input();

		int ownedby = board[moveRow][moveCol].OwnedBy;
		if (ownedby == 0 || ownedby == player )
		{
			Rxn(moveRow, moveCol, player);
			turn++;
		}
		else
		{
			cout << "This tile is owned by another Player " << endl;
			Input();
		}

	}

	void Refree()
	{
		int playerOwned = 0;

		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
			{
				if (board[i][j].OwnedBy != 0)
				{
					if (playerOwned == 0)
						playerOwned = board[i][j].OwnedBy;
					else if (board[i][j].OwnedBy != playerOwned)
						return;
				}
 			}

 		win = playerOwned;
 		return;
	}

	void Rxn(int i, int j, int playermove)
	{
		board[i][j].mass++;
		board[i][j].OwnedBy = playermove;
		Display();

		if (board[i][j].mass == board[i][j].critcialMass)
		{
			if (board[i][j].critcialMass == 4)
			{
				board[i][j].mass = 0;
				board[i][j].OwnedBy = 0;
				Rxn(i-1, j, playermove);
				Rxn(i+1, j, playermove);
				Rxn(i, j-1, playermove);
				Rxn(i, j+1, playermove);
			}

			else if (board[i][j].critcialMass == 3)
			{
				if (i== row-1 || i == 0 )
				{
					board[i][j].mass = 0;
					board[i][j].OwnedBy = 0;
					Rxn(i, j+1, playermove);
					Rxn(i, j-1, playermove);
				}
				else if (j== col-1 || j == 0 )
				{
					board[i][j].mass = 0;
					board[i][j].OwnedBy = 0;
					Rxn(i+1, j, playermove);
					Rxn(i-1, j, playermove);
				}
			}

			else if (board[i][j].critcialMass == 2)
			{
				
				if (i==0 && j==0)
				{
					board[i][j].mass = 0;
					board[i][j].OwnedBy = 0;
					Rxn(i, j+1, playermove);
					Rxn(i+1, j, playermove);
				}
				else if (i==0 && j==col-1)
				{
					board[i][j].mass = 0;
					board[i][j].OwnedBy = 0;
					Rxn(i, j-1, playermove);
					Rxn(i+1, j, playermove);
				}
				else if (i==row-1 && j==0)
				{
					board[i][j].mass = 0;
					board[i][j].OwnedBy = 0;
					Rxn(i, j+1, playermove);
					Rxn(i-1, j, playermove);
				}
				else if (i==row-1  && j==col-1 )
				{
					board[i][j].mass = 0;
					board[i][j].OwnedBy = 0;
					Rxn(i-1, j, playermove);
					Rxn(i, j-1, playermove);
				}
			}

		}
	}
};

int main()
{
	int row;
	int col;
	int players = 2;
	
	cout << "\t####################" << endl;
	cout << "\t********RXN********" << endl;
	cout << "\t####################" << endl;

	cout << "Board Dimensions: " << endl;
	cin >> row >> col;

	Board newgame(players, row, col);
	newgame.MakeTiles();
	newgame.Display();

	newgame.Input();

	while(newgame.win == 0)
	{
		newgame.Input();
		newgame.Refree();
	}

	cout << "########################################################" << endl;
	cout << "\t \t PLAYER " << newgame.sign[newgame.win - 1] << " WINS!" << endl;
	cout << "########################################################" << endl;
	cout << endl; 
	return 0;
}