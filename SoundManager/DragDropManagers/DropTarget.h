#pragma once
#ifndef DROP_MANAGER_H
#define DROP_MANAGER_H
#include <strsafe.h> 
#include <shlobj.h> 
#include "IDropGuiTarget.h"
#include "DragManager.h"

typedef bool (*renderLoopUpdate) (bool newFrame);
//typedef  IDropGuiTarget  IDROPGUI;
class DropTarget: public IDropTarget
{
	
	ULONG m_cRef;
	static IDropGuiTarget *item;
	static std::vector<IDropGuiTarget*> items;
public:
	renderLoopUpdate renderUpdate;
	HWND mainWnd;
	DragManager* dragManager;
	DropTarget():m_cRef(1) 
	{
		//CurrentDropManager = this;
	}
	static void GetCurrentGui(IDropGuiTarget*item);
	STDMETHODIMP QueryInterface(REFIID riid, void** ppvObj);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	STDMETHODIMP  DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	STDMETHODIMP DragLeave(void);
	STDMETHODIMP Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	static void AddItem(IDropGuiTarget* item);
	void getHoveredItem();
	//static DropTarget *CurrentDropManager;
};
#endif
