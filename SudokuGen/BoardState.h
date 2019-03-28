#pragma once
#include <vector>
#include <deque>
#include <optional>
#include <cassert>

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
	BoardWithFlags(const std::vector<CellValue>& values, int8_t maxValue);

	BoardWithFlags(const BoardWithFlags&) = default;
	BoardWithFlags(BoardWithFlags&&) = default;
	BoardWithFlags& operator=(const BoardWithFlags&) = default;
	BoardWithFlags& operator=(BoardWithFlags&&) = default;

	CellValue value(size_t id) const;
	const std::vector<CellValue>& internalValues();

	void setValue(size_t id, CellValue nr);
	bool setFlags(size_t id, uint32_t flags);

	SolverState solverState() const;

private:
	std::vector<uint32_t> flags;
	std::vector<CellValue> values;
	int8_t maxValue;
};