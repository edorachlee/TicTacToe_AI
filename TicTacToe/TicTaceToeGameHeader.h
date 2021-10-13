// TicTacToeGameHeader.h
// Author : Chang Hi Lee / lee.c@wustl.edu
// Header file for TicTacToeGame.cpp. Contains declarations TicTacToeGame class, member variables, and functions.

#pragma once
#include "MainHeader.h"

enum errorMsgs { autoSuccess = 101, printSuccess = 101, coordReadSuccess = 102, validMove = 103, quit = 104, coordReadFail = 105, promptFail = 106,  turnFail = 107, playFail = 108 };
enum gameResult{ win = 0, noWin = 1 };
enum pieceType { blank, X, O };
enum board {width = 5, height = 5, turnZero = 0 , turnMax = 9};
enum maxInput { userInputMaxLength = 3 };
enum piecePosition {lower_left = 6, lower_center = 7, lower_right = 8, mid_left = 11, center = 12, mid_right = 13, upper_left = 16, upper_center = 17, upper_right = 18};
enum winningPieces {zero, one, two, three, four };

string enum2type(pieceType type); // Function declaration for converting enum value to piece type

class TicTacToeGame {
	friend ostream& operator<<(ostream& os, const TicTacToeGame& game); //enables access to member variables by the ostream operator

private:
	int boardWidth;
	int boardHeight;
	vector<pieceType> pieceList;
	int turnCount;

public:
	TicTacToeGame(); //constructor
	bool done();
	bool draw();
	int prompt(unsigned int& x, unsigned int& y);
	int turn();
	int play();
	int auto_player();
	int auto_play();
};

ostream& operator<<(ostream& os, const TicTacToeGame& game); //enables TicTacToe class objects to be passed to the ostream operator


