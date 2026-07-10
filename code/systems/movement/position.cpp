// every tick, possibly change to just dispatching (no time check, no health check)
void updatePositions(PathsData &rpd, Array<Coord> &positions, Array<float> &timers,
		     Array<Action> &actions, Array<uint32_t> &requireNewPathIndices);
