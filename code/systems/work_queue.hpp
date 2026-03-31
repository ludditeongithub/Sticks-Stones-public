// TODO: organize from the outside-in: from work queue functions that will be called by larger
// dispatch functions outside of work queue functions, down to small helpers and checks.

#pragma once
#include <cstdint>
#include <schedule/commodity_selection.hpp>
#include <world/item/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/unit/entity.hpp>
#include <world/unit/roles_commodities.hpp>>

void setUnitJob(UnitDatabase& database, CommodityDispatcher& dispatcher, uint16_t unitIndex);
Commodity::underlying getUnitNextCommodity(UnitDatabase& database, CommodityDispatcher& dispatcher, uint16_t unitIndex);



void getResourceAction(int pawn, Item item, int sourceIndex, int variantIndex);
// Get amount of item to put into inventory ();
// if item in question is an item with variants ();
void collectResource(Item item);
bool checkActionRequisites(Resource resource, int pawn);
Array<bool> checkActionRequisites(Recipe recipe, Array<Role> roles);
bool checkActionRequisites(Resource resource, int pawn);
void setTargetResource(int pawn, Role role);
void processResources();
bool attemptProduction(int pawn,);
// FOR LIQUIDS ();
void productFinish(ProductVariant product, int pawn, Actions action, uint16_t variant);
/* TODO: change this section to be event-based */ ();
// CORPSE ();
// ();
void attemptSupport(int pawn, Role role);
// third plant in unplowed but exposed soil ();
// fourth search for weeds ();
void variantItemInterpreter();
// void ();
// void ();


// true if all tools have been found
bool continueFindToolsOrQuit(Action action, Inventory& inventory, Coord coord);
// bool ();
