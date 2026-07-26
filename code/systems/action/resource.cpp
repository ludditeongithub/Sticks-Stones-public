// RESOURCES PAWN MANAGEMENT
//  change to assumming that the pawn is valid --> invalid pawns should never have been given this
//  task in the first place gets resource at certain tile, when pawn is adjacent to it, by
//  confirming action.
void collect_resource(Item item)
{
	if (item < Item::RESOURCEMAX)
		return;
	Source resource = resources[item];
	// find available pawns who can perform actions (On^3)
	bool found_pawn = false;
	int pawn_index;
	int action_index;
	Role role;
	for (int i = 0; i < roles.size(); i++)
	{ // check each pawn
		if (!check_occupied(i))
		{
			for (int j = 0; j < roles[i].size(); j++)
			{
				for (int k = 0; k < resources.action.size(); k++)
				{
					if (action_to_roles[resources.action[k]] == roles[i][j])
					{
						pawn_index = i;
						action_index = k;
						role = roles[i][j];
						found_pawn = true;
					}
					if (found_pawn)
						break;
				}
				if (found_pawn)
					break;
			}
			if (found_pawn)
				break;
		}
		// get compatible SourceVariant (Tile, Plant, Animal, Scavengeable, or Item)
		SourceVariant source = resource.source[action_index];
		std::pair<int, int> coords = find_nearest_source(source);
		// SHORTEST PATH ALGORITHM
	}
}


// variant_index superfluous for non-variant items
void get_resource_action(int pawn, Item item, int source_index, int variant_index)
{
	Resource resource = resources[item];
	Action action = resource.action[source_variant_index];
	SourceVariant source = resource.source[source_index];
	// see if Object should be removed from tile
	bool remove_object = true;
	if (action == Actions::Collect)
	{
		if (source == Tile::ShallowWater || source == Tile::FlowingWater ||
		    source == Tile::DeepWater || source == Tile::ShallowSaltWater ||
		    source == Tile::Sand || source == Scavengeable::Beehive ||
		    source == Scavengeable::ArtificialBeehive)
		{
			remove_object = false;
		}
	}
	if (remove_object)
	{
		if (action == Actions::Milk)
			remove_object = false;
		else if (action == Actions::Fish)
			remove_object = false;
		else if (action == Actions::Shear)
			remove_object = false;
		else
			for (int i = 0; i < regrowth_crops.size(); i++)
			{
				if (item == regrowth_crops[i])
				{
					remove_object = false;
				}
			}
	}
	// Get amount of item to put into inventory
	if (action == Action::Lift)
	{
		Inventories[pawn].left_hand == Tool::Log;
		Inventories[pawn].right_hand == Tool::Log;
	}
	else
	{
		int amt = resources[item].amount[source_index];
		// if item in question is an item with variants
		if (static_cast<int>(item) < static_cast<int>(Item::VARIANTSMAX))
		{
			Inventories[pawn].variant_items.push_back({item, amt});
			Inventories[pawn].variant_item_types.push_back(variant_index);
		}
		else
		{
			Inventories[pawn].items.push_back({item, amt});
		}
	}
}
