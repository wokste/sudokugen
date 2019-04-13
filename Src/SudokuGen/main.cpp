// SudokuGen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Puzzle.h"
#include "PuzzlePrinter.h"
#include "Globals.h"
#include <iostream>
#include <string>

using namespace std;

void printBoard(const Puzzle& puzzle)
{

}

void printPuzzle(const Puzzle& puzzle, const std::vector<CellValue>& board)
{
	
}

int main()
{
	std::random_device rd;
	Globals::rng.seed(rd());
	auto puzzle = PuzzleGen::makeSudokuBoard(3, 3);
	auto boardOpt = PuzzleGen::generate(*puzzle, 5);

	if (boardOpt.has_value())
	{
		cout << "Successfully created a sudoku!\n";

		auto board = boardOpt.value();
		assert(board.size() == puzzle->size());

		SvgPuzzlePrinter printer;
		printer.print(*puzzle, board);
	}
	else
	{
		cout << "Failed to create sudoku!";
	}
}
