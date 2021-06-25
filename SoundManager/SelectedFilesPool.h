#pragma once
#include "ImGuiAdvanced/ISelectable.h"
#include <string>


/// <summary>
/// TODO:
/// select files with shift 
/// connect with drag manager (multiple files drag)
/// queue to play files
/// </summary>
 class SelectedFilesPool
{
	
	 ISelectable* selectedFile;
public:
	static SelectedFilesPool* Pool;
	

	 void AddSelectedFile(ISelectable* file);
	 std::wstring GetSelectedFile();



};

