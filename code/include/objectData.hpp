#ifndef OBJECTDATA_H_
#define OBJECTDATA_H_

#include "absl/container/flat_hash_map.h"
#include "basic.hpp"
#include "categories.hpp"
#include <flat_map>
#include <flat_set>

class ObjectDatabase
{
private:
std::flat_map<std::pair<int,int>, std::pair<bool, Item>> filledLiquidContainers(); //bool is whether still processing or not. only counts ones filled with actual liquid
std::vector<std::vector<std::flat_map<Object, std::flat_set<std::pair<int,int>>>>> globalMap;

public:
  ObjectDatabase() {};

  
};


void insertObject(Object object, int x, int y);

#endif // OBJECTDATA_H_
