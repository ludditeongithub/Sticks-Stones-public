#ifndef MAPDIMENSIONS_H_
#define MAPDIMENSIONS_H_

#include "basic.hpp"


// Constants
// IN CELLS
const int WIDTH = 50;  // Amount of Cells generated WIDTH
const int HEIGHT = 50; // Amount of Cells generated HEIGHT
const int BORDER_WIDTH = 3; // Border WIDTH
const int BORDER_HEIGHT = 3; // Border HEIGHT
const int CELL_SIZE = 10; // average WIDTH and HEIGHT of each cell
const int EQUATOR = HEIGHT / 2;
// IN TILES
const int WORLD_WIDTH = WIDTH * CELL_SIZE;
const int WORLD_HEIGHT = HEIGHT * CELL_SIZE;
const int STARTING_MAP_WIDTH = 300; //for starting player map
const int STARTING_MAP_HEIGHT = 300;

// New variables to store the size of the map with borders
const int WIDTH_WITH_BORDER = WIDTH + BORDER_WIDTH * 2;
const int HEIGHT_WITH_BORDER = HEIGHT + BORDER_HEIGHT * 2;

#endif // MAPDIMENSIONS_H_
