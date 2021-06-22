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
	bool treeOPne = ImGui::TreeNodeEx(s.c_str(), flags);
	CheckIsMouseOver();
	checkDrag();
	
	if (treeOPne)
	{
		
		for (auto &&i: treeItems)
		{
			i->Update();
		}

		ImGui::TreePop();
	}
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
