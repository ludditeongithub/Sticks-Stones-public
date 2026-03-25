#include "../include/plant.hpp"
#include "animal.hpp"
#include "cropdata.hpp"
#include "event.hpp"
#include "mapdimensions.hpp"
#include "objectData.hpp"
#include "unit.hpp"

// an event is sent to the event manager which triggers the mass spawn of all
// that type of plant, by this function, which sends events distributed over a
// set amount of time to germinate all seeds of that plant

// plants update loop
void PlantDatabase::updatePlants()
{
	for (int i = 0; i < plantList.size(); i++)
	{
		// get data for planttype
		Plants c = plantList[i];
		float fga = fullyGrownAmt[c];
		float ngmin = noGrowthMin[c];
		float ngmax = noGrowthMax[c];
		float omin = optimalMin[c];
		float omax = optimalMax[c];
		float dmin = deathMin[c];
		float dmax = deathMax[c];
		float wr = waterRequired[c];
		float wd = waterDeath[c];
		float ha = harvestAmt[c];
		float rs = requiresScythe[c];
		/* determine water status:
		 * all 3 states determined by one waterRequired variable. Plant can collect
		 * x2 of waterRequired. If <, yieldMissed, too dry. If x4, waterlogged,
		 * yieldMissed. */
		float wcomp = 1.0;
		// 1. collect water from ground
		// check for waterlog
		if (collectedWater[i] < wr)
		{
			yieldMisses[i]++;
			wcomp = collectedWater[i] / wr;
		}
		else
		{
			lastFullyWatered[i] = date;
		}
		// check if plant death
		if (temp < dmin || temp > dmax || date - lastFullyWatered[i] > wd)
		{
			plantList[i] = EMPTY;
			continue;
		}
		if (fullyGrown[i])
			continue;
		// growthrate = sunlight * watercomponent *  soilquality * temperature
		if (sunlight == 0.0)
		{
			growthAmt[i] = 0.0;
		}
		else
		{
			// get temp component
			float tcomp;
			if (temp > omin && temp < omax)
			{
				tcomp = 1.0;
			}
			else if (temp < omin)
			{
				if (temp < ngmin)
				{
					tcomp = 0.0;
				}
				else
				{
					tcomp = (20.0 - (cmath::abs(temp - omin))) * 0.05;
				}
			}
			else
			{
				if (temp > ngmax)
				{
					tcomp = 0.0;
				}
				else
				{
					tcomp = (20.0 - (cmath::abs(temp - omax))) * 0.05;
				}
			}
			// add growthrate
			growthAmt[i] += sunlight * tcomp * wcomp;
			if (growthAmt[i] >= fga)
				fullyGrown[i] = true;
		} // if sunlight == 0
	}
}

// plants update loop
void PlantDatabase::updateRegrowthPlants()
{
	for (int i = 0; i < regrowthPlantList.size(); i++)
	{
		// get data for planttype
		RegrowthPlants c = rPlantList[i];
		float la = lifespanAmt[c];
		float ngmin = rnoGrowthMin[c];
		float ngmax = rnoGrowthMax[c];
		float omin = roptimalMin[c];
		float omax = roptimalMax[c];
		float dmin = rdeathMin[c];
		float dmax = rdeathMax[c];
		float wr = rwaterRequired[c];
		float wd = rwaterDeath[c];
		float sha = rstartingHarvestAmt[c];
		float eha = rendingHarvestAmt[c];
		float rs = regrowthStart[c];
		float r = regrowthPeriod[c];
		/* determine water status:
		 * all 3 states determined by one waterRequired variable. Plant can collect
		 * x2 of waterRequired. If <, yieldMissed, too dry. If x4, waterlogged,
		 * yieldMissed. */
		float wcomp = 1.0;
		// 1. collect water from ground
		// check for waterlog
		if (rCollectedWater[i] < wr)
		{
			rYieldMisses[i]++;
			wcomp = rCollectedWater[i] / wr;
		}
		else
		{
			regrowthLastFullyWatered[i] = date;
		}
		// check if plant death
		if (temp < dmin || temp > dmax || date - rLastFullyWatered[i] > wd)
		{
			regrowthPlantList[i] = EMPTY;
			continue;
		}
		// growthrate = sunlight * watercomponent *  soilquality * temperature
		if (sunlight == 0.0)
		{
			regrowthGrowthAmt[i] = 0.0;
		}
		else
		{
			// get temp component
			float tcomp;
			if (temp > omin && temp < omax)
			{
				tcomp = 1.0;
			}
			else if (temp < omin)
			{
				if (temp < ngmin)
				{
					tcomp = 0.0;
				}
				else
				{
					tcomp = (20.0 - (cmath::abs(temp - omin))) * 0.05;
				}
			}
			else
			{
				if (temp > ngmax)
				{
					tcomp = 0.0;
				}
				else
				{
					tcomp = (20.0 - (cmath::abs(temp - omax))) * 0.05;
				}
			}
			// add growthrate
			regrowthGrowthAmt[i] += sunlight * tcomp * wcomp;
			if (regrowthGrowthAmt[i] >= la)
			{
				regrowthPlantList[i] = EMPTY;
				continue;
			}
			// add regrowth
			if (regrowthGrowthAmt[i] < rs && !regrowthHarvestable[i])
			{
				regrowthAmt[i] += sunlight * tcomp * wcomp;
			}
			if (regrowthAmt[i] > rs)
			{
				regrowthHarvestable[i] = true;
			}
		} // if sunlight == 0
	}
}
