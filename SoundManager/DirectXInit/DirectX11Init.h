#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
class DirectX11Init
{
private:
	//ImGuiIO io;
	//HWND* hwnd;
	static ID3D11Device* g_pd3dDevice;
	static ID3D11DeviceContext* g_pd3dDeviceContext ;
	static IDXGISwapChain* g_pSwapChain ;
	static ID3D11RenderTargetView* g_mainRenderTargetView ;

	// Forward declarations of helper functions
	

public:
	ImGuiContext* context;
	bool CreateDeviceD3D(HWND& hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();



	void CleanupRenderTarget();
	void CreateContext();
	void SetupRenderBackend(HWND hwnd);
	int  Initialize(LPCWSTR wndName, HINSTANCE hInstance,  HWND hwnd);
	void Shutdown(LPCWSTR wndName, HINSTANCE hInstance, HWND hwnd);
	DirectX11Init();
	DirectX11Init(HWND* hWnd);
	void BeginNewFrame();
	void Render();
	void RenderTargetChange(WPARAM wParam, LPARAM lParam);
};

