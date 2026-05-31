#pragma once
#include "ui/system.hpp"
#include <core/data.hpp>
class ButtonFunctionality {
	virtual void trigger();		
};

struct ChangeDimensionsBF : public ButtonFunctionality
{
	Coord screenDimensions;
	void trigger() override
	{
		UISystem->setDisplaySettings(screenDimensions.x, screenDimensions.y);
	}
};

