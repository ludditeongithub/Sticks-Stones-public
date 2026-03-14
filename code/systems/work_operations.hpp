#include <world/unit/rolesAndActions.hpp>
#include <world/tile/enum.hpp>
#include <world/scavengeables/enum.hpp>
#include <world/item/enum.hpp>
#include <world/item/item_recipes.hpp>

void collectResourceAction(int pawn, Item item, int sourceIndex, int variantIndex);
// Get amount of item to put into inventory ();
// if item in question is an item with variants ();
void collectResource(Item item);
bool checkActionRequisites(Resource resource, int pawn);
bool checkActionRequisites(Recipe recipe, int pawn);
bool checkActionRequisites(Resource resource, int pawn);
void attemptResource(int pawn, Role role);
void attemptProduction(int pawn, ProductVariant product);
//FOR LIQUIDS ();
void productFinish(ProductVariant product, int pawn, uint16_t variant);
/* TODO: change this section to be event-based */ ();
// CORPSE ();
// ();
void attemptSupport(int pawn, Role role);
//third plant in unplowed but exposed soil ();
//fourth search for weeds ();
void nextRole(int pawn, int roleIndex);
