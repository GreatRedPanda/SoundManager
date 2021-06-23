#pragma once
#include "GuiItem.h"
#include "ImGui/imgui.h"
#include <vector>
#include <boost/signals2.hpp>

class GuiTree: public GuiItem
{
	std::wstring itemData;
	std::vector<GuiTree*> treeItems = std::vector<GuiTree*>();
	ImGuiTreeNodeFlags flags;
	bool isIncluded;
	bool isCheckboxExist;
	bool isDirectory = false;
	bool isMenuOpen;
	bool isPopUpOpen;
	boost:: signals2::signal <void(GuiTree *child)> OnRemoved;
public:
	GuiTree(const GuiTree& origin)
	{
		flags=	origin.flags;
		name = origin.name;

		itemData = origin.itemData;
		treeItems = origin.treeItems;
		isDirectory = origin.isDirectory;

		isCheckboxExist = origin.isCheckboxExist;

	}
	GuiTree(std::string name):GuiItem(name, ImVec2(0,0))
	{
		isIncluded = true;
		isCheckboxExist = false;
		flags = ImGuiTreeNodeFlags_None ;
		
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
		tree->OnRemoved.connect(boost::bind(&GuiTree::RemoveChild, this, tree));
		treeItems.push_back(tree);
		return tree;
	}
	GuiTree* AddLeaf(std::string data)
	{
		GuiTree* tree = new GuiTree(data);
		tree->flags = ImGuiTreeNodeFlags_Leaf;
		tree->OnRemoved.connect(boost::bind(&GuiTree::RemoveChild, this, tree));
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



	void RemoveChild(GuiTree *child)
	{

	auto ch=	find(treeItems.begin(), treeItems.end(), child);
		if(ch!=treeItems.end())
		treeItems.erase(ch);
	
	}
	void Remove()
	{
		OnRemoved(this);
		for (auto i : treeItems)
		{

			delete i;
		}
		treeItems.clear();

		delete this;
		
	}
};

