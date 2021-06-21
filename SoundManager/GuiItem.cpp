#include "GuiItem.h"

#include "DropTarget.h"
#include <iostream>

GuiItem::GuiItem()
{
	IDropGuiTarget::AddListener(&DropTarget::GetCurrentGui);
	IDragGuiTarget::AddListener(dm::SetDraggingItem);
	//DropTarget::AddItem(this);
}

GuiItem::GuiItem(std::string name,  ImVec2 siz)
{
	IDropGuiTarget::AddListener(&DropTarget::GetCurrentGui);
	IDragGuiTarget::AddListener(dm::SetDraggingItem);
	//DropTarget::AddItem(this);
	this->name = name;
	this->size = siz;
	
	
}


void GuiItem::Update()
{



		ImGui::Button(name.c_str(), size);
		CheckIsMouseOver();
}

bool GuiItem::CheckIsMouseOver()
{
	
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
	{
		//std::cout << name.c_str() << std::endl;
		invokeOnMouseOverItem();
		return true;
	
	}

	return false;
}

void GuiItem::AcceptFiles(std::vector<std::wstring> files)
{
}

void GuiItem::DrawFileAccept()
{
}

bool GuiItem::IsDropAccepting()
{
	//std::cout << name.c_str() << std::endl;
	return isAcceptingDrop;
}
void GuiItem::checkDrag()
{

	if (!isDragging)
	{
		if (ImGui::BeginDragDropSource())
		{
			isDragging = true;
			ImGui::EndDragDropSource();
		}
		if (isDragging)
			invokeOnBeginDrag();
	}
}
void GuiItem::EndDrag()
{
	ImGui::GetIO().MouseDown[0] = false;
	isDragging = false;
}

