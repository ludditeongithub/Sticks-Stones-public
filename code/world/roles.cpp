#include "roles.hpp"
#include "basic.hpp"
#include "categories.hpp"
#include "unit.hpp"

// without upgrades, a pawn can only be an apprentice of one role at a time.

std::stack next_apprentice_index;

struct ApprenticeData
{
	uint16_t pawnIndex;
	Role role;
	uint16_t xpLeft;
}

vector<ApprenticeData>
    apprentices;

void add_apprentice(uint16_t pawnIndex, Role apprenticeRole)
{
	bool found = false;
	int reductions = 0;
	for (int j = 0; j < roles[pawn].size(); j++)
	{
		for (int i = 0; i < roleDatas[static_cast<int>(role)].validPrerequisiteRole.size();
		     i++)
		{
			if (roleDatas[static_cast<int>(role)].validPrerequisiteRole[i] ==
			    roles[pawn][j])
			{
				found = true;
				break;
			}
		}
		if (!found)
			return ""; // TODO: ERROR MESSAGE TO UI
    for (int i = 0; i < roleDatas[static_cast<int>)
	    (role).reductions.size(); i++)
    {
	    if (roleDatas[static_cast<int>(role)].reductions[i].first == roles[pawn][j])
		    reductions += roleDatas[static_cast<int>(role)] reductions[i].second;
    }
    if (remainingRoleMana[i] - roleDatas[static_cast<int>].cost - reductions >= 0)
    {
	    remainingRoleMana[i] -= roleDatas[static_cast<int>].cost - reductions;
    }
    else
    {
	    // TODO: ERROR MESSAGE TO UI
	    return "";
    }
	}
	uint16_t xp_left = apprenticeXPRequired[static_cast<int>(apprenticeRole)];
	apprentices[nextApprenticeIndex.pop()]({pawnIndex, apprenticeRole, xpLeft});
}

void finish_apprenticeship(uint16_t apprenticeIndex)
{
	uint16_t pawn_index = apprentices[apprenticeIndex].pawnIndex;
	roles[pawnIndex].push_back(apprentices[apprenticeIndex].role);
	next_apprentice_index.push(apprenticeIndex);
}

void remove_role(int pawn, int roleIndex) { roles[pawn][roleIndex] = Role::EMPTY; }
