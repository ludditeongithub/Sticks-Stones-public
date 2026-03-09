#include "pathfinding.hpp"

//TODO: reserve vector size of estimated length from start to goal, + a little based on average to lower reallocations. cut off excess space at the end.
PathData aStar(Coord start, Coord goal, int width, int height) {
    int startIndex = toIndex(start.x, start.y, width);
    int goalIndex = toIndex(goal.x, goal.y, width);

    uint16_t estimate = getPathLengthEstimate(start, goal);
    
    nodeData[startIndex].gCost = 0;
    nodeData[startIndex].fCost = heuristic(start, goal);

    Array<int> openSet;
    openSet.reserve(estimate);
    openSet.emplace_back(startIndex);

    while (!openSet.empty()) {
        int currentIndex = openSet.front();
        for (int i = 0; i < openSet.size(); ++i) {
            if (nodeData[openSet[i]].fCost < nodeData[currentIndex].fCost) {
                currentIndex = openSet[i];
            }
        }

        if (currentIndex == goalIndex) {
	  return reconstructPath(startIndex, goalIndex);
        }

        openSet.erase(std::remove(openSet.begin(), openSet.end(), currentIndex), openSet.end());
        nodeData[currentIndex].closedFlag = true;

        std::vector<int> neighbors = {
            currentIndex - width,
            currentIndex + width,
            currentIndex - 1,
            currentIndex + 1
        };

        for (int neighbor : neighbors) {
            if (neighbor < 0 || neighbor >= width * height) continue;
            if (nodeData[neighbor].closedFlag) continue;

            float tentativeGCost = nodeData[currentIndex].gCost + tileMoveCosts[neighbor];

            if (tentativeGCost < nodeData[neighbor].gCost) {
                nodeData[neighbor].cameFrom = currentIndex;
                nodeData[neighbor].gCost = tentativeGCost;
                nodeData[neighbor].fCost = tentativeGCost + heuristic(toCoord(neighbor), goal);

                openSet.emplace_back(neighbor);  // Add to open set, no need for a separate openFlag
            }
        }
    }
    return {};
}

PathData reconstructPath(int startIndex, int goalIndex) {
    std::vector<Coord> path;
    int current = goalIndex;
    int size = 0;
    while (current != startIndex) {
        path.push_back(toCoord(current));
        current = nodeData[current].cameFrom;
	size++;
    }

    path.emplace_back(toCoord(startIndex));
    std::reverse(path.begin(), path.end());

    return {size,path};
}


// sets start and end, inputted from all types of jobs
PathsBuffer setNewPaths(PathDispatchData& pdd) {
  PathsBuffer pb = PathsBuffer(pdd.positions.size);
  for (uint16_t i = 0; i < pdd.positions.size; i++) {
    Array<Array<Coord>> data(pdd.positions.size);
     PathData pd;
     pd = aStar(pdd.positions[i], pdd.destinations[i], WIDTH, HEIGHT);
    pb.currents[i] = 0;
    pb.ends[i] = pd.end;
    pb.datas[i] = pd.data;
    pb.destinations[i] = pdd.destinations[i];
  }
  return pb;  
}


