#include "pch.h"
#include "BoardState.h"
#include <cassert>

using namespace std;

const CellValue CellValue::Contradiction = -2;
const CellValue CellValue::Unknown = -1;


CellValue CellValue::fromFlags(uint32_t flags)
{
	switch (flags)
	{
	case 0: return CellValue::Contradiction;
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
	assert(value >= 0);
	return value;
}

BoardState::BoardState(const std::vector<CellValue>& values, int8_t maxValue) : values(values), maxValue(maxValue)
{
	assert(maxValue >= 2 && maxValue < 32); // Within uint bounds for bitshifts
	uint32_t baseFlagValue = maxValue == 32 ? -1 : (1 << maxValue) - 1;

	int numCells = values.size();
	flags = std::vector<uint32_t>(numCells, baseFlagValue);
}

CellValue BoardState::getValue(size_t id) const
{
	return values[id];
}

const std::vector<CellValue>& BoardState::getValues()
{
	return values;
}

void BoardState::setValue(size_t id, CellValue nr)
{
	setFlags(id, nr.toFlags());
	assert(values[id].is_ok() || getState() == FinishState::Contradict); // Setting a value actually sets a value
}

bool BoardState::setFlags(size_t id, uint32_t mask)
{
	auto oldFlags = flags[id];
	auto newFlags = oldFlags & mask;
	if (oldFlags == newFlags)
		return false;

	flags[id] = newFlags;
	values[id] = CellValue::fromFlags(newFlags);
	return true;
}

FinishState BoardState::getState() const
{
	bool hasUnfilledSymbols = false;

	for (const CellValue v : values)
	{
		if (v == CellValue::Contradiction)
			return FinishState::Contradict;

		if (!v.is_ok())
			hasUnfilledSymbols = true;

		return FinishState::InProgress;
	}

	return hasUnfilledSymbols ? FinishState::InProgress : FinishState::FilledIn;
}