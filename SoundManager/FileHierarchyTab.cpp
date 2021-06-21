#include "FileHierarchyTab.h"
#include <iostream>
#include "SoundsDataBase.h"

void FileHierarchyTab::searchInFolder(std::vector<GuiTree>& result, GuiTree& folder, std::string searchData)
{

	for (auto& i : folder.GetChildren())
	{

		if (i->IsDirectory() )
		{
			if( i->IsIncludedInSearch())
			searchInFolder(result ,*i, searchData);
		}
		else
		{

		bool fileHasMeta=	SoundsDataBase::GetSoundDataBase()->CheckFileMeta(i->GetData(), { searchData });

			if (fileHasMeta)
			{
				result.push_back(*i);
			}
		}
	}
	
}

void FileHierarchyTab::Update(HWND hWnd)
{
	
	ImGui::SetNextWindowPos(GetPositionScaled(), 0, ImVec2(0, 0));
	bool isOPne = false;
	ImGui::Begin(name.c_str(), &isOPne, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration
	|ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::SetWindowSize(name.c_str(), GetSizeScaled());
	
bool over=	CheckIsMouseOver();
	ImGui::Button("All folders");
	ImGui::SameLine();
	ImGui::Button("None");
	bool border = false;
	ImGui::BeginChild("##child", ImVec2(GetSizeScaled().x-10, GetSizeScaled().y - 35), border, ImGuiWindowFlags_HorizontalScrollbar
		| ImGuiWindowFlags_AlwaysVerticalScrollbar);


	if (over && ImGui::GetIO().MouseDown[0])
	{


		ImVec2 mPos = ImGui::GetMousePos();
		ImVec2 pos = ImGui::GetItemRectMin();
		ImVec2 size = ImGui::GetWindowContentRegionMax();
		float maxW = ImGui::GetWindowPos().y  + ImGui::GetWindowHeight();
		float percent = 0.1f * maxW;
		bool mouseInUpperRect = mPos.y >= pos.y && mPos.y <= pos.y + percent;
		bool mouseInBotRect = mPos.y >= maxW - percent && mPos.y <= maxW;
	//	std::cout << maxW << "  " << maxW << "   " << mPos.x << "   " << mPos.y << "\n";
		std::cout << mouseInBotRect << "\n";

		scrollHierarchy = ImGui::GetScrollY();
		
		//scrollHierarchy -= 15 *(ImGui::GetIO().MouseDelta.y/(abs(ImGui::GetIO().MouseDelta.y)));
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
	//else
	

	
	/*if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenDisabled | ImGuiHoveredFlags_RootAndChildWindows))
	{
		invokeOnMouseOverItem();
	}*/
		for (auto& i : childGuiItems)
		{
			i->Update();
		}
	ImGui::EndChild();
	ImGui::End();
}

void FileHierarchyTab::AcceptFiles(std::vector<std::wstring> files)
{
	for (auto &i: files)
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
			tree->AddListenerToDrop(this, handlerFunc);
			tree->SetData(i);
		}
		else if(isSound)
		{
			GuiTree* nf = defaultFolder->AddLeaf(fn);
			nf->SetData(i);
		}
	}
}

void FileHierarchyTab::handlerFunc(Handler* fh, IDropGuiTarget *tg, std::vector<std::wstring> files)
{
		for (auto& i : files)
		{
			bool isDir;
			bool isSound;
			std::string fn = SoundsDataBase::GetSoundDataBase()->HandleAddedFile(i, isDir, isSound);
			GuiTree *gt = dynamic_cast<GuiTree*>(tg);
			if (isDir)
			{
				GuiTree* nf=	gt->AddChildNode(fn);
				nf->SetCheckbox(true);
				nf->SetDropAccept();
				nf->AddListenerToDrop(fh, handlerFunc);
				nf->SetData(i);
				std::vector<std::wstring> filesFromDir=	SoundsDataBase::GetSoundDataBase()->LoadDirectoryFiles(i);
				if (filesFromDir.size() != 0)
				{

					for (auto& iD : filesFromDir)
					{
						bool isD,  isS;
						std::string fnD = SoundsDataBase::GetSoundDataBase()->HandleAddedFile(iD, isD, isS);
						GuiTree* newFile = nf->AddLeaf(fnD);
						newFile->SetData(iD);
					}
				}

			}
			else if (isSound)
			{
				GuiTree* nf = gt->AddLeaf(fn);
				nf->SetData(i);
			}
		}
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

