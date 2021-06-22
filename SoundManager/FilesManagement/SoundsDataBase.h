#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <windows.h>
//using namespace  std::filesystem ;
class SoundsDataBase
{
	static std::vector<std::string> filter;
	static SoundsDataBase* dataBase;
public:
	SoundsDataBase()
	{
	
		dataBase = this;
	}
	void Load();
	void Save();
	std::vector<std::wstring>  LoadDirectoryFiles(std::wstring path);
	bool HandleAddedFiles(std::vector<std::wstring> files);
	std::string  HandleAddedFile(std::wstring filePath, bool &isDirectory, bool &isSound);
	static SoundsDataBase* GetSoundDataBase();
	static	bool CheckFileMeta(std::wstring filePath, std::vector<std::string> keyWords);

};

