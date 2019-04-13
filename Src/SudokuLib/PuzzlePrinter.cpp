#include "PuzzlePrinter.h"
#include <vector>
#include <string_view>

using namespace std;

void SvgPuzzlePrinter::print(const Puzzle & puzzle, std::vector<CellValue>& board) const
{
	// TODO: <svg version="1.1" baseProfile="full" width="360" height="360" viewBox="0 0 9 9" xmlns="http://www.w3.org/2000/svg">
	printGrid(puzzle);
	printNumbers(puzzle, board);

}

void SvgPuzzlePrinter::printGrid(const Puzzle & puzzle) const
{
	for (int x = 0; x < puzzle.width; ++x)
	{
		// TODO: <line x1="1" x2="1" y1="0" y2="9" stroke="black" stroke-width="0.01"/>
	}

	for (int y = 0; y < puzzle.height; ++y)
	{
		// TODO: <line y1="1" y2="1" x1="0" x2="9" stroke="black" stroke-width="0.01"/>
	}
		
}

void SvgPuzzlePrinter::printNumbers(const Puzzle & puzzle, std::vector<CellValue>& board) const
{
	const char* symbols[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D", "E", "F" };
	for (int y = 0; y < puzzle.height; ++y)
		for (int x = 0; x < puzzle.width; ++x)
		{
			auto cell = board[x + y * puzzle.width];
			if (cell.ok())
			{
				printNumber(x, y, symbols[cell.get()]);
			}
		}
}

void SvgPuzzlePrinter::printNumber(int x, int y, std::string_view digit) const
{
	// TODO: <text x="2.5" y="4.8" font-size="0.75" text-anchor="middle" fill="black">4</text>
}
