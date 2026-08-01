#ifndef INVENTORIESANDWORKQUEUES_H_
#define INVENTORIESANDWORKQUEUES_H_

#include "work_queue.hpp"
#include <limits>
#include <variant>
#include "inventory_manager.hpp"

void set_unit_job(unit::Database &database, CommodityDispatcher& dispatcher, uint16_t unit_index) {
	Commodity::underlying commodity = get_unit_next_commodity(database, dispatcher, unit_index);
	auto commodity_variant = Commodity::cast(commodity);
	if (auto ptr = std::get_if<Item>( &commodity_variant )) {
		attempt_production(unit_index);
	}
	else if (auto ptr = std::get_if<Buildable>( &commodity_variant )) {
		
	}
	else if (auto ptr = std::get_if<Order>( &commodity_variant )) {

	}
	else if (auto ptr = std::get_if<Knowledge>( &commodity_variant )) {

	}
	else if (auto ptr = std::get_if<Ritual>( &commodity_variant )) {
	}
}


Commodity::underlying get_unit_next_commodity(unit::Database& database, CommodityDispatcher& dispatcher, uint16_t unit_index)
{
	assert(unit_index < database.size);
	int highest = std::numeric_limits<int>::min();
	int role_index = std::numeric_limits<int>::max();
	int commodity_index =  std::numeric_limits<int>::max();
	

	for (size_t i = 0; i < database.roles[unit_index].size(); i++) {
		Role role = database.roles[unit_index][i];
		auto range = CommodityDispatcher::get_priority_range(role);

		for (int j = 0; j < range.second(); j++) {
			if (dispatcher.priorities[j] > highest) 
			{
				highest = dispatcher.priorities[j];
				role_index = i;
				commodity_index = j;
			}
		}
	}
	return roles_to_commodities.get(static_cast<Role>(role_index), commodity_index);
}	

bool continue_or_find_tools_or_quit(
					  Action& action, Target& target, Inventory& inventory, NecessaryToolsBuffer& buffer, Coord coord, uint16_t unit_index)
{
	buffer = ensure_necessary_tools(overflows, overflow_containers, action, inventory, unit_index, coord);
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

// TODO: processes basic productions that do not include liquids, buildables. Break this function down into an 'attempt_recipe' function, which all attempt work fucntions that consume inputs can use.
// variant items
bool attempt_production(int pawn)
{
	// TODO: get type of product variant to deterine item_type
	bool attempt_alternate_recipe = false;
	for (int i = 0; i < 2; i++)
	{
		if (item_type == ItemType::Item)
		{
			attempt_altenate_recipe ? return
					      : Recipe recipe = products[static_cast<int>(product)];
		}
		else if (item_type == ItemType::Tool)
		{
			attempt_alternate_recipe
			    ? return
			    : ToolRecipe recipe = tools[static_cast<int>(product)];
		}
		else if (item_type == ItemType::Buildable)
		{
			attempt_alternate_recipe
			    ? BuildableRecipe recipe = buildables_alternate_interpreter(product)
			    : BuildableRecipe recipe = buildables[static_cast<int>(product)];
		}
		else if (item_type == ItemType::Container)
		{
			attempt_alternate_recipe
			    ? return
			    : ContainerRecipe recipe = containers[static_cast<int>(product)];
		}
		else if (item_type == ItemType::Vehicle)
		{
			attempt_altenate_recipe
			    ? return
			    : VehicleRecipe recipe = vehicles[static_cast<int>(product)];
		}
		
		bool tools_found = false;
		while (!tools_found) {
		NecessaryToolsBuffer buffer = ensure_necessary_tools(pawn, action, mini_actions, items, dests);

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

		vector<std::pair<int, int>> ingredients_found;
		vector<std::pair<int, int>> variant_ingredients_found;

		// FOR LIQUIDS
		if (recipe.item::TAGS.has_tag(item::TAGS::Liquid))
		{
			// TODO: find nearest unprocessing liquid vessel, or get from inventory if
			// none
			bool found = false;
			while (!found)
			{
				if (filled_liquid_containers.find(find_nearest_liquid_container(
					coords[pawn].first, coords[pawn] second)) !=
				    filled_liquid_containers.end())
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
						if (max_amount >
						    (int)(inventories[pawn] recipe.amounts[j] /
							  recipe.ingredients[i]))
							max_amount = (int)(inventories[pawn] recipe
									      .amounts[j] /
									  recipe.ingredients[i]);

						// add the right amount of the type of item in
						// inventory
						ingredients_found.push_back({i, recipe.amounts[i]});
						found_ingredient = true;
						while (recipe.replaceables[i] ==
						       recipe.replaceables[i + 1])
							i++;
						break;
					}
				}
				for (int j = 0; j < inventories[pawn].variant_items.size(); j++)
				{
					if (inventories[pawn].variant_items[j].first ==
						recipe.ingredients[i] &&
					    inventories[pawn].variant_items[j].second >=
						recipe.amounts[i])
					{
						// find which recipe item is the bottleneck for
						// mixing the liquid, or if the amount of water in
						// container is the factor
						if (max_amount >
						    (int)(inventories[pawn] recipe.amounts[j] /
							  recipe.ingredients[i]))
							max_amount = (int)(inventories[pawn] recipe
									      .amounts[j] /
									  recipe.ingredients[i]);

						// add the right amount of the type of item in
						// inventory
						variant_ingredients_found.push_back(
						    {i, recipe.amounts[i]});
						found_ingredient = true;
						break;
					}
				}
				if (!found_ingredient)
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
						time = get_variable_product_time(pawn, product);
					}
					else
						time = products[static_cast<int>(product)].time;
					add_event(time, EventType::ProductComplete, product, pawn,
						 static_cast<Actions>(recipe.action));
					for (int i = 0; i < ingredients_found.size(); i++)
					{
						remove_item(pawn, ingredients_found.first,
							   ingredients_found.second);
					}
					for (int i = 0; i < variant_ingredients_found.size(); i++)
					{
						remove_item(pawn, variant_ingredients_found.first,
							   variant_ingredients_found.second);
					}
					return true;
				}
			}
		}

		// CORPSE
		else if (recipe.item::TAGS.has_tag(item::TAGS::Corpse))
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
						ingredients_found.push_back({i, recipe.amounts[i]});
						found_ingredient = true;
						while (recipe.replaceables[i] ==
						       recipe.replaceables[i + 1])
							i++;
					}
					if (found_ingredient)
						break;
				}
				// loop through variant items
				for (int j = 0; j < inventories[pawn].variant_items.size(); j++)
				{
					if (inventories[pawn].variant_items[j].first ==
						recipe.ingredients[i] &&
					    inventories[pawn].variant_items[j].second >=
						recipe.amounts[i])
					{
						// add the right amount of the type of item in
						// inventory
						variant_ingredients_found.push_back(
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
						std::pair<int, int> item_coord = find_nearest_object(
						    recipe.ingredients[i], coords[pawn].first,
						    coords[pawn] second);
						if (item_coord != {-1, -1} &&
						    man_dist(coords[pawn], item_coord) <
							near_gather_range)
						{
							dests[pawn] = tile_indices[item_coord];
							moving_status[pawn] =
							    MovingStatus::ApproachItem;
							// NOTE: async logic here?
							find_promise[pawn] = std::promise<void>();
							find_future[pawn] =
							    find_promise[pawn].get_future();
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
			add_event(products[static_cast<int>(product)].time,
				 EventType::ProductComplete, static_cast<int>(product), pawn,
				 static_cast<int>());
			for (int i = 0; i < ingredients_found.size(); i++)
			{
				remove_item(pawn, ingredients_found.first, ingredients_found.second);
			}
			for (int i = 0; i < variant_ingredients_found.size(); i++)
			{
				remove_item(pawn, variant_ingredients_found.first,
					   variant_ingredients_found.second);
			}
		}
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
		// get compatible SourceVariant (Tile, Plant, Animal, Scavengeable, or Item)
		SourceVariant source = resource.source[action_index];
		std::pair<int, int> coords = find_nearest_source(source);
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
		for (int j = 0; j < action_to_roles[static_cast<int>(action)].size(); j++)
		{
			for (int k = 0; k < roles[pawn].size; k++)
			{
				if (action_to_roles[action][j] == roles[pawn][k])
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
		int tool_replaceable_list = action_to_tools_replaceables[static_cast<int>(action)];
		for (int j = 0; j < action_to_tools[static_cast<int>(action)].size(); j++)
		{
			bool found_tool = false;
			if (tool_replaceable_list[j] < 0)
				continue; // optional tools
			for (int k = 0; k < tools[pawn].size; k++)
			{
				if (action_to_tools[action][j] == tools[pawn][k])
				{
					while (tool_replaceable_list[j] == tool_replaceable_list[j + 1])
						j++;
					found_tool = true;
				}
			}
			if (!found_tool)
				continue;
		}
		if (found_tool && found_role)
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
		bool found_role = false;
		for (int j = 0; j < action_to_roles[static_cast<int>(action)].size(); j++)
		{
			for (int k = 0; k < roles[pawn].size; k++)
			{
				if (action_to_roles[static_cast<int>(action)][j] == roles[pawn][k])
				{
					found_role = true;
					break;
				}
			}
			if (found_role)
				break;
		}
		if (!found_role)
			return false;
	}
	int tool_replaceable_list = action_to_tools_replaceables[action];
	for (int j = 0; j < action_to_tools[static_cast<int>(action)].size(); j++)
	{
		bool found_tool = false;
		if (tool_replaceable_list[j] < 0)
			continue; // optional tools
		for (int k = 0; k < tools[pawn].size; k++)
		{
			if (action_to_tools[static_cast<int>(action)][j] == tools[pawn][k])
			{
				while (tool_replaceable_list[j] == tool_replaceable_list[j + 1])
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
			for (int j = 0; j < action_to_roles[static_cast<int>(action)].size(); j++)
			{
				for (int k = 0; k < roles[pawn].size; k++)
				{
					if (action_to_roles[static_cast<int>(action)][j] ==
					    roles[pawn][k])
					{
						found_role = true;
						break;
					}
				}
				if (found_role)
					break;
			}
			if !(found_role)
				continue;
			// find tools if role has been found
			int tool_replaceable_list = action_to_tools_replaceables[action];
			bool missing_tool = false;
			for (int j = 0; j < action_to_tools[static_cast<int>(action)].size(); j++)
			{
				bool found_tool = false;
				if (tool_replaceable_list[j] < 0)
					continue; // optional tools
				for (int k = 0; k < tools[pawn].size; k++)
				{
					if (action_to_tools[static_cast<int>(action)][j] ==
					    tools[pawn][k])
					{
						while (tool_replaceable_list[j] ==
						       tool_replaceable_list[j + 1])
							j++;
						found_tool = true;
					}
				}
				if (!found_tool)
				{
					missing_tool = true;
					break;
				}
			}
			if !(missing_tool)
				return true;
		}
	}
	return false;
}

// TODO: check if item or fruit object is removed, if amt 0, remove from
// object_location

// RESOURCE PAWN MANAGEMENT
void set_target_resource(int pawn, Role role)
{
	if !(role < Role : RESOURCEMAX)
		return;
	for (int i = 0; i < resource_unit_resources[static_cat<int>(role)].size(); i++)
	{
		Item item = resource_unit_resources[static_cast<int>(role)][i];
		Resource resource = item_to_resource(item);
		if !(check_action_requisites(resource, pawn))
			return;
		/* TODO: max man dist, nearest search logic for known areas
		dests[pawn] = find_nearest_object_index(item, pawn_coords[pawn].first,
		pawn_coords[pawn].second);
		*/
		// method 2 (unpreferred): prowl for resource
		current_target[pawn] = item;
		moving_status[pawn] = MovingStatus::CheckProwl;
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
		bool child = child_status[pawn];
		// CORPSE
		if (p.tags.has_tag(item::TAGS::Corpse))
		{
			CorpseData corpse = corpse_interpreter(inventories[pawn].focus_station);
			for (int i = 0; i < corpse.products.size(); i++)
			{
				// for each of the products made by butchering corpse, check if it
				// fits in inventory, then containers
				//  if (current_bulk +
				//  bulk_and_weights[static_cast<int>(current_products[pawn])].bulk >
				//  current_max_bulk(current_bulk_status, false) || current_weight +
				//  bulk_and_weights[static_cast<int>(current_products[pawn])].weight >
				//  max_weight(false))  {
				float product_amount = corpse.amounts[i];
				float remaining_space =
				    min(current_max_bulk(inventories[pawn].current_bulk_status, child) -
					    inventories[pawn].total_bulk,
					0);
				if (remaining_space > bulks_and_weights[corpse.products[i]].bulk)
				{
					if (corpse.products[i] == Item::RawMeat)
					{
						uint16_t var = static_cast<uint16_t>(corpse.meat);
						full_add_variant_item(pawn, corpse.products[i],
								   product_amount, var);
					}
					else if (corpse.products[i] == Item::AnimaHides)
					{
						uint16_t var = static_cast<uint16_t>(corpse.hide);
						full_add_variant_item(pawn, corpse.products[i],
								   product_amount, var);
					}
					else
						full_add_item(pawn, corpse.products[i],
							    product_amount);
				}
			}
		}
		// CONTAINER
		else if (recipe.item::TAGS.has_tag(item::TAGS::Container))
			add_container(pawn, product, child);
		// TODO: deal with if container doesnt fit
		// BUILDABLE
	}
	else if (std::holds_alternative<Buildable>(current_products[pawn]))
	{
		std::pair<int, int> item_coords = coords_from_facing(coords[pawn], directions[pawn]);
		tile_object[tile_index[item_coords]] = current_products[pawn];
		// VEHICLE
	}
	else if (std::holds_alternative<Vehicle>(current_products[pawn]))
	{
		std::pair<int, int> item_coords = coords_from_facing(coords[pawn], directions[pawn]);
		tile_object[tile_index[item_coords]] = current_products[pawn];
	} // OTHER ITEMS
	else
	{
		if (static_cast<int>(product) < static_cast<int>(VARIANTSMAX))
		{
			full_add_variant_item(pawn, product, variant, p.amount);
		}
		else
		{
			full_add_item(pawn, product, p.amount);
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
			if (tile_coords[index] == plowables[j])
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
		if (&out_dist_sqr[i] > threshold)
		{
			// second plant in plowed soil
			plowed_soil.knn_search(&query_point[0], num_results, &ret_index[0],
					     &out_dist_sqr[0]);
			nearest_index = ret_index[i];
			break;
			// third plant in unplowed but exposed soil
			if (&out_dist_sqr[i] > threshold)
			{
				soil.knn_search(&query_point[0], num_results, &ret_index[0],
					       &out_dist_sqr[0]);
				nearest_index = ret_index[i];
				break;
				// fourth search for weeds
				if (&out_dist_sqr[i] > threshold)
				{
					weed.knn_search(&query_point[0], num_results, &ret_index[0],
						       &out_dist_sqr[0]);
					nearest_index = ret_index[i];
					break;
				}
			}
		}
		break;
	}

	void variant_item_interpreter() {}

	// NOTE: bad
	void next_role(int pawn, int role_index)
	{
		std::swap(roles[pawn][role_index], roles[pawn][roles[pawn].size()]);
	}

	// // TODO
	// void process_variant_productions() {}

	// // TODO
	// void process_custom_productions() {}



	// }

#endif // INVENTORIESANDWORKQUEUES_H_
