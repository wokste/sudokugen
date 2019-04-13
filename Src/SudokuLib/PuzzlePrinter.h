#include "Puzzle.h"
#include <string_view>
#include "XmlWriter.h"

class SvgPuzzlePrinter {
public:
	void print(const Puzzle& puzzle, std::vector<CellValue>& board) const;
	void printGrid(const Puzzle& puzzle) const;
	void printNumbers(const Puzzle& puzzle, std::vector<CellValue>& board) const;
	void printNumber(int x, int y, std::string_view digit) const;
};