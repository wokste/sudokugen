#pragma once
#include "Puzzle.h"

class ITechnique {
public:
	virtual bool apply(const Puzzle& puzzle, BoardWithFlags& board) const = 0;
};

class RemoveFilledInNumbersTechnique : public ITechnique {
public:
	bool apply(const Puzzle& puzzle, BoardWithFlags& board) const override;
};