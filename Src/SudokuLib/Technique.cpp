#include "Technique.h"

bool RemoveFilledInNumbersTechnique::apply(const Puzzle & puzzle, BoardWithFlags & board) const
{
	bool changed = false;
	for (auto& layer : puzzle.layers)
	{
		// TODO: Limit types of layers

		for (size_t l = 0; l < layer->zones(); ++l)
		{
			uint32_t flags = ~0;

			// Find flags
			for (size_t i = 0; i < layer->zoneSizes(l); ++i)
			{
				auto cell = layer->cell(l, i);
				auto value = board.value(cell);
				if (value.ok())
				{
					flags &= ~(1 << value.get());
				}
			}

			// Apply flags
			for (size_t i = 0; i < layer->zoneSizes(l); ++i)
			{
				auto cell = layer->cell(l, i);
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
