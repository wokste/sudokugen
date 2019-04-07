
#include "Layer.h"
#include <vector>
#include <cassert>

using namespace std;


class AllUniqueLayer : public ILayer {
protected:
	int dimension;
public:
	AllUniqueLayer(int dimension) : dimension(dimension)
	{
	}
	size_t zones() const override
	{
		return dimension;
	}
	size_t zoneSizes(size_t zoneID) const override
	{
		return dimension;
	}
};

// --------------------------------------

class RowLayer : public AllUniqueLayer {
public:
	RowLayer(int dimension) : AllUniqueLayer(dimension)
	{
	}

	size_t cell(size_t zoneID, size_t index) const override
	{
		return index + zoneID * dimension;
	}
	size_t zoneID(size_t cellID) const override
	{
		return cellID / dimension;
	}
};

unique_ptr<ILayer> LayerFactory::MakeRowLayer(int dimension)
{
	return make_unique<RowLayer>(dimension);
}

// --------------------------------------

class ColumnLayer : public AllUniqueLayer {
public:
	ColumnLayer(int dimension) : AllUniqueLayer(dimension)
	{
	}

	size_t cell(size_t zoneID, size_t index) const override
	{
		return zoneID + index * dimension;
	}
	size_t zoneID(size_t cellID) const override
	{
		return cellID % dimension;
	}
};

unique_ptr<ILayer> LayerFactory::MakeColumnLayer(int dimension)
{
	return make_unique<ColumnLayer>(dimension);
}

// --------------------------------------

class CellLayer : public AllUniqueLayer {
	int areaWidth, areaHeight;
public:
	CellLayer(int areaWidth, int areaHeight) : areaWidth(areaWidth), areaHeight(areaHeight), AllUniqueLayer(areaWidth * areaHeight)
	{
	}

	size_t cell(size_t zoneID, size_t index) const override
	{
		auto horAreaCount = areaHeight;
		auto zone_x = zoneID % horAreaCount;
		auto zone_y = zoneID / horAreaCount;

		auto cell_x = index % areaWidth;
		auto cell_y = index / areaWidth;

		auto x = zone_x * areaWidth + cell_x;
		auto y = zone_y * areaHeight + cell_y;

		return x + y * dimension;
	}
	size_t zoneID(size_t cellID) const override
	{
		auto horAreaCount = areaHeight;
		auto y = cellID / dimension;
		auto x = cellID % dimension;

		auto zone_x = x / areaWidth;
		auto zone_y = y / areaHeight;
		return zone_x + zone_y * horAreaCount;
	}
};

unique_ptr<ILayer> LayerFactory::MakeCellLayer(int areaWidth, int areaHeight)
{
	return make_unique<CellLayer>(areaWidth, areaHeight);
}