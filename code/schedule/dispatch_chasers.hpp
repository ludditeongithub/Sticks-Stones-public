// a chaser is someone who is going after a moving target, and thus needs their
// destination updated frequently, and short paths.
// TODO: make chaser give up if it knows target type is much faster

#include "schedule/dispatch.hpp"
#include <world/animal/entity.hpp>
#include <world/unit/entity.hpp>

struct ChaserDispatch
{
	void dispatchAnimalHunters(DispatchData<Animal> &dd) {}

	void dispatchUnitChasers(DispatchData<>) {}
};
