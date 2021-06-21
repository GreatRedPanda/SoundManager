#include "DragManager.h"
#include <iostream>
#include"ImGui/imgui.h"
#include <future>





int CTinyDataObject::GetDataIndex(const FORMATETC* pfe)
{
    for (int i = 0; i < ARRAYSIZE(m_rgfe); i++) {
        if (pfe->cfFormat == m_rgfe[i].cfFormat &&
            (pfe->tymed & m_rgfe[i].tymed) &&
            pfe->dwAspect == m_rgfe[i].dwAspect &&
            pfe->lindex == m_rgfe[i].lindex) {
            return i;
        }
    }
    return DATA_INVALID;
}

HRESULT CreateHGlobalFromBlob(const void* pvData, SIZE_T cbData, UINT uFlags, HGLOBAL* phglob)
{
    HGLOBAL hglob = GlobalAlloc(uFlags, cbData);
    if (hglob) {
        void* pvAlloc = GlobalLock(hglob);
        if (pvAlloc) {
            CopyMemory(pvAlloc, pvData, cbData);
            GlobalUnlock(hglob);
        }
        else {
            GlobalFree(hglob);
            hglob = NULL;
        }
    }
    *phglob = hglob;
    return hglob ? S_OK : E_OUTOFMEMORY;
}

HRESULT CTinyDataObject::QueryInterface(REFIID riid, void** ppvObj)
{
    if (!ppvObj)
        return E_POINTER;
    if (IsEqualIID(riid, IID_IDataObject) || IsEqualIID(riid, IID_IUnknown)) {
        *ppvObj = static_cast<IDataObject*>(this);
    }
    else if (inAsyncMode && riid== IID_IDataObjectAsyncCapability )
        //       IsEqualIID(riid, __uuidof(IDataObjectAsyncCapability))
    {
        *ppvObj = static_cast<IDataObjectAsyncCapability*>(this);
    }
    else {http://www.microsoft.com/
        *ppvObj = NULL;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
  /*  IUnknown* punk = NULL;
    if (riid == IID_IUnknown) {
        IDataObject *t= static_cast<IDataObject*>(this);
        punk = static_cast<IUnknown*>(t);
    }
    else if (riid == IID_IDataObject) {
        punk = static_cast<IDataObject*>(this);
    }
    else if (riid == IID_AsyncIUnknown) {
        punk = static_cast<IDataObjectAsyncCapability*>(this);
    }
    *ppvObj = punk;
    if (punk) {
        punk->AddRef();
        return S_OK;
    }
    else {
        return E_NOINTERFACE;
    }*/
}
ULONG CTinyDataObject::AddRef()
{
    return ++m_cRef;

}
ULONG CTinyDataObject::CTinyDataObject::Release()
{

    ULONG cRef = --m_cRef;
    if (cRef == 0) delete this;
    return cRef;

}
// IDataObject
CHAR c_szURL[] = "http://www.microsoft.com/";
HRESULT CTinyDataObject::GetData(FORMATETC* pfe, STGMEDIUM* pmed)
{
    // CHAR c_szURL[] = "http://www.microsoft.com/";
    ZeroMemory(pmed, sizeof(*pmed));
    switch (GetDataIndex(pfe)) {
    case DATA_TEXT:
        pmed->tymed = TYMED_HGLOBAL;
        return CreateHGlobalFromBlob(c_szURL, sizeof(c_szURL),
            GMEM_MOVEABLE, &pmed->hGlobal);
    }
    return DV_E_FORMATETC;
}
HRESULT CTinyDataObject::GetDataHere(FORMATETC* pfe, STGMEDIUM* pmed)
{
    return E_NOTIMPL;
}
HRESULT CTinyDataObject::QueryGetData(FORMATETC* pfe)
{
    return GetDataIndex(pfe) == DATA_INVALID ? S_FALSE : S_OK;

}
HRESULT CTinyDataObject::GetCanonicalFormatEtc(FORMATETC* pfeIn, FORMATETC* pfeOut)
{
    *pfeOut = *pfeIn;
    pfeOut->ptd = NULL;
    return DATA_S_SAMEFORMATETC;

}
HRESULT CTinyDataObject::SetData(FORMATETC* pfe, STGMEDIUM* pmed, BOOL fRelease)
{
    return E_NOTIMPL;
}
HRESULT CTinyDataObject::EnumFormatEtc(DWORD dwDirection, LPENUMFORMATETC* ppefe)
{
    if (dwDirection == DATADIR_GET) {
        return SHCreateStdEnumFmtEtc(ARRAYSIZE(m_rgfe), m_rgfe, ppefe);
    }
    *ppefe = NULL;
    return E_NOTIMPL;
}
HRESULT CTinyDataObject::DAdvise(FORMATETC* pfe, DWORD grfAdv, IAdviseSink* pAdvSink, DWORD* pdwConnection)
{
    return OLE_E_ADVISENOTSUPPORTED;
}
HRESULT CTinyDataObject::DUnadvise(DWORD dwConnection)
{
    return OLE_E_ADVISENOTSUPPORTED;
}
HRESULT CTinyDataObject::EnumDAdvise(LPENUMSTATDATA* ppefe)
{
    return OLE_E_ADVISENOTSUPPORTED;
}
void SetFORMATETC(FORMATETC* pfe, UINT cf, TYMED tymed = TYMED_HGLOBAL, LONG lindex = -1,
    DWORD dwAspect = DVASPECT_CONTENT, DVTARGETDEVICE* ptd = NULL)
{
    pfe->cfFormat = (CLIPFORMAT)cf;
    pfe->tymed = tymed;
    pfe->lindex = lindex;
    pfe->dwAspect = dwAspect;
    pfe->ptd = ptd;
}
CTinyDataObject::CTinyDataObject() : m_cRef(1)
{
    SetFORMATETC(&m_rgfe[DATA_TEXT], CF_TEXT);
}

HRESULT  CTinyDataObject::SetAsyncMode(BOOL fDoOpAsync)
{
    inAsyncMode = fDoOpAsync;
  
    return S_OK;
}
HRESULT  CTinyDataObject::GetAsyncMode(BOOL* pfIsOpAsync)
{
    *pfIsOpAsync = inAsyncMode;
    return S_OK;
}
HRESULT  CTinyDataObject::StartOperation(IBindCtx* pbcReserved)
{
    if(inAsyncMode)
    asyncOPStarted = true;
    return S_OK;
}
HRESULT  CTinyDataObject::InOperation(BOOL* pfInAsyncOp)
{
    *pfInAsyncOp = asyncOPStarted;
    return S_OK;
}
HRESULT  CTinyDataObject::EndOperation(HRESULT hResult, IBindCtx* pbcReserved, DWORD dwEffects)
{
    asyncOPStarted = false;
    return S_OK;
}



















CDropSource::CDropSource() :m_cRef(1)
{

}

HRESULT  CDropSource::QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState)
{
    std::cout<< grfKeyState << "  DRAGGG \n";

   // WH_GETMESSAGE
    if (fEscapePressed) return DRAGDROP_S_CANCEL;

    if (!(grfKeyState & (MK_LBUTTON | MK_RBUTTON)))
        return DRAGDROP_S_DROP;


    return S_OK;
}
HRESULT  CDropSource::GiveFeedback(DWORD dwEffect)
{
    return DRAGDROP_S_USEDEFAULTCURSORS;
}
ULONG  CDropSource::AddRef()
{
    return ++m_cRef;
}
ULONG  CDropSource::Release()
{
    ULONG cRef = --m_cRef;
    if (cRef == 0) delete this;
    return cRef;

}
HRESULT  CDropSource::QueryInterface(REFIID riid, void** ppvObj)
{
    IUnknown* punk = NULL;
    if (riid == IID_IUnknown) {
        punk = static_cast<IUnknown*>(this);
    }
    else if (riid == IID_IDataObject) {
        punk = static_cast<IDropSource*>(this);
    }
    *ppvObj = punk;
    if (punk) {
        punk->AddRef();
        return S_OK;
    }
    else {
        return E_NOINTERFACE;
    }
}


DragManager* DragManager::MainDragManager = nullptr;
HRESULT DragManager::GetUIObjectOfFile(HWND hwnd, LPCWSTR pszPath, REFIID riid, void** ppv)
{
    *ppv = NULL;
    HRESULT hr;
    LPITEMIDLIST pidl;
    SFGAOF sfgao;
    if (SUCCEEDED(hr = SHParseDisplayName(pszPath, NULL, &pidl, 0, &sfgao))) {
        IShellFolder* psf;
        LPCITEMIDLIST pidlChild;
        if (SUCCEEDED(hr = SHBindToParent(pidl, IID_IShellFolder,
            (void**)&psf, &pidlChild))) {
            hr = psf->GetUIObjectOf(hwnd, 1, &pidlChild, riid, NULL, ppv);
            psf->Release();
        }
        CoTaskMemFree(pidl);
    }
    return hr;
}

void DragManager::BegingDrag(IDragGuiTarget* draggingItem)
{

    if (currentItem == nullptr)
        return;
    // auto  taskDrag = std::async(std::launch::async, &DragManager::BegingDrag,&dragManager, dragManager.currentItem);
    //idgt* draggingItem
    IDataObject* pdto;// = new CTinyDataObject();
    GetUIObjectOfFile(mainWnd, currentItem->GetPath(), IID_IDataObject, (void**)&pdto);
    if(pdto)
    {
        /*auto task = std::async(std::launch::async,
           &DragManager::startDrag, this, pdto);*/
      //  task.wait();
       IDataObjectAsyncCapability *pAsyncOp;
            IDropSource* pds = new CDropSource();
            if (pds) {
                DWORD dwEffect;
             //   dynamic_cast<CTinyDataObject*>(pdto)->SetAsyncMode(true);
               /* if (SUCCEEDED(pdto->QueryInterface(IID_IDataObjectAsyncCapability,  pAsyncOp))) {
                    pAsyncOp->SetAsyncMode(VARIANT_TRUE);
                }*/

                HRESULT result = DoDragDrop(pdto, pds,
                    DROPEFFECT_COPY | DROPEFFECT_LINK ,
                    &dwEffect);

                if(result== DRAGDROP_S_DROP)
                {
                    //ImGui::GetIO().MouseReleased[0] = true;
                    currentItem->EndDrag();
                  /*  if(dwEffect == DROPEFFECT_NONE)  
                            draggingItem->EndDrag();*/
                   
                    if (dwEffect & DROPEFFECT_MOVE)
                    {
                       // draggingItem->EndDrag();
                        // DeleteFile(TEXT("C:\\Users\\Office_1\\231.txt"));
                    }
                    currentItem = nullptr;
                }
                pds->Release();
            }
            pdto->Release();
    }
}

void DragManager::SetDraggingItem(IDragGuiTarget* draggingItem)
{
    MainDragManager->currentItem = draggingItem;
    //idgt* draggingItem
   // MainDragManager->BegingDrag(draggingItem);
}

void DragManager::startDrag(IDataObject* pdto)
{
    IDropSource* pds = new CDropSource();
    if (pds) {
        DWORD dwEffect;
        HRESULT result = DoDragDrop(pdto, pds,
            DROPEFFECT_COPY | DROPEFFECT_LINK,
            &dwEffect);
        if (result == DRAGDROP_S_DROP)
        {
            currentItem->EndDrag();
            if (dwEffect & DROPEFFECT_MOVE)
            {
               
            }
            currentItem = nullptr;
        }
        pds->Release();
    }
}
