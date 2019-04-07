// SudokuGen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Puzzle.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	auto puzzle = PuzzleGen::makeSudokuBoard(3, 3);
	auto boardOpt = PuzzleGen::generate(*puzzle, 5);
	vector<string> symbols = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D", "E", "F" };

	if (boardOpt.has_value())
	{
		cout << "Successfully created a sudoku!\n";

		auto board = boardOpt.value();
		assert(board.size() == puzzle->size());

		for (int y = 0; y < puzzle->height; ++y)
		{
			for (int x = 0; x < puzzle->width; ++x)
			{
				auto cell = board[x + y * puzzle->width];
				if (cell.ok())
				{
					cout << symbols[cell.get()];
				}
				else
				{
					cout << " ";
				}


				
			}
			cout << '\n';
		}
	}
	else
	{
		cout << "Failed to create sudoku!";
	}
}
