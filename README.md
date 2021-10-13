# TicTacToe_AI
 A TicTacToe game in C++ that has a built in AI for you to play against. It's smart but not perfect - can you win?
Author: Chang Hi Lee(lee.c@wustl.edu)
Function: Implements a 3x3 board and player objects to play a game of TicTacToe. Can be played with either 1-player or 2-player options.
Usage:
- 2-player VS mode: TicTacToe.exe TicTacToe
- 1-player VS AI mode: TicTacToe.exe TicTacToe auto_player
- Inputting coordinates: x,y (no spaces, range 1~3)
Detailed Instructions:
- Please note this program only works on Windows. 
- You will be playing this game entirely within your command prompt window. Bring up your command prompt(cmd.exe) and type in the following: cd {DOWNLOAD_LOCATION}\TicTacToe_AI\TicTacToe\x64\Release
- Replace the entire bracket with the downloaded location of TicTacToe_AI. For example, if you placed it in Downloads, the full path is C:\Users\{user}\Downloads\TicTacToe_AI\TicTacToe\x64\Release. Make sure to replace {user} with your Windows username.
- Next, run TicTacToe.exe according to the proper usage format. (2-player: TicTacToe.exe TicTacToe, 1-player: TicTacToe.exe TicTacToe auto_player)
- The game is initialized. Input coordinates by using {x,y}. **Note that the axes range from 0 to 4, but you can only input in spaces 1 to 3.**
- Play a game of TicTacToe! Choosing the 1-player option will pit you against my AI.
AI design choice:
- I conceptualized the board as lines of three pieces(lines can be horizontal, vertical, or diagonal). I classified these lines into subcategories of winning lines, touching lines, balanced lines, or blank lines. 
- Winning lines had two pieces of a same piece with an empty space, touching lines had one piece with two empty spaces, balanced lines had two different pieces with one empty space, and blank lines had no pieces. 
- I also made an enum signifying whether the player or AI had a winning line at the end of each move. Based on the enum, the AI would choose to be defensive or aggressive. If the player had a higher enum(i.e. closer to winning), the AI would play defensively and act to block the empty space in the player's winning line. If the player had a lower enum, the AI would play aggressively to secure a win. There is an exception case for the AI at the start of a new game where the board is empty except the player's first inputted piece. 
- I always had the player go first, then I gathered the lines on which the user's piece was on, randomized their order, and had the AI put a piece on that line as to block the player from making a meaningful move next turn. 
- I tested the AI with random, unlogical movements to see if it would pursue a win, while defending against a player victory, which it did.

Example output of logical moves by the player(will result in a draw) : 

4
3
2
1
0
 0 1 2 3 4
(Player X, the user, goes first)

4
3
2      X
1
0
 0 1 2 3 4

Player X: 3,2;



4
3
2      X
1      O
0
 0 1 2 3 4

Player O: 3,1;

4
3
2    X X
1      O
0
 0 1 2 3 4

Player X: 2,2; 3,2;


4
3
2  O X X
1      O
0
 0 1 2 3 4
Player O: 3,1; 1,2;

4
3
2  O X X
1  X   O
0
 0 1 2 3 4

Player X: 1,1; 2,2; 3,2;



4
3      O
2  O X X
1  X   O
0
 0 1 2 3 4

Player O: 3,1; 1,2; 3,3;


4
3      O
2  O X X
1  X X O
0
 0 1 2 3 4

Player X: 1,1; 2,1; 2,2; 3,2;


4
3    O O
2  O X X
1  X X O
0
 0 1 2 3 4

Player O: 3,1; 1,2; 2,3; 3,3;

4
3  X O O
2  O X X
1  X X O
0
 0 1 2 3 4

Player X: 1,1; 2,1; 2,2; 3,2; 1,3;

The game was played for 9 turns. No winning moves remain and the game is a draw.

Example output of playing illogically to let the AI win : 

4
3
2
1  X
0
 0 1 2 3 4

Player X: 1,1;



4
3
2  O
1  X
0
 0 1 2 3 4

Player O: 1,2;

4
3  X
2  O
1  X
0
 0 1 2 3 4

Player X: 1,1; 1,3;



4
3  X
2  O O
1  X
0
 0 1 2 3 4

Player O: 1,2; 2,2;

4
3  X X
2  O O
1  X
0
 0 1 2 3 4

Player X: 1,1; 1,3; 2,3;



4
3  X X
2  O O O
1  X
0
 0 1 2 3 4

Player O: 1,2; 2,2; 3,2;

Player O won the game!