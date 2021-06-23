#pragma once
#include "TabBase.h"
#include <boost/signals2.hpp>

class SearchTab : public TabBase
{
	
	static char str0[128] ;

protected:
	void UpdateTabItems() override;
public:
	SearchTab(std::string name, ImVec2 pos, ImVec2 size) :TabBase(name, pos, size)
	{

	}
	//void Update(HWND hWnd) override;
	//std::string &input
	boost::signals2::signal <void(std::string )> OnSearchInit;
	boost::signals2::signal <void()> OnClearResult;
};
