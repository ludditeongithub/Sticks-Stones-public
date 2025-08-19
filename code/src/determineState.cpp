#include "determineState.h"
// COMMAND
// The authority (you) commands what the pawns produce, and you own all goods. Large Order (Satisfaction) decrease and production decrease. Resource estimates are terrible and especially if order is low

// MIXED COMMAND
// The authority (you) also sends mandatory quotas of goods pawns must produce, which they produce first, but after that pawns switch roles and produce whatever they like to produce, and also keep their goods. Pawns receive a large a small bonus and a small Order (Satisfaction) bonus, and are somewhat more likely to produce high quality items. You can buy goods from your pawns. Resource estimates are poor

// MARKET
// You can buy goods from your pawns, and also tax them, but cannot set quotas. Money is crucial in this run. Pawns receive a medium bonus and a medium Order (Satisfaction) bonus, and are quite more likely to produce high quality items. Resource estimates are great. True bureaucratic recording is expensive

// ANARCHY
// Pawns switch roles and produce whatever they like to produce, and also keep their goods. Only minimum taxes can be set, and only certain types. However, they receive a large production bonus and a large Order (Satisfaction) bonus, and are more likely to produce high quality items. You only control truly control the government and military pawns. You can buy and sell goods from your pawns, as well as hire mercenaries that form among your pawns. Pawns buy and sell goods among each other. Resource Estimates are decent, but true bureaucratic recording is impossible

/* Get jobs from  */
//NOTE: can implement jump table. this is for authority command structure
void decideTask(int pawnIndex) {
    int taskIndex = -1;
    TaskType type = TaskType::NONE;
    Role role;
    for (int i = 0; i < taskPriorityQueue.size; i++) {
        //TODO: check if role is producer vs resource vs etc on lookup table
        if (taskPriorityQueue[i].priority < highest) {
            for (int j = 0; j < roles[pawnIndex].size; j++) {
                Role tRole = taskPriorityQueue[i].role;

                if (tRole < Roles::RESOURCEMAX && tRole > Roles::SUPPORTMAX)  {
                    //RESOURCES
                         for (int k = 0; k < resourcerResources[static_cast<int>(tRole)].size; k++) {
                    if (resourcerResources[static_cast<int>(tRole)][k] == resourcePriorityQueue[i].first) {
                        attemptResource(pawnIndex, tRole);
                    }
                }
                } else if (tRole < Roles::PRODUCTSMAX && tRole > Roles::RESOURCEMAX) {
                    //PRODUCTS
                     for (int k = 0; k < producerProducts[static_cast<int>(tRole)].size; k++) {
                    if (producerProducts[static_cast<int>(tRole)][k] == static_cast<Item>(taskPriorityQueue[i].task)) {

                    }
                }

            }
        }

        }
    }


          if (highest == 1) {
              attemptProduction(pawnIndex, producerProducts[static_cast<int>(tRole)][taskIndex]);
              return;
          }
        }
    }

 for  (int i = 0; i < supportPriorityQueue.size; i++) {
          if (supportPriorityQueue[i].second < highest) {
              for (int j = 0; j < roles[pawnIndex].size; j++) {
                Role tRole = roles[pawnIndex][j];
                if (tRole == supportPriorityQueue[i])
               (producerProducts[static_cast<int>(tRole)][k] == productsPriorityQueue[i].first) {
                        type = TaskType::Suppot
                        highest = productsPriorityQueue[i].second;
                        taskIndex = i;

                    }
                }
            }
        }
          if (highest == 1) {
              attemptProduct(pawnIndex, role);
              return;
          }
        }
    }

    if (movingStatus[pawnIndex] != MovingStatus::Production) {
                attemptProduction(pawnIndex, producerProducts[static_cast<int>(roles[pawnIndex[i]])]);
    }

}
