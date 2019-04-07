#pragma once
#include <memory>

class ILayer {
public:
	virtual size_t zones() = 0;
	virtual size_t zoneSizes(size_t zoneID) = 0;
	virtual size_t cell(size_t zoneID, size_t index) = 0;
	virtual size_t zoneID(size_t cellID) = 0;

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