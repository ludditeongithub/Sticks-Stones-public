#ifndef GROWTH_MANAGER_HPP
#define GROWTH_MANAGER_HPP

class GrowthManager
{
private:
  int interval;
public:
  GrowthManager() {};
  bool viableHarvest();
  void attemptPlantGrowth(int plant, int time, int biomeIndex);
  void updatePlants();
  void updateRegrowthPlants();
  // the interval of time between when path growth is calculated is determined by simulation accuracy settings set at the start, which tells the main event manager at which intervals to send signals to managers.
};




#endif
