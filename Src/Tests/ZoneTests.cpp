#include <catch.hpp>
#include "Layer.h"
#include <unordered_set>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace stdx {
	template< typename ... Args >
	std::string cat(Args const& ... args)
	{
		std::ostringstream stream;
		using List = int[];
		(void)List {
			0, ((void)(stream << args), 0) ...
		};

		return stream.str();
	}
}

TEST_CASE("All cells are invertable.", "[Zones]")
{
	vector<tuple<string, LayerPtr>> layers;

	layers.emplace_back("row", LayerFactory::MakeRowLayer(4));
	layers.emplace_back("column", LayerFactory::MakeColumnLayer(4));
	layers.emplace_back("cell", LayerFactory::MakeCellLayer(2,2));

	for (auto&[name, layer] : layers)
	{
		unordered_set<size_t> seenVecIDs;

		GIVEN(stdx::cat("layer: ", name))
		{
			auto zoneCount = layer->zones();
			for (int zoneID = 0; zoneID < zoneCount; ++zoneID)
			{
				GIVEN(stdx::cat("zone: ", zoneID))
				{
					auto itemCount = layer->zoneSizes(zoneID);
					for (int itemID = 0; itemID < itemCount; ++itemID)
					{
						GIVEN(stdx::cat("cell: ", itemID))
						{
							auto vecID = layer->cell(zoneID, itemID);
							CHECK(vecID >= 0);
							CHECK(vecID < 16);

							//CHECK(layer->zoneID(vecID) == zoneID);
							bool hasSeenID = seenVecIDs.count(vecID) > 0;
							CHECK(!hasSeenID);
							seenVecIDs.emplace(vecID);
						}
					}
				}
			}
		}
	}
}

TEST_CASE("Known positions for cells: Horizontal", "[Zones]") {
}

TEST_CASE("Known positions for cells: Vertical", "[Zones]") {
}

TEST_CASE("Known positions for cells: Grid", "[Zones]") {
}