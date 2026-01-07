#include <core/memory.hpp>

//all possible tasks
AutoEnum<> Tasks; //this needs to be automatically filled, using Items + Variants other actions, probably think of other way to make variants optional because there are just too many

struct PlayerTaskJobData {
  Task task;
  uint32_t amount;
  uint8_t skillReq;
};

struct TaskJobData {
  uint32_t amount;
  uint8_t skillReq;
};

using PlayerTaskJobOrder = Pool<PlayerTaskJobData>;

//binary tree by Task ID, to ensure that if player changes amount or priority a new Task Job isn't created. Check if easier to remake pq every time
void updateTaskJobPriorities(HashMap<Task, TaskJobData>& hm, std::priority_queue<std::pair<uint8_t, Task>>& pq, PlayerTaskJobOrder pt) {

  for (int i = 0; i < pt.size(); i++) {
    Task t = pt[i].data.task;
    //check validity
    uint8_t np = pt[i].data.priority;
    uint8_t na = pt[i].data.amount;
    if (hm[t] != hm.end()) {
      uint8_t& p = hm[task].priority;
      if (np != p) {
	//TODO: check if you are able to get a specific priority from a pq
	pq[p].set(np);
	p = np;
      }

      uint8_t& a = hm[task].amount;
      if (na != a) a = na;

      hm[t] = {np, na};
      }
  } else {
    hm[task] = {np, na};
    pq.push(np, t);
  }
}

void updateJobScores() {
  
}

//TODO: make certain tasks pausable and resumable, change to iterating over tasks per pawn rather than other way around (when pawns stats are implemented)-- timers will skip most pawns repeatedly, maybe need bool for whether job has just started
void updateTasks(std::priority_queue<std::pair<uint8_t, PlayerTaskJobData>> pq, Pool<uint16_t> timers, Pool<Task> tasks, Pool<Skills> skills) {
  int i = 0;
    for (int i = 0; i < timers.size(); i++) {
      if (timers[i] > 0) continue;
      if (healths[i] <= 0) {
	action[i] = Action::Dead;
	continue;
      }
      if (action[i] == Action::Assign) {      
	
        // get valid task for selected pawn
      bool v = false;	      	
	auto ji = INVALID;
	while (v == false && pq.next != nullptr) {
	PlayerTaskJobData td = pq.top();
	Task t = td.task;
	uint32_t& a = td.amount;
	for (int j = 0; j < rd[i].size(); j++) {
	//TODO: precompute all scores for all roles
	  uint8_t ts = getJobScore(rd[i][j], skills[i]); //returns 0 if invalid
	if (ts > taskData[i].skillReq) {
	  tasks[i] = t;
	  v = true;
	  a -= getMinimumOutput[t];
	  timers[i] = getTaskTimer(task, skills[i]);
	  if (a <= 0) pq.pop();
	  //TODO: set action
	  break;	  	  
	} 
	}
	}
	if (!v) action[i] = Action::Idle;
      }      
    }
}


