//#include "Utils.h"
//#include <vector>
//#include <algorithm>
////
//std::vector< std::string> StringModif::Split(std::string origin, std::string delimiter)
//{
//
//    std::vector< std::string> result = {};
//    int startIndex = 0;
//    int delimFindIndex = origin.find(delimiter);
//    std::string left = origin;
//    while (delimFindIndex != -1)
//    {
//        std::string part = left.substr(0, delimFindIndex - 1);
//        left = left.substr(delimFindIndex);
//        result.push_back(part);
//        delimFindIndex = left.find(delimiter);
//    }
//
//    return result;
//}
//
// std::string  StringModif::ToLower(std::string origin)
//{
//
//    std::for_each(origin.begin(), origin.end(), [](char& c) {
//        c = ::tolower(c);
//        });
//    return origin;
//}
//
// std::string StringModif::ToUpper(std::string origin)
// {
//
//     std::for_each(origin.begin(), origin.end(), [](char& c) {
//         c = ::toupper(c);
//         });
//     return origin;
// }
////  bool StringSearch::PhrasePartsExists(std::string origin, std::string phrase)
//// {
////
////     std::vector< std::string> words = StringModif::Split(phrase, " ");
////     for (auto& i : words)
////     {
////         int index = FindIndexNoRegister(origin, i);
////         if (index != -1)
////         {
////             return true;
////         }
////     }
////
////     return false;
//// }
////   int StringSearch::FindIndexNoRegister(std::string origin, std::string target)
////  {
////      std::string oNoR = StringModif::ToLower(origin);
////      std::string tNoR = StringModif::ToLower(target);
////      return oNoR.find(tNoR);
////  }