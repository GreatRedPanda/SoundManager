#include "IDropGuiTarget.h"

void IDropGuiTarget::invokeOnMouseOverItem()
{
	for (auto& i : onMouseOverItem)
	{	
		i(this);
	}
}

void IDropGuiTarget::invokeOnDropAccepted(std::vector<std::wstring> files)
{
	for (auto& i : onDropAcceptHandlers)
	{
		i.listener(i.obj, this, files);
	}
}

void IDropGuiTarget::AddListener(OnMouseOverItem listener)
{
	onMouseOverItem.push_back(listener);
}

void IDropGuiTarget::AddDropAcceptListener(OnDropAccepted listener)
{
}

void IDropGuiTarget::AddDropListener(OnDropAccepted listener)
{
}

void IDropGuiTarget::SetDropAccept()
{
	isAcceptingDrop = true;
}

bool IDropGuiTarget::IsDropAccepting()
{
	return isAcceptingDrop;
}
void IDropGuiTarget::AddListenerToDrop(Handler* obj, DropAcceptedCallBack<Handler> listener)
{
	HandlerArgs ha = HandlerArgs();
	ha.listener = listener;
	ha.obj = obj;
	onDropAcceptHandlers.push_back(ha);
	//onDropAcceptHandlers.push_back(obj);
	//onDropAccept.push_back(listener);
}
