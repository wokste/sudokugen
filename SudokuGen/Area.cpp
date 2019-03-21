#include "pch.h"
#include "Area.h"
#include <vector>

using namespace std;

class RowArea : public IArea {
	int start;
	int count;
	int offset;
public:
	RowArea(int start, int count, int offset) : start(start), count(count), offset(offset)
	{
	}

	size_t size() override
	{
		return count;
	}

	virtual size_t get(int id) {
		return start + id * offset;
	}
};

unique_ptr<IArea> AreaFactory::MakeLine(int start, int count, int offset)
{
	return make_unique<RowArea>(start, count, offset);
}

class RectArea : public IArea
{
	int start;
	int width;
	int height;
	int puzzleWidth;
public:
	RectArea(int start, int width, int height, int puzzleWidth) : start(start), width(width), height(height), puzzleWidth(puzzleWidth)
	{
	}

	size_t size() override
	{
		return width + height;
	}

	size_t get(int id) override
	{
		auto dx = id % width;
		auto dy = id / height;
		return start + dx + dy * puzzleWidth;
	}
};

unique_ptr<IArea> AreaFactory::MakeRect(int topLeft, int width, int height, int puzzleWidth)
{
	return make_unique<RectArea>(topLeft, width, height, puzzleWidth);
}
