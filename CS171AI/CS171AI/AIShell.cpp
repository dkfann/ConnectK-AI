#include "AIShell.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <stdlib.h>


//#include <Windows.h>
extern double diff = 0;


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline = 0;
	this->numRows = numRows;
	this->numCols = numCols;
	this->gravityOn = gravityOn;
	this->gameState = gameState;
	this->lastMove = lastMove;
}


AIShell::~AIShell()
{

	//delete the gameState variable.
	for (int i = 0; i<numCols; i++) {
		delete[] gameState[i];
	}
	delete[] gameState;

}

void AIShell::printEval(std::vector<int> eval)
{
	std::cout << "Feature Values: " << std::endl;
	for (int i = 0; i < eval.size(); i++)
	{
		std::cout << " Col[" << i << "] = " << eval[i];
	}

	std::cout << std::endl;
}

std::vector<std::pair<int, int> > AIShell::possMoves(int **S)
{
	std::vector<std::pair<int, int> > move_list;
	std::cout << "In possmoves" << std::endl;
	std::pair<int, int> coord;

	for (int col = 0; col < numCols; col++)
	{
		for (int row = 0; row < numRows; row++)
		{
			if (S[col][row] == NO_PIECE)
			{
				std::cout << "Adding piece: " << "(" << col << "," << row << ")" << std::endl;
				coord = std::make_pair(col, row);
				move_list.push_back(coord);
				break;
			}
		}
	}
	return move_list;
}

//void AIShell::printMoves()
//{
//	std::cout << "Possible Moves: ";
//	std::cout << move_list.size() << std::endl;
//	for (int i = 0; i < move_list.size(); i++)
//	{
//		std::cout << "(" << move_list[i].first << "," << move_list[i].second << "), ";
//	}
//	std::cout << std::endl;
//}
int AIShell::PieceCheckAI(int col, int row, int **S)
{
	int l, r, t, b, tl, tr, bl, br;
	l = r = t = b = tl = tr = bl = br = 0;

	int i;
	int result = 0;
	for (i = 1; i < std::min(col, k); i++)
	{
		if (S[col - i][row] == AI_PIECE)
		{
			l++;
		}
		else
		{
			break;
		}
	}

	//Checking pieces to the right
	for (i = 1; i < std::min(numCols - col, k); i++)
	{
		if (S[col + i][row] == AI_PIECE)
		{
			r++;
		}
		else
		{
			break;
		}
	}

	//Checking pieces to bottom left
	for (i = 1; i < std::min(std::min(row, col), k); i++)
	{
		if (S[col - i][row - i] == AI_PIECE)
		{
			bl++;
		}
		else
		{
			break;
		}
	}

	//Checking pieces to bottom right
	for (i = 1; i < std::min(std::min(row, numCols - col), k); i++)
	{
		if (S[col + i][row - i] == AI_PIECE)
		{
			br++;
		}
		else
		{
			break;
		}
	}

	//Checking pieces to top left
	for (i = 1; i < std::min(std::min(numRows - row, col), k); i++)
	{
		if (S[col - i][row + i] == AI_PIECE)
		{
			tl++;
		}
		else
		{
			break;
		}

	}

	//Checking pieces to top right
	for (i = 1; i < std::min(std::min(numRows - row, numCols - col), k); i++)
	{
		if (S[col + i][row + i] == AI_PIECE)
		{
			tr++;
		}
		else
		{
			break;
		}
	}

	//Checking pieces to top
	for (i = 1; i < std::min(numRows - row, k); i++)
	{
		if (S[col][row + i] == AI_PIECE)
		{
			t++;
		}

		else
		{
			break;
		}
	}

	//Checking pieces to bottom
	for (i = 1; i < std::min(row, k); i++)
	{
		if (S[col][row - i] == AI_PIECE)
		{
			b++;
		}
		else
		{
			break;
		}
	}
	std::vector<int> values = { l, r, t, b, tl, tr, bl, br };
	for (i = 0; i < values.size(); i++)
	{
		if (values[i] == k - 1)
		{
			result += values[i] + 100;
		}

		else
		{
			result += values[i] * 15;
		}
	}
	return result;
}

int AIShell::PieceCheckHU(int col, int row, int **S)
{
	int l, r, t, b, tl, tr, bl, br;
	l = r = t = b = tl = tr = bl = br = 0;

	int i;
	int result = 0;
	for (i = 1; i < std::min(col, k); i++)
	{
		if (S[col - i][row] == HUMAN_PIECE)
		{
			l++;
			if (l == k - 2)
			{
				if (S[col - i - 1][row] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}
		else
		{
			break;
		}
	}


	//Checking pieces to the right
	for (i = 1; i < std::min(numCols - col, k); i++)
	{
		if (S[col + i][row] == HUMAN_PIECE)
		{
			r++;
			if (r == k - 2)
			{
				if (S[col + i + 1][row] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}
		else
		{
			break;
		}
	}

	//Checking pieces to bottom left
	for (i = 1; i < std::min(std::min(row, col), k); i++)
	{
		if (S[col - i][row - i] == HUMAN_PIECE)
		{
			bl++;
			if (bl == k - 2)
			{
				if (S[col - i - 1][row - i - 1] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}
		else
		{
			break;
		}
	}

	//Checking pieces to bottom right
	for (i = 1; i < std::min(std::min(row, numCols - col), k); i++)
	{
		if (S[col + i][row - i] == HUMAN_PIECE)
		{
			br++;
			if (br == k - 2)
			{
				if (S[col + i + 1][row - i - 1] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}
		else
		{
			break;
		}
	}

	//Checking pieces to top left
	for (i = 1; i < std::min(std::min(numRows - row, col), k); i++)
	{
		if (S[col - i][row + i] == HUMAN_PIECE)
		{
			tl++;
			if (tl == k - 2)
			{
				if (S[col - i - 1][row + i + 1] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}
		else
		{
			break;
		}

	}

	//Checking pieces to top right
	for (i = 1; i < std::min(std::min(numRows - row, numCols - col), k); i++)
	{
		if (S[col + i][row + i] == HUMAN_PIECE)
		{
			tr++;
			if (tr == k - 2)
			{
				if (S[col + i + 1][row + i + 1] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}
		else
		{
			break;
		}
	}

	//Checking pieces to top
	for (i = 1; i < std::min(numRows - row, k); i++)
	{
		if (S[col][row + i] == HUMAN_PIECE)
		{
			t++;
			if (t == k - 2)
			{
				if (S[col][row + i + 1] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}

		else
		{
			break;
		}
	}

	//Checking pieces to bottom
	for (i = 1; i < std::min(row, k); i++)
	{
		if (S[col][row - i] == HUMAN_PIECE)
		{
			b++;
			if (b == k - 2)
			{
				if (S[col][row - i - 1] == AI_PIECE)
				{
					result += 25;
					break;
				}
				else
				{
					result -= 100;
				}
			}
		}
		else
		{
			break;
		}
	}
	std::vector<int> values = { l, r, t, b, tl, tr, bl, br };
	for (i = 0; i < values.size(); i++)
	{

		if (values[i] == k - 1)
		{
			result = values[i] + 100;
		}

		else
		{
			result += values[i];
		}
	}
	return result;
}

int AIShell::Eval(int **S)
{
	std::vector<int> eval_util = { 0, 0 };
	for (int col = 0; col < numCols; col++)
	{
		for (int row = 0; row < numRows; row++)
		{
			if (S[col][row] == AI_PIECE)
			{
				eval_util[0] += PieceCheckAI(col, row, S);
				if (col == std::floor(numCols / 2) || col == std::floor(numCols / 2) + 1 || col == std::floor(numCols / 2) - 1)
				{
					eval_util[0] += 25;
				}
			}

			else if (S[col][row] == HUMAN_PIECE)
			{
				eval_util[1] += PieceCheckHU(col, row, S);
			}
		}
	}
	int result = eval_util[0] * 0.5 + eval_util[1];

	return(result);
}
//Move AIShell::makeMove() {
//	//this part should be filled in by the student to implement the AI
//	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2
//
//
//	//this will move to the left-most column possible.
//	Eval();
//
//	for (int col = 0; col<numCols; col++) {
//		for (int row = 0; row<numRows; row++) {
//			if (gameState[col][row] == NO_PIECE) {
//				Move m(col, row);
//				return m;
//			}
//		}
//	}
//	Move m(0, 0);
//	return m;
//
//}

std::pair<std::pair<int, int>, int> AIShell::DFS(int depth, int **S, int player, clock_t t)
{
	//int **gsc = S;
	float curr = clock() - t;
	curr = ((float)curr / CLOCKS_PER_SEC);

	std::cout << "Time: " << curr << std::endl;
	//diff = difftime(time(0), start) * 1000;
	if (curr >= (deadline/1000)-1)
	{
		std::cout << "STARTING TIME OUT" << std::endl;
		std::pair<int, int> what;
		what = std::make_pair(0, 0);
		std::pair<std::pair<int, int>, int> dummy;
		dummy = std::make_pair(what, 1);
		return dummy;
	}
	int **gsc = new int*[numCols];
	for (int i = 0; i < numCols; i++) {
		gsc[i] = new int[numRows];
	}

	for (int col = 0; col < numCols; col++)
	{
		for (int row = 0; row < numRows; row++)
		{
			gsc[col][row] = S[col][row];
		}
	}
	if (depth == 0)
	{
		std::cout << "Depth = " << depth << ", at base case." << std::endl;
		std::pair<int, int> what;
		what = std::make_pair(0, 0);
		std::pair<std::pair<int, int>, int> dummy;
		int eval_num = Eval(S);
		std::cout << "Eval result = " << eval_num << std::endl;
		dummy = std::make_pair(what, eval_num);

		return(dummy);

	}

	else
	{
		std::cout << "Depth = " << depth << ", inside else statement." << std::endl;
		std::vector<int> nodes;
		std::vector<std::pair<int, int> > moves_list = possMoves(gsc);
		for (int i = 0; i < moves_list.size(); i++)
		{
			std::cout << "Iterating through Moveslist: " << i << " = (" << moves_list[i].first << "," << moves_list[i].second << ")" << std::endl;
			gsc[moves_list[i].first][moves_list[i].second] = player;
			curr = clock() - t;
			curr = ((float)curr / CLOCKS_PER_SEC);
			if (curr >= (deadline/1000)-1)
			{
				std::pair<int, int> what;
				what = std::make_pair(0, 0);
				std::pair<std::pair<int, int>, int> dummy;
				int eval_num = Eval(S);
				std::cout << "Eval result = " << eval_num << std::endl;
				dummy = std::make_pair(what, eval_num);
				return(dummy);
			}
			nodes.push_back(DFS(depth - 1, gsc, -1 * player, t).second);
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					gsc[col][row] = S[col][row];
				}
			}
		}
		//std::cout << "NODES: " << "( " << depth << " )";
		//for (int j = 0; j < nodes.size(); j++)
		//{
		//	std::cout << nodes[j] << " ";
		//}
		std::cout << std::endl;
		if (player == 1)
		{
			int max_val = 0;
			int index = 0;
			std::pair<std::pair<int, int>, int> eval_data;
			for (int i = 0; i < nodes.size(); i++)
			{
				//std::cout << "CURRENT: " << nodes[i] << " and MAX: " << max_val << std::endl;
				if (nodes[i] > max_val)
				{
					max_val = nodes[i];
					index = i;
				}
			}
			eval_data = std::make_pair(moves_list[index], max_val);
			for (int i = 0; i < numCols; i++) {
				delete[] gsc[i];
			}
			delete[] gsc;
			return(eval_data);
		}

		else
		{
			int min_val = 0;
			int index = 0;
			std::pair<std::pair<int, int>, int> eval_data;
			for (int i = 0; i < nodes.size(); i++)
			{
				//std::cout << "CURRENT: " << nodes[i] << " and MIN: " << min_val << std::endl;
				if (i == 0)
				{
					min_val = nodes[i];
					index = i;
				}
				if (nodes[i] < min_val)
				{
					min_val = nodes[i];
					index = i;
				}
			}
			eval_data = std::make_pair(moves_list[index], min_val);
			for (int i = 0; i < numCols; i++) {
				delete[] gsc[i];
			}
			delete[] gsc;
			return(eval_data);
		}
	}
}

std::pair<std::pair<int, int>, int> AIShell::IDS()
{
	clock_t t;
	t = clock();
	float curr = clock() - t;
	curr = ((float)curr / CLOCKS_PER_SEC);
	int depth = 1;
	std::pair <int, int> temp;
	temp = std::make_pair(0, 0);
	std::pair<std::pair<int, int>, int> result;
	result = std::make_pair(temp, 0);
	auto du = result;
	while(curr < (deadline/1000)-1)
	{
		du = DFS(depth, gameState, AI_PIECE, t);
		if (curr <= (deadline/1000)-1)
		{
			result = du;
			std::cout << "UPDATED WITH : " << du.first.first << du.first.second << du.second << std::endl;
		}
		else
		{
			std::cout << "TIMEOUT" << std::endl;
		}

		depth++;
		curr = clock() - t;
		curr = ((float)curr / CLOCKS_PER_SEC);
	}
	return result;
}

Move AIShell::makeMove() {
	deadline = (deadline <= 0 || deadline>5000) ? 5000 : deadline;
	srand(time(NULL));
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2


	//this will move to the left-most column possible.
	//std::vector<int> eval_util = Eval();
	//possMoves(gameState);
	//printMoves();
	std::pair<std::pair<int, int>, int>  temp = IDS();
	std::cout << temp.first.first << " " << temp.first.second;
	Move m(temp.first.first, temp.first.second);
	return m;
}
