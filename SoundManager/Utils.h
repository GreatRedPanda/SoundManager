#pragma once
#include <string>
#include <stringapiset.h>
#include <vector>
#include <algorithm>

 class StringConvert
{
public:
	static std::string StringToUTF8(std::string origin)
	{

        int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, origin.c_str(),
            origin.length(), nullptr, 0);
        std::wstring utf16_str(size, '\0');
        MultiByteToWideChar(CP_ACP, MB_COMPOSITE, origin.c_str(),
            origin.length(), &utf16_str[0], size);

        int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
            utf16_str.length(), nullptr, 0,
            nullptr, nullptr);
        std::string utf8_str(utf8_size, '\0');
        WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
            utf16_str.length(), &utf8_str[0], utf8_size,
            nullptr, nullptr);
        return utf8_str;
	}
    static std::string WStringToUTF8(std::wstring origin)
    {
        int utf8_size = WideCharToMultiByte(CP_UTF8, 0, origin.c_str(),
            origin.length(), nullptr, 0,
            nullptr, nullptr);
        std::string utf8_str(utf8_size, '\0');
        WideCharToMultiByte(CP_UTF8, 0, origin.c_str(),
            origin.length(), &utf8_str[0], utf8_size,
            nullptr, nullptr);

        return utf8_str;
    }
    static
        std::wstring StringToUTF16(const std::string& str)
    {
        if (str.empty())
            return std::wstring();

        size_t charsNeeded = ::MultiByteToWideChar(CP_UTF8, 0,
            str.data(), (int)str.size(), NULL, 0);
        if (charsNeeded == 0)
            return L" ";

        std::vector<wchar_t> buffer(charsNeeded);
        int charsConverted = ::MultiByteToWideChar(CP_UTF8, 0,
            str.data(), (int)str.size(), &buffer[0], buffer.size());
        if (charsConverted == 0)
            return L" ";

        return std::wstring(&buffer[0], charsConverted);
    }


};
 class StringModif
 {
 public:
     static std::vector< std::wstring> Split(std::wstring origin, std::wstring delimiter)
     {
       
         std::vector< std::wstring> result = {};
         int startIndex = 0;
         int delimFindIndex = origin.find(delimiter);
         std::wstring left = origin;
         while (delimFindIndex != -1)
         {
             std::wstring part = left.substr(0, delimFindIndex - 1);
             int next = delimFindIndex + 1;
             if(next!=left.size()-1)
             left = left.substr(next);


             result.push_back(part);
             delimFindIndex = left.find(delimiter);
         }
         if(left!=L"" && left!=L" ")
         result.push_back(left);
         return result;
     }
     
     static std::wstring ToLower(std::wstring origin)
     {
    
        std::for_each(origin.begin(), origin.end(), [](wchar_t& c) {
            c = ::tolower(c);
            });
        return origin;
    }
     static std::wstring ToUpper(std::wstring origin)
     {

         std::for_each(origin.begin(), origin.end(), [](wchar_t& c) {
             c = ::toupper(c);
             });
         return origin;
     }
 };

 class StringSearch
{
public:
    static bool PhrasePartsExists(std::wstring origin, std::string phrase)
    {
        std::wstring phraseW = StringConvert::StringToUTF16(phrase);
     std::vector< std::wstring> words = StringModif::Split(phraseW, L" ");
     for (auto& i : words)
     {
         int index = FindIndexNoRegister(origin, i);
         if (index != -1)
         {
             return true;
         }
     }

     return false;
 }
    static int FindIndexNoRegister(std::wstring origin, std::wstring target)
          {
      std::wstring oNoR = StringModif::ToLower(origin);
      std::wstring tNoR = StringModif::ToLower(target);
      return oNoR.find(tNoR);
  }

};
