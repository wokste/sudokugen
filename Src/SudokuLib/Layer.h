#pragma once
#include <memory>

class ILayer {
public:
	virtual size_t zones() const = 0;
	virtual size_t zoneSizes(size_t zoneID) const = 0;
	virtual size_t cell(size_t zoneID, size_t index) const = 0;
	virtual size_t zoneID(size_t cellID) const = 0;

	virtual ~ILayer() {}
};

using LayerPtr = std::unique_ptr<ILayer>;

class LayerZoneIterator {
	
};

namespace LayerFactory {
	LayerPtr MakeRowLayer(int dimension);
	LayerPtr MakeColumnLayer(int dimension);
	LayerPtr MakeCellLayer(int areaWidth, int areaHeight);
}