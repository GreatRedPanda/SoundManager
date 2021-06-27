#pragma once
#include "TabBase.h"
#include <boost/signals2.hpp>
#include "SelectedFilesPool.h"
#include "RtAudioPlayer.h"
class SoundPlayerTab : public TabBase
{

	typedef void (*valgetter) (void* data, int id);
	RtAudioPlayer player;
protected:
	
	void UpdateTabItems() override;
public:
	SoundPlayerTab(RtAudioPlayer audioPlayer, std::string name, ImVec2 pos, ImVec2 size) :TabBase(name, pos, size)
	{
		player = audioPlayer;
	}

	boost::signals2::signal <void()> OnSoundPlay;
	boost::signals2::signal <void()> OnSoundStop;
	static float vals(void* data, int id)
	{
	
		int* iptr = (int*)data;
		int num=iptr[id];
		
		return num;
	};

};
