#pragma once
#include "GuiItem.h"
#include "ImGui/imgui.h"
#include <vector>
//#include "IDragGuiTarget.h"

class GuiTree: public GuiItem
{
	std::wstring itemData;
	std::vector<GuiTree*> treeItems = std::vector<GuiTree*>();
	ImGuiTreeNodeFlags flags;
	bool isIncluded;
	bool isCheckboxExist;
	bool isDirectory = false;
public:
	GuiTree(std::string name):GuiItem(name, ImVec2(0,0))
	{
		isIncluded = true;
		isCheckboxExist = false;
		flags = ImGuiTreeNodeFlags_None;
		
	}
	GuiTree(std::string name, ImVec2 size) :GuiItem(name, size)
	{
		isIncluded = true;
		isCheckboxExist = false;
		flags = ImGuiTreeNodeFlags_None;
	}
	
	void SetData(std::wstring data) {
	
		itemData = data;
	}
	std::wstring GetData() {

		return itemData ;
	}
	void Update() override;
	virtual void AcceptFiles(std::vector<std::wstring> files) override;
	virtual void DrawFileAccept() override;

	GuiTree* AddChildNode(std::string data)
	{
		GuiTree *tree = new GuiTree(data);
		treeItems.push_back(tree);
		return tree;
	}
	GuiTree* AddLeaf(std::string data)
	{
		GuiTree* tree = new GuiTree(data);
		tree->flags = ImGuiTreeNodeFlags_Leaf;
		
		treeItems.push_back(tree);
		return tree;
	}
	GuiTree* FindChild(std::string data)
	{
		return nullptr;
	}

	void SetCheckbox(bool isCheckboxExist)
	{
		isDirectory = true;
		this->isCheckboxExist = isCheckboxExist;
	}
	LPCWSTR GetPath() override;

	std::vector<GuiTree*> GetChildren()
	{
		return treeItems;
	}
	bool IsIncludedInSearch()
	{
	
		return isCheckboxExist && isIncluded;
	}
	bool IsDirectory()
	{
		return 	isDirectory ;
	;}
};

