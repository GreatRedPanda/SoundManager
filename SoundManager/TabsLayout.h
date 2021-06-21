#pragma once
#include "TabBase.h"

#include <map>

struct TabNeighbours
{


	TabBase* up;
	TabBase* down;
	TabBase* left;
	TabBase* right;

	TabBase* upLeft;
	TabBase* upRight;
	TabBase* downLeft;
	TabBase* downRight;

};
class TabsLayout
{

	std::map<TabBase*, TabNeighbours*> connections =  std::map<TabBase*, TabNeighbours*> ();

public:
	void AddTabLayout(TabBase* tab, TabNeighbours* neighbours)
	{
		connections.insert(std::make_pair(tab, neighbours));
	}
	void SetSizes(TabBase *resizingTab, int draggedSize, ImVec2 resizeAmount)
	{
		TabNeighbours *neibs = connections.at(resizingTab);
		ImVec2 oldSizeT = resizingTab->GetSize();
		ImVec2 oldPosT = resizingTab->GetPosition();
		if (draggedSize == 0) //вверх
		{
			
			ImVec2 oldSize=neibs->up->GetSize();
			if (oldSize.y + resizeAmount.y > 0.3f)
			{
				resizingTab->SetPosition(ImVec2(oldPosT.x, oldPosT.y + resizeAmount.y));
				resizingTab->SetSize(ImVec2(oldSizeT.x, oldSizeT.y - resizeAmount.y));
				neibs->up->SetSize(ImVec2(oldSize.x, oldSize.y + resizeAmount.y));

				ImVec2 oldSizeR = neibs->right->GetSize();
				ImVec2 oldPosR = neibs->right->GetPosition();
				neibs->right->SetSize(ImVec2(oldSizeR.x, oldSizeR.y - resizeAmount.y));
				neibs->right->SetPosition(ImVec2(oldPosR.x, oldPosR.y + resizeAmount.y));


				/*ImVec2 oldSizeD = neibs->down->GetSize();
				ImVec2 oldPosD = neibs->down->GetPosition();
				neibs->down->SetSize(ImVec2(oldSizeD.x, oldSizeD.y - resizeAmount.y));
				neibs->down->SetPosition(ImVec2(oldPosD.x, oldPosD.y + resizeAmount.y));*/

			}



		


		}
	
	}
};

