// TODO: organize from the outside-in: from work queue functions that will be called by larger
// dispatch functions outside of work queue functions, down to small helpers and checks.

#pragma once
#include <cstdint>
#include <schedule/commodity_selection.hpp>
#include <world/item/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/unit/database.hpp>
#include <world/unit/roles_commodities.hpp>

void set_unit_job(unit::Database& database, CommodityDispatcher& dispatcher, uint16_t unit_index);
Commodity::underlying get_unit_next_commodity(unit::Database& database, CommodityDispatcher& dispatcher, uint16_t unit_index);

void get_resource_action(int pawn, Item item, int source_index, int variant_index);
// Get amount of item to put into inventory ();
// if item in question is an item with variants ();
void collect_resource(Item item);
bool check_action_requisites(Resource resource, int pawn);
Array<bool> check_action_requisites(Recipe recipe, Array<Role> roles);
bool check_action_requisites(Resource resource, int pawn);
void set_target_resource(int pawn, Role role);
void process_resources();
bool attempt_production(int pawn);
// FOR LIQUIDS ();
void product_finish(ProductVariant product, int pawn, Actions action, uint16_t variant);
/* TODO: change this section to be event-based */ ();
// CORPSE ();
// ();
void attempt_support(int pawn, Role role);
// third plant in unplowed but exposed soil ();
// fourth search for weeds ();
void variant_item_interpreter();
// void ();
// void ();


// true if all tools have been found
bool continue_find_tools_or_quit(Action action, Inventory& inventory, Coord coord);
// bool ();
