#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <basic/coord.hpp>
#include <basic/target.hpp>
#include <entt/entt.hpp>
#include "enum.hpp"
#include "entity.hpp"

namespace animal {

class AnimalRegistry {
private:
    entt::registry registry;

public:
    AnimalRegistry() = default;

    entt::registry& get() { return registry; }
    const entt::registry& get() const { return registry; }

    entt::entity addAnimal(Type type, Coord pos, Sex sex) {
        auto e = registry.create();
        registry.emplace<Type>(e, type);
        registry.emplace<Coord>(e, pos);
        registry.emplace<Sex>(e, sex);
        registry.emplace<Age>(e, 0.0);
        registry.emplace<Health>(e, maxHealth[(size_t)type]);
        registry.emplace<Hunger>(e, maxHunger[(size_t)type]);
        registry.emplace<Facing>(e, random_enum<Direction>());
        registry.emplace<Mating>(e, MatingStatus::Infertile);
        registry.emplace<Movement>(e, MovingStatus::Idle);
	registry.emplace<Target>(e, TargetType::NONE);
        return e;
    }

    void killAnimal(entt::entity e) {
        registry.destroy(e);
    }
};

} // namespace animal


#endif // ANIMAL_H_
