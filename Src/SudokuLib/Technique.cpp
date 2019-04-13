#include "Technique.h"

bool RemoveFilledInNumbersTechnique::apply(const Puzzle & puzzle, BoardWithFlags & board) const
{
	bool changed = false;
	for (auto& layer : puzzle.layers)
	{
		// TODO: Limit types of layers

		for (size_t zoneID = 0; zoneID < layer->size(); ++zoneID)
		{
			auto zone = (*layer)[zoneID];
			uint32_t flags = ~0;

			// Find flags
			for (size_t cellID = 0; cellID < zone.size(); ++cellID)
			{
				auto value = board.value(zone[cellID]);
				if (value.ok())
				{
					flags &= ~(1 << value.get());
				}
			}

			// Apply flags
			for (size_t cellID = 0; cellID < zone.size(); ++cellID)
			{
				auto cell = zone[cellID];
				auto value = board.value(cell);
				if (!value.ok())
				{
					changed |= board.requireFlags(cell, flags);
				}
			}
		}


		// TODO: Stuff
	}
	return changed;
}
