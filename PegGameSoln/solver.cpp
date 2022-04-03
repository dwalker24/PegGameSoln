//solve peg game
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

//adts
struct boardSetup
{
	vector<vector<int>> board;
	vector<vector<vector<int>>> path;
};


//fcn prototypes
vector<boardSetup> generateSolns(boardSetup);
vector<boardSetup> generateNextMoves(boardSetup);
void printSolnPaths(vector<boardSetup>);
void printBoard(vector<vector<int>>);
bool isSolved(vector<vector<int>>);

int main()
{
	//solve using bfs
	vector<vector<int>> board = {
		{-1, -1, -1, 1, 1, 1, -1, -1, -1},
		{-1, -1, -1, 1, 1, 1, -1, -1, -1},
		{-1, -1, -1, 1, 1, 1, -1, -1, -1},
		   {1, 1, 1, 1, 1, 1, 1, 1, 1},
		   {1, 1, 1, 1, 0, 1, 1, 1, 1},
		   {1, 1, 1, 1, 1, 1, 1, 1, 1},
		{-1, -1, -1, 1, 1, 1, -1, -1, -1},
		{-1, -1, -1, 1, 1, 1, -1, -1, -1},
		{-1, -1, -1, 1, 1, 1, -1, -1, -1}
	};
	printBoard(board);
	boardSetup initialBoard = { board, {} };
	
	vector<boardSetup> solns = generateSolns(initialBoard);
	printSolnPaths(solns);
	system("pause");
	return 0;
}

vector<boardSetup> generateSolns(boardSetup board)
{
	//vector to hold solns
	vector<boardSetup> solns;

	//bfs
	queue<boardSetup> boardQueue;
	boardQueue.push(board);
	while (!boardQueue.empty())
	{
		if (isSolved(boardQueue.front().board))
		{
			solns.push_back(board);
			boardQueue.pop();
		}

		vector<boardSetup> nextBoard = generateNextMoves(board);
		for (int i = 0; i < nextBoard.size(); i++)
		{
			boardQueue.push(nextBoard[i]);
		}
	}
	
	return solns;
}

vector<boardSetup> generateNextMoves(boardSetup board)
{
	//for each peg, see if you can eat another; if so, add to vector of next moves
	vector<boardSetup> nextMoves;
	for (int i = 0; i < board.board.size(); i++)
	{
		for (int j = 0; j < board.board.size(); j++)
		{
			if (board.board[i][j] != -1)
			{
				//check if you can eat up
				if (i - 2 >= 0)
				{
					if (board.board[i - 2][j] == 0 && board.board[i - 1][j] == 1)
					{
						vector<vector<int>> newBoard(board.board.begin(), board.board.end());
						newBoard[i - 1][j] = 0;
						newBoard[i - 2][j] = 1;
						newBoard[i][j] = 0;

						boardSetup newBoardSetup = { newBoard, board.path };
						newBoardSetup.path.push_back(board.board);
						nextMoves.push_back(newBoardSetup);
					}
				}

				//check if you can eat down
				if (i + 2 < board.board.size())
				{
					if (board.board[i + 2][j] == 0 && board.board[i + 1][j] == 1)
					{
						vector<vector<int>> newBoard(board.board.begin(), board.board.end());
						newBoard[i + 1][j] = 0;
						newBoard[i + 2][j] = 1;
						newBoard[i][j] = 0;

						boardSetup newBoardSetup = { newBoard, board.path };
						newBoardSetup.path.push_back(board.board);
						nextMoves.push_back(newBoardSetup);
					}
				}

				//check if you can eat left
				if (j - 2 >= 0)
				{
					if (board.board[i][j - 2] == 0 && board.board[i][j - 1] == 1)
					{
						vector<vector<int>> newBoard(board.board.begin(), board.board.end());
						newBoard[i][j - 1] = 0;
						newBoard[i][j - 2] = 1;
						newBoard[i][j] = 0;

						boardSetup newBoardSetup = { newBoard, board.path };
						newBoardSetup.path.push_back(board.board);
						nextMoves.push_back(newBoardSetup);
					}
				}
				//check if you can eat right
				if (j + 2 < board.board.size())
				{
					if (board.board[i][j + 2] == 0 && board.board[i][j + 1] == 1)
					{
						vector<vector<int>> newBoard(board.board.begin(), board.board.end());
						newBoard[i][j + 1] = 0;
						newBoard[i][j + 2] = 1;
						newBoard[i][j] = 0;

						boardSetup newBoardSetup = { newBoard, board.path };
						newBoardSetup.path.push_back(board.board);
						nextMoves.push_back(newBoardSetup);
					}
				}
			}
		}
	}

	return nextMoves;
}

void printSolnPaths(vector<boardSetup> boards)
{
	for (int i = 0; i < boards.size(); i++)
	{
		cout << "Soln " << i << ":" << endl;
		for (int j = 0; j < boards[i].path.size(); j++)
		{
			printBoard(boards[i].path[j]);
		}
	}
}

void printBoard(vector<vector<int>> board)
{
	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board.size(); col++)
		{
			if (board[row][col] == -1)
			{
				cout << setw(3) << "";
			}
			else
			{
				cout << setw(3) << board[row][col];
			}
		}

		cout << endl;
	}
}

bool isSolved(vector<vector<int>> board)
{
	int counter = 0;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board.size(); j++)
		{
			if (board[i][j] == 1)
			{
				counter++;
			}
			if (counter > 1)
			{
				return false;
			}
		}
	}

	return true;
}