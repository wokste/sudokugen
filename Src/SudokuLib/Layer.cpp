
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
	size_t size() const override
	{
		return dimension;
	}
	size_t zoneSize(size_t zoneID) const override
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

	Point getCell(size_t zoneID, size_t index) const override
	{
		return Point(index, zoneID);
	}
	size_t zoneID(Point cell) const override
	{
		return cell.y;
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

	Point getCell(size_t zoneID, size_t index) const override
	{
		return Point(zoneID, index);
	}
	size_t zoneID(Point cell) const override
	{
		return cell.x;
	}
};

unique_ptr<ILayer> LayerFactory::MakeColumnLayer(int dimension)
{
	return make_unique<ColumnLayer>(dimension);
}

// --------------------------------------

class CellLayer : public AllUniqueLayer {
	Point area;
public:
	CellLayer(Point area) : area(area), AllUniqueLayer(area.x * area.y)
	{
	}

	Point getCell(size_t zoneID, size_t index) const override
	{
		auto horAreaCount = area.y;
		auto zone = Point::fromIndex(zoneID, horAreaCount);

		auto localCell = Point(index % area.x, index / area.y);

		return Point(zone.x * area.x + localCell.x, zone.y * area.y + localCell.y);
	}
	size_t zoneID(Point cell) const override
	{
		auto horAreaCount = area.y;

		auto zone_x = cell.x / area.x;
		auto zone_y = cell.y / area.y;
		return zone_x + zone_y * horAreaCount;
	}
};

unique_ptr<ILayer> LayerFactory::MakeCellLayer(Point area)
{
	return make_unique<CellLayer>(area);
}


// == LayerZone ==

Point LayerZone::operator[](size_t index) const
{
	return layer.getCell(zoneID, index);
}

size_t LayerZone::size() const
{
	return layer.zoneSize(zoneID);
}