#include "inventory.hpp"
#include "world/item/enum.hpp"
#include "world/item/tags.hpp"
#include "world/unit/database.hpp"
#include <world/item/container.hpp>
#include <array>
#include <cstdint>
#include <optional>
#include <variant>
// OPTI: stop runtime dispatch (std::variant)
// TODO: change to work for tools/variants of different weights
inline float calculate_remaining_bulk(BulkStatus bulk_status, float bulk)
{
	switch (bulk_status)
	{
	case BulkStatus::Fine:
		return FINE_BULK_MAX - bulk;
		break;
	case BulkStatus::Mid:
		return MID_BULK_MAX - bulk;
		break;
	case BulkStatus::Single:
		return SINGLE_BULK_MAX - bulk;
		break;
	default:
		// TODO: error handling
		std::cerr << "Invalid Bulk Status." << std::endl;
	}
}

inline float calculate_remaining_bulk(ContainerType type, float bulk)
{
	return container_bulk_capacities[type] - bulk;
}

inline float calculate_remaining_weight(ContainerType type, float weight)
{
	return container_weight_capacities[type] - weight;
}

inline ContainerStorageData get_remaining_storage(Inventory &inventory, Container &container)
{
	ContainerStorageData csd;
	// OPTI: extra check here
	if (container.type == ContainerType::Hands)
	{
		csd.remaining_bulk = calculate_remaining_bulk(inventory.bulk_status, container.bulk);
	}
	else
	{
		csd.remaining_bulk = calculate_remaining_bulk(container.type, container.bulk);
	}
	csd.remaining_weight = calculate_remaining_weight(container.type, inventory.weight);
	return csd;
}

// TODO: redo all these functions to also work for Tools, VariantItems
inline uint16_t get_max_items_stored(Item holdable, ContainerStorage storage)
{
	StorageData sd = item_bulk_and_weights[holdable];
	return min(storage.remaining_weight / sd.weight, storage.remaining_bulk / sd.bulk);
}

inline uint16_t get_max_weight(Strength strength) { return 40 + (strength * 30); }

struct InventoryAddBuffer
{
	Item holdable;
	SpecialItemData special_data;
	uint8_t variant;
	uint16_t container_amount;
	std::array<uint16_t, 8> amounts_per_container;
	std::array<bool, 8> overflow;
};

template <typename Slots>
void add_item_overflow(Slots &slots, HoldableSlot holdable,
		     std::optional<uint16_t> unit_index = std::nullopt,
		     std::optional<uint16_t> container_index = std::nullopt)
{
	if constexpr (std::is_same_v<Slots, std::vector<ItemSlot>>)
	{
		slots.push_back(holdable);
	}
	else if constexpr (std::is_same_v<Slots,
					  std::array<ItemSlot, HOLDABLE_UNDERFLOW_LIMIT>>)
	{
		g_overflow_hash_map[overflow_hash(unit_index.value(), container_index.value())].push_back(
		    holdable);
	}
}

void add_item(std::vector<HoldableSlot> &holdables,
	     InventoryAddBuffer &buffer, std::optional<uint8_t> amount = std::nullopt)
{
	Item item_to_add = buffer.holdable;

	bool found = false;
	if (has_tag(ItemTags::OneHandedTool, item::TAGS[item_to_add]) || has_tag(ItemTags::TwoHandedTool, item::TAGS[item_to_add]))
	{
			for (size_t i = 0; i < holdables.size(); i++)
			{                          
				if (auto* content = std::get_if<ToolSlot>(&holdables[i]))
				{
				if (content->is_empty())
				{
					holdables[i] = ToolSlot(item_to_add, buffer.special_data);
                                        HoldableSlot h = ToolSlot(item_to_add, buffer.special_data);
					return;
				}	
				}										
			}
		add_item_overflow(overflows, holdables, ToolSlot(item_to_add, buffer.special_data));
	}
	else 
	{
          if (has_tag(ItemTags::Variant, item::TAGS[item_to_add]))
		{
			for (size_t i = 0; i < holdables.size(); i++)
			{
				if (found)
					break;
				if (holdables[i] == nullptr) {
					holdables[i] = VariantItemSlot(item_to_add, amount.value(), buffer.variant);
					return;
				}
				
				if (auto* content = std::get_if<VariantItemSlot>(&holdables[i]))
				{
				if (content->is_empty())
				{
					holdables[i] = VariantItemSlot(item_to_add, amount.value(),
								       buffer.variant);
					return;
				}	
				if (content->item == item_to_add && buffer.variant == content->variant) 
				{
					content->amount += amount.value();
					found = true;
				}
				}										
			}
			if (!found)
				add_item_overflow(
				    overflows, holdables,
				    VariantItemSlot(item_to_add, amount.value(), buffer.variant));
		}
		else
		{
			for (size_t i = 0; i < holdables.size(); i++)
			{
				if (found)
					break;
				if (holdables[i] == nullptr) {
					holdables[i] = ItemSlot(item_to_add, amount.value());
					return;
				}

				if (auto* content = std::get_if<ItemSlot>(&holdables[i]))
				{
				if (content->is_empty())
				{
					holdables[i] = ItemSlot(item_to_add, amount.value());
					return;
				}	
				if (content->item == item_to_add) 
				{
					content->amount += amount.value();
					found = true;
				}
				}
			}
			if (!found)
				add_item_overflow(overflows, holdables,
						ItemSlot(item_to_add, amount.value()));
		}
	}
}

void add_items_to_inventory(
			 uint16_t unit_index,
			 Inventory &inventory, InventoryAddBuffer &buffer)
{

	bool is_tool = has_tags(ItemTags::Tool, item::TAGS[buffer.holdable]);

	for (size_t i = 0; i < buffer.container_amount; i++)
	{
		uint16_t amount = buffer.amounts_per_container[i];
		if (amount == 0)
			continue;

		inventory.weight += item_bulk_and_weights[buffer.holdable].weight;

		if (buffer.overflow[i])
		{
			if (is_tool)
				add_item(holdable_overflows,
					holdable_overflows.get(overflow_hash(unit_index, i)), buffer);
			else
				add_item(holdable_overflows,
					holdable_overflows.get(overflow_hash(unit_index, i)), buffer,
					std::optional<uint16_t>(amount));
		}
		else
		{
			Container *container;
			if (i < CONTAINER_UNDERFLOW_LIMIT)
				container = inventory.containers[i];
			else
				container = overflow_containers.get(unit_index)[i];
			if (is_tool)
			{
				add_item(holdable_overflows, container->holdables, buffer);
			}
			else
				add_item(holdable_overflows, container->holdables, buffer,
					std::optional<uint16_t>(amount));
		}
	}
}

inline SizeData get_bulk_and_weight(Item holdable, uint16_t amount)
{
	SizeData sd = item_bulk_and_weights[holdable];
	sd.bulk *= amount;
	sd.weight *= amount;
	return sd;
}

// adds weight and bulk of items to be added, but does not add them to containers yet
inline void tabulate_item_add_container_data(Inventory &inventory, InventoryAddBuffer &buffer,
					 Container &container, uint16_t &item_amount,
					 bool &found_space, bool &unsearched_inventory,
					 int container_index, Item holdable,
					 uint16_t &added_amount)
{
	ContainerStorageData csd = get_remaining_storage(inventory, container);
	uint16_t storage_capacity = (uint16_t)fmin(item_amount, get_max_items_stored(holdable, csd));
	if (storage_capacity > 0)
	{
		buffer.container_amount += 1;
		item_amount -= storage_capacity;
		added_amount += storage_capacity;
		buffer.amounts_per_container[container_index] = storage_capacity;
		// change container stats
		SizeData sd = get_bulk_and_weight(holdable, storage_capacity).;
		container.weight += sd.weight;
		container.bulk += sd.bulk;
	}

	// TODO: different checks for different categories
	has_tag(ContainerFullTags::ItemOverflow, container.tags)
	    ? buffer.overflow[container_index] = true
	    : buffer.overflow[container_index] = false;
	found_space = (item_amount <= 0);
	unsearched_inventory = has_tag(ContainerFullTags::NextContainer, container.tags);
}

void clear_necessary_space(Inventory &inventory)
{
}

// returns amount of items successfully added
uint16_t add_items_force(Inventory &inventory, 
		       Item holdable,
		       std::variant<uint16_t, Material> item_amount_or_material,
		       std::optional<uint8_t> variant = std::nullopt)
{
	uint16_t amount_left = 1;
	if (std::holds_alternative<uint16_t>(item_amount_or_material))
		amount_left = item_amount_or_material;
	if (variant.has_value())
	{
		while (amount_left >= 0)
		{
			SizeData sd = get_bulk_and_weight(holdable, amount_left);
		}
	}
}

// TODO: add 'ContainerFull' tag to make things easier.
// returns amount of items successfully added
template <typename T>
uint16_t attempt_add_items( 
			 Inventory &inventory, uint16_t unit_index, Strength strength,
			 Item holdable, T item_amount_or_material,
			 std::optional<uint8_t> variant = std::nullopt, bool force)
{
	InventoryAddBuffer buffer;
	bool found_space = false;
	bool unsearched_inventory = true;
	uint16_t container_index = 0;
	uint16_t added_amount = 0;

	uint16_t max_amount =
	    (get_max_weight(strength) - inventory.weight) / item_bulk_and_weights[holdable].weight;

	if (max_amount < 1 && !force && get_max_weight(strength) < item_bulk_and_weights[holdable].weight)
		return 0;

	uint16_t required_amount = item_amount_or_material;
	if (std::holds_alternative<Material>(item_amount_or_material))
	{
		required_amount = 1;
		buffer.material = std::optional<Material>(item_amount_or_material);
	}

	if (variant.has_value())
		buffer.variant = variant;

	// containers in main inventory
	while (!found_space && unsearched_inventory)
	{
		Container &container = inventory.containers[container_index];
		tabulate_item_add_container_data(inventory, buffer, container, required_amount,
					     found_space, unsearched_inventory, container_index,
					     holdable, added_amount);
	}
	// overflow containers
	if (!found_space && unsearched_inventory)
		container_index = 0;
	while (!found_space && unsearched_inventory)
	{
		std::vector<Container> &unit_overflow_containers = overflow_containers[unit_index];
		Container &container = unit_overflow_containers[container_index];
		tabulate_item_add_container_data(inventory, buffer, container, required_amount,
					     found_space, unsearched_inventory, container_index,
					     holdable, added_amount);
	}

	if (added_amount > 0)
		add_items_to_inventory(overflows, overflow_containers, unit_index, inventory, buffer);
	if (force && required_amount < added_amount)
	{
		if (std::holds_alternative<Item>(holdable))
		{
			add_items_force(inventory, overflows, overflow_containers, holdable,
				      required_amount - added_amount, variant);
		}
		else if (std::holds_alternative<Tool>(holdable))
			add_items_force(inventory, overflows, overflow_containers, holdable,
				      std::get<Material>(item_amount_or_material));
	}
}
return added_amount;
}

//right now does NOT check for material match
inline bool remove_art_or_tool(Inventory& inventory, Item item, //std::optional<SpecialItemData> special_data, 
bool check = false)
{
	for (size_t i = 0; i < inventory.containers.size(); i++)
		{
			for (auto& content : inventory.containers[i])
			{
				if (std::holds_alternative<ArtSlot>(content) || std::holds_alternative<ToolSlot>(content))
				{
					Item item;
					std::visit([&](auto &obj) { item = obj.get_type(); },
						   content);
					if (item == content)
					{
						if (!check) content = nullptr;
						return true;
					}
				}
			}
		}
	return false;
}

inline uint16_t remove_item(Inventory& inventory, Item item, uint16_t amount, bool check = false, std::optional<uint8_t> variant = std::nullopt)
{
	uint16_t removed_amount = 0;
	for (size_t i = 0; i < inventory.containers.size(); i++)
		{
			for (auto content : inventory.containers[i])
			{
				if (variant == std::nullopt)
				{
					if (std::holds_alternative<ItemSlot>(content)) {
					Item content_item;
					std::visit([&](auto &obj) { content_item = obj.get_type(); },
						   content);
					if (item == content_item)
					{
						removed_amount = min(amount, content.amount);
						if (!check) content.amount -= removed_amount;
					}
					}
				}
				else
				{
					if (std::holds_alternative<VariantItemSlot>(content)) {
						Item content_item;
					std::visit([&](auto &obj) { content_item = obj.get_type(); },
						   content);
					if (item == content_item && content.variant = variant)
					{
						removed_amount = min(amount, content.amount);
						if (!check) content.amount -= removed_amount;
					}
					}
				}
			}
		}
	return removed_amount;
}

// check means won' actually remove, just see amount
//returns amount removed
uint16_t remove_item(Inventory &inventory, uint16_t unit_index,
					  Item item,
				      std::optional<uint16_t> item_amount_or_material = std::nullopt, std::optional<uint8_t> variant = std::nullopt, bool check = false)
{
	if !(has_tags(ItemTags::Tool, item::TAGS[item]))
	{
	if (variant == std::nullopt) {
		return remove_item(inventory, item, std::get<uint16_t>(item_amount_or_material), check);
	} else remove_item(inventory, item, std::get<uint16_t>(item_amount_or_material), variant, check);
	} else {
		remove_art_or_tool(inventory, tool, //std::get<Material>(item_amount_or_material), 
check) ? return 1 : return 0;
	}
}	

NecessaryToolsBuffer ensure_necessary_tools(SearchGrid& search, Action action, Inventory& inventory, uint16_t unit_index, Coord coord)
{
	NecessaryToolsBuffer buffer;
	
		constexpr int tool_amount= action_to_tools[static_cast<uint16_t>(action)].size();
		std::array<int, tool_amount> found_tool_replaceables;
		int found_tools = 0;
		int currently_searched = 0;

			for (int i = 0; i < tool_amount; i++)
		{
			Item tool = action_to_tools[action][i].tool;
			int requirement_slot = action_to_tools[action]
					[i].second();
			// skip if replaceable equivalent has already been found,
			for (int j = 0; j < currently_searched; j++)
				if (found_tool_replaceables[j] == requirement_slot)
					continue;
				
			// skip if tool is optional
			    if (requirement_slot < 0) continue;

			    found = remove_item(overflows,
					  overflow_containers,
					  inventory, unit_index,
					  tool, true);
				
			
if (found) {
				    found_tools_replaceables[found_tools++] = requirement_slot;
				    found = true;
				    break;
				    } 

			    if (!found) {
			    data = search.get_nearest(tool, coord.first, coord.second);
			    if (man_dist(coord, new_dest) > MID_GATHER_RANGE) {
				    buffer.state = ToolsState::Finding;
				    buffer.destination.value() = NewDest;				    // buffer.missing_tool_type.value() = tool;
				    return buffer;
			}
			else
			{
				buffer.state = ToolsState::CannotFind;
				return buffer;
			}
			    }				
				
			// TODO:: "search home function", which checks if a pawn's home/workplace
			// contains the necessary tools, giving user warning if not
			    currently_searched++;
		}
		buffer.state = ToolsState::FoundAll;
		return buffer;
	}
