#ifndef INVENTORIESANDWORKQUEUES_H_
#define INVENTORIESANDWORKQUEUES_H_

#include "work_queue.hpp"
#include <limits>
#include <variant>
#include "inventory_manager.hpp"

void set_unit_job(UnitDatabase &database, CommodityDispatcher& dispatcher, uint16_t unitIndex) {
	Commodity::underlying commodity = getUnitNextCommodity(database, dispatcher, unitIndex);
	auto commodity_variant = Commodity::cast(commodity);
	if (auto ptr = std::get_if<Item>( &commodityVariant )) {
		attempt_production(unitIndex);
	}
	else if (auto ptr = std::get_if<Buildable>( &commodityVariant )) {
		
	}
	else if (auto ptr = std::get_if<Order>( &commodityVariant )) {

	}
	else if (auto ptr = std::get_if<Knowledge>( &commodityVariant )) {

	}
	else if (auto ptr = std::get_if<Ritual>( &commodityVariant )) {
	}
}


Commodity::underlying get_unit_next_commodity(UnitDatabase& database, CommodityDispatcher& dispatcher, uint16_t unitIndex)
{
	assert(unitIndex < database.size);
	int highest = std::numeric_limits<int>::min();
	int role_index = std::numeric_limits<int>::max();
	int commodity_index =  std::numeric_limits<int>::max();
	

	for (size_t i = 0; i < database.roles[unitIndex].size(); i++) {
		Role role = database.roles[unitIndex][i];
		auto range = CommodityDispatcher::getPriorityRange(role);

		for (int j = 0; j < range.second(); j++) {
			if (dispatcher.priorities[j] > highest) 
			{
				highest = dispatcher.priorities[j];
				role_index = i;
				commodity_index = j;
			}
		}
	}
	return rolesToCommodities.get(static_cast<Role>(roleIndex), commodityIndex);
}	

bool continue_or_find_tools_or_quit(OverflowHashMap &overflows,
					  OverflowContainerMap &overflowContainers, Action& action, Target& target, Inventory& inventory, NecessaryToolsBuffer& buffer, Coord coord, uint16_t unitIndex)
{
	buffer = ensureNecessaryTools(overflows, overflowContainers, action, inventory, unitIndex, coord);
	switch (buffer.state) {
	case ToolsState::FoundAll:
		return true;
		break;
	case ToolsState::Finding:
		action = Action::PickupTool;
		target = {};
		return false;
		break;
	case ToolsState::CannotFind:
		action = Action::Assign;
		return false;
		break;
	default:	
	}
}


bool attempt_recipe(bool alternate) {

}

// TODO: processes basic productions that do not include liquids, buildables. Break this function down into an 'attemptRecipe' function, which all attempt work fucntions that consume inputs can use.
// variant items
bool attempt_production(int pawn)
{
	// TODO: get type of product variant to deterine itemType
	bool attempt_alternate_recipe = false;
	for (int i = 0; i < 2; i++)
	{
		if (itemType == ItemType::Item)
		{
			attemptAltenateRecipe ? return
					      : Recipe recipe = products[static_cast<int>(product)];
		}
		else if (itemType == ItemType::Tool)
		{
			attemptAlternateRecipe
			    ? return
			    : ToolRecipe recipe = tools[static_cast<int>(product)];
		}
		else if (itemType == ItemType::Buildable)
		{
			attemptAlternateRecipe
			    ? BuildableRecipe recipe = buildablesAlternateInterpreter(product)
			    : BuildableRecipe recipe = buildables[static_cast<int>(product)];
		}
		else if (itemType == ItemType::Container)
		{
			attemptAlternateRecipe
			    ? return
			    : ContainerRecipe recipe = containers[static_cast<int>(product)];
		}
		else if (itemType == ItemType::Vehicle)
		{
			attemptAltenateRecipe
			    ? return
			    : VehicleRecipe recipe = vehicles[static_cast<int>(product)];
		}
		
		bool tools_found = false;
		while (!tools_found) {
		NecessaryToolsBuffer buffer = ensureNecessaryTools(pawn, action, miniActions, items, dests);

		switch (buffer.state) {
		case ToolsState::FoundAll:			
			tools_found = true;
			break;
		case ToolsState::Finding:
			
			break;
		case case-2:
			
			break;
		default:
			
		}
		}

		vector<std::pair<int, int>> ingredientsFound;
		vector<std::pair<int, int>> variantIngredientsFound;

		// FOR LIQUIDS
		if (recipe.itemTags.hasTag(itemTags::Liquid))
		{
			// TODO: find nearest unprocessing liquid vessel, or get from inventory if
			// none
			bool found = false;
			while (!found)
			{
				if (filledLiquidContainers.find(findNearestLiquidContainer(
					coords[pawn].first, coords[pawn] second)) !=
				    filledLiquidContainers.end())
			}
			int max_amount = 99999;
			for (int i = 0; i < recipe.ingredients.size(); i++)
			{
				// TODO: get amount of liquid in found vessel
				for (int j = 0; j < inventories[pawn].items.size(); j++)
				{
					if (inventories[pawn].items[i].first ==
						recipe.ingredients[i] &&
					    inventories[pawn].items[j].second >= recipe.amounts[i])
					{
						// find which recipe item is the bottleneck for
						// mixing the liquid, or if the amount of water in
						// container is the factor
						if (maxAmount >
						    (int)(inventories[pawn] recipe.amounts[j] /
							  recipe.ingredients[i]))
							maxAmount = (int)(inventories[pawn] recipe
									      .amounts[j] /
									  recipe.ingredients[i]);

						// add the right amount of the type of item in
						// inventory
						ingredientsFound.push_back({i, recipe.amounts[i]});
						foundIngredient = true;
						while (recipe.replaceables[i] ==
						       recipe.replaceables[i + 1])
							i++;
						break;
					}
				}
				for (int j = 0; j < inventories[pawn].variantItems.size(); j++)
				{
					if (inventories[pawn].variantItems[j].first ==
						recipe.ingredients[i] &&
					    inventories[pawn].variantItems[j].second >=
						recipe.amounts[i])
					{
						// find which recipe item is the bottleneck for
						// mixing the liquid, or if the amount of water in
						// container is the factor
						if (maxAmount >
						    (int)(inventories[pawn] recipe.amounts[j] /
							  recipe.ingredients[i]))
							maxAmount = (int)(inventories[pawn] recipe
									      .amounts[j] /
									  recipe.ingredients[i]);

						// add the right amount of the type of item in
						// inventory
						variantIngredientsFound.push_back(
						    {i, recipe.amounts[i]});
						foundIngredient = true;
						break;
					}
				}
				if (!foundIngredient)
				{
					if (!attempt_alternate_recipe)
					{
						attempt_alternate_recipe = true;
					}
					else
						return false; // item not craftable
				}
				else
				{
					// START CRAFTING
					//  if product time is variable or not applicable
					uint16_t time = 0;
					if (products[static_cast<int>(product)].time == 0)
					{
						time = getVariableProductTime(pawn, product);
					}
					else
						time = products[static_cast<int>(product)].time;
					addEvent(time, EventType::ProductComplete, product, pawn,
						 static_cast<Actions>(recipe.action));
					for (int i = 0; i < ingredientsFound.size(); i++)
					{
						removeItem(pawn, ingredientsFound.first,
							   ingredientsFound.second);
					}
					for (int i = 0; i < variantIngredientsFound.size(); i++)
					{
						removeItem(pawn, variantIngredientsFound.first,
							   variantIngredientsFound.second);
					}
					return true;
				}
			}
		}

		// CORPSE
		else if (recipe.itemTags.hasTag(itemTags::Corpse))
		{
			// TODO: determine how pawn focuses on station, on when it lets go, go
			// find corpse if needed
		}
		// NORMAL ITEMS
		else
		{
			for (int i = 0; i < recipe.ingredients.size(); i++)
			{
				if (recipe.replaceables[i] == 0)
				{ // optional ingredient
				  // TODO: optional ingredient interpreter
				}
				if (recipe.ingredients[i] == Item::EMPTY)
					continue;
				bool found_ingredient = false;
				// loop through non-variant items
				for (int j = 0; j < inventories[pawn].items.size(); j++)
				{
					if (inventories[pawn].items[i].first ==
						recipe.ingredients[i] &&
					    inventories[pawn].items[j].second >= recipe.amounts[i])
					{
						// add the right amount of the type of item in
						// inventory
						ingredientsFound.push_back({i, recipe.amounts[i]});
						found_ingredient = true;
						while (recipe.replaceables[i] ==
						       recipe.replaceables[i + 1])
							i++;
					}
					if (found_ingredient)
						break;
				}
				// loop through variant items
				for (int j = 0; j < inventories[pawn].variantItems.size(); j++)
				{
					if (inventories[pawn].variantItems[j].first ==
						recipe.ingredients[i] &&
					    inventories[pawn].variantItems[j].second >=
						recipe.amounts[i])
					{
						// add the right amount of the type of item in
						// inventory
						variantIngredientsFound.push_back(
						    {i, recipe.amounts[i]});
						found_ingredient = true;
					}
					if (found_ingredient)
						break;
				}
				if (!found_ingredient)
				{
					if (!attempt_alternate_recipe)
					{
						attempt_alternate_recipe = true;
					}
					else
					{
						// try to find nearest ingredient
						// TODO: create nearest with lower man dist, also do
						// for non-alternate recipe
						std::pair<int, int> itemCoord = findNearestObject(
						    recipe.ingredients[i], coords[pawn].first,
						    coords[pawn] second);
						if (itemCoord != {-1, -1} &&
						    manDist(coords[pawn], itemCoord) <
							nearGatherRange)
						{
							dests[pawn] = tileIndices[itemCoord];
							movingStatus[pawn] =
							    MovingStatus::ApproachItem;
							// NOTE: async logic here?
							findPromise[pawn] = std::promise<void>();
							findFuture[pawn] =
							    findPromise[pawn].get_future();
						}
					}
				}
			}
		}
		else
		{
			// make pawn perform task, and add event to complete
			// TODO: Possible error here, if cast to product variant is not cast to
			// underlying type
			addEvent(products[static_cast<int>(product)].time,
				 EventType::ProductComplete, static_cast<int>(product), pawn,
				 static_cast<int>());
			for (int i = 0; i < ingredientsFound.size(); i++)
			{
				removeItem(pawn, ingredientsFound.first, ingredientsFound.second);
			}
			for (int i = 0; i < variantIngredientsFound.size(); i++)
			{
				removeItem(pawn, variantIngredientsFound.first,
					   variantIngredientsFound.second);
			}
		}
	}
}

// variantIndex superfluous for non-variant items
void get_resource_action(int pawn, Item item, int sourceIndex, int variantIndex)
{
	Resource resource = resources[item];
	Action action = resource.action[sourceVariantIndex];
	SourceVariant source = resource.source[sourceIndex];
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
			for (int i = 0; i < regrowthCrops.size(); i++)
			{
				if (item == regrowthCrops[i])
				{
					remove_object = false;
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

// RESOURCES PAWN MANAGEMENT

// gets resource at certain tile, when pawn is adjacent to it, by confirming
// action.
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
		for (int j = 0; j < roles[i].size(); j++)
		{
			for (int k = 0; k < resources.action.size(); k++)
			{
				if (actionToRoles[resources.action[k]] == roles[i][j])
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
		// get compatible SourceVariant (Tile, Plant, Animal, Scavengeable, or Item)
		SourceVariant source = resource.source[action_index];
		std::pair<int, int> coords = findNearestSource(source);
		// SHORTEST PATH ALGORITHM
	}
}

// NOTE: this seems a little shifty, tools part
bool check_action_requisites(Resource resource, int pawn)
{
	for (int i = 0; i < resource.action.size(); i++)
	{
		Actions action = recipe.action;
		if (action == Actions::NONE)
			continue;
		bool found_role = false;
		for (int j = 0; j < actionToRoles[static_cast<int>(action)].size(); j++)
		{
			for (int k = 0; k < roles[pawn].size; k++)
			{
				if (actionToRoles[action][j] == roles[pawn][k])
				{
					found_role = true;
					break;
				}
			}
			if (found_role)
				break;
		}
		if (!found_role)
			continue;
		int tool_replaceable_list = actionToToolsReplaceables[static_cast<int>(action)];
		for (int j = 0; j < actionToTools[static_cast<int>(action)].size(); j++)
		{
			bool found_tool = false;
			if (toolReplaceableList[j] < 0)
				continue; // optional tools
			for (int k = 0; k < tools[pawn].size; k++)
			{
				if (actionToTools[action][j] == tools[pawn][k])
				{
					while (toolReplaceableList[j] == toolReplaceableList[j + 1])
						j++;
					found_tool = true;
				}
			}
			if (!found_tool)
				continue;
		}
		if (foundTool && foundRole)
			return true;
	}
	return false;
}

// TODO: finish array-ifying
Array<bool> check_action_requisites(Recipe recipe, Array<Role> roles)
{
	if !(recipe.action == Actions::NONE)
	{
		// confirm pawn can perform action necessary to produce product
		Actions action = recipe.action;
		bool foundRole = false;
		for (int j = 0; j < actionToRoles[static_cast<int>(action)].size(); j++)
		{
			for (int k = 0; k < roles[pawn].size; k++)
			{
				if (actionToRoles[static_cast<int>(action)][j] == roles[pawn][k])
				{
					foundRole = true;
					break;
				}
			}
			if (foundRole)
				break;
		}
		if (!foundRole)
			return false;
	}
	int toolReplaceableList = actionToToolsReplaceables[action];
	for (int j = 0; j < actionToTools[static_cast<int>(action)].size(); j++)
	{
		bool found_tool = false;
		if (toolReplaceableList[j] < 0)
			continue; // optional tools
		for (int k = 0; k < tools[pawn].size; k++)
		{
			if (actionToTools[static_cast<int>(action)][j] == tools[pawn][k])
			{
				while (toolReplaceableList[j] == toolReplaceableList[j + 1])
					j++;
				found_tool = true;
			}
		}
		if (!found_tool)
			return false;
	}
	return true;
}

bool check_action_requisites(Resource resource, int pawn)
{
	bool found_role = false;
	for (int i = 0; i = resource.actions.size(); i++)
	{
		if !(resource.action == Actions::NONE)
		{
			// confirm pawn can perform action
			Actions action = resource.actions[i];
			for (int j = 0; j < actionToRoles[static_cast<int>(action)].size(); j++)
			{
				for (int k = 0; k < roles[pawn].size; k++)
				{
					if (actionToRoles[static_cast<int>(action)][j] ==
					    roles[pawn][k])
					{
						foundRole = true;
						break;
					}
				}
				if (foundRole)
					break;
			}
			if !(foundRole)
				continue;
			// find tools if role has been found
			int toolReplaceableList = actionToToolsReplaceables[action];
			bool missingTool = false;
			for (int j = 0; j < actionToTools[static_cast<int>(action)].size(); j++)
			{
				bool foundTool = false;
				if (toolReplaceableList[j] < 0)
					continue; // optional tools
				for (int k = 0; k < tools[pawn].size; k++)
				{
					if (actionToTools[static_cast<int>(action)][j] ==
					    tools[pawn][k])
					{
						while (toolReplaceableList[j] ==
						       toolReplaceableList[j + 1])
							j++;
						foundTool = true;
					}
				}
				if (!foundTool)
				{
					missingTool = true;
					break;
				}
			}
			if !(missingTool)
				return true;
		}
	}
	return false;
}

// TODO: check if item or fruit object is removed, if amt 0, remove from
// objectLocation

// RESOURCE PAWN MANAGEMENT
void set_target_resource(int pawn, Role role)
{
	if !(role < Role : RESOURCEMAX)
		return;
	for (int i = 0; i < resourceUnitResources[static_cat<int>(role)].size(); i++)
	{
		Item item = resourceUnitResources[static_cast<int>(role)][i];
		Resource resource = itemToResource(item);
		if !(checkActionRequisites(resource, pawn))
			return;
		/* TODO: max man dist, nearest search logic for known areas
		dests[pawn] = findNearestObjectIndex(item, pawnCoords[pawn].first,
		pawnCoords[pawn].second);
		*/
		// method 2 (unpreferred): prowl for resource
		currentTarget[pawn] = item;
		movingStatus[pawn] = MovingStatus::CheckProwl;
	}
}

void process_resources() {}


// when production of item is finished, wear tools that were used, place if
// buildable or vehicle or go to inventory if item, variant optional
void product_finish(ProductVariant product, int pawn, Actions action, uint16_t variant)
{

	/* TODO: change this section to be event-based */
	if (std::holds_alternative<Item>(products))
	{
		Recipe p = products[static_cast<int>(product)];
		bool child = childStatus[pawn];
		// CORPSE
		if (p.tags.hasTag(itemTags::Corpse))
		{
			CorpseData corpse = corpseInterpreter(inventories[pawn].focusStation);
			for (int i = 0; i < corpse.products.size(); i++)
			{
				// for each of the products made by butchering corpse, check if it
				// fits in inventory, then containers
				//  if (currentBulk +
				//  bulkAndWeights[static_cast<int>(currentProducts[pawn])].bulk >
				//  currentMaxBulk(currentBulkStatus, false) || currentWeight +
				//  bulkAndWeights[static_cast<int>(currentProducts[pawn])].weight >
				//  maxWeight(false))  {
				float product_amount = corpse.amounts[i];
				float remaining_space =
				    min(currentMaxBulk(inventories[pawn].currentBulkStatus, child) -
					    inventories[pawn].totalBulk,
					0);
				if (remainingSpace > bulksAndWeights[corpse.products[i]].bulk)
				{
					if (corpse.products[i] == Item::RawMeat)
					{
						uint16_t var = static_cast<uint16_t>(corpse.meat);
						fullAddVariantItem(pawn, corpse.products[i],
								   product_amount, var);
					}
					else if (corpse.products[i] == Item::AnimaHides)
					{
						uint16_t var = static_cast<uint16_t>(corpse.hide);
						fullAddVariantItem(pawn, corpse.products[i],
								   product_amount, var);
					}
					else
						fullAddItem(pawn, corpse.products[i],
							    product_amount);
				}
			}
		}
		// CONTAINER
		else if (recipe.itemTags.hasTag(itemTags::Container))
			addContainer(pawn, product, child);
		// TODO: deal with if container doesnt fit
		// BUILDABLE
	}
	else if (std::holds_alternative<Buildable>(currentProducts[pawn]))
	{
		std::pair<int, int> itemCoords = coordsFromFacing(coords[pawn], directions[pawn]);
		tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
		// VEHICLE
	}
	else if (std::holds_alternative<Vehicle>(currentProducts[pawn]))
	{
		std::pair<int, int> itemCoords = coordsFromFacing(coords[pawn], directions[pawn]);
		tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
	} // OTHER ITEMS
	else
	{
		if (static_cast<int>(product) < static_cast<int>(VARIANTSMAX))
		{
			fullAddVariantItem(pawn, product, variant, p.amount);
		}
		else
		{
			fullAddItem(pawn, product, p.amount);
		}
	}
}

// SUPPORT (means they do not gain items from their action), but also don't do
// damage
void attempt_support(int pawn, Role role)
{
	switch (role)
	{
	case Role::Plower:
		// TODO: switch between plowing,planting, and harvesting modes for farmer
		bool plowable;
		for (int j = 0; j < plowables.size(); j++)
		{
			if (tileCoords[index] == plowables[j])
			{
				plowable = true;
				break;
			}
		}
		if (!plowable)
		{
			// TODO: wander to new tile
		}
		break;
	case Role::Planter:
		if (&outDistSqr[i] > threshold)
		{
			// second plant in plowed soil
			plowedSoil.knnSearch(&queryPoint[0], numResults, &retIndex[0],
					     &outDistSqr[0]);
			nearestIndex = retIndex[i];
			break;
			// third plant in unplowed but exposed soil
			if (&outDistSqr[i] > threshold)
			{
				soil.knnSearch(&queryPoint[0], numResults, &retIndex[0],
					       &outDistSqr[0]);
				nearestIndex = retIndex[i];
				break;
				// fourth search for weeds
				if (&outDistSqr[i] > threshold)
				{
					weed.knnSearch(&queryPoint[0], numResults, &retIndex[0],
						       &outDistSqr[0]);
					nearestIndex = retIndex[i];
					break;
				}
			}
		}
		break;
	}

	void variantItemInterpreter() {}

	// NOTE: bad
	void nextRole(int pawn, int roleIndex)
	{
		std::swap(roles[pawn][roleIndex], roles[pawn][roles[pawn].size()]);
	}

	// // TODO
	// void processVariantProductions() {}

	// // TODO
	// void processCustomProductions() {}



	// }

#endif // INVENTORIESANDWORKQUEUES_H_
