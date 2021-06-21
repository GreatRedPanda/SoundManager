#pragma once
#ifndef DRAG_MANAGER_H
#define DRAG_MANAGER_H
#include <strsafe.h> 
#include <shlobj.h> 
#include "IDragGuiTarget.h"
#include <ShlDisp.h>
//typedef IDragGuiTarget idgt;



class CTinyDataObject : public IDataObject, public IDataObjectAsyncCapability
{

private:
    enum {
        DATA_TEXT,
        DATA_NUM,
        DATA_INVALID = -1,
    };
    int GetDataIndex(const FORMATETC* pfe);


private:
    bool asyncOPStarted = false;
    bool inAsyncMode;
    ULONG m_cRef;
    FORMATETC m_rgfe[DATA_NUM];

public:
    STDMETHODIMP QueryInterface(REFIID riid, void** ppvObj);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    // IDataObject
    STDMETHODIMP GetData(FORMATETC* pfe, STGMEDIUM* pmed);
    STDMETHODIMP GetDataHere(FORMATETC* pfe, STGMEDIUM* pmed);
    STDMETHODIMP QueryGetData(FORMATETC* pfe);
    STDMETHODIMP GetCanonicalFormatEtc(FORMATETC* pfeIn,
        FORMATETC* pfeOut);
    STDMETHODIMP SetData(FORMATETC* pfe, STGMEDIUM* pmed,
        BOOL fRelease);
    STDMETHODIMP EnumFormatEtc(DWORD dwDirection,
        LPENUMFORMATETC* ppefe);
    STDMETHODIMP DAdvise(FORMATETC* pfe, DWORD grfAdv,
        IAdviseSink* pAdvSink, DWORD* pdwConnection);
    STDMETHODIMP DUnadvise(DWORD dwConnection);
    STDMETHODIMP EnumDAdvise(LPENUMSTATDATA* ppefe);
    CTinyDataObject();
    // Унаследовано через IDataObjectAsyncCapability
    STDMETHODIMP SetAsyncMode(BOOL fDoOpAsync) ;
    STDMETHODIMP GetAsyncMode(BOOL* pfIsOpAsync) ;
    STDMETHODIMP StartOperation(IBindCtx* pbcReserved) ;
    STDMETHODIMP InOperation(BOOL* pfInAsyncOp) ;
    STDMETHODIMP EndOperation(HRESULT hResult, IBindCtx* pbcReserved, DWORD dwEffects) ;
};




class CDropSource : public IDropSource
{
private:
    ULONG m_cRef;
public:
    STDMETHODIMP QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState);
    STDMETHODIMP GiveFeedback(DWORD dwEffect);
    STDMETHODIMP QueryInterface(REFIID riid, void** ppvObj);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    CDropSource();

    
};
class DragManager
{

public:
    HWND mainWnd;
    IDragGuiTarget* currentItem;
    DragManager(HWND hwnd)
    {
        mainWnd = hwnd;
        MainDragManager = this;
    }

    HRESULT GetUIObjectOfFile(HWND hwnd, LPCWSTR pszPath, REFIID riid, void** ppv);
    void BegingDrag(IDragGuiTarget* draggingItem);
    static void SetDraggingItem(IDragGuiTarget* draggingItem);
    void startDrag(IDataObject *pdto);
    static DragManager* MainDragManager;
};

#endif
