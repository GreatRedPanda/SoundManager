#include "SelectedFilesPool.h"

SelectedFilesPool* SelectedFilesPool::Pool = new SelectedFilesPool();
void SelectedFilesPool::AddSelectedFile(ISelectable* file)
{

    selectedFile = file;
}

std::wstring SelectedFilesPool::GetSelectedFile()
{
    if (selectedFile != nullptr)
        return selectedFile->GetData();
    else
        return L"";
}
