#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
//#include "ImGui/imstb_rectpack.h"
#include <tchar.h>
#include <wtypes.h>
#include <iostream>

 class  ItemPosCalc{

 public:
 static HWND m_hwnd;

 static void SetAppRect(HWND hwnd)
	{
	
		 m_hwnd = hwnd;
	}
 static 	 bool IsMouseOverItem()
	{
		 RECT rect;
		 POINT p;
		 GetWindowRect(m_hwnd, &rect);
		 if (GetCursorPos(&p))
		 {
			 //cursor position now in p.x and p.y
		 }
		ImVec2 min = ImGui::GetItemRectMin();
		ImVec2 max = ImGui::GetItemRectMax();

		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();	
		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 bound = ImGui::GetContentRegionMax();
		ImVec2 size=	ImGui::GetWindowSize();
		ImGuiContext& g = *ImGui::GetCurrentContext();
		ImGuiWindowSettings* settings = ImGui::FindOrCreateWindowSettings("My Folders");
		ImVec2 vp=	ImGui::GetWindowViewport()->Pos;
		//min.x += windowPos.x;
		//max.x += vMax.x + windowPos.x;
		//min.y +=  windowPos.y;
		//max.y += vMax.y+windowPos.y;
  //    

		min.x += rect.left;
		//min.y += rect.bottom;
		max.x = min.x+ max.x;
		//max.y = rect.bottom - max.y;
		//

		//min.y += rect.top+35;
		//max.y = rect.top + vMax.y+ windowPos.y+35;
		min.y = rect.top + windowPos.y;
		max.y = rect.bottom-(vMax.y-vMin.y);
	
		//std::cout << min.x << " " << min.y << " " << max.x << " " << max.y << " Mouse " << p.x << "  " << p.y << "\n";
		//std::cout <<  min.y << " "  << max.y  << " Mouse "  << p.y << "\n";
		//&& p.y >= min.y && p.y <= max.y
		bool isMouseOverItem = (p.x >= min.x && p.x <= max.x );
		if(isMouseOverItem)
			std::cout << vp.y << " " << min.y << " Mouse " << p.y << "\n";
		//	std::cout << min.x << " " << min.y << " " << max.x << " " << max.y << " " << p.x << " " << p.y << "\n";
		//std::cout<< isMouseOverItem << "\n";
		return isMouseOverItem;
	}

} ;