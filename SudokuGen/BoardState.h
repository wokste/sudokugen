#pragma once
#include <vector>
#include <deque>
#include <optional>
#include <cassert>

enum class FinishState {
	FilledIn = 0,
	InProgress = 1,
	Contradict = 3 // Value chosen such that it works with bitwise or.
};

class CellValue {
	int8_t value;

public:
	CellValue(int8_t value) : value(value) {}

	static CellValue fromFlags(uint32_t flags);
	uint32_t toFlags() const;

	bool is_ok() const { return value >= 0; }
	int8_t get() const;
	bool operator==(const CellValue& other) const { return value == other.value; }

	static const CellValue Contradiction;
	static const CellValue Unknown;
};

class BoardState {
public:
	BoardState(const std::vector<CellValue>& values, int8_t maxValue);

	BoardState(const BoardState&) = default;
	BoardState(BoardState&&) = default;
	BoardState& operator=(const BoardState&) = default;
	BoardState& operator=(BoardState&&) = default;

	CellValue getValue(size_t id) const;
	const std::vector<CellValue>& getValues();

	void setValue(size_t id, CellValue nr);
	bool setFlags(size_t id, uint32_t flags);

	FinishState getState() const;

private:
	std::vector<uint32_t> flags;
	std::vector<CellValue> values;
	int8_t maxValue;
};