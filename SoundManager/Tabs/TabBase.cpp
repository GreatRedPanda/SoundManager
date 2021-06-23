#include "TabBase.h"
#include "ImGui/imstb_rectpack.h"
#include <iostream>
ImVec2 TabBase::scale = ImVec2(1, 1);
bool TabBase::sizeChanged = false;
void TabBase::UpdateStart()
{
	ImGui::SetNextWindowPos(GetPositionScaled(), 0, ImVec2(0, 0));
	bool isOpen = false;
	ImGui::Begin(name.c_str(), &isOpen, ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize 
		| ImGuiWindowFlags_NoDecoration  
	);
	ImGui::SetWindowSize(name.c_str(), GetSizeScaled());
	CheckIsMouseOver();
}
void TabBase::UpdateTabItems()
{
	for (auto& i : childGuiItems)
	{
		i->Update();
	}
}
void TabBase::UpdateTabEnd()
{
	ImGui::End();
}
TabBase::TabBase(std::string name, ImVec2 pos, ImVec2 size)
{
	
	//DropTarget::AddItem(this);
	AddListener(&DropTarget::GetCurrentGui);
	this->name = name;
	this->pos = pos;
	this->size = size;
	//SetPosition(ImVec2(int(pos.x * scale.x), int(pos.y * scale.y)));
	//SetSize(ImVec2(int(size.x * scale.x), int(size.y * scale.y)));
}

ImVec2 TabBase::GetVieportScale(ImVec2 scaleCoef)
{
	sizeChanged = false;
	ImGuiViewport* main = ImGui::GetMainViewport();
	ImVec2	sc;
		sc.x= main->Size.x/scaleCoef.x;
		sc.y = main->Size.y / scaleCoef.y;
		if (sc.x != scale.x || sc.y != scale.y)
		{
			sizeChanged = true;
		}
		scale = sc;
		return scale;
}

void TabBase::Update(HWND hWnd)
{

	UpdateStart();
	UpdateTabItems();
	UpdateTabEnd();
}

bool TabBase::CheckIsMouseOver()
{

	/*std::cout << ImGui::GetIO().MousePos.x << "  " << ImGui::GetIO().MousePos.y << "Before\n";*/
	
	//std::cout << name.c_str() << std::endl;
	//ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem|ImGuiHoveredFlags_AllowWhenDisabled | ImGuiHoveredFlags_RootAndChildWindows))
	{
		/*if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)
		{
			std::cout << ImGui::GetIO().MousePos.x << "  " << ImGui::GetIO().MousePos.y << " In tabs\n";
		}*/
	//	std::cout << name.c_str() << std::endl;
		//std::cout << "Window hover\n";
		invokeOnMouseOverItem();
		return true;
	}
	return false;
}

void TabBase::AcceptFiles(std::vector<std::wstring> files)
{
}
void TabBase::DrawFileAccept()
{
}

bool TabBase::IsDropAccepting()
{
	//std::cout << name.c_str() << std::endl;
	return isAcceptingDrop;
}









//if (GetFocus() != hWnd)
	////{
	////	RECT rect;
	////	GetWindowRect(hWnd, &rect);
	////	POINT p;
	////	(GetCursorPos(&p));

	////	//ImGui::GetIO().MousePosPrev = ImVec2(0, 0);
	////    ImGui::GetIO().MousePos = ImVec2(p.x - rect.left - 8, p.y - rect.top - 31);
	////	//ImGui::GetIO().MousePos = ImVec2(520, 240);

	////}
	////if (isResizing)
	////{
	////	//ImGui::GetIO().MouseDown[0] = 0;
	////	
	////	OnResizing( this, 0, resize);

	////}

	//ImGui::SetNextWindowPos(GetPositionScaled(), 0, ImVec2(0, 0));
	//bool isOpen = false;
	//
	//
	//ImGui::Begin(name.c_str(), &isOpen,  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoDecoration );
	////if (isFirstSetup || sizeChanged)
	////{	
	////	isFirstSetup = false;
	////	ImGui::SetWindowSize(name.c_str(), ImVec2(size.x * scale.x, size.y * scale.y));
	////}
	//
	//ImGui::SetWindowSize(name.c_str(), GetSizeScaled());
	// 
	//
	//
	////ImVec2 newSize=ImGui::GetWindowSize();
	////ImVec2 newPos = ImGui::GetWindowPos();
	////ImVec2 rectSize= ImGui::GetItemRectSize();

	////if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)
	////{
	////	ImVec2 delta=	ImGui::GetMouseDragDelta();
	////}
	////if (ImGui::GetIO().MouseDown[0] && (newPos.x != GetPositionScaled().x || newPos.y != GetPositionScaled().y))
	////{
	////	isResizing = true;
	////	resize.x = (newPos.x - GetPositionScaled().x);
	////	resize.y = (newPos.y- GetPositionScaled().y)/scale.y;
	////	//std::cout << newPos.x << "  " << newPos.y << "  " << pos.x * scale.x << "  " << pos.y * scale.y << '\n';
	////	std::cout << ImGui::GetWindowViewport()->Size.x << "  " << ImGui::GetWindowViewport()->Size.y << "  "  << '\n';
	////	std::cout << GetSizeScaled().x << "  " << GetSizeScaled().y << "  " << '\n';
	////}
	////else
	////	isResizing = false;


	////if (ImGui::GetIO().MouseDown[0] && (newSize.x != int(size.x * scale.x) || newSize.y != int(size.y * scale.y)))
	////{
	////	isResizing = true;
	////	resize.x = newSize.x / scale.x - size.x;
	////	resize.y = newSize.y / scale.y - size.y;
	////}
	////else
	////	isResizing = false;
	////
	////

	//CheckIsMouseOver();
	//for (auto& i : childGuiItems)
	//{
	//	i->Update();
	//}