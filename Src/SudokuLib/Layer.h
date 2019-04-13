#pragma once
#include <memory>
#include "Point.h"

class ILayer;

class LayerZone {
public:
	LayerZone(const ILayer& layer, const size_t zoneID) : layer(layer), zoneID(zoneID) {}
	const size_t zoneID;
	const ILayer& layer;

	Point operator[](size_t index) const;
	size_t size() const;
};

class ILayer {
public:
	virtual size_t size() const = 0;
	virtual size_t zoneID(Point cell) const = 0;

	virtual ~ILayer() {}
private:
	virtual size_t zoneSize(size_t zoneID) const = 0;
	virtual Point getCell(size_t zoneID, size_t index) const = 0;
	friend LayerZone;
public:
	LayerZone operator[](size_t zoneID) { return LayerZone(*this, zoneID); }
};

using LayerPtr = std::unique_ptr<ILayer>;

namespace LayerFactory {
	LayerPtr MakeRowLayer(int dimension);
	LayerPtr MakeColumnLayer(int dimension);
	LayerPtr MakeCellLayer(Point areaSize);
}