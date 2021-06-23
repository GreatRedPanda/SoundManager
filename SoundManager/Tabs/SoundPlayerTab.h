#pragma once
#include "TabBase.h"
class SoundPlayerTab : public TabBase
{
protected:

	void UpdateTabItems() override;
public:
	SoundPlayerTab(std::string name, ImVec2 pos, ImVec2 size) :TabBase(name, pos, size)
	{

	}

};
