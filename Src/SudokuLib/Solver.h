#pragma once
#include "Puzzle.h"
#include "Technique.h"

class Solver {
public:
	Solver();

	bool unique = true;
	std::optional<Point> requiredSquare = std::nullopt;

	SolverState solve(const Puzzle& puzzle, BoardWithFlags& board) const;

private:
	std::optional<SolverState> isSolved(const Puzzle& puzzle, BoardWithFlags& board) const;
	std::vector<std::unique_ptr<ITechnique>> techniques;
};
