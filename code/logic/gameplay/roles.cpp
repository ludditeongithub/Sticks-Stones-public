#include <cstdint>
#include <stack>
#include <data/types/unit.hpp>


// without upgrades, a pawn can only be an apprentice of one role at a time.

std::stack<size_t> next_apprentice_index;

struct ApprenticeData
{
	uint16_t pawn_index;
	Role role;
	uint16_t xp_left;
}

std::vector<ApprenticeData> apprentices;

void add_apprentice(size_t pawn_index, Role apprentice_role)
{
	bool found = false;
	int reductions = 0;
	for (int j = 0; j < roles[pawn_index].size(); j++)
	{
		for (int i = 0; i < role_datas[static_cast<int>(role)].valid_prerequisite_role.size();
		     i++)
		{
			if (role_datas[static_cast<int>(role)].valid_prerequisite_role[i] ==
			    roles[pawn][j])
			{
				found = true;
				break;
			}
		}
		if (!found)
			return ""; // TODO: ERROR MESSAGE TO UI
    for (int i = 0; i < role_datas[static_cast<int>)
	    (role).reductions.size(); i++)
    {
	    if (role_datas[static_cast<int>(role)].reductions[i].first == roles[pawn][j])
		    reductions += role_datas[static_cast<int>(role)] reductions[i].second;
    }
    if (remaining_role_mana[i] - role_datas[static_cast<int>].cost - reductions >= 0)
    {
	    remaining_role_mana[i] -= role_datas[static_cast<int>].cost - reductions;
    }
    else
    {
	    // TODO: ERROR MESSAGE TO UI
	    return "";
    }
	}
	uint16_t xp_left = apprentice_xprequired[static_cast<int>(apprentice_role)];
	apprentices[next_apprentice_index.pop()]({pawn_index, apprentice_role, xp_left});
}

void finish_apprenticeship(uint16_t apprentice_index)
{
	uint16_t pawn_index = apprentices[apprentice_index].pawn_index;
	roles[pawn_index].push_back(apprentices[apprentice_index].role);
	next_apprentice_index.push(apprentice_index);
}

void remove_role(int pawn, int role_index) { roles[pawn][role_index] = Role::EMPTY; }
