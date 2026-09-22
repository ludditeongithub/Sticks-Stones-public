// every tick, possibly change to just dispatching (no time check, no health check)
void update_positions(PathsData &rpd, Array<Coord> &positions, Array<float> &timers,
		     Array<Action> &actions, Array<uint32_t> &require_new_path_indices);
