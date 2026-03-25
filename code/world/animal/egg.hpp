#ifndef EGG_H_
#define EGG_H_

#include "entity.hpp"
#include "enum.hpp"
#include <basic/coord.hpp>
#include <basic/random.hpp>
#include <basic/time.hpp>
#include <entt/entt.hpp>
#include <station/scavengeables.hpp>

namespace egg
{

constexpr int getHatchTime(scavengeable::Type egg)
{
	switch (egg)
	{
	case scavengeable::Type::DuckEgg:
		return 43320;
	case scavengable::Type::ChickenEgg:
		return 28830;
	case scavengeable::Type::TurtleEgg:
		return 65400;
	default:
		return 0;
	}
}

struct HatchTime
{
	Time ht;
	explicit HatchTime(scavengeable::Type type) : ht(now() + getHatchTime(type)) {}
}

class EggManager
{
      private:
	entt::registry<> registry;

      public:
	EggManager() {};
	entt::entity addEgg(Coord c, animal::Type a) {};
	void hatchEgg() {};
};

} // namespace egg

#endif // EGG_H_
