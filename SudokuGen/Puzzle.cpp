#include "pch.h"
#include "Puzzle.h"

using namespace std;

std::unique_ptr<Puzzle> PuzzleGen::makeSudokuBoard(int cellWidth, int cellHeight)
{
	int size = cellWidth * cellHeight;

	auto puzzle = make_unique<Puzzle>(size, size, size);

	// Add rows
	for (int i = 0; i < size; ++i)
	{
		auto area = AreaFactory::MakeLine(i * size, size, 1);
		puzzle->constraints.emplace_back(area, ConstraintType::AllUnique, size);
	}

	// Add columns
	for (int i = 0; i < size; ++i)
	{
		auto area = AreaFactory::MakeLine(i, size, size);
		puzzle->constraints.emplace_back(area, ConstraintType::AllUnique, size);
	}

	// Add cells
	for (int x = 0; x < size; x += cellWidth)
	{
		for (int y = 0; y < size; y += cellHeight)
		{
			int startID = x + y * size;
			auto area = AreaFactory::MakeRect(startID, cellWidth, cellHeight, size);
			puzzle->constraints.emplace_back(area, ConstraintType::AllUnique, size);
		}
	}

	return puzzle;
}

std::optional<BoardState> PuzzleGen::generate(const Puzzle & puzzle, int maxAttempts)
{
	for (int attempt = 0; attempt < maxAttempts; ++attempt)
	{
		auto filled = fillEmpty(puzzle);

		if (!filled.has_value())
			continue;

		return iterativeReduce(puzzle, filled.value());
	}
	return nullopt;
}

std::optional<BoardState> PuzzleGen::fillEmpty(const Puzzle & puzzle)
{
	// TODO: Try to solve
	return nullopt;
}

std::optional<BoardState> PuzzleGen::solve(const Puzzle & puzzle, const BoardState& initialState)
{
	// TODO: Try various techniques to solve
	return nullopt;
}

BoardState PuzzleGen::iterativeReduce(const Puzzle & puzzle, const BoardState& finalState)
{
	vector<size_t> cellIDs;

	for (auto i = 0; i < puzzle.size(); ++i)
		cellIDs.push_back(i);

	// TODO: shuffle vec
	// From http://www.cplusplus.com/reference/algorithm/shuffle/
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//shuffle(cellIDs.begin(), cellIDs.end(), std::default_random_engine(seed));

	BoardState reduced = finalState;

	for (auto& id : cellIDs)
	{
		// TODO: Unset value

		if (!solve(puzzle, reduced))
		{
			// TODO: Reset the value again.
		}
	}

	return reduced;
}
