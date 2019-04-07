#include <catch.hpp>
#include "Layer.h"
#include <unordered_set>
#include <iostream>
#include <string>
#include <sstream>

#define RANGE(a) begin(a),end(a)

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
	vector<tuple<string, int, LayerPtr>> layers;

	layers.emplace_back("row", 16, LayerFactory::MakeRowLayer(4));
	layers.emplace_back("column", 16, LayerFactory::MakeColumnLayer(4));
	layers.emplace_back("cell23", 36, LayerFactory::MakeCellLayer(2,3));

	for (auto&[name, count, layer] : layers)
	{
		GIVEN(stdx::cat("layer: ", name))
		{
			std::vector<bool> vecIDsSeen(count, false);
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
							GIVEN(stdx::cat("vecID: ", vecID))
							{
								CHECK(vecID >= 0);
								CHECK(vecID < count);

								CHECK(layer->zoneID(vecID) == zoneID);
								CHECK(!vecIDsSeen[vecID]);
								vecIDsSeen[vecID] = true;
							}
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