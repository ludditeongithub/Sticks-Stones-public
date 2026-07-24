// COMMAND
// The authority (you), oligarchy, or democratic state commands what the pawns produce, and you own all goods.
// Large Order (Satisfaction) decrease and production decrease. Resource
// estimates are terrible and especially if order is low

// MIXED COMMAND
// The authority (you) also sends mandatory quotas of goods pawns must produce,
// which they produce first, but after that pawns switch roles and produce
// whatever they like to produce, and also keep their goods. Pawns receive a
// large a small bonus and a small Order (Satisfaction) bonus, and are somewhat
// more likely to produce high quality items. You can buy goods from your pawns.
// Resource estimates are poor

// MARKET
// You can buy goods from your pawns, and also tax them, but cannot set quotas.
// Money is crucial in this run. Pawns receive a medium bonus and a medium Order
// (Satisfaction) bonus, and are quite more likely to produce high quality
// items. Resource estimates are great. True bureaucratic recording is expensive

// ANARCHY
// Pawns switch roles and produce whatever they like to produce, and also keep
// their goods. Only minimum taxes can be set, and only certain types. However,
// they receive a large production bonus and a large Order (Satisfaction) bonus,
// and are more likely to produce high quality items. You only control truly
// control the government and military pawns. You can buy and sell goods from
// your pawns, as well as hire mercenaries that form among your pawns. Pawns buy
// and sell goods among each other. Resource Estimates are decent, but true
// bureaucratic recording is impossible

/* Get jobs from  */
// NOTE: can implement jump table. this is for authority command structure
void decide_task(EntityID pawn_index, UnitDatabase& database)
{
	int task_index = -1;
	TaskType type = TaskType::NONE;
	Role role;
	for (size_t i = 0; i < g_TaskPriorityQueue.size; i++)
	{
		// TODO: check if role is producer vs resource vs etc on lookup table
		if (g_TaskPriorityQueue[i].priority < highest)
		{
			for (EntityID j = 0; j < roles[pawn_index].size; j++)
			{
				Role t_role = g_TaskPriorityQueue[i].role;

				if (t_role < Role::RESOURCEMAX && t_role > Role::SUPPORTMAX)
				{
					
				}
				else if (t_role < Role::PRODUCTSMAX && t_role > Role::RESOURCEMAX)
				{

				}
			}
		}
	}

	if (highest == 1)
	{
		attempt_production(pawn_index, producer_products[static_cast<int>(t_role)][task_index]);
		return;
	}
}
}

for (int i = 0; i < support_priority_queue.size; i++)
{
	if (support_priority_queue[i].second < highest)
	{
		for (int j = 0; j < roles[pawn_index].size; j++)
		{
			Role t_role = roles[pawn_index][j];
			if (t_role == support_priority_queue[i])
				(producer_products[static_cast<int>(t_role)][k] ==
				 products_priority_queue[i].first)
				{
					type = TaskType::Suppot highest =
					    products_priority_queue[i].second;
					task_index = i;
				}
		}
	}
}
if (highest == 1)
{
	attempt_product(pawn_index, role);
	return;
}
}
}

if (moving_status[pawn_index] != MovingStatus::Production)
{
	attempt_production(pawn_index, producer_products[static_cast<int>(roles[pawn_index[i]])]);
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
