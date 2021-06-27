#pragma once
#include "ImGuiAdvanced/ISelectable.h"
#include <string>
#include <irrKlang.h>

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

	 //irrklang::ISoundSource  getSound(irrklang::ISoundEngine& engine)
	 //{
	 //
	 //return engine.getSoundSource()
	 //}

};

