#include "FilesViewerTab.h"

//void FilesViewerTab::Update(HWND hWnd)
//{
//	TabBase::Update(hWnd);
//
//
//	ImGui::End();
//}
void FilesViewerTab::PrintSearchResult(std::vector<GuiTree>& result)
{
	for (auto& i : result)
	{
		GuiTree *newItem= new GuiTree(i);
		newItem->SetIsApplicationDropAllowed(false);
		childGuiItems.push_back(newItem);
	}
}

void FilesViewerTab::ClearResult()
{
	for (auto i : childGuiItems)
	{
		delete i;
	}
	
	childGuiItems.clear();

}