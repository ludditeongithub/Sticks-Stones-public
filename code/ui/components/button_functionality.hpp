#pragma once
#include "ui/system.hpp"
#include <core/data.hpp>
class ButtonFunctionality
{
	public:
	virtual void trigger();
};

class NullBF : public ButtonFunctionality
{
private:
public:
	void trigger() override {};
};


class ChangeScreenDimensionsBF : public ButtonFunctionality
{
	public:
	  Coord screenDimensions;
	ChangeScreenDimensionsBF(Coord screenDimensions) : screenDimensions(screenDimensions) {}
	void trigger() override
	{
		UISystem->setDisplaySettings(screenDimensions.x, screenDimensions.y);
	}
};

