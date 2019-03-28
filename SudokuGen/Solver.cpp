#include "pch.h"
#include "solver.h"
#include "puzzle.h"

#include <algorithm>

using namespace std;

SolverState Solver::solve(const Puzzle& puzzle, BoardWithFlags& board) const
{
	while (true)
	{
		{
			auto ret = isSolved(puzzle, board);
			if (ret.has_value())
				return ret.value();
		}

		if (removeFilledInNumbers(puzzle, board))
			continue;

		return SolverState::InProgress;
	}
}

optional<SolverState> Solver::isSolved(const Puzzle& puzzle, BoardWithFlags& board) const
{
	if (requiredSquare.has_value())
		if (board.value(requiredSquare.value()).ok())
			return SolverState::Done;
	
	auto state = board.solverState();
	if (state == SolverState::InProgress)
		return nullopt;
	return state;
}

bool Solver::removeFilledInNumbers(const Puzzle& puzzle, BoardWithFlags& board) const
{
	bool changed = false;
	for (auto& constraint : puzzle.constraints)
	{
		if (constraint.type != ConstraintType::AllUnique)
			continue;

		auto& area = constraint.area;
		

		// TODO: Stuff
	}
	return changed;
}