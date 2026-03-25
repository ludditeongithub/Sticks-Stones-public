#include <world/item/enum.hpp>
#include <world/item/item_recipes.hpp>
#include <world/scavengeables/enum.hpp>
#include <world/tile/enum.hpp>
#include <world/unit/rolesAndActions.hpp>

//checkers
bool checkActionRequisites(Resource resource, int pawn);
bool checkActionRequisites(Recipe recipe, int pawn);
bool checkActionRequisites(Resource resource, int pawn);

//attempt job
void attemptResource(int pawn, Role role);
void attemptProduction(int pawn, ProductVariant product);
void attemptSupport(int pawn, Role role);

//finishers
void collectResourceAction(int pawn, Item item, int sourceIndex, int variantIndex);
void collectResource(Item item);
void productFinish(ProductVariant product, int pawn, uint16_t variant);


//TODO: move to scheduling, finish scheduling
void nextRole(int pawn, int roleIndex);
