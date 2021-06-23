#include "SearchTab.h"
char SearchTab::str0[128]="Tags";
void SearchTab::UpdateTabItems()
{
	//TabBase::Update(hWnd);

	
	ImGui::InputText("##Tags", str0, IM_ARRAYSIZE(str0));

	ImGui::SameLine();
	if (ImGui::Button("Search"))
	{
		std::string data = str0;

		OnSearchInit(data);
	}
	ImGui::SameLine();
	if (ImGui::Button("Clear"))
	{

		OnClearResult();
	}


//	ImGui::End();
}
