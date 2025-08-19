#ifndef MAINTENANCELOOPS_H_
#define MAINTENANCELOOPS_H_

#include "basic.hpp"

template <typename EnumType>
void cleanup(std::vector<EnumType>& vec) {
    vec.erase(std::__remove_if(vec.begin(), vec.end(), [](EnumType e) {
        return static_cast<int>(e) == -1; // Cast enum to underlying type and check for sentinel value
    }), vec.end());
}

#endif // MAINTENANCELOOPS_H_
