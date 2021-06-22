#pragma once
#include <vector>
#include <string>

class IDropGuiTarget;

//template <typename X>
//struct Handler
//{
//	typedef bool   (X::* OnDropAccepted)(IDropGuiTarget* item);
//
//};
typedef void  (* OnMouseOverItem)(IDropGuiTarget* item);
typedef bool   (* OnDropAccepted)(IDropGuiTarget* item);
template<typename T>
using DropAcceptedCallBack = void (*)(T* l, IDropGuiTarget* item, std::vector<std::wstring> files);

class Handler
{
};
struct HandlerArgs
{
	Handler* obj;
	DropAcceptedCallBack<Handler> listener;
};

class IDropGuiTarget
{
	
protected:
	void AddListener(OnMouseOverItem listener);
	void AddDropAcceptListener(OnDropAccepted listener);
	std::vector<OnMouseOverItem> onMouseOverItem = std::vector<OnMouseOverItem>();
	 std::vector<OnDropAccepted> onDropAccept = std::vector<OnDropAccepted>();
	 std::vector<HandlerArgs> onDropAcceptHandlers = std::vector<HandlerArgs>();
	void invokeOnMouseOverItem();
	void invokeOnDropAccepted(std::vector<std::wstring> files);
	bool isAcceptingDrop = false;

public:


	void AddDropListener(OnDropAccepted listener);
	void AddListenerToDrop(Handler*obj, DropAcceptedCallBack<Handler> listener);
	//void Update();
	virtual bool CheckIsMouseOver()=0;
	void SetDropAccept();
	virtual bool IsDropAccepting();
	virtual void AcceptFiles(std::vector<std::wstring> files) = 0;
	virtual void DrawFileAccept() = 0;
};




