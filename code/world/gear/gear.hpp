#ifndef GEAR_H_
#define GEAR_H_

#include "categories.hpp"
#include "itemBulkAndWeight.hpp"
#include <optional>

//at base material, cloth for underlayers and bronze for armor,  and average quality.
struct ClothingData {
    float toughness;
    float durability;
    float bulk;
    float weight;
    BulkLevel bulkLevel;
    float minTemp;
    float maxTemp;
    std::vector<BodyArea> covers;
};

struct AccesoryData {

};

struct WeaponData {
    int range;
    float damage;
    float speed;
    float durability;
    bool sharp; //whether it needs to be sharp, or if it is purely a smasher
    float pierceOrSmash; //pierce/smash value
};


constexpr float SLOW = 0.4;
constexpr float MEDIUM = 1.0;
constexpr float FAST = 1.6;

struct ToolData {
    vector<std::pair<Actions, float>> actionData; //last float takes speed from action data lookup table that says whether tool is SLOW MEDIUM or FAST at that particular task, multiples that value by time. Can override time instead of multiplying by making it a negative
    uint16_t durability; //how many times it can perform tasks before wearing out/breaking
    float bulk;
    float weight;
    BulkLevel bulkLevel = BulkLevel::Solid;
    std::optional<uint16_t> sharpness;
};

struct VariableGearData {
    Quality quality;
    Material material;
};

void initClothingData() {
    PartTribalwear {8.0, 250.0, 5.2, 5.2, BulkLevel::Solid, -8.0, 50.0, {BodyArea::LeftLeg, BodyArea::RightLeg}}
    Tribalwear {8.0, 250.0, 9.2, 8.4, BulkLevel::Solid, -16.0, 50.0, {BodyArea::Chest, BodyArea::RightShoulder, BodyArea::LeftShoulder, BodyArea::RightArm, BodyArea::RightArm, BodyArea::RightLeg, BodyArea::LeftLeg}}
    Robe {3.0, 120.0, 2.8, 2.2, BulkLevel::Soft, -6.0, 58.0, {BodyArea::Chest, BodyArea::RightShoulder, BodyArea::LeftShoulder, BodyArea::RightArm, BodyArea::RightArm, BodyArea::RightLeg, BodyArea::LeftLeg}}
    Tunic {4.0, 120.0, 1.6, 1.5, BulkLevel::Soft, -10.0, 54.0, {BodyArea::Chest, BodyArea::RightShoulder, BodyArea::LeftShoulder, BodyArea::RightArm, BodyArea::LeftArm}}
    Pants {4.5, 200.0, 1.5, 1.9, BulkLevel::Soft, -8.0, 50.0,  {BodyArea::LeftLeg, BodyArea::RightLeg}}
    Dress {4.5, 120.0, 1.5, 1.9, BulkLevel::Soft, -4.0, 60.0,  {BodyArea::LeftLeg, BodyArea::RightLeg}}
    Sandles {0.0, 320.0, 6.2, 2.2, BulkLevel::Solid, -1.0, 60.0, {BodyArea::LeftFoot, BodyArea::RightFoot}}
    Boots {33.0, 650.0, 11.5, 5.5, BulkLevel::Solid, -15.0, 50.0, {BodyArea::LeftFoot, BodyArea::RightFoot}}
    Scarf {6.0, 450.0, 0.9, 1.4, BulkLevel::Soft, -30.0, 60.0, {BodyArea::Neck}}
    Headwrap {4.0, 450.0, 1.4, 1.3, BulkLevel::Soft, -18.0, 58.0, {BodyArea::Neck, BodyArea::Head, BodyArea::Face}}
    Mitts {3.0, 200.0, 0.3, 0.5, BulkLevel::Soft, -20.0, 35.0, {BodyArea::LeftHand, BodyArea::RightHand}}
    Gloves {29.0, 300.0, 1.0, 1.2, BulkLevel::Solid, -5.0, 50.0, {BodyArea::LeftHand, BodyArea::RightHand}}
    Apron {3.0, 250.0, 0.2, 0.3, BulkLevel::Soft, -1.0, 40.0, {BodyArea::Chest}}
    Helmet {36.0, 450.0, 5.5, 3.5, BulkLevel::Solid, -5.0, 35.0, {BodyArea::Head}}
    Bracers {35.0, 400.0, 4.5, 2.4, BulkLevel::Solid, -5.0, 35.0, {BodyArea::LeftArm, BodyArea::RightArm}}
    Guards {26.0, 400.0, 6.5, 4.5, BulkLevel::Solid, -5.0, 25.0, {BodyArea::LeftLeg, BodyArea::RightLeg}}
    Cape {2.0, 80.0, 1.2, 0.9, BulkLevel::Soft, -1.0, 40.0, {}}
    HeavyShirt {9.0, 300.0, 3.5, 5.5, BulkLevel::Soft, -18.0, 25.0, {BodyArea::Chest, BodyArea::LeftArm, BodyArea::RightArm, BodyArea::LeftShoulder, BodyArea::RightShoulder}}
    HeavyPants {9.5, 300.0, 3.8, 6.2, BulkLevel::Soft, -18.0, 25.0, {BodyArea::LeftLeg, BodyArea::RightLeg}}
    Gambeson {18.0, 400.0, 12.1, 12.1, BulkLevel::Solid, -18.0, 25.0, {BodyArea::Chest, BodyArea::LeftShoulder, BodyArea::RightShoulder}}
    Chainmail {34.0, 280.0, 25.0, 8.8, BulkLevel::Single, -1.0, 40.0,  {BodyArea::Chest, BodyArea::RightShoulder, BodyArea::LeftShoulder, BodyArea::RightArm, BodyArea::RightArm, BodyArea::RightLeg, BodyArea::LeftLeg}}
    Breastplate {32.0, 500.0, 16.8, 32.2, BulkLevel::Single, -6.0, 40.0, {BodyArea::Chest, BodyArea::RightShoulder, BodyArea::LeftShoulder}}
    Plate {49.0, 500.0, 120.0, 130.0, BulkLevel::Single, -6.0, 35.0, {BodyArea::Chest, BodyArea::RightShoulder, BodyArea::LeftShoulder, BodyArea::RightArm, BodyArea::RightArm, BodyArea::RightLeg, BodyArea::LeftLeg}}
    WoodCrown {0.0, 100.0, 5.0, 3.3, BulkLevel::Solid, -1.0, 40.0, {BodyArea::Head}}
    GoldCrown {0.0, 100.0, 4.0, 4.3, BulkLevel::Solid, -1.0, 40.0, {BodyArea::Head}}
    RoyalCrown {0.0, 100.0, 4.0, 4.3, BulkLevel::Solid, -1.0, 40.0, {BodyArea::Head}}
    bulkAndWeights[static_cast<int>(Item::Necklace)] = {0.1f, 0.2f, BulkLevel::Solid};
}

//only values other than MEDIUM are listed, MEDIUM is default and assummed if not found
void initToolData() {
    //TODO: find actions for handaxe
    Handaxe {{{}}}
    Machete {{{Actions::Cut, FAST}, {Actions::FineChop, SLOW}, {Actions::Shear, SLOW}}, 1800, 8.5, 2.5, BulkLevel::Solid, 250}
    Knife {{{Actions::FineChop, FAST}, {Actions::Butcher, SLOW}} 2000, 3.2, 0.8, BulkLevel::Solid, 200}
    //TODO: balance, right now just worse than machete
    Cleaver {{}, 3500, 6.2, 1.2, BulkLevel::Solid, 120}
    Trowel {{{Actions::Dig, SLOW}, {Actions::Weed, FAST}}, 2500, 5.4, 1.2, BulkLevel::Solid}
    Chisel {{{Actions::Knapp, FAST}}, 480, 1.2, 3.4, BulkLevel::Solid}
    Hammer {{{Actions::Build, FAST}, {Actions::Crush, FAST}}, 2200, 7.2, 5.8, BulkLevel::Solid}
    Scalpel {{{Actions::Operate, FAST}, 4800, 1.1, 0.6, BulkLevel::Solid}
        Mallet {{{Actions::WoodCarve, SLOW}}, 1600, 4.2, 3.3}
        Sickle {{}, 8000, 4.2, 3.3}
        Adze {{}, 1800, 3.2, 2.1}
        Awl {{}, 1800, 3.2, 2.1}
        Graver {{}, 800, 1.2, 0.7}
        Pickaxe {{}, 50, 12.6, 8.8}
        Axe {{Actions::CanoeCarve, SLOW}, 480, 14.2, 9.2}
        Shovel {{Actions::Dig, FAST}, 2800, 24.8, 12.2}
        Saw {{Actions::CanoeCarve, FAST}, 250, 18.8, 5.2}
        //TODO: check ard facts
        Ard {{Actions::Plow, SLOW}, 1400, 22.8, 25.8}
        HeavyPlow {{Actions::Plow, FAST}, 1000, 43.9, 75.8, BulkLevel::Single}
        Whip {Actions::Herd, FAST}, 4500, 1.0, 1.0, BulkLevel::Soft}
    //TODO: allow fishing rod to catch speciality fish, research fishig methods, require string
    FishingRod {{Actions::Fish, SLOW}, 95, 16.2, 2.8}
    Staff {1800, 12.2, 7.8}
    DiggingStick {{Actions::Dig, SLOW}, 320, 9.5, 3.0}
    Scythe {{Actions::Harvest, FAST}, 4000, 16.2, 4.4}
    Blowpipe {{}, 6000, 3.1, 1.5}
    Shears {{Actions::Shear, FAST}, 1800, 5.3, 4.5, .sharpness=40}
    //TODO
    HandheldBellows
        Pestle {{}, 40000, 2.5, 2.5}
    Needle {{}, 4, 0.04, 0.002, BulkLevel::Loose}
    Drum {{}, 200, 20.2, 14.6}
    Torch {{}, }

    bulkAndWeights[static_cast<int>(Item::SimpleLoom)] = {34.0f, 8.5f, BulkLevel::Single};
    bulkAndWeights[static_cast<int>(Item::Blowpipe)] = {0.5f, 1.0f, BulkLevel::Solid};
    bulkAndWeights[static_cast<int>(Container::Crucible) + static_cast<int>(Item::MAX)] = {0.5f, 2.5f, BulkLevel::Solid};
    bulkAndWeights[static_cast<int>(Item::Whip)] = {1.8f, 0.5f, BulkLevel::Soft};
    bulkAndWeights[static_cast<int>(Item::HandheldBellows)] = {0.6f, 1.2f, BulkLevel::Soft};

}

void initWeaponData() {

bulkAndWeights[static_cast<int>(Item::Shortbow)] = {15.5f, 0.8f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Bow)] = {20.6f, 1.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Crossbow)] = {25.8f, 2.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Longbow)] = {28.9f, 1.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Spear)] = {19.9f, 2.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Axe)] = {17.0f, 2.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Sword)] = {18.0f, 3.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Greataxe)] = {28.2f, 7.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Halberd)] = {24.3f, 5.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Pike)] = {43.0f, 4.0f, BulkLevel::Single};
}

void initContainerData() {
bulkAndWeights[static_cast<int>(Container::Pot) + static_cast<int>(Item::MAX)] = {5.7f, 2.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::LargePot) + static_cast<int>(Item::MAX)] = {20.7f, 8.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::Kettle) + static_cast<int>(Item::MAX)] = {3.8f, 2.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::Jar) + static_cast<int>(Item::MAX)] = {0.8f, 1.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::Bucket) + static_cast<int>(Item::MAX)] = {14.6f, 2.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::Basket) + static_cast<int>(Item::MAX)] = {10.4f, 0.70f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::Satchel) + static_cast<int>(Item::MAX)] = {0.6f, 0.30f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::Bottle) + static_cast<int>(Item::MAX)] = {0.4f, 0.10f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Container::LargeSatchel) + static_cast<int>(Item::MAX)] = {1.2f, 0.20f, BulkLevel::Solid};
}
#endif // GEAR_H_
