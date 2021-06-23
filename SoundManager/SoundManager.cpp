#include "ImGUI\imgui.h"
#include "ImGUI\imgui_impl_win32.h"
#include "ImGUI\imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include "DirectXInit\DirectX11Init.h"
#include "Tabs\TabBase.h"
#include "Tabs\FileHierarchyTab.h"
#include "Tabs\SearchTab.h"
#include "Tabs\FilesViewerTab.h"

#include "Tabs\SoundPlayerTab.h"

#include <DragDropManagers\DropTarget.h>
#include "DragDropManagers\DragManager.h"
#include "Tabs\TabsLayout.h"

#include <format>

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
struct InnerWindowOrientation
{


    bool sameLine;
    float maxWidthPercent;
    float maxHeightPercent;

};
DirectX11Init d11Init;
HWND w_HWND;
std::vector<TabBase*> tabs;
std::vector<ImVec2> positions;
std::vector<ImVec2> sizes;
std::vector<InnerWindowOrientation*> flags;
ImGuiIO io;
float scaleCoefX = 20;
float scaleCoefY = 20;
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool render(bool newFrame);
bool renderLoop(bool newFrame,DirectX11Init dxInit, HWND hwnd, std::vector<TabBase*> tabs);
// Main code
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
int main(int, char**)
{

    //int, char**
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Sound search"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);
    d11Init = DirectX11Init(&hwnd);
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }
   // d11Init.Initialize(wc.lpszClassName, wc.hInstance, hwnd);
    // Initialize Direct3D
    OleInitialize(NULL);

    

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
     io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags  |=console
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
   // ImVector<ImWchar> ranges;
   // ImFontGlyphRangesBuilder builder;
  ///  builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic()); // Add one of the default ranges
 //   builder.BuildRanges(&ranges);                          // Build the final result (ordered ranges with all the unique characters submitted)

   
    io.Fonts->AddFontFromFileTTF("tahoma.ttf", 15, NULL, io.Fonts->GetGlyphRangesCyrillic());
   // io.Fonts->Build();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
   /* d11Init.CreateContext();
    d11Init.SetupRenderBackend(hwnd);*/

    //bool show_demo_window = true;
    //bool show_another_window = false;
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    w_HWND = hwnd;
    SearchTab searchTab = SearchTab("Search", ImVec2(0, 0.5f), ImVec2(20,2));
    InnerWindowOrientation winOr_st = InnerWindowOrientation();
    winOr_st.sameLine = false;
    winOr_st.maxWidthPercent = 1;  winOr_st.maxHeightPercent = 2/ scaleCoefY;


    FileHierarchyTab fhTab = FileHierarchyTab("My Folders", ImVec2(0,2), ImVec2(8,10));
    InnerWindowOrientation winOr_fht = InnerWindowOrientation();
    winOr_fht.sameLine = false;
    winOr_fht.maxWidthPercent = 8/ scaleCoefX; winOr_fht.maxHeightPercent = 13 / scaleCoefY;


    FilesViewerTab fViewerTab = FilesViewerTab("Sounds", ImVec2(8, 2), ImVec2(12, 10));
    InnerWindowOrientation winOr_fvt = InnerWindowOrientation();
    winOr_fvt.sameLine = true;
    winOr_fvt.maxWidthPercent = 12 / scaleCoefX; winOr_fvt.maxHeightPercent = 13 / scaleCoefY;


    SoundPlayerTab soundPlayerTab = SoundPlayerTab("Player", ImVec2(0, 12), ImVec2(20, 8));
    InnerWindowOrientation winOr_spt = InnerWindowOrientation();
    winOr_spt.sameLine = false;
    winOr_spt.maxWidthPercent = 1; winOr_spt.maxHeightPercent = 5 / scaleCoefY;
    positions = { ImVec2(0, 0.5f) , ImVec2(0,2),ImVec2(8, 2),  ImVec2(0, 12) };
    sizes= { ImVec2(20, 2) , ImVec2(8,10),ImVec2(12, 10),  ImVec2(20, 5) };
    flags = { &winOr_st,&winOr_fht,&winOr_fvt,& winOr_spt };
    // Main loop
    //bool done = false;

    DragManager dragManager= DragManager(hwnd);
    DropTarget dm;
    
    RegisterDragDrop(hwnd, &dm);
    dm.mainWnd = hwnd;
    dm.renderUpdate = render;
    tabs = { &searchTab, &fhTab ,&fViewerTab ,&soundPlayerTab };
  
    fhTab.OnGetSearchResult.connect(boost::bind(&FilesViewerTab::PrintSearchResult, &fViewerTab, boost::placeholders::_1));
    searchTab.OnSearchInit.connect(boost::bind(&FileHierarchyTab::SearchInit, &fhTab,boost::placeholders::_1));
    searchTab.OnClearResult.connect(boost::bind(&FilesViewerTab::ClearResult, &fViewerTab));
    dm.dragManager = &dragManager;


    TabsLayout tabsLayout = TabsLayout();

    TabNeighbours fHiTabNbs = TabNeighbours();
    fHiTabNbs.up = &searchTab;
    fHiTabNbs.down = &soundPlayerTab;
    fHiTabNbs.right = &fViewerTab;

    tabsLayout.AddTabLayout(&fhTab, &fHiTabNbs);
    fhTab.OnResizing.connect(boost::bind(&TabsLayout::SetSizes, &tabsLayout,
        boost::placeholders::_1,
        boost::placeholders::_2, boost::placeholders::_3));
    bool done = false;
    while (!done)
    {          
       // SetFocus(hwnd);
       // SetActiveWindow(hwnd);
      
      
      done=  render(true);




      //  render(true);

        //if (dragManager.currentItem != nullptr)
        //{

        //   /* auto  taskDrag = std::async(std::launch::async, &DragManager::BegingDrag,&dragManager, dragManager.currentItem);*/
         dragManager.BegingDrag(dragManager.currentItem);
        //}
    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

  //  d11Init.Shutdown(wc.lpszClassName, wc.hInstance, hwnd);
    RevokeDragDrop(hwnd);
    OleUninitialize();
    return 0;
}
bool render(bool newFrame)
{
  return  renderLoop(newFrame,d11Init, w_HWND, tabs);
}
bool renderLoop(bool newFrame, DirectX11Init dxInit, HWND hwnd, std::vector<TabBase*> tabs)
{
   
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_MOUSEWHEEL)
            std::cout << "WM_MOUSEWHEEL\n";
        if (msg.message == WM_QUIT)
            return true;

    }
   /* if (done)
        break;*/

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    if (GetFocus() != hwnd)
    {
        RECT rect;
        GetWindowRect(hwnd, &rect);
        POINT p;
        (GetCursorPos(&p));
        ImGui::GetIO().MousePos = ImVec2(p.x - rect.left - 8, p.y - rect.top - 31);
    }
  //  std::cout << ImGui::GetIO().MousePos.x << "   " << ImGui::GetIO().MousePos.y << "\n";
    ImGui::NewFrame();
    //  dxInit.BeginNewFrame();

    ImVec2 scale = TabBase::GetVieportScale(ImVec2(scaleCoefX, scaleCoefY));
    ImGui::BeginMainMenuBar();
    ImGui::EndMainMenuBar();


    ImVec2 sizeBar = ImGui::GetItemRectSize();

    ImVec2 prevPos = ImVec2(0, 0);
    ImVec2 prevSize = ImVec2(sizeBar.x / scale.x, sizeBar.y / scale.y);
    float prevY = sizeBar.y / scale.y;
    int num = 0;
    for (auto& i : tabs)
    {


        InnerWindowOrientation* winOr = flags[num];
        if (winOr->sameLine)
        {
            prevSize.y = prevY;
        }
        else
        {

            prevSize.x = 0;

        }
        ImVec2 size = ImVec2(scaleCoefX * winOr->maxWidthPercent, scaleCoefY * winOr->maxHeightPercent);

        i->SetPosition(prevSize);
        i->SetSize(size);

        prevY = prevSize.y;

        prevSize = ImVec2(size.x + prevSize.x, size.y + prevSize.y);

        i->Update(hwnd);

        num++;
    }
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    g_pSwapChain->Present(0, 0); // Present with vsync
    return false;
}


bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   // int delta = GET_WHEEL_DELTA_WPARAM(wParam);
   // std::cout << "WPR\n";
  /*  if(d11Init.context!=nullptr)
    ImGui::SetCurrentContext(d11Init.context);*/
  //ImGui::SetCurrentContext(ImGui::GetMa)
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
   /* else
        std::cout << "WND PROC\n";*/
  /*  HDROP hDrop;
    POINT pt;
    int cnt;
    char fileName[512];
    char szWndCaption[512];*/
    //strstream names;
    switch (msg)
    {
    case WM_MOUSEMOVE:
    {     
        std::cout << "wheel\n";
    }
    break;
    case WM_RBUTTONDOWN:

        break;
    case WM_CREATE:
    {
       // d11Init.RenderTargetChange(wParam, lParam);
    }
    break;
    case WM_SIZE:
    {
        /*d11Init.RenderTargetChange(wParam, lParam);*/
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
    }
       break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
