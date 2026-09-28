#include "pack_movement_patterns.h"

MovingStatus::PackRegroup MovingStatus::PackFollow
    // valid pack movingstatuses:
    Sleep,
    PackProwl, PackWander,

    struct PackCenter
{
	Animal pack_type;
	int current_size;
	Direction direction;
}
// add PackCenter to object

// TODO: nth neareest pack center based on nthnearestobject

uint8_t pack_sizes[static_cast<int>(Animal::MAX)];
vector<PackCenter> pack_centers;
vector<Coord> pack_coords;

void return_to_pack(int animal_index)
{
	moving_status[animal_index] = MovingStatus::PackRegroup;
	int i = 0;
	bool found = false;
	while (!found)
	{
		int pack = get_nth_nearest_pack(PackCenter[animal_index].pack_type,
					     animal_coords[animal_index].first,
					     animal_coords[animal_index].second, i);
		if (pack_centers[pack].current_size < pack_sizes[animals[animal_index]] - rint(-1, 1))
		{
			found = true;
			current_dest[i] = pack;
		}
		i++;
	}
}

void check_pack_distance(int animal)
{
	if (moving_status[animal_index] == MovingStatus::PackProwl ||
	    moving_status[animal_index] == MovingStatus::PackWander ||
	    moving_status[animal_index] == MovingStatus::PackIdle)
	{
		man_dist(animal_coords, pack_coords[animal_target[animal_index]]);
	}
}

void move_pack_center() {}

void notify_squad(int notifier, bool grouped)
{
	Squad &squad = player_squads[pawn];
	for (int i = 0; i < squad.pawns.size(); i++)
	{
		current_dest[squad.pawns[i]] = current_dest[notifier];
		if (grouped)
			moving_status[i] = MovingStatus::BlobMarch;
		else
			moving_status[i] = MovingStatus::March;
	}
}

void deliver_news(int pawn, bool player)
{
	if (player)
	{
		int squad = player_squads[pawn];
		notify_squad(pawn);
	}
}

void move_center_in_direction() {}

if (moving_status[i] !=)
{
	if (inertia[i] == 0)
	{
		movement(moving_status[i]);
		inertia[i] = calc_speed(animal, moving_status[i], animal_coords[i]);
	}
	else
		inertia--;
}

if (moving_status[i] = MovingStatus::PackFollow)
{
	if (check_pack_distance(animal) > 1)
		// NOTE: bad
		move_in_direction(find_next_direction(animal_coords[animal]),
				pack_coords[animal_target[animal_index]]);
	if (check_pack_distance(animal) > pack_max[static_cast<int>(animal)])
		moving_status[i] = MovingStatus::PackRegroup;
}
if (moving_status[i] == MovingStatus::PackRegroup)
{
	move_in_direction(pawn, find_next_direction(animal_coords[animal]),
			pack_coords[animal_target[animal_index]]);
	if (check_pack_distance(animal) < pack_max[static_cast<int>(animal)])
		moving_status[i] = MovingStatus::PackFollow;
}
if (moving_status[i] == MovingStatus::Raid)
{
}
// brigade + squad specific moving statuses
if (moving_status[i] == MovingStatus::FanOut)
{
	if (squads[pawn].organizing)
		directions[pawn] = get_random_direction();
	else
	{
    if (rint(0,3 == 3) Direction direction = just_not_backwards(directions[pawn]);
	else Direction direction = directions[pawn];
    move_in_direction(pawn, direction);
	if (check_enemy_settlement()) notify_squad(pawn);
	}
}
if (moving_status[i] == MovingStatus::ScoutAndRegroup)
{
	if (time_till_change_operation == 0)
	{
		if (man_dist(current_coords[pawn, squads[player_squads[pawn]].center] <
			    (int)(log(2, current_size))))
		{
			move_in_direction(current_coords[pawn],
					find_next_direction(squads[pawn].center));
		}
		else
			moving_status[i] == MovingStatus::Idle;
	}
	if (check_enemy_settlement())
	{
		current_dest[i] = moving_status[i] = MovingStatus::ReturnWithNews;
	}
}

if (moving_status[i] == MovingStatus::ReturnWithNews)
{
	// Make this a pointer
	if (man_dist(current_coords[pawn, squads[pawn].center] < (int)(log(2, current_size))))
	{
		move_in_direction(current_coords[pawn], find_next_direction(squads[pawn].center));
	}
	else
	{
		if (all_within_suitable_distance)
			deliver_news(pawn);
	}
}

if (moving_status[i] == MovingStatus::BlobMarch)
{
	if (all_within_suitable_distance) attempt_move_in_direction(current_coords[pawn], current_dest[i]));
}

struct Squad
{
	bool player;
	bool all_within_suitable_distance;
	vector<int> pawns;
	vector<bool> within_suitable_distance;
	Direction direction;
	Coord center;
	bool organizing;
	bool in_brigade;
	uint16_t time_till_change_operation;
}

struct Brigade
{
	vector<int> squads;
	Direction direction;
	Coord center;
}
