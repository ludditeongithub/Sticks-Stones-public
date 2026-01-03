struct Coord {
  int x;
  int y;
};

enum class Direction {
  NONE,
  North,
  South,
  West,
  East,
  MAX
};

Coord newCoordsFromFacing(Coord coords, Direction direction) {
switch(direction) {
    case Direction::North:
        return {coords.x+1, coords.y};
    case Direction::East:
        return {coords.x, coords.y+1};
    case Direction::South:
        return {coords.x-1, coords.y};
    default:
        return {coords.x, coords.y-1};
}
}
