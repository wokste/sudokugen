#include "pch.h"
#include "Puzzle.h"
#include "Solver.h"

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

std::optional<std::vector<CellValue>> PuzzleGen::generate(const Puzzle & puzzle, int maxAttempts)
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

std::optional<std::vector<CellValue>> PuzzleGen::fillEmpty(const Puzzle & puzzle)
{
	// TODO: Smarter algorithm
	std::vector<CellValue> values = {
		0,1,2, 3,4,5, 6,7,8,
		6,7,8, 0,1,2, 3,4,5,
		3,4,5, 6,7,8, 0,1,2,

		8,0,1, 2,3,4, 5,6,7,
		5,6,7, 8,0,1, 2,3,4,
		2,3,4, 5,6,7, 8,0,1,

		7,8,0, 1,2,3, 4,5,6,
		4,5,6, 7,8,0, 1,2,3,
		1,2,3, 4,5,6, 7,8,0,
	};
	return values;
}

std::vector<CellValue> PuzzleGen::iterativeReduce(const Puzzle & puzzle, const std::vector<CellValue>& finalState)
{
	vector<int> cellIDs;

	for (auto i = 0; i < puzzle.size(); ++i)
		cellIDs.push_back(i);

	// TODO: shuffle vec
	// From http://www.cplusplus.com/reference/algorithm/shuffle/
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//shuffle(cellIDs.begin(), cellIDs.end(), std::default_random_engine(seed));

	auto reduced = finalState;

	for (auto& id : cellIDs)
	{
		reduced[id] = CellValue::Unknown;
		// TODO: Unset value

		Solver solver;
		solver.unique = true;
		solver.requiredSquare = id;

		BoardWithFlags board(reduced, puzzle.maxValue);

		switch (solver.solve(puzzle, board))
		{
		case SolverState::Done:
			break;
		case SolverState::InProgress:
			reduced[id] = finalState[id]; // Could not solve puzzle. This value is essential.
			break;
		case SolverState::Contradict:
		default:
			assert(false);
			break;
		}
	}

	return reduced;
}
