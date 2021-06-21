#include "GuiText.h"

void GuiText::Update()
{
	ImGui::Text(name.c_str());
}

void GuiText::AcceptFiles(std::vector<std::wstring> files)
{
}

void GuiText::DrawFileAccept()
{
}
