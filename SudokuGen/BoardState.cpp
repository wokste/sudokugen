#include "pch.h"
#include "BoardState.h"
#include <cassert>

using namespace std;

std::optional<int8_t> log2_optional(uint32_t flags)
{
	switch (flags)
	{
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
	return nullopt;
}

BoardState::BoardState(int numCells, int8_t maxValue) : maxValue(maxValue)
{
	assert(maxValue >= 2 && maxValue < 32); // Within uint bounds for bitshifts

	uint32_t baseFlagValue = maxValue == 32 ? -1 : (1 << maxValue) - 1;
	flags = std::vector<uint32_t>(numCells, baseFlagValue);
	values = std::vector<int8_t>(numCells, VALUE_UNKNOWN);
}

std::optional<int8_t> BoardState::getValue(size_t id) const
{
	auto v = values[id];
	if (v >= 0)
		return v;
	return nullopt;
}

void BoardState::setValue(size_t id, int8_t nr)
{
	assert(nr >= 0 && nr < maxValue); // Within uint bounds after bitshifts.

	setFlags(id, (1 << (uint32_t)nr));

	assert(getValue(id).has_value() || getState() == FinishState::Contradict); // Setting a value actually sets a value
}

void BoardState::setFlags(size_t id, uint32_t newFlags)
{
	bool hadValue = getValue(id).has_value();

	//TODO: Stuff
	flags[id] &= newFlags;
	
	if (flags[id] == 0)
	{
		values[id] = VALUE_INVALID;
	}
	else if (!hadValue)
	{
		auto newNr = log2_optional(flags[id]);
		if (newNr.has_value())
		{
			values[id] = newNr.value();
			indicesToProcess.push_back(id);
		}
	}
}

FinishState BoardState::getState() const
{
	bool hasUnfilledSymbols = false;

	for (auto& f : flags)
	{
		if (f == VALUE_INVALID)
			return FinishState::Contradict;

		if (f == VALUE_UNKNOWN)
			hasUnfilledSymbols = true;

		return FinishState::InProgress;
	}

	return hasUnfilledSymbols ? FinishState::InProgress : FinishState::FilledIn;
}

optional<size_t> BoardState::nextIndex()
{
	//TODO: Stuff
	return nullopt;
}