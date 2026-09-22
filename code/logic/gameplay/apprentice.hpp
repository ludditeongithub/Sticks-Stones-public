// without upgrades, a pawn can only be an apprentice of one role at a time.

std::stack next_apprentice_index;

// links pawn to role, which they are apprentice of. second int is experience remaining.
vector<uint16_t, Role, uint16_t> apprentice_xpleft;

void add_apprentice(uint16_t pawn_index, Role apprentice_role)
{
	bool found = false;
	int reductions = 0;
	for (int j = 0; j < roles[pawn].size(); j++)
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
    }
	}
	uint16_t XPtoGet = apprentice_xprequired[static_cast<int>(apprentice_role)];
	apprentice_xpleft.push_back(pawn_index, apprentice_role, XPtoGet);
}

void finish_apprenticeship(uint16_t apprentice_index)
{
	add next_apprentice_index.push(apprentice_index);
}
