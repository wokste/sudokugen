#include "solver.h"
#include "puzzle.h"

#include <algorithm>

using namespace std;

Solver::Solver()
{
	techniques.emplace_back(make_unique<RemoveFilledInNumbersTechnique>());
}

SolverState Solver::solve(const Puzzle& puzzle, BoardWithFlags& board) const
{
	while (true)
	{
		{
			auto ret = isSolved(puzzle, board);
			if (ret.has_value())
				return ret.value();
		}

		bool hasChanges = false;
		for (auto& technique : techniques)
		{
			if (technique->apply(puzzle, board))
			{
				hasChanges = true;
				break;
			}
		}

		if (!hasChanges)
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