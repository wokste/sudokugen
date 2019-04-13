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

	layers.emplace_back("row", 4, LayerFactory::MakeRowLayer(4));
	layers.emplace_back("column", 4, LayerFactory::MakeColumnLayer(4));
	layers.emplace_back("cell23", 6, LayerFactory::MakeCellLayer(Point(2,3)));

	for (auto&[name, sizeXOrY, layer] : layers)
	{
		GIVEN(stdx::cat("layer: ", name))
		{
			for (size_t zoneID = 0; zoneID < layer->size(); ++zoneID)
			{
				auto zone = (*layer)[zoneID];
				GIVEN(stdx::cat("zone: ", zoneID))
				{
					for (size_t itemID = 0; itemID < zone.size(); ++itemID)
					{
						GIVEN(stdx::cat("cell: ", itemID))
						{
							Point vec = zone[itemID];
							GIVEN(stdx::cat("vec: ", vec.x, ",", vec.y ))
							{
								CHECK(vec.x >= 0);
								CHECK(vec.y >= 0);
								CHECK(vec.x < sizeXOrY);
								CHECK(vec.y < sizeXOrY);

								CHECK(layer->zoneID(vec) == zoneID);
							}
						}
					}
				}
			}
		}
	}
}