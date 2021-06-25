#pragma once
#include <string>
#include <boost/signals2.hpp>
class ISelectable
{
protected:
	std::wstring itemData;
	boost::signals2::signal <void(GuiTree*)> OnSelected;
};

