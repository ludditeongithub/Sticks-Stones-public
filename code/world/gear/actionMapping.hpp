#ifndef ACTIONS_H_
#define ACTIONS_H_
#include "basic.hpp"
#include "categories.hpp"

template <typename T>
struct FixedList {
    std::array<T, 8> list;
    uint8_t size = 0;

    void add(T t) {
        if (size < 8) list[size++] = t;
    }

    T operator[](int i) const { return list[i]; }

    auto begin() const { return list.begin(); }
    auto end() const { return list.begin() + size; }
};

using ToolOrStation = std::variant<Tool, Station>;

//which tools can be used to perform which actions


struct ActionData {
    Actions action;
    bool sharp; //whether it needs to be sharp, and thus may need to be sharpened, and will decrease in sharpness, becoming slower or unusable if low
    bool tough; //whether it needs to be tough and can absorb energy, lowering durability variably on uses, and possibly destroying tool if brittle, depending on opposite material, as well as being slower based on material comparison
    //TODO: make enum tiers of how hard materials are, including tiles
    float durabilityPerUse; //how much durability lost per use on the tool in question, on a non-catastrophic use
};

void initActionData {
Collect false, false, 0
Hunt false, false -0.1 //TODO: write code to to deal with N/A, additional processing required
Mine false, true, 2.2
Cut true, false, 0.05
Chop true, true, 0.6
Dig false, true, 0.12
Light false, false, -0.1
Butcher true, true,
}

bool queuedActioInnterpreter(Actions actionToQueue) {

}



#endif // ACTIONS_H_
