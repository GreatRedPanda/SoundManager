#include "DropTarget.h"

#include "ImGui/imgui.h"
#include <iostream>
IDropGuiTarget*  DropTarget::item=nullptr;
std::vector<IDropGuiTarget*> DropTarget::items =  std::vector<IDropGuiTarget*>();
void DropTarget::GetCurrentGui(IDropGuiTarget* item)
{
	DropTarget::item = item;
}
HRESULT __stdcall DropTarget::QueryInterface(REFIID riid, void** ppvObject)
{
	IUnknown* punk = NULL;
	if (riid == IID_IUnknown) {
		punk = static_cast<IUnknown*>(this);
	}
	else if (riid == IID_IDataObject) {
		punk = static_cast<IDropTarget*>(this);
	}
	*ppvObject = punk;
	if (punk) {
		punk->AddRef();
		return S_OK;
	}
	else {
		return E_NOINTERFACE;
	}
}

ULONG __stdcall DropTarget::AddRef(void)
{
    return ++m_cRef;
}

ULONG __stdcall DropTarget::Release(void)
{
    ULONG cRef = --m_cRef;
    if (cRef == 0) delete this;
    return cRef;
}

HRESULT __stdcall DropTarget::DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	//SetForegroundWindow(mainWnd);
	*pdwEffect &= DROPEFFECT_COPY;
	return S_OK;
}

HRESULT __stdcall DropTarget::DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	//std::cout << "dropOver\n";
	//ImGui::GetIO().MouseDown[0] = 1;

	renderUpdate(false);
	*pdwEffect &= DROPEFFECT_COPY;
	if (dragManager->currentItem != nullptr)
	{
		bool a = dragManager->currentItem->GetIsApplicationDropAllowed();

		if (!a)
			return 1L;
		IDragGuiTarget* dgt = dynamic_cast<IDragGuiTarget*>(item);
		//IDropGuiTarget *idgt = reinterpret_cast<IDropGuiTarget*>(dragManager->currentItem);
		if (dgt!= nullptr)
		{
			//std::cout << dgt->GetPath() << "    " << dragManager->currentItem->GetPath() << std::endl;
			if (dgt->GetPath() == dragManager->currentItem->GetPath())
			{
				if(!dragManager->currentItem->GetIsSelfDropAllowed())
					return  1L;
			}
		}
	}
	
	if (item!=nullptr && item->IsDropAccepting())
	return S_OK;
	else
	return  1L;// 1L;
}

void DropTarget::getHoveredItem()
{

	for (auto &i: items)
	{
		bool hovered=i->CheckIsMouseOver();
		
	}
}

void DropTarget::AddItem(IDropGuiTarget* item)
{
	items.push_back(item);
}

HRESULT __stdcall DropTarget::DragLeave()
{
	return S_OK;
}

HRESULT __stdcall DropTarget::Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	
	//renderUpdate(false);
	FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stgm;

	if (SUCCEEDED(pDataObj->GetData(&fmte, &stgm)))
	{

		HDROP hdrop = (HDROP)stgm.hGlobal; // or reinterpret_cast<HDROP> if preferred

		
		UINT file_count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
		std::vector<std::wstring> files = std::vector<std::wstring>();
		// we can drag more than one file at the same time, so we have to loop here
		for (UINT i = 0; i < file_count; i++)
		{
			TCHAR szFile[MAX_PATH];
			char fileName[512];
			wchar_t fn[512];
			UINT cch = DragQueryFile(hdrop, i, szFile, MAX_PATH);
			if (cch > 0 && cch < MAX_PATH)
			{
				
				DragQueryFileW(hdrop, i, fn, 512);
				
				files.push_back(fn);
			//	std::cout << fileName << std::endl;
			}
		}
		if (item != nullptr && item->IsDropAccepting())
			item->AcceptFiles(files);
		// we have to release the data when we're done with it
		ReleaseStgMedium(&stgm);

		// notify our application somehow that we've finished dragging the files (provide the data somehow)

	}
	
	
	// trigger MouseUp for button 1 within ImGui

	*pdwEffect &= DROPEFFECT_COPY;
	return S_OK;
}
