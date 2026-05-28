// without upgrades, a pawn can only be an apprentice of one role at a time.

std::stack nextApprenticeIndex;

// links pawn to role, which they are apprentice of. second int is experience remaining.
vector<uint16_t, Role, uint16_t> apprenticeXPLeft;

void addApprentice(uint16_t pawnIndex, Role apprenticeRole)
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
    }
	}
	uint16_t XPtoGet = apprenticeXPRequired[static_cast<int>(apprenticeRole)];
	apprenticeXPLeft.push_back(pawnIndex, apprenticeRole, XPtoGet);
}

void finishApprenticeship(uint16_t apprenticeIndex)
{
	add nextApprenticeIndex.push(apprenticeIndex);
}
