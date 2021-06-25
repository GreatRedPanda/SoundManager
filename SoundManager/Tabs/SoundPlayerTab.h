#pragma once
#include "TabBase.h"
#include <boost/signals2.hpp>
class SoundPlayerTab : public TabBase
{
protected:

	void UpdateTabItems() override;
public:
	SoundPlayerTab(std::string name, ImVec2 pos, ImVec2 size) :TabBase(name, pos, size)
	{

	}

	boost::signals2::signal <void()> OnSoundPlay;
	boost::signals2::signal <void()> OnSoundStop;


};
