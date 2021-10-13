// TicTacToeGame.cpp
// Author : Chang Hi Lee / lee.c@wustl.edu
// This .cpp file contains function definitions for the TicTacToeGame class.

#include "TicTaceToeGameHeader.h"
#include <vector>


string enum2type(pieceType type)
{
	vector<string> pieceTypeList = { " ", "X", "O" };
	return pieceTypeList[type];
}

TicTacToeGame::TicTacToeGame() //initialize blank board via constructor, set turnCount to 0 (X goes first)
{
	boardWidth = width;
	boardHeight = height;
	turnCount = turnZero;
	for (int i = 0; i < boardWidth * boardHeight; i++)
	{
		pieceList.push_back(blank);
	}
}

ostream& operator<<(ostream& os, const TicTacToeGame& game) //allow game board to be printed out via '<<'
{
	for (int rowPos = height - 1; rowPos >= 0; rowPos--)
	{
		os << rowPos;
		for (int colPos = 0; colPos < width; colPos++)
		{
			int index = width * rowPos + colPos;
			os << enum2type(game.pieceList[index]) << " ";
		}
		os << endl;
	}
	os << " 0 1 2 3 4" << endl;

	return os;
}

bool TicTacToeGame::done() //Define win conditions for tic tac toe
{
	bool done = false;
	vector<int> searchAt = { lower_left, mid_left, upper_left, upper_center, upper_right };
	// Start check at lower left corner, move along edges to upper right corner
	for (int i = 0; i < searchAt.size(); i++)
	{
		pieceType foundPiece = pieceList[searchAt[i]];
		if (foundPiece != blank)
		{
			if (searchAt[i] == lower_left) //search from lower left corner
			{
				if (foundPiece == pieceList[mid_left] && foundPiece == pieceList[upper_left])
				{
					done = true;
				}

				else if (foundPiece == pieceList[center] && foundPiece == pieceList[upper_right])
				{
					done = true;
				}

				else if (foundPiece == pieceList[lower_center] && foundPiece == pieceList[lower_right])
				{
					done = true;
				}
			}

			else if (searchAt[i] == mid_left) //search from middle left
			{
				if (foundPiece == pieceList[center] && foundPiece == pieceList[mid_right])
				{
					done = true;
				}
			}

			else if (searchAt[i] == upper_left) //search from upper left
			{
				if (foundPiece == pieceList[upper_center] && foundPiece == pieceList[upper_right])
				{
					done = true;
				}

				else if (foundPiece == pieceList[center] && foundPiece == lower_right)
				{
					done = true;
				}
			}

			else if (searchAt[i] == upper_center) //search from upper center
			{
				if (foundPiece == pieceList[center] && foundPiece == pieceList[lower_center])
				{
					done = true;
				}
			}

			else if (searchAt[i] == upper_right) //search from upper right
			{
				if (foundPiece == pieceList[mid_right] && foundPiece == pieceList[lower_right])
				{
					done = true;
				}
			}
		}

	}
	return done;
}

bool TicTacToeGame::draw() //Define draw conditions for tic tac toe
{
	bool draw = true;
	///lower_left = 6, lower_center = 7, lower_right = 8, mid_left = 11, center = 12, mid_right = 13, upper_left = 16, upper_center = 17, upper_right = 18
	vector<pieceType> gameBoard =
	{ pieceList[lower_left], pieceList[lower_center], pieceList[lower_right], pieceList[mid_left],
		pieceList[center], pieceList[mid_right], pieceList[upper_left], pieceList[upper_center], pieceList[upper_right] };

	if (done() || find(gameBoard.begin(), gameBoard.end(), blank) != gameBoard.end()) // if done() returns true or a blank space is left within the game board
	{
		draw = false;
	}
	return draw;
}

int TicTacToeGame::prompt(unsigned int& x, unsigned int& y)
{
	string userInput;
	bool isShort = false;
	bool containsComma = false;
	bool readCoord = false;

	while (!isShort || !containsComma || !readCoord) //while user input is too long, does not contain a comma, or coordinates cannot be read
	{
		cout << "Please input a valid coordinate in the form of x,y for your next move. Type 'quit' to quit the game." << endl;
		cin >> userInput;

		if (userInput == "quit")
		{
			return quit;
		}

		else
		{
			if (userInput.length() <= userInputMaxLength) //if user input length is less than the allowed maximum length
			{
				isShort = true;
			}

			for (int i = 0; i < userInput.length(); i++)
			{
				if (userInput[i] == ',')
				{
					userInput[i] = ' '; //replace comma with space
					containsComma = true;

				}
			}

			if (isShort && containsComma) //if user input is allowed length and contains a comma
			{
				istringstream iss(userInput);
				if (iss >> x && iss >> y) //if coordinate values were successfully extracted from user input
				{
					readCoord = true;
					return coordReadSuccess;
				}
			}
		}
	}

	return promptFail;
}

int TicTacToeGame::turn() //X goes first
{
	pieceType piece;
	if (turnCount % 2 == turnZero) //if it is X's turn(turn starts at 0)
	{
		piece = X;
		cout << "Player X's turn." << endl;
	}

	else //if it is O's turn(turn starts at 1)
	{
		piece = O;
		cout << "Player O's turn." << endl;
	}

	unsigned int x, y = 0;
	bool end = false;
	while (!end)
	{

		if (prompt(x, y) == quit)
		{
			return quit;
		}

		else if (x <= 0 || y <= 0 || x >= 4 || y >= 4) //if input coordinate is in edge space or exceeds it
		{
			cout << "Invalid position." << endl;
		}

		else if (pieceList[boardWidth * y + x] != blank) //if a piece already exists at input coordinate
		{
			cout << "A game piece already exists at that position." << endl;
		}

		else
		{
			pieceList.at(boardWidth * y + x) = piece; //replace blank piece with new game piece
			vector<int> validPieceList;

			for (int i = 0; i < pieceList.size(); i++)
			{
				if (pieceList[i] == piece)
				{
					validPieceList.push_back(i);
				}
			}

			int rowPos, colPos;

			cout << endl << endl << *this << endl;
			cout << "Player " << enum2type(piece) << ": ";
			for (int j = 0; j < validPieceList.size(); j++) //calculating each valid piece's coordinates
			{
				rowPos = validPieceList[j] / boardWidth;
				colPos = validPieceList[j] % boardWidth;

				cout << colPos << "," << rowPos << "; ";
			}
			cout << endl << endl;
			turnCount++; //increase turn counter stored in game
			end = true;
			return validMove;
		}
	}
	return turnFail;
}

int TicTacToeGame::play()
{
	cout << *this << endl;
	while (turnCount <= turnMax)
	{
		if (turn() == quit)
		{
			cout << "The game was played for " << turnCount << " turns. A player decided to quit." << endl;
			return quit;
		}

		else if (done()) //if there is a winner
		{
			if (turnCount % 2 == 1) //if player X wins
			{
				cout << "Player X won the game!" << endl;
			}

			else //if player O wins
			{
				cout << "Player O won the game!" << endl;
			}
			return win;
		}

		else if (draw()) //if the game is a draw
		{
			cout << "The game was played for " << turnCount << " turns. No winning moves remain and the game is a draw." << endl;
			return noWin;
		}
	}

	return playFail;
}

int TicTacToeGame::auto_player() //Player goes first
{
	winningPieces AIWinningPieces = zero;
	winningPieces playerWinningPieces = zero;

	vector<int> row1 = { lower_left, lower_center, lower_right };
	vector<int> row2 = { mid_left, center, mid_right };
	vector<int> row3 = { upper_left, upper_center, upper_right };
	vector<int> col1 = { lower_left, mid_left, upper_left };
	vector<int> col2 = { lower_center, center, upper_center };
	vector<int> col3 = { lower_right, mid_right, upper_right };
	vector<int> diag1 = { lower_left, center, upper_right };
	vector<int> diag2 = { upper_left, center, lower_right };

	vector<vector<int>> lines = { row1, row2, row3, col1, col2, col3, diag1, diag2 };

	vector<vector<int>> playerWinningLines; //winning lines with two same pieces and one empty space
	vector<vector<int>> AIWinningLines;
	vector<vector<int>> playerTouchingLines; //lines with one piece and two empty spaces
	vector<vector<int>> AITouchingLines;

	for (int i = 0; i < lines.size(); i++)
	{
		int XCounter = 0;
		int OCounter = 0;
		for (int j = 0; j < lines[i].size(); j++)
		{
			if (pieceList[lines[i][j]] == X)
			{
				XCounter++;
			}

			else if (pieceList[lines[i][j]] == O)
			{
				OCounter++;
			}
		}

		if (XCounter != zero && OCounter == zero)
		{
			if (XCounter == two)
			{
				playerWinningLines.push_back(lines[i]);
				playerWinningPieces = two;
			}

			else
			{
				playerTouchingLines.push_back(lines[i]);
			}
		}

		else if (OCounter != zero && XCounter == zero)
		{
			if (OCounter == two)
			{
				AIWinningLines.push_back(lines[i]);
				AIWinningPieces = two;
			}

			else
			{
				AITouchingLines.push_back(lines[i]);
			}
		}
	}
	
	if (turnCount == turnZero+1) // AI start condition
	{
		int randomIndex = rand() % four;
		for (int i = 0; i < playerTouchingLines[randomIndex].size(); i++) //randomize the order of player touching lines
		{
			if (pieceList[playerTouchingLines[randomIndex][i]] == blank) //replace the first blank space in a player touched line with the AI's piece
			{
				pieceList[playerTouchingLines[randomIndex][i]] = O;
				i = playerTouchingLines[randomIndex].size();
			}
		}
	}

	else if (playerWinningLines.size() == zero && AIWinningLines.size() == zero) //if there are no definitely winning lines(either empty or balanced)
	{
		if (AITouchingLines.size() != zero) //if there is at least one AI touched line
		{
			for (int i = 0; i < AITouchingLines.size(); i++)
			{
				for (int j = 0; j < AITouchingLines[i].size(); j++)
				{
					if (pieceList[AITouchingLines[i][j]] == blank) //replace the first blank space in an AI touched line with the AI's piece, making a winning line
					{
						pieceList[AITouchingLines[i][j]] = O;
						j = AITouchingLines[i].size();
					}
				}
				i = AITouchingLines.size();
			}
			
		}
	}

	else if (AIWinningPieces >= playerWinningPieces) //if the AI is closer to winning than the player, play aggressively
	{
		//Act to secure a win
		for (int i = 0; i < AIWinningLines.size(); i++)
		{
			for (int j = 0; j < AIWinningLines[i].size(); j++)
			{
				if (pieceList[AIWinningLines[i][j]] == blank)
				{
					pieceList[AIWinningLines[i][j]] = O;
					j = AIWinningLines[i].size();
				}
			}
			i = AIWinningLines.size();
		}
	}
	
	else if (AIWinningPieces < playerWinningPieces) //if player is closer to winning than AI, play defensively
	{
		//Act to prevent player from winning
		for (int i = 0; i < playerWinningLines.size(); i++)
		{
			for (int j = 0; j < playerWinningLines[i].size(); j++)
			{
				if (pieceList[playerWinningLines[i][j]] == blank)
				{
					pieceList[playerWinningLines[i][j]] = O;
					j = playerWinningLines[i].size();
				}
			}
			i = playerWinningLines.size();
		}
	}

	vector<int> validPieceList;
	pieceType piece = O;
	for (int i = 0; i < pieceList.size(); i++)
	{
		if (pieceList[i] == piece)
		{
			validPieceList.push_back(i);
		}
	}

	int rowPos, colPos;

	cout << endl << endl << *this << endl;
	cout << "Player " << enum2type(piece) << ": ";
	for (int j = 0; j < validPieceList.size(); j++) //calculating each valid piece's coordinates
	{
		rowPos = validPieceList[j] / boardWidth;
		colPos = validPieceList[j] % boardWidth;

		cout << colPos << "," << rowPos << "; ";
	}
	cout << endl << endl;
	turnCount++; //increase turn counter stored in game
	return validMove;
}

int TicTacToeGame::auto_play() //a similar method to play() designed for use with auto_player
{
	cout << *this << endl;
	while (turnCount <= turnMax)
	{
		if (turnCount % 2 == turnZero) //if it is X's turn(turn starts at 0)
		{
			if (turn() == quit)
			{
				cout << "The game was played for " << turnCount << " turns. A player decided to quit." << endl;
				return quit;
			}
		}

		else //if it is O's turn(turn starts at 1)
		{
			auto_player();
		}

		if (done()) //if there is a winner
		{
			if (turnCount % 2 == 1) //if player X wins
			{
				cout << "Player X won the game!" << endl;
			}

			else //if player O wins
			{
				cout << "Player O won the game!" << endl;
			}
			return win;
		}

		else if (draw()) //if the game is a draw
		{
			cout << "The game was played for " << turnCount << " turns. No winning moves remain and the game is a draw." << endl;
			return noWin;
		}
	}

	return playFail;
}
