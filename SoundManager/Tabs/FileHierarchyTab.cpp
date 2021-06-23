#include "FileHierarchyTab.h"
#include <iostream>
#include "FilesManagement\SoundsDataBase.h"


void FileHierarchyTab::UpdateStart()
{
	ImGui::SetNextWindowPos(GetPositionScaled(), 0, ImVec2(0, 0));
	bool isOpen = false;
	ImGui::Begin(name.c_str(), &isOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration
		| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::SetWindowSize(name.c_str(), GetSizeScaled());

	bool over = CheckIsMouseOver();
}

void FileHierarchyTab::UpdateTabItems()
{
	ImGui::Button("All folders");
	ImGui::SameLine();
	ImGui::Button("None");
	bool border = false;
	ImGui::BeginChild("##child", ImVec2(GetSizeScaled().x - 10, GetSizeScaled().y - 35), border, ImGuiWindowFlags_HorizontalScrollbar
		| ImGuiWindowFlags_AlwaysVerticalScrollbar);

	bool over = false;
	if (over && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mPos = ImGui::GetMousePos();
		ImVec2 pos = ImGui::GetItemRectMin();
		ImVec2 size = ImGui::GetWindowContentRegionMax();
		float maxW = ImGui::GetWindowPos().y + ImGui::GetWindowHeight();
		float percent = 0.1f * maxW;
		bool mouseInUpperRect = mPos.y >= pos.y && mPos.y <= pos.y + percent;
		bool mouseInBotRect = mPos.y >= maxW - percent && mPos.y <= maxW;
		scrollHierarchy = ImGui::GetScrollY();
		if (mouseInBotRect)
		{
			scrollHierarchy += 2;
			ImGui::SetScrollY(scrollHierarchy);
		}
		else
			if (mouseInUpperRect)
			{
				scrollHierarchy -= 2;
				ImGui::SetScrollY(scrollHierarchy);
			}
		//ImGui::SetScrollFromPosY(scrollHierarchy, 0.5f);
	}
	for (auto& i : childGuiItems)
	{
		i->Update();
	}
	ImGui::EndChild();
}



void FileHierarchyTab::AcceptFiles(std::vector<std::wstring> files)
{
	addFilesToHierarchy(this, defaultFolder, files);

	/*for (auto &i: files)
	{
		bool isDir;
		bool isSound;
		std::string fn=	SoundsDataBase::GetSoundDataBase()->HandleAddedFile(i, isDir, isSound);		
		if (isDir)
		{
			GuiTree* tree = new GuiTree(fn);	
			tree->SetDropAccept();
			tree->SetCheckbox(true);
			childGuiItems.push_back(tree);			
			tree->AddListenerToDrop(this, HandleDropToTabChild);
			tree->SetData(i);
		}
		else if(isSound)
		{
			GuiTree* nf = defaultFolder->AddLeaf(fn);
			nf->SetData(i);
		}
	}*/
}

void FileHierarchyTab::HandleDropToTabChild(Handler* fh, IDropGuiTarget *tg, std::vector<std::wstring> files)
{

	FileHierarchyTab* tab = reinterpret_cast<FileHierarchyTab*>(fh);
	tab->addFilesToHierarchy(tab, tg, files);
}

void FileHierarchyTab::SearchInit(std::string searchData)
{
	//std::string searchData = "sdf";
	std::vector<GuiTree> result = std::vector<GuiTree>();

	//searchInFolder(result, *defaultFolder, searchData);

	for (auto& i : childGuiItems)
	{
		GuiTree* gt = dynamic_cast<GuiTree*>(i);

		if(gt!=nullptr)
		searchInFolder(result, *gt, searchData);

	}


	OnGetSearchResult(result);
}

void FileHierarchyTab::addFilesToHierarchy(FileHierarchyTab* fh, IDropGuiTarget* tg, std::vector<std::wstring> files)
{
	
	GuiTree* gt = nullptr;
		gt = dynamic_cast<GuiTree*>(tg);
	for (auto& i : files)
	{
		bool isDir;
		bool isSound;
		std::string fileName = SoundsDataBase::GetSoundDataBase()->HandleAddedFile(i, isDir, isSound);

		if (isDir)
		{
			GuiTree* nf=nullptr;
			
			//if (gt != defaultFolder)
			{
				nf=	gt->AddChildNode(fileName);
				
			}
			/*else
			{
				nf = new GuiTree(fileName);
				childGuiItems.push_back(nf);
			}*/
			nf->SetCheckbox(true);
			nf->SetDropAccept();
			nf->AddListenerToDrop(fh, HandleDropToTabChild);
			nf->SetData(i);
			std::vector<std::wstring> filesFromDir = SoundsDataBase::GetSoundDataBase()->LoadDirectoryFiles(i);
			if (filesFromDir.size() != 0)
			{

				for (auto& iD : filesFromDir)
				{
					bool isD, isS;
					std::string fnD = SoundsDataBase::GetSoundDataBase()->HandleAddedFile(iD, isD, isS);
					GuiTree* newFile = nf->AddLeaf(fnD);
					newFile->SetData(iD);
				}
			}

		}
		else if (isSound)
		{
			GuiTree* nf = gt->AddLeaf(fileName);
			nf->SetData(i);
		}
	}



}

void FileHierarchyTab::searchInFolder(std::vector<GuiTree>& result, GuiTree& folder, std::string searchData)
{

	for (auto& i : folder.GetChildren())
	{

		if (i->IsDirectory())
		{
			if (i->IsIncludedInSearch())
				searchInFolder(result, *i, searchData);
		}
		else
		{

			bool fileHasMeta = SoundsDataBase::GetSoundDataBase()->CheckFileMeta(i->GetData(), { searchData });

			if (fileHasMeta)
			{
				result.push_back(*i);
			}
		}
	}

}
