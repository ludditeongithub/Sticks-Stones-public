#include "packMovementPatterns.h"

MovingStatus::PackRegroup
MovingStatus::PackFollow
//valid pack movingstatuses:
Sleep, PackProwl, PackWander,

struct PackCenter {
  Animal packType;
  int currentSize;
  Direction direction;
}
//add PackCenter to object

//TODO: nth neareest pack center based on nthnearestobject

uint8_t packSizes[static_cast<int>(Animal::MAX)];
vector<PackCenter> packCenters;
vector<std::pair<int,int>> packCoords;

void returnToPack(int animalIndex) {
  movingStatus[animalIndex] = MovingStatus::PackRegroup;
  int i = 0; bool found = false;
  while (!found) {
    int pack = getNthNearestPack(PackCenter[animalIndex].packType, animalCoords[animalIndex].first, animalCoords[animalIndex].second, i);
      if (packCenters[pack].currentSize < packSizes[animals[animalIndex]] - rint(-1,1)) {
	found = true;
	currentDest[i] = pack;
  }
   i++;
}
}


void checkPackDistance(int animal) {
  if (movingStatus[animalIndex] == MovingStatus::PackProwl || movingStatus[animalIndex] == MovingStatus::PackWander || movingStatus[animalIndex] == MovingStatus::PackIdle) {
    manDist(animalCoords,packCoords[animalTarget[animalIndex]]);
  }
}

void movePackCenter() {

}




void notifySquad(int notifier, bool grouped) {
  Squad& squad = playerSquads[pawn];
  for (int i = 0; i < squad.pawns.size(); i++) {
    currentDest[squad.pawns[i]] = currentDest[notifier];
    if (grouped) movingStatus[i] = MovingStatus::BlobMarch;
    else movingStatus[i] = MovingStatus::March;
  }
}

void deliverNews(int pawn, bool player) {
  if (player) {
    int squad = playerSquads[pawn];
    notifySquad(pawn);
  }
}

void moveCenterInDirection() {

}


if (movingStatus[i] != ) {
  if (inertia[i] == 0) {
    movement(movingStatus[i]);
    inertia[i] = calcSpeed(animal, movingStatus[i], animalCoords[i]);
  } else inertia--;
 }

if (movingStatus[i] = MovingStatus::PackFollow) {
  if (checkPackDistance(animal) > 1)
    //NOTE: bad
    moveInDirection(findNextDirection(animalCoords[animal]), packCoords[animalTarget[animalIndex]]);
  if (checkPackDistance(animal) > packMax[static_cast<int>(animal)]) movingStatus[i] = MovingStatus::PackRegroup;
 }
if (movingStatus[i] == MovingStatus::PackRegroup) {
  moveInDirection(pawn, findNextDirection(animalCoords[animal]), packCoords[animalTarget[animalIndex]]);
  if (checkPackDistance(animal) < packMax[static_cast<int>(animal)]) movingStatus[i] = MovingStatus::PackFollow;
}
if (movingStatus[i] == MovingStatus::Raid) {

}
// brigade + squad specific moving statuses
if (movingStatus[i] == MovingStatus::FanOut) {
  if (squads[pawn].organizing) directions[pawn] = getRandomDirection();
  else {
    if (rint(0,3 == 3) Direction direction = justNotBackwards(directions[pawn]);
	else Direction direction = directions[pawn];
    moveInDirection(pawn, direction);
	if (checkEnemySettlement()) notifySquad(pawn);
  }
}
if (movingStatus[i] == MovingStatus::ScoutAndRegroup) {
  if (timeTillChangeOperation == 0) {
    if (manDist(currentCoords[pawn, squads[playerSquads[pawn]].center] < (int)(log(2, currentSize)))) {
     moveInDirection(currentCoords[pawn], findNextDirection(squads[pawn].center));
    } else movingStatus[i] == MovingStatus::Idle;
  }
  if (checkEnemySettlement()) {
     currentDest[i] =
     movingStatus[i] = MovingStatus::ReturnWithNews;
  }
}

if (movingStatus[i] == MovingStatus::ReturnWithNews) {
  //Make this a pointer
    if (manDist(currentCoords[pawn, squads[pawn].center] < (int)(log(2, currentSize)))) {
     moveInDirection(currentCoords[pawn], findNextDirection(squads[pawn].center));
    } else {
      if (allWithinSuitableDistance) deliverNews(pawn);
    }
}

if (movingStatus[i] == MovingStatus::BlobMarch) {
  if (allWithinSuitableDistance) attemptMoveInDirection(currentCoords[pawn], currentDest[i]));
}

struct Squad {
  bool player;
  bool allWithinSuitableDistance;
  vector<int> pawns;
  vector<bool> withinSuitableDistance;
  Direction direction;
  std::pair<int,int> center;
  bool organizing;
  bool inBrigade;
  uint16_t timeTillChangeOperation;
}

struct Brigade {
  vector<int> squads;
  Direction direction;
  std::pair<int,int> center;
}
