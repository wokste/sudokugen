#pragma once
#include <vector>
#include <deque>
#include <optional>

enum class FinishState {
	FilledIn = 0,
	InProgress = 1,
	Contradict = 3 // Value chosen such that it works with bitwise or.
};

class BoardState {
public:
	BoardState(int numCells, int8_t maxValue);
	BoardState(BoardState&) = default;
	BoardState(BoardState&&) = default;

	const int8_t VALUE_UNKNOWN = -1;
	const int8_t VALUE_INVALID = -2;

	std::optional<int8_t> getValue(size_t id) const;
	void setValue(size_t id, int8_t nr);
	void setFlags(size_t id, uint32_t flags);

	FinishState getState() const;

	std::optional<size_t> nextIndex();

private:
	std::vector<uint32_t> flags;
	std::vector<int8_t> values;
	std::deque<size_t> indicesToProcess;
	int8_t maxValue;
};