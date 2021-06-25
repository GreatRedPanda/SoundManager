#pragma once
#include "TabBase.h"
#include "ImGuiAdvanced\GuiTree.h"
#include <boost/signals2.hpp>
class FileHierarchyTab: public TabBase, Handler
{
	GuiTree* defaultFolder;
	GuiTree* currentSelectedItem;
	float scrollHierarchy;
	void addFilesToHierarchy(FileHierarchyTab* fh, IDropGuiTarget* tg, std::vector<std::wstring> files);
	void searchInFolder(std::vector<GuiTree > &result, GuiTree & folder, std::string searchData);


	

protected:
	void UpdateStart() override;
	void UpdateTabItems() override;
public:
	FileHierarchyTab(std::string name, ImVec2 pos, ImVec2 size) :TabBase(name, pos, size)
	{
		SetDropAccept();
		defaultFolder = new GuiTree("Main");
		defaultFolder->SetCheckbox(true);
		defaultFolder->AddListenerToDrop(this, HandleDropToTabChild);
		defaultFolder->SetDropAccept();
		childGuiItems.push_back(defaultFolder);
	}
	~FileHierarchyTab()
	{
		delete defaultFolder;
	}

	void AcceptFiles(std::vector<std::wstring> files) override;
	static void HandleDropToTabChild(Handler*fh,IDropGuiTarget* tg, std::vector<std::wstring> files);
	void SearchInit(std::string searchData); //std::string &searchData
	boost::signals2::signal <void(std::vector<GuiTree >& result)> OnGetSearchResult;
};


