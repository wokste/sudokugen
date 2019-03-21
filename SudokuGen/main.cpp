// SudokuGen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Puzzle.h"
#include <iostream>

int main()
{
	auto puzzle = PuzzleGen::makeSudokuBoard(3,3);
	auto board = PuzzleGen::generate(*puzzle, 5);
	if (board.has_value())
	{
		std::cout << "Successfully created a sudoku!\n";
	}
	else
	{
		std::cout << "Failed to create sudoku!";
	}
}
