#ifndef LIFETIME_MANAGER_HPP
#define LIFETIME_MANAGER_HPP
#include <stdexcept>
#include <vector>

class LifetimeManager
{
private:
  std::vector<bool> alives;
  size_t size;
public:
  LifetimeManager() {};
  void markDestroyed(size_t index) {
    if (index > size) {
      throw std::out_of_range("Tried to mark for destruction larger than size.");
    } else {
      alives[index] = false;
    }      
  }
};


#endif
