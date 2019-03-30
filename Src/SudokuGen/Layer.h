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

class LayerZoneIterator {
	
};

namespace LayerFactory {
	std::unique_ptr<ILayer> MakeRowLayer(int dimension);
	std::unique_ptr<ILayer> MakeColumnLayer(int dimension);
	std::unique_ptr<ILayer> MakeCellLayer(int areaWidth, int areaHeight);
}