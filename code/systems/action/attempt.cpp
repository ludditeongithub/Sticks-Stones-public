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
void decideTask(EntityID pawnIndex, UnitDatabase& database)
{
	int taskIndex = -1;
	TaskType type = TaskType::NONE;
	Role role;
	for (size_t i = 0; i < g_TaskPriorityQueue.size; i++)
	{
		// TODO: check if role is producer vs resource vs etc on lookup table
		if (g_TaskPriorityQueue[i].priority < highest)
		{
			for (EntityID j = 0; j < roles[pawnIndex].size; j++)
			{
				Role tRole = g_TaskPriorityQueue[i].role;

				if (tRole < Role::RESOURCEMAX && tRole > Role::SUPPORTMAX)
				{
					
				}
				else if (tRole < Role::PRODUCTSMAX && tRole > Role::RESOURCEMAX)
				{

				}
			}
		}
	}

	if (highest == 1)
	{
		attemptProduction(pawnIndex, producerProducts[static_cast<int>(tRole)][taskIndex]);
		return;
	}
}
}

for (int i = 0; i < supportPriorityQueue.size; i++)
{
	if (supportPriorityQueue[i].second < highest)
	{
		for (int j = 0; j < roles[pawnIndex].size; j++)
		{
			Role tRole = roles[pawnIndex][j];
			if (tRole == supportPriorityQueue[i])
				(producerProducts[static_cast<int>(tRole)][k] ==
				 productsPriorityQueue[i].first)
				{
					type = TaskType::Suppot highest =
					    productsPriorityQueue[i].second;
					taskIndex = i;
				}
		}
	}
}
if (highest == 1)
{
	attemptProduct(pawnIndex, role);
	return;
}
}
}

if (movingStatus[pawnIndex] != MovingStatus::Production)
{
	attemptProduction(pawnIndex, producerProducts[static_cast<int>(roles[pawnIndex[i]])]);
}
}


// variantIndex superfluous for non-variant items
void getResourceAction(int pawn, Item item, int sourceIndex, int variantIndex)
{
	Resource resource = resources[item];
	Action action = resource.action[sourceVariantIndex];
	SourceVariant source = resource.source[sourceIndex];
	// see if Object should be removed from tile
	bool removeObject = true;
	if (action == Actions::Collect)
	{
		if (source == Tile::ShallowWater || source == Tile::FlowingWater ||
		    source == Tile::DeepWater || source == Tile::ShallowSaltWater ||
		    source == Tile::Sand || source == Scavengeable::Beehive ||
		    source == Scavengeable::ArtificialBeehive)
		{
			removeObject = false;
		}
	}
	if (removeObject)
	{
		if (action == Actions::Milk)
			removeObject = false;
		else if (action == Actions::Fish)
			removeObject = false;
		else if (action == Actions::Shear)
			removeObject = false;
		else
			for (int i = 0; i < regrowthCrops.size(); i++)
			{
				if (item == regrowthCrops[i])
				{
					removeObject = false;
				}
			}
	}
	// Get amount of item to put into inventory
	if (action == Action::Lift)
	{
		Inventories[pawn].leftHand == Tool::Log;
		Inventories[pawn].rightHand == Tool::Log;
	}
	else
	{
		int amt = resources[item].amount[sourceIndex];
		// if item in question is an item with variants
		if (static_cast<int>(item) < static_cast<int>(Item::VARIANTSMAX))
		{
			Inventories[pawn].variantItems.push_back({item, amt});
			Inventories[pawn].variantItemTypes.push_back(variantIndex);
		}
		else
		{
			Inventories[pawn].items.push_back({item, amt});
		}
	}
}
