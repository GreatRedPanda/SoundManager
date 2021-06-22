#pragma once
#ifndef GUIITEM_H
#define GUIITEM_H
#include "ImGui/imgui.h"
#include "DragDropManagers\IDropGuiTarget.h"
#include <string>
#include <vector>
#include <wtypes.h>
#include "DragDropManagers\DragManager.h"
typedef DragManager dm;
class GuiItem;

class GuiItem :public IDropGuiTarget, public IDragGuiTarget
{
protected:
	std::string name;
	ImVec2 size;

public:	
	GuiItem();
	GuiItem(std::string name,  ImVec2 size);
	virtual	void Update();


	// Унаследовано через IDropGuiTarget
	virtual bool CheckIsMouseOver() override;

	virtual void AcceptFiles(std::vector<std::wstring> files) override;
	virtual void DrawFileAccept() override;
	bool IsDropAccepting() override;
	void	checkDrag() override;

	void EndDrag() override;
};

#endif
