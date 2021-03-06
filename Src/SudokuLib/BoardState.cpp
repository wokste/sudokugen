#include "BoardState.h"
#include "Point.h"
#include "Puzzle.h"
#include <cassert>

using namespace std;

const CellValue CellValue::Contradiction = -2;
const CellValue CellValue::Unknown = -1;


CellValue CellValue::fromFlags(uint32_t flags)
{
	switch (flags)
	{
	case 0:
		return CellValue::Contradiction;
	case 0x1: return 00;
	case 0x2: return 01;
	case 0x4: return 02;
	case 0x8: return 03;
	case 0x10: return 04;
	case 0x20: return 05;
	case 0x40: return 06;
	case 0x80: return 07;
	case 0x100: return 010;
	case 0x200: return 011;
	case 0x400: return 012;
	case 0x800: return 013;
	case 0x1000: return 014;
	case 0x2000: return 015;
	case 0x4000: return 016;
	case 0x8000: return 017;
	case 0x10000: return 020;
	case 0x20000: return 021;
	case 0x40000: return 022;
	case 0x80000: return 023;
	case 0x100000: return 024;
	case 0x200000: return 025;
	case 0x400000: return 026;
	case 0x800000: return 027;
	case 0x1000000: return 030;
	case 0x2000000: return 031;
	case 0x4000000: return 032;
	case 0x8000000: return 033;
	case 0x10000000: return 034;
	case 0x20000000: return 035;
	case 0x40000000: return 036;
	case 0x80000000: return 037;
	}
	return CellValue::Unknown;
}

uint32_t CellValue::toFlags() const
{
	assert(value >= 0 && value < 32);
	return 1 << value;
}

int8_t CellValue::get() const
{
	assert(this->ok());
	return value;
}

BoardWithFlags::BoardWithFlags(const Puzzle& puzzle, const std::vector<CellValue>& values) : values(values), puzzle(puzzle)
{
	assert(puzzle.maxValue >= 2 && puzzle.maxValue < 32); // Within uint bounds for bitshifts
	uint32_t baseFlagValue = (((uint32_t)1) << puzzle.maxValue) - 1;

	size_t numCells = values.size();
	flags = std::vector<uint32_t>(numCells, baseFlagValue);
}

CellValue BoardWithFlags::value(Point pos) const
{
	return values[posToId(pos)];
}

const std::vector<CellValue>& BoardWithFlags::internalValues()
{
	return values;
}

void BoardWithFlags::setValue(Point pos, CellValue nr)
{
	requireFlags(pos, nr.toFlags());
	assert(values[posToId(pos)].ok() || solverState() == SolverState::Contradict); // Setting a value actually sets a value
}

bool BoardWithFlags::requireFlags(Point pos, uint32_t mask)
{
	auto id = posToId(pos);
	auto oldFlags = flags[id];
	auto newFlags = oldFlags & mask;
	if (oldFlags == newFlags)
		return false;

	flags[id] = newFlags;
	values[id] = CellValue::fromFlags(newFlags);
	return true;
}

SolverState BoardWithFlags::solverState() const
{
	bool hasUnfilledSymbols = false;

	for (const CellValue v : values)
	{
		if (v == CellValue::Contradiction)
			return SolverState::Contradict;

		if (!v.ok())
			hasUnfilledSymbols = true;
	}

	return hasUnfilledSymbols ? SolverState::InProgress : SolverState::Done;
}

size_t BoardWithFlags::posToId(Point pos) const
{
	return pos.toIndex(puzzle.width);
}
