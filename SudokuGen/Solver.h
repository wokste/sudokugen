#pragma once
#include "puzzle.h"

class Solver {
public:
	bool unique = true;
	std::optional<int> requiredSquare = std::nullopt;

	SolverState solve(const Puzzle& puzzle, BoardWithFlags& board) const;

private:
	std::optional<SolverState> isSolved(const Puzzle& puzzle, BoardWithFlags& board) const;
	bool removeFilledInNumbers(const Puzzle& puzzle, BoardWithFlags& board) const;
};