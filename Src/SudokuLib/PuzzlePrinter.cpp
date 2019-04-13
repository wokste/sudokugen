#include "PuzzlePrinter.h"
#include <vector>
#include <string_view>
#include <iostream>

using namespace std;

void SvgPuzzlePrinter::print(const Puzzle & puzzle, std::vector<CellValue>& board) const
{
	XmlWriter xmlDoc(cout);
	auto svg = xmlDoc.makeTag("svg");
	svg.set("version", 1.1);
	svg.set("baseProfile", "full");
	svg.set("width", 360);
	svg.set("height", 360);
	svg.set("viewBox", "0 0 9 9");
	svg.set("xmlns", "http://www.w3.org/2000/svg");

	printGrid(svg, puzzle);
	printNumbers(svg, puzzle, board);

}

void SvgPuzzlePrinter::printGrid(XmlElementWriter& svgNode, const Puzzle & puzzle) const
{
	for (int x = 0; x <= puzzle.width; ++x)
	{
		auto line = svgNode.makeTag("line");
		line.set("x1", x);
		line.set("x2", x);
		line.set("y1", 0);
		line.set("y2", puzzle.height);
		line.set("stroke", "black");
		line.set("stroke-width", 0.01);

	}

	for (int y = 0; y <= puzzle.height; ++y)
	{
		auto line = svgNode.makeTag("line");
		line.set("x1", 0);
		line.set("x2", puzzle.width);
		line.set("y1", y);
		line.set("y2", y);
		line.set("stroke", "black");
		line.set("stroke-width", 0.01);
	}
		
}

void SvgPuzzlePrinter::printNumbers(XmlElementWriter& svgNode, const Puzzle & puzzle, std::vector<CellValue>& board) const
{
	const char* symbols[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D", "E", "F" };
	for (int y = 0; y < puzzle.height; ++y)
		for (int x = 0; x < puzzle.width; ++x)
		{
			auto cell = board[x + y * puzzle.width];
			if (cell.ok())
			{
				printNumber(svgNode, x, y, symbols[cell.get()]);
			}
		}
}

void SvgPuzzlePrinter::printNumber(XmlElementWriter& svgNode, int x, int y, std::string_view digit) const
{
	auto textNode = svgNode.makeTag("text");
	textNode.set("x", x + 0.5);
	textNode.set("y", y + 0.8);
	textNode.set("text-anchor", "middle");
	textNode.set("fill", "black");
	textNode.setText(digit);
}
