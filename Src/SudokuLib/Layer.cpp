
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
	size_t zones() override
	{
		return dimension;
	}
	size_t zoneSizes(size_t zoneID) override
	{
		return dimension;
	}
};


class RowLayer : public AllUniqueLayer {
public:
	RowLayer(int dimension) : AllUniqueLayer(dimension)
	{
	}

	size_t cell(size_t zoneID, size_t index) override
	{
		return index + zoneID * dimension;
	}
	size_t zoneID(size_t cellID) override
	{
		assert(false); //TODO implement;
		return 0;
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

	size_t cell(size_t zoneID, size_t index) override
	{
		return zoneID + index * dimension;
	}
	size_t zoneID(size_t cellID) override
	{
		assert(false); //TODO implement;
		return 0;
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

	size_t cell(size_t zoneID, size_t index) override
	{
		auto horAreaCount = areaHeight;
		auto x = zoneID % horAreaCount + index % areaWidth;
		auto y = zoneID / horAreaCount + index / areaWidth;

		return x + y * dimension;
	}
	size_t zoneID(size_t cellID) override
	{
		assert(false); //TODO implement;
		return 0;
	}
};

unique_ptr<ILayer> LayerFactory::MakeCellLayer(int areaWidth, int areaHeight)
{
	return make_unique<CellLayer>(areaWidth, areaHeight);
}