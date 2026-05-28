#ifndef EXCRETION_MANAGER_HPP
#define EXCRETION_MANAGER_HPP
#include <entt/entt.hpp>
#include <plant/enum.hpp>

class ExcretionManager
{
      private:
      public:
	ExcretionManager() {};
	void prepareSeedDropping(entt::entity &animal, plant::Type plant);
	void excreteSeed(entt::entity &e, plant::Type plant);
};

#endif
