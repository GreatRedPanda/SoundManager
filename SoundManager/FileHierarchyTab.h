#pragma once
#include "TabBase.h"
#include "GuiTree.h"
#include <boost/signals2.hpp>
class FileHierarchyTab: public TabBase, Handler
{
	GuiTree* defaultFolder;

	void searchInFolder(std::vector<GuiTree > &result, GuiTree & folder, std::string searchData);
	float scrollHierarchy;
public:
	FileHierarchyTab(std::string name, ImVec2 pos, ImVec2 size) :TabBase(name, pos, size)
	{
		SetDropAccept();
		defaultFolder = new GuiTree("Main");
		defaultFolder->SetCheckbox(true);
		defaultFolder->AddListenerToDrop(this, handlerFunc);
		defaultFolder->SetDropAccept();
		childGuiItems.push_back(defaultFolder);
	}
	void Update(HWND hWnd) override;
	void AcceptFiles(std::vector<std::wstring> files) override;
	static void handlerFunc(Handler*fh,IDropGuiTarget* tg, std::vector<std::wstring> files);
	void SearchInit(std::string searchData); //std::string &searchData
	boost::signals2::signal <void(std::vector<GuiTree >& result)> OnGetSearchResult;
};


