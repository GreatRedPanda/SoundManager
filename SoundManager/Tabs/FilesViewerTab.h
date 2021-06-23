#pragma once
#include "TabBase.h"
#include "ImGuiAdvanced\GuiTree.h"
class FilesViewerTab : public TabBase
{

public:
	FilesViewerTab(std::string name, ImVec2 pos, ImVec2 size) :TabBase(name, pos, size)
	{

	}
	//void Update(HWND hWnd) override;

	void PrintSearchResult(std::vector<GuiTree> &result);

	void ClearResult();
};
