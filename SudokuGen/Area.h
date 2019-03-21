#pragma once
#include <memory>

class IArea {
public:
	virtual size_t size() = 0;
	virtual size_t get(int id) = 0;

	virtual ~IArea() {}
};

namespace AreaFactory {
	std::unique_ptr<IArea> MakeRect(int topLeft, int width, int height, int puzzleWidth);
	std::unique_ptr<IArea> MakeLine(int start, int count, int offset = 1);
}