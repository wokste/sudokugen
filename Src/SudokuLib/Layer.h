#pragma once
#include <memory>
#include "Point.h"

class ILayer {
public:
	virtual size_t zones() const = 0;
	virtual size_t zoneSizes(size_t zoneID) const = 0;
	virtual Point cell(size_t zoneID, size_t index) const = 0;
	virtual size_t zoneID(Point cell) const = 0;

	virtual ~ILayer() {}
};

using LayerPtr = std::unique_ptr<ILayer>;

namespace LayerFactory {
	LayerPtr MakeRowLayer(int dimension);
	LayerPtr MakeColumnLayer(int dimension);
	LayerPtr MakeCellLayer(Point areaSize);
}