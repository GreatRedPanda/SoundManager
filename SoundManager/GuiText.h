#pragma once
#include "GuiItem.h"
#include "ImGui/imgui.h"
class GuiText : public GuiItem
{
	std::string itemData;
public:
	GuiText(std::string name) :GuiItem(name, ImVec2(0, 0))
	{

	}
	GuiText(std::string name, ImVec2 size) :GuiItem(name, size)
	{

	}
	void Update() override;
	virtual void AcceptFiles(std::vector<std::wstring> files) override;
	virtual void DrawFileAccept() override;

};

