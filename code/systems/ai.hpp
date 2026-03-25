
// TODO: factor in variable distances creating variable chance of hitting
void updateAttacks(float *chances, Weapon *weapons, Stats *stats, Coord *positions, float *healths,
		   int *targets, Action *actions)
{
	// precompute attack success and damages

	Arena<bool> attackSuccess; // ensure arena makes default value
	Arena<float> damages;
	for (int i = 0; i < targets; i++)
	{
		if (timers[i] <= 0 && actions[i] == Action::Attack)
		{
			auto ti = targets[i];
			if (hit(chances[i], weapons[i], stats[i], armors[ti], dodges[i], stats[ti]))
		}
	}
	int j = 0;
	for (int i = 0; i < ; i++)
	{
		if (timers[i] <= 0 && actions[i] == Action::Attack)
		{
			auto ti = targets[i];
			float &h = healths[ti];
			if (attackSuccess[j++])
				h -= damages[j];
			if (h <= 0.0)
				actions[i] = Action::Assign;
		}
	}
}

void getNewAction(roleData &rd, Action *actions)
{
	for (int i = 0; i < unitsSize; i++)
	{
		if (healths[i] <= 0)
			action[i] = Action::Dead;
		if (action[i] == Action::Assign)
		{

			// get best role for pawn to inhabit
			float highest = std::numeric_limits<float>(min);
			auto ji = INVALID;
			for (int j = 0; j < rd[i].size(); j++)
			{
				// TODO: precompute all scores for all roles
				float t = getJobScore(rd[i][j]);
				if (t > highest)
				{
					highest = t;
					ji = j;
				}
			}
			actions[i] = roleToAction[rd[i][ji]];
		}
	}
}

void updateJobScores() {}
