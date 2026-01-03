  entt::entity addEgg(Coord c, animal::Type a) {
    auto e = registry.create;
    registry.emplace<animal::Type>(e, type);
    registry.emplace<Coord>(e, c);
    registry.emplace<Sex>(e, rbool());
     scavengeable::Type eggType = animalToEgg(a);
     registry.emplace<HatchTime>(e, eggType);
  }

void EggManager::hatchEgg(entt::entity& e) {
    AnimalRegistry::addAnimal(e<animal::Type>, e<Coord>, e<Sex>);    
    registry.destroy(e);
}


