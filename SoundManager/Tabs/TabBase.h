#pragma once
#include "ImGUI\imgui.h"
#include <string>
#include <wtypes.h>
#include <ImGuiAdvanced\GuiItem.h>
#include <vector>
#include <DragDropManagers\DropTarget.h>
#include <boost/signals2.hpp>
#include <iostream>
class TabBase: public IDropGuiTarget
{
protected:
	ImVec2 pos;
	ImVec2 size;
	ImVec2 posScaled;
	ImVec2 sizeScaled;
	std::string name;
	bool isFirstSetup;
	static ImVec2 scale;
	ImVec2 resize;
	static bool sizeChanged;
	std::vector<GuiItem*>  childGuiItems = std::vector<GuiItem*>();
	bool isResizing = false;

	virtual void UpdateStart();
	virtual void   UpdateTabItems();
	virtual void   UpdateTabEnd();


public: 
	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"> name of window</param>
	/// <param name="pos"> scaled pos of the window (in units)</param>
	/// <param name="size">scaled size of the window (in units)</param>
	TabBase(std::string name, ImVec2 pos, ImVec2 size);
	static 	ImVec2 GetVieportScale(ImVec2 scaleCoef);
	 void Update(HWND hWnd);
	// Унаследовано через IDropGuiTarget
	virtual bool CheckIsMouseOver() override;
	virtual void AcceptFiles(std::vector<std::wstring> files) override;
	virtual void DrawFileAccept() override;
	bool	IsDropAccepting() override;
	ImVec2 GetSize()
	{
		return size;
	}
	ImVec2 GetPosition()
	{
		
		return pos;
	}
	ImVec2 GetPositionScaled()
	{

		return ImVec2(int(pos.x * scale.x), int(pos.y * scale.y));
	}
	ImVec2 GetSizeScaled()
	{
		return ImVec2(int(size.x * scale.x), int(size.y * scale.y));
	}
	void SetSize(ImVec2 newSize)
	{
		size = newSize;
		//sizeScaled = newSize;
	}
	void SetPosition(ImVec2 newPos)
	{
	
		//posScaled = newPos;
		pos = newPos;
	}

	boost::signals2::signal <void(TabBase *source, int dir, ImVec2 amount)> OnResizing;

	~TabBase()
	{
		/*for (auto i : childGuiItems)
		{

			delete i;
		}*/
		 //childGuiItems.clear();
	
	}
};


