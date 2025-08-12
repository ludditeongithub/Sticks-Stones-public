#include "support.h"

void attemptHeal(int healer, int receiver) {
   bool found = true; int index = -1;
   for (int i = 0; i < in.items.size(); i++) {
     //TODO: all med items
     if (in.items[i].first == Item::Bandage || in.items[i].first == Item::Tonic) {
       found = true;
       index = i;
     }
   }
   //NOTE: maybe can stitch up fresh wounds?
   if !(found) return;
   std::pair<int,int> ta = calcHealTimeAndAmount(in.items[i], healer);
   //TODO: check if this works
   removeItem(healer, i);
   //TODO: add doctor skill, fail chance?
   addEvent(ta.first, EventType::Heal, receiver, ta.second, healer);
 }

void attemptHaul() {
}

void attemptSupport(int pawnIndex) {
  switch (role) {
  case Role::Surgeon:
    movingStatus[pawnIndex] = MovingStatus::SupportSearch;
    break;
  case Role::Hauler:
    findHaul(pawnIndex);
    break;
  }
}

struct VehicleHaulers() {
	int ownerIndex;
	Vehicle vehicle;
	std::pair<int,int> coords;
	int currentWeight;
	float currentBulk;
      }

      void attemptAttatchCart(int pawn, int tile) {

      }

      void addToCart() {

      }

      void startHaul() {
      }
