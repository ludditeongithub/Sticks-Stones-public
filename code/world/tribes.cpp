#include "tribes.h"

// 4. tribes - members in tribes do not actualy produce, production is just
// estimated based on role, and then given to the tribe at intervals. maybe turn
// this off if player is near. tribe members only get one role unlike player
// units. tribes do not have several units, depending on size of tribe. they can
// also build buildings in one go, if necessary.
struct GroupData
{
	GroupType groupType;
	uint16_t size;
	uint16_t maxSize;
	Age age;
	int opinion;
	std::pair<int, int> foundingTile;
	vector<std::pair<int, int>> memberCoords;
	vector<Role> memberRoles;
	vector<uint16_t> roleAmounts;		       // indices link to indices of relevant role
						       // vector, not all Roles.
	vector<std::pair<int, int>> claimedTileCoords; // maybe unnecessary, especially with areas?
	vector<Item, uint16_t> items;
	vector<Areas> areas;
	vector<Station> stations;
	vector<uint16_t, int> allies; // second int is opinion
};

vector<GroupData> groups;

// probably put military roles at the front as they may need to be found
std::tuple<Role, uint16_t, int16_t> smallTribeRoles[];
std::tuple<Role, uint16_t, int16_t> mediumTribeRoles[];
std::tuple<Role, uint16_t, uint16_t> largeTribeRoles[];
// consider replacing tribes with smaller lords (who can still be subjects of
// kings or princes) once player has reached higher ages.

std::tuple<Role, uint16_t, uint16_t> smallWarbandRoles[];
std::tuple<Role, uint16_t, uint16_t> mediumWarbandRoles[];
std::tuple<Role, uint16_t, uint16_t> largeWarbandRoles[];
// hordeRoles;

// princedomRoles;
// kingdomRoles;
// empireRoles;

// smallMultiplier;
// mediumMultiplier;
// largeMultiplier;

void initializeGroupRoles()
{
	// SMALL TRIBE - changes from each age
	// PALEO
	//  SpearHunter, 2, 4;
	//  Gatherer 2, 6;
	//  Knapper 1, 2;
	//  Crafter 1, 4;
	//  Carver 1, 2;
	//  HideTanner 1, 1;
	//  Firekeeper 1, 2;
	//  //MESO
	//  SpearFisher 0, 4; // different for coastal tribes
	//  ShelterBuilder 1, 3;
	//  Herbalist 0, 2;
	//  //NEO
	//  Farmer 2, 6;
	//  Ornamenter 0, 1;
	//  Chief 1, 1;
	//  //MINI WARBAND
	//  //PALEO
	//  SpearHunter, 10, 20;
	//  //MESO
	//  Slinger, 2, 5;
	//  //NEO
	//  Warrior 8, 15;
	//  Skirmisher, 5, 10;
	//  Shaman 0,2;
	//  Chief 1, 1;

	// Swordsman, 4, 10;
	// Archer 5, 10;
	// Horseman 3, 8;
}

bool roleInAge(Role role, Age age)
{
	// if role is a predecessor, making it obsolete
  for (int i = 0; i < roleDatas[static_cast<int>([roleDatas[static_cast<int>(role)].requisitesOf.size(); i++) {
		if (roleDatas[static_cast<int>(roleDatas[static_cast<int>(role)].requisitesOf[i])]
			.age >= age)
			return false;
  }
  return roleDatas[static_cast<int>(role)].age <= age;
}

bool attemptAddGroupMember(GroupData &group, std::tuple<Role, uint16_t, uint16_t> &groupRoles,
			   int roleIndex, bool min)
{
	if !(roleInAge(groupRoles[roleIndex].get<0>, group.age))
		return false;
	if (min)
		bool met = groupRoles[roleIndex].get<1> > group.roleAmounts[roleIndex];
	else
		bool met = group.roleAmounts[roleIndex] < groupRoles[roleIndex].get<2>;
	if (met)
	{
		group.memberRoles.push_back(groupRoles[roleIndex].get<0>);
		group.roleAmounts[static_cast<int>(groupRoles[roleIndex].get<0>)]++;
		return true;
	}
}

void addGroupMember(uint16_t group)
{
	if (groups[group].size == groups[group].maxSize)
		return;
	vector<Role, uint16_t, uint16_t> &groupRoles = getGroupRoles(groups[group].groupType);
	Group &group = groups[group];
	bool found = false;
	for (int i = 0; i < groupRoles.size(); i++)
	{
		if (attemptAddGroupMember(group, groupRoles, i))
		{
			found = true;
			break;
		}
	}
	while (!found) found = attemptAddGroupMember(group, groupRoles, rint(0, groupRoles.size());
					       groups[i].memberCoords.push_back(getNearestAdjacentCoord(group.foundingTile.first + rint(- group.size / (group.size/9), group.size / (group.size / 9)) , group.foundingTile.second + rint(- group.size / (group.size/9), group.size / (group.size / 9))));
}

void generateTribe(uint16_t group)
{
	int tribeNum = groups[group].size();
	for (int i = 0; i < tribeNum; i++)
		addGroupMember(i);
}
// tribe ratios
// small tribe
void generateSmallTribe()
{
	uint16_t size = rint(10, 20);
	uint16_t maxSize = rint(20, 25);

	groups.push_back();
	// NOTE: may be size - 1
	generateTribe(groups.size());
}

// medium tribe
void generateMediumTribe()
{
	uint16_t size = rint(20, 45);
	uint16_t maxSize = rint(45, 55);

	groups.push_back();
	// NOTE: may be size - 1
	generateTribe(groups.size());
}

// large tribe
void generateLargeTribe()
{
	uint16_t size = rint(55, 150);
	uint16_t maxSize = rint(150, 250);

	groups.push_back();
	// NOTE: may be size - 1
	generateTribe(groups.size());
}

// warbands
void generateMiniWarband()
{
	uint16_t size = rint(10, 20);
	uint16_t maxSize = rint(20, 25);

	groups.push_back();
	// NOTE: may be size - 1
	generateTribe(groups.size());
}

void generateSmallWarband()
{
	uint16_t size = rint(20, 45);
	uint16_t maxSize = rint(45, 55);

	groups.push_back();
	// NOTE: may be size - 1
	generateTribe(groups.size());
}

void generateMediumWarband()
{
	uint16_t size = rint(55, 150);
	uint16_t maxSize = rint(150, 250);

	groups.push_back();
	// NOTE: may be size - 1
	generateTribe(groups.size());
}

// kingdoms
