#include <core/memory.hpp>
#include <world/unit/roles_and_actions.hpp>

struct PlayerJobOrder
{
	Action action;
	int32_t amount;
};

struct JobData
{
	uint32_t amount;
	uint8_t skill_req;
};

void add_player_order();


// binary tree by Task ID, to ensure that if player changes amount or priority a new Task Job isn't
// created. Check if easier to remake pq every time
void update_task_priorities(std::unordered_map<Task, JobData> &hm, PlayerJobOrder pt)
{

	for (int i = 0; i < pt.size(); i++)
	{
		Task t = pt[i].data.task;
		// check validity
		uint8_t np = pt[i].second().priority;
		uint8_t na = pt[i].second().amount;
		if (hm[t] != hm.end())
		{
			uint8_t &p = hm[task].second().priority;
			if (np != p)
			{
				// TODO: check if you are able to get a specific priority from g_task_priority_queue
				g_task_priority_queue[p].set(np);
				p = np;
			}

			uint8_t &a = hm[task].second().amount;
			if (na != a)
				a = na;

			hm[t] = {np, na};
		}
	}
	else
	{
		hm[task] = {np, na};
		g_task_priority_queue.push(np, t);
	}
}
