#ifndef PLANT_H_
#define PLANT_H_

#include "basic.hpp"
#include <array>
#include <cstdlib>


namespace plant {
 
class PlantDatabase {
  //TODO consider having plantdatabases for each region so that only necessary plant databases needs to be loaded in at a time.
    private:

    std::vector<Plant> plants;
    std::stack nextPlantIndex;
 
    public:
    PlantDatabase();
};

}


#endif // PLANT_H_
