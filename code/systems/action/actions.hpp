#pragma once
#include <core/data.hpp>
#include <core/containers.hpp>
#include <vector>
#include <world/action/enum.hpp>
#include <world/animal/enum.hpp>

struct ActionEventDispatchBuffer
{
		bool animals;
		std::vector<EntityID> movingTiles;
		std::vector<EntityID> checkNearTargets;
		std::vector<EntityID> approachs;
		std::vector<EntityID> units;

		ActionEventDispatchBuffer(size_t size, bool animals) : animals(animals)
		{
			if (animals)
					{
					}
					else
							{
									units.reserve(size);
							}
			movingTiles.reserve(size);
			checkNearTargets.reserve(size);
			approachs.reserve(size);
		}

		void shrink_to_fit()
		{
			if (animals)
					{
					}
					else
							{
									units.shrink_to_fit();
							}
			movingTiles.shrink_to_fit();
			checkNearTargets.shrink_to_fit();
			approachs.shrink_to_fit();
		}			
};

ActionEventDispatchBuffer& mark_acting_entities(std::vector<EntityID> &indices, std::optional<Array<Animal>> &animals, Array<Coord> &coords, Array<size_t>& targets, Array<Action>& actions, Array<FrameData>& frameDatas);
