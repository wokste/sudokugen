#pragma once
#include "BoardState.h"
#include "Layer.h"

#include <memory>
#include <vector>

enum class ConstraintType {
	AllUnique,
};

class Puzzle {
public:
	Puzzle(int width, int height, int8_t maxValue) : width(width), height(height), maxValue(maxValue)
	{
	}

	int size() const {
		return width * height;
	}

	std::vector<std::unique_ptr<ILayer>> layers;
	const int width;
	const int height;
	const int8_t maxValue;
};

namespace PuzzleGen {
	std::unique_ptr<Puzzle> makeSudokuBoard(int cellWidth, int cellHeight);

	std::optional<std::vector<CellValue>> generate(const Puzzle& puzzle, int maxAttempts);
	std::optional<std::vector<CellValue>> fillEmpty(const Puzzle& puzzle);
	std::vector<CellValue> iterativeReduce(const Puzzle& puzzle, const std::vector<CellValue>& finalState);
}