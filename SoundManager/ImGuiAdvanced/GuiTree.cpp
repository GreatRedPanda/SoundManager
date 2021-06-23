#include "GuiTree.h"
#include <iostream>
#include "Utils.h"
void GuiTree::Update()
{
	if (isCheckboxExist)
	{
		
		bool incl= isIncluded;
		if (ImGui::Checkbox(("##"+name).c_str(), &incl))
		{

		}
		this->isIncluded = incl;
		ImGui::SameLine();
	
	}
	

	std::string s = StringConvert::StringToUTF8(name);
	bool treeOpen = ImGui::TreeNodeEx(s.c_str(), flags);
	//ImGui::TreePush("32423");
	CheckIsMouseOver();
	checkDrag();
	

	if (ImGui::IsItemClicked(1) && !isMenuOpen)
	{
		isMenuOpen = true;
		
	}
	

	
	if (isMenuOpen)
	{
		if (!isPopUpOpen)
			isPopUpOpen = true;
		//else
		{
			ImGui::OpenPopup("##nodeMenu");

			if (ImGui::BeginPopup("##nodeMenu"))
			{

				if (ImGui::Button("Remove"));
				{
					if(ImGui::IsItemClicked(0))
					Remove();

				}
				ImGui::EndPopup();
			}
		}
	}
	
	if (ImGui::IsMouseDown(0) && isMenuOpen)
	{
		isPopUpOpen = false;
		isMenuOpen = false;
	}
	if (treeOpen)
	{
		if (treeItems.size() > 0)
		{
			for (auto&& i : treeItems)
			{
				
				i->Update();
			}
			
		}
		
		ImGui::TreePop();
	}
	//ImGui::TreePop();

	
}

void GuiTree::AcceptFiles(std::vector<std::wstring> files)
{
	invokeOnDropAccepted(files);
}

void GuiTree::DrawFileAccept()
{

}

//void GuiTree::checkDrag()
//{
//	
//	if (!isDragging )
//	{
//		if(ImGui::BeginDragDropSource())
//		{		
//			isDragging = true;
//			ImGui::EndDragDropSource();
//		}
//		if(isDragging)
//		invokeOnBeginDrag();
//	}
//}

LPCWSTR GuiTree::GetPath()
{
	LPCWSTR str = itemData.c_str();
	return str;
}

//void GuiTree::EndDrag()
//{
//	ImGui::GetIO().MouseDown[0] = false;
//	isDragging = false;
//}
