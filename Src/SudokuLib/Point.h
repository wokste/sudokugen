#pragma once
#include <cassert>

struct Point {
	Point(int x, int y) : x(x), y(y) {}
	Point(size_t x, size_t y) : x((int)x), y((int)y) {}

	static Point fromIndex(size_t index, int horizontalCount) {
		return Point(index % horizontalCount, index / horizontalCount);
	}

	size_t toIndex(int horizontalCount) {
		assert(horizontalCount > 0);
		assert(x >= 0);
		assert(y >= 0);
		return (size_t)(x + y * horizontalCount);
	}

	int x = 0;
	int y = 0;
};