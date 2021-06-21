#include "IDragGuiTarget.h"


void IDragGuiTarget::invokeOnBeginDrag()
{
	for (auto& i : onOnDragItemHandlers)
	{
		i(this);
	}
}

void IDragGuiTarget::checkDrag()
{

}

void IDragGuiTarget::AddListener(OnDragItem listener)
{
    onOnDragItemHandlers.push_back(listener);
}

LPCWSTR IDragGuiTarget::GetPath()
{
    return LPCWSTR();
}

void IDragGuiTarget::EndDrag()
{
}
