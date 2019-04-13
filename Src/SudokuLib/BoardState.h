#pragma once
#include <vector>
#include <optional>
#include <cassert>
#include "Point.h"

class Puzzle;

enum class SolverState {
	InProgress = 0,
	Done = 1,
	Contradict = 2
};

class CellValue {
	int8_t value;

public:
	CellValue(int8_t value) : value(value) {}

	static CellValue fromFlags(uint32_t flags);
	uint32_t toFlags() const;

	bool ok() const { return value >= 0; }
	int8_t get() const;
	bool operator==(const CellValue& other) const { return value == other.value; }

	static const CellValue Contradiction;
	static const CellValue Unknown;
};

class BoardWithFlags {
public:
	BoardWithFlags(const Puzzle& puzzle, const std::vector<CellValue>& values);

	BoardWithFlags(const BoardWithFlags&) = default;
	BoardWithFlags(BoardWithFlags&&) = default;
	BoardWithFlags& operator=(const BoardWithFlags&) = default;
	BoardWithFlags& operator=(BoardWithFlags&&) = default;

	CellValue value(Point pos) const;
	const std::vector<CellValue>& internalValues();

	void setValue(Point pos, CellValue nr);
	bool requireFlags(Point pos, uint32_t flags);

	SolverState solverState() const;

private:
	std::vector<uint32_t> flags;
	std::vector<CellValue> values;
	const Puzzle& puzzle;

	size_t posToId(Point pos) const;
};