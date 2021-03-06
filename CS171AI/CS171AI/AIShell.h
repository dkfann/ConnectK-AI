#ifndef AISHELL_H
#define AISHELL_H

#pragma once
#include "Move.h"
#include <time.h>
#include <vector>


// A new AIShell will be created for every move request.
class AIShell {

public:
	//these represent the values for each piece type. 
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;
	double diff;

private:
	//Do not alter the values of numRows or numcols. 
	//they are used for deallocating the gameState variable.
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	Move lastMove; //this is the move made last by your oppenent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead. 
	

public:
	int deadline; //this is how many milliseconds the AI has to make move. 
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4 

	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move makeMove();
	int PieceCheckAI(int col, int row, int **S);
	int PieceCheckHU(int col, int row, int **S);
	int Eval(int **S);
	void printEval(std::vector<int> eval);
	std::vector<std::pair<int, int> > possMoves(int **S);
	//std::vector<std::pair<int, int>> move_list;
	void printMoves();
	std::pair<std::pair<int, int>, int> DFS(int depth, int **S, int player, time_t start);
	std::pair<std::pair<int, int>, int> IDS();
};

#endif //AISHELL_H
