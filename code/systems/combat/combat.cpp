// TODO: factor in variable distances creating variable chance of hitting
void update_attacks(float *chances, Weapon* weapons, Stats *stats, Coord *positions, float *healths,
				   int *targets, Action *actions)
{
	// precompute attack success and damages

	Arena<bool> attack_success; // ensure arena makes default value
	Arena<float> damages;
	for (int i = 0; i < targets.size(); i++)
	{
		if (timer(i) <= 0 && action(i) == Action::Attack)
		{
			auto ti = targets(i);
			if (hit(chance(i), weapon(i), stat(i), armor(ti), dodge(i), stat(ti)))
			{
			}
		}
	}
	int j = 0;
	for (int i = 0; i < ; i++)
	{
		if (timer(i) <= 0 && action(i) == Action::Attack)
		{
			auto ti = target(i);
			float &h = health(ti);
			if (attack_success[j++])
				h -= damage[j];
			if (h <= 0.0)
				action(i) = Action::Assign;
		}
	}
}
