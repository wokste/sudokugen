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
	for (auto& layer : puzzle.layers)
	{
		// TODO: Limit types of layers

		for (size_t l = 0; l < layer->zones(); ++l)
		{
			uint32_t flags = ~0;

			// Find flags
			for (size_t i = 0; i < layer->zoneSizes(l); ++i)
			{
				auto cellID = layer->cell(l, i);
				auto value = board.value(cellID);
				if (value.ok())
				{
					flags &= ~(1 << value.get());
				}
			}

			// Apply flags
			for (size_t i = 0; i < layer->zoneSizes(l); ++i)
			{
				auto cellID = layer->cell(l, i);
				auto value = board.value(cellID);
				if (!value.ok())
				{
					changed |= board.requireFlags(cellID, flags);
				}
			}
		}
		

		// TODO: Stuff
	}
	return changed;
}