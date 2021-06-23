#include "SoundPlayerTab.h"

void SoundPlayerTab::UpdateTabItems()
{


	ImGui::Button("Play");
	ImGui::SameLine();
	ImGui::Button("Stop");
	ImVec2 btnSize = ImGui::GetItemRectSize();
	static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
    char overlay[32];
    ImGui::PlotLines("##Lines", arr, IM_ARRAYSIZE(arr), 0, overlay, -1.0f, 1.0f,
	ImVec2(GetSizeScaled().x,GetSizeScaled().y-btnSize.y -35));
    
  
	
}
