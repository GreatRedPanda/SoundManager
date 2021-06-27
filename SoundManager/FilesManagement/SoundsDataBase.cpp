#include "SoundsDataBase.h"

#include <iostream>

#include <algorithm>
#include "Utils.h"
#define TAGLIB_STATIC
#include "taglib/tag.h"
#include "taglib/fileref.h"



namespace fs = std::filesystem;
SoundsDataBase* SoundsDataBase::dataBase=nullptr;
std::vector<std::string> SoundsDataBase::filter = { ".mp3", ".wav", ".m4p", ".ogg"};
//_stdcall 
void SoundsDataBase::Load()
{
}
void SoundsDataBase::Save()
{
}
std::vector<std::wstring>  SoundsDataBase::LoadDirectoryFiles(std::wstring path)
{
    fs::path dir(path);
    fs::directory_iterator dirIt = fs::directory_iterator(dir);
    std::vector<std::wstring> result = std::vector<std::wstring>();
    for (auto it = fs::begin(dirIt); it != fs::end(dirIt); ++it)
    {
        fs::path file = (*it).path();
        if (std::filesystem::is_directory(file))
        {
            std::vector<std::wstring> resultFromDir =  LoadDirectoryFiles(file.wstring());
            result.insert(result.end(), resultFromDir.begin(), resultFromDir.end());

        }
        else
        {
            std::string ext = file.extension().string();
            std::for_each(ext.begin(), ext.end(), [](char& c) {
                c = ::tolower(c);
                });
            auto found = std::find(filter.begin(), filter.end(), ext);
             bool isSound = found != filter.end();
             if (isSound)
             {
                 result.push_back(file.wstring());
             }

        }
    }
    return result;
}
bool SoundsDataBase::HandleAddedFiles(std::vector<std::wstring> files)
{
    return false;
}

std::string SoundsDataBase::HandleAddedFile(std::wstring filePath, bool& isDirectory, bool& isSound)
{
  /*  boost::filesystem::path boostPath(filePath);

    boost::filesystem::file_status statis = boost::filesystem::status(boostPath);*/
    
    fs::path p(filePath);
    std::string ext=   p.extension().string();
    std::string fn = p.filename().string();
    isDirectory =fs::is_directory(p);
    std::for_each(ext.begin(), ext.end(), [](char& c) {
        c = ::tolower(c);
    });
    auto found = std::find(filter.begin(), filter.end(), ext);
    isSound = found!=filter.end();


  
 
    return fn;

}

SoundsDataBase* SoundsDataBase::GetSoundDataBase()
{
    return dataBase;
}
char* getSamples(std::wstring filePath)
{
    TagLib::FileRef fr(filePath.c_str());
    //TagLib::IOStream::
    TagLib::ByteVector b=fr.file()->readBlock(10);

    
    return  b.data();
}
bool SoundsDataBase::CheckFileMeta(std::wstring filePath, std::vector<std::string> keyWords)
{
    std::string keyWord = keyWords[0];
    TagLib::FileRef fr(filePath.c_str());
    
    ////TagLib::IOStream::
    //TagLib::ByteVector b = fr.file()->readBlock(20);
    //char* d = b.data();
    //for(int i = 0; i < 20; i++)
    //{
    //    int k = *d;
    //    d++;
    //}
    //getSamples(filePath);
    //TagLib::String name = fr.file()->name().toString();
    //TagLib::String artist = fr.tag()->artist();
    //TagLib::String album = fr.tag()->album();
   
   std::wstring name = fr.file()->name().wstr();
   // int hasInName = fr.file()->name().toString().find(keyWord);
  //fr.file()->readBlock(1000);
   // hasInName = StringSearch::PhrasePartsExists(name, keyWord);
    if (StringSearch::PhrasePartsExists(name, keyWord))
        return true;
    int hasInGenre = fr.tag()->genre().find(keyWord);
    if (hasInGenre != -1)
        return true;
    int hasInArtist = fr.tag()->artist().find(keyWord);
    if (hasInArtist != -1)
        return true;
    int hasInAlbum = fr.tag()->album().find(keyWord);
    if (hasInAlbum != -1)
        return true;
//    std::cout << (fr.tag()->isEmpty()) << std::endl;

    return false;
}
