#include "unit.hpp"

Role getActionRole(int pawnIndex, Actions action) {
    for (int i = 0; i < actionToRoles[static_cast<int>(action)]; i++) {
        if (roles[pawnIndex] == actionToRoles[i]) return roles[pawnIndex];
}

void nextRole(int pawnIndex) {
    // pawn cannot move to next role if only has 1 role
    if (currentRole[pawnIndex].size() == 1) {
        movingStatus[pawnIndex] = MovingStatus::Waiting;
        return;
    }
    if (currentRole[pawnIndex] < roles[pawnIndex].size() - 1) {
        currentRole[pawnIndex]++;
    } else {
        currentRole[pawnIndex] = 0;
    }
}


void birth(int unitIndex) {

}
