#pragma once
#include <wtypes.h>
class Input
{
	bool isMousedown;
	float DragDistance;
public:

	Input()
	{
		InputData = this;
	}
	static Input* InputData;
	 bool MouseDrag()
	{}
	 void Update(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	 
	 


	 }
};

