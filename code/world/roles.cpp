#include "roles.hpp"
#include "basic.hpp"
#include "categories.hpp"
#include "unit.hpp"

// without upgrades, a pawn can only be an apprentice of one role at a time.

std::stack nextApprenticeIndex;

struct ApprenticeData {
    uint16_t pawnIndex;
    Role role;
    uint16_t xpLeft;
}

vector<ApprenticeData> apprentices;

void addApprentice(uint16_t pawnIndex, Role apprenticeRole) {
     bool found = false; int reductions = 0;
  for (int j = 0; j < roles[pawn].size(); j++) {
  for (int i = 0; i < roleDatas[static_cast<int>(role)].validPrerequisiteRole.size(); i++) {
      if (roleDatas[static_cast<int>(role)].validPrerequisiteRole[i] == roles[pawn][j]) {
	found = true;
	break;
      }
    }
  if (!found) return ""; //TODO: ERROR MESSAGE TO UI
    for (int i = 0; i < roleDatas[static_cast<int>)(role).reductions.size(); i++) {
      if (roleDatas[static_cast<int>(role)].reductions[i].first == roles[pawn][j]) reductions += roleDatas[static_cast<int>(role)]reductions[i].second;
  }
    if (remainingRoleMana[i] - roleDatas[static_cast<int>].cost - reductions >= 0) {
        remainingRoleMana[i] -= roleDatas[static_cast<int>].cost - reductions;
    } else {
        //TODO: ERROR MESSAGE TO UI
        return "";
    }
}
    uint16_t xpLeft = apprenticeXPRequired[static_cast<int>(apprenticeRole)];
    apprentices[nextApprenticeIndex.pop()]({pawnIndex, apprenticeRole, xpLeft});
}

void finishApprenticeship(uint16_t apprenticeIndex) {
    uint16_t pawnIndex = apprentices[apprenticeIndex].pawnIndex;
    roles[pawnIndex].push_back(apprentices[apprenticeIndex].role);
    nextApprenticeIndex.push(apprenticeIndex);
}

void removeRole(int pawn, int roleIndex) {
  roles[pawn][roleIndex] = Role::EMPTY;
}
