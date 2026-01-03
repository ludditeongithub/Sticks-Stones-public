#ifndef EXCRETION_MANAGER_HPP
#define EXCRETION_MANAGER_HPP
#include <plant/enum.hpp>
#include <entt/entt.hpp>


class ExcretionManager
{
private:
public:
  ExcretionManager() {};
  void prepareSeedDropping(entt::entity& animal, plant::Type plant);
  void excreteSeed(entt::entity& e, plant::Type plant);
};





#endif
