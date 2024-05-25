#pragma once
#include <cstring>
#include <string>
#include <random>
#include <vector>
#include <string_view>
#include <cmath>
#include <cstdlib>

#include <ProtonSDK/RTTEX.h>

class Utils
{
public:
    static std::vector<std::string> StringTokenize(const std::string& text, const std::string& delim = "|");
    static std::vector<std::string> SplitString(const std::string& text, const std::string& delim);
    static bool SeparateString (const char str[], int num, char delim, char* pResult);
    static std::string SeparateStringSTL(std::string input, int index, char delim);
    static void StringReplace(const std::string& what, const std::string& with, std::string& in);
    static bool IsStringNumber(const std::string& str);

	static void RemoveBadCharacters(std::string& str);
	static void TrimSpacesLeftOfString(std::string& s);
	static void TrimSpacesRightOfString(std::string& s);
    static void TrimSpaceBothSidesOfString(std::string& s);
    static void RemoveExtraSpaces(std::string& str);
    static void RemoveSpaces(std::string& str);

    static uint32_t HashString(const void* pMem, uint32_t dataLength);
    static int32_t GenerateUniqueTag(const std::string& name, const std::string& relativeId, const std::string& key);
    static std::string ResolveIPAddress(const uint32_t& ip);
    static std::string NormalizeString(const std::string& str);

    static bool SaveToFile(const std::string& fName, const std::string& content);
    static unsigned int GetHashOfFile(const std::string& fName);

};