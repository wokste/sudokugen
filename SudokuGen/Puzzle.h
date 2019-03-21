#pragma once
#include "BoardState.h"
#include "Area.h"

#include <memory>
#include <vector>

enum class ConstraintType {
	AllUnique,
};

struct Constraint {
	std::unique_ptr<IArea> area;
	ConstraintType type;
	int total = 0; // Useful for storing sums, products, etc

	Constraint(std::unique_ptr<IArea>& area, ConstraintType type, int total = 0) : area(std::move(area)), type(type), total(total)
	{
	}
};


struct Puzzle {
	Puzzle(int width, int height, int8_t maxValue) : width(width), height(height), maxValue(maxValue)
	{
	}

	int size() const {
		return width * height;
	}

	std::vector<Constraint> constraints;
	const int width;
	const int height;
	const int8_t maxValue;
};

namespace PuzzleGen {
	std::unique_ptr<Puzzle> makeSudokuBoard(int cellWidth, int cellHeight);

	std::optional<BoardState> generate(const Puzzle& puzzle, int maxAttempts);
	std::optional<BoardState> fillEmpty(const Puzzle& puzzle);
	std::optional<BoardState> solve(const Puzzle& puzzle, const BoardState& initialState);
	BoardState iterativeReduce(const Puzzle& puzzle, const BoardState& finalState);
}