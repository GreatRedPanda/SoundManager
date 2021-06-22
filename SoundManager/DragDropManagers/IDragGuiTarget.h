#pragma once
#include <vector>
#include <wtypes.h>

class IDragGuiTarget;
typedef void  (*OnDragItem)(IDragGuiTarget* item);
class IDragGuiTarget
{
protected:
	bool isDragging;
	void invokeOnBeginDrag();
	virtual void checkDrag();
	std::vector<OnDragItem> onOnDragItemHandlers= std::vector<OnDragItem>();

	bool isAppDrop = true;
	bool isSelfDropAllowed = false;

public:
	bool GetIsApplicationDropAllowed()
	{
		return isAppDrop;
	}
	bool GetIsSelfDropAllowed()
	{
		return isSelfDropAllowed;
	}
	void SetIsApplicationDropAllowed(bool val)
	{
		 isAppDrop=val;
	}
	void GetIsSelfDropAllowed(bool val)
	{
		 isSelfDropAllowed=val;
	}
	void AddListener(OnDragItem listener);
	virtual	LPCWSTR GetPath() ;
	virtual void EndDrag();
};

