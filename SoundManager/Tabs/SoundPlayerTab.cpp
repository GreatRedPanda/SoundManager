#include "SoundPlayerTab.h"
#include <vector>
#include "ImGui/implot.h"
void SoundPlayerTab::UpdateTabItems()
{


	ImGui::Button("Play");
	if (ImGui::IsItemClicked(0))
	{
		OnSoundPlay();
	}
	ImGui::SameLine();
	ImGui::Button("Stop");
	if (ImGui::IsItemClicked(0))
	{
		OnSoundStop();
	}
	ImVec2 btnSize = ImGui::GetItemRectSize();
	
	//ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2(0, 0));
	//if (ImPlot::BeginPlot("##sound", 0, 0, ImVec2(GetSizeScaled().x-15, GetSizeScaled().y - btnSize.y - 35),
	//	ImPlotFlags_CanvasOnly, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)
	//	
	//	)
	//{
	////	ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
	//	//ImPlot
	///*	ImPlot::PushColormap("Hot");
	//	ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);*/
	//	//ImPlotCol e;
	//	
	////	ImPlot::PushStyleColor(ImPlotCol_PlotBg, ImVec4(0.92f, 0.92f, 0.95f, 1.00f));

	//	ImPlot::PushColormap("Hot");
	//	ImPlot::PushStyleVar(ImPlotStyleVar_PlotBorderSize, 0);
	//	ImPlot::EndPlot();
	//}
	//ImPlot::PopStyleVar();
	if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
	{
		static float selection[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };// { 0, 1, 1, 1 };
		float* samples = player.GetSamples();
		char overlay[32];
		ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2(0, 0));
		if (ImPlot::BeginPlot("##sound", 0, 0, ImVec2(GetSizeScaled().x - 15, GetSizeScaled().y - btnSize.y - 35),
			ImPlotFlags_CanvasOnly, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)
			)
		{

		//	ImPlot::PushColormap("Hot");
			ImPlot::PushStyleVar(ImPlotStyleVar_PlotBorderSize, 0);
			ImPlot::PlotLine("##wavefront", samples, player.GetSamplesSize());
			ImPlot::PlotLine("##selection", selection, IM_ARRAYSIZE(selection));
			ImPlot::EndPlot();

		}
		ImPlot::PopStyleVar();
		if (ImGui::IsItemClicked(0))
		{
		}
		if (ImGui::IsItemHovered())
		{
			
		}

	}


	
}



//if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
//{
//	irrklang::ISoundSource* s = player.getSound();
//	 int len = s->getAudioFormat().getSampleDataSize();
//	 irrklang::ESampleFormat f = s->getAudioFormat().SampleFormat;
//	
//	 
//	//int length= player.getSound().get
//	void* pointer =s->getSampleData();

//	int size = sizeof(pointer);

//	len = len / size;
//	int* charPtr1 = static_cast<int*>(pointer);
//	float* fPtr1 = static_cast<float*>(pointer);
//	//float testArr[]= { 2,42,4,2,4,5,2,5,2,5,6,7,8 };
////	void* d = testArr;
///*	for (int i = 0; i < len; i++)
//	{
//		float l = *fPtr1;
//		int c = *charPtr1;
//		charPtr1++;
//		fPtr1++;
//		
//	}*/
//	////static float (*array)[150] = (float(*)[150])pointer;
//	//std::vector <float> arr = std::vector <float>(len);
//
//	//memcpy(arr, (float**)pointer, sizeof arr);
//	char overlay[32];

///*	void ImGui::PlotLines(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
//	{
//		PlotEx(ImGuiPlotType_Lines, label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
//	}*/
//	ImGui::PlotLines("##Lines", &vals, pointer, len, 0, overlay);
//		//graph_size::ImVec2(GetSizeScaled().x, GetSizeScaled().y - btnSize.y - 35));
//}
// 