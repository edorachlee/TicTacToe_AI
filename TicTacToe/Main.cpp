// Main.cpp
// Author : Chang Hi Lee / lee.c@wustl.edu
// This .cpp file contains the 'main' function. Defines a TicTacToeGame class object 'game', and starts a Tic Tac Toe game using the play() method from the class.

#include "MainHeader.h"
#include "TicTaceToeGameHeader.h"

int helpMsg() //Helper function called in main() that prints out a help message and returns wrongNumCmdArgs = 2. The input will always be argv[0].
{
	cout << "For two players, follow this format : TicTacToe.exe TicTacToe" << endl << "For one player, follow this format : TicTacToe.exe TicTacToe auto_player";
	return wrongNumCmdArgs;
}

int main(int argc, char* argv[])
{
	if (argc != argcTwo && argc != argcThree) //argc is not two or three
	{
		helpMsg();
	}

	else //argc is either two or three
	{
		TicTacToeGame game;
		/*string arg1 = argv[argvOne];
		string arg2 = argv[argvTwo];*/
		if (argv[argvOne] == string ("TicTacToe")) //if first argument is TicTacToe
		{
			if (argc == argcTwo) //if there are two inputs
			{
				return game.play();
			}

			else if (argc == argcThree) //if second argument is auto_player
			{
				if (argv[argvOne] == string("TicTacToe") && argv[argvTwo] == string ("auto_player"))
				{
					return game.auto_play();
				}

				else
				{
					helpMsg();
				}
			}
		}

		else
		{
			helpMsg();
		}
	}
}
