#ifndef ROLES_H_
#define ROLES_H_

#include "basic.hpp"
#include "categories.hpp"

struct RoleData {
uint8_t cost;
Age age;
vector<vector<Role>> validPrerequisiteRole;
vector<vector<Role>> requisitesOf;
vector<std::pair<Role, uint8_t>> reductions;
  vector<int> apprenticeTime;
}

  RoleData roleDatas[static_cast<int>(Roles::MAX)];



#endif // ROLES_H_
