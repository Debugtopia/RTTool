#include <chrono>
#include <array>
#include <cassert>
#include <regex>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <ProtonSDK/MiscUtils.h>

std::vector<std::string> Utils::StringTokenize(const std::string& text, const std::string& delim)
{
    std::vector<std::string> result;
    if (text.empty())
        return result;

    size_t start = 0, end = 0;
    while (end != std::string::npos) 
	{
        end = text.find(delim, start);
        result.push_back(text.substr(start, (end == std::string::npos) ? std::string::npos: end - start ));
        start = ((end > (std::string::npos - delim.size())) ? std::string::npos :  end + delim.size());
    }

    return result;
}

std::vector<std::string> Utils::SplitString(const std::string& text, const std::string& delim)
{
    std::size_t startPos = 0, endPos, delimiterLength = delim.length();
    std::string token{};
    std::vector<std::string> ret{};

    while ((endPos = text.find(delim, startPos)) != std::string::npos) 
	{
        token = text.substr(startPos, endPos - startPos);
        startPos = endPos + delimiterLength;
        ret.push_back(token);
    }

    ret.push_back(text.substr(startPos));
    return ret;
}

bool Utils::SeparateString(const char str[], int num, char delim, char* pResult) 
{
    size_t sLen = std::strlen(str);
    int l = 0;
    int c = 0;
    for (unsigned int k = 0; str[k] != 0; k++) 
	{
        if (str[k] == delim) 
		{
            l++;
            if (l == num+1)
                break;

            if (k < sLen) c = 0;
        }

        if (str[k] != delim)
            pResult[c++] = str[k];
    }

    pResult[c] = 0;

    if (l < num) 
	{
        pResult[0] = 0;
        return(false);
    }

    return true;
}

std::string Utils::SeparateStringSTL(std::string input, int index, char delim)
{
    if (input.size() > 4048)
        return "";

    char stInput[4048];
    if (SeparateString(input.c_str(), index, delim, stInput))
        return stInput;

    return "";
}

void Utils::StringReplace(const std::string& what, const std::string& with, std::string& in)
{
    size_t pos = 0;
    size_t whatLen = what.length();
    size_t withLen = with.length();

    while ((pos = in.find(what, pos)) != std::string::npos) 
	{
        in.replace(pos, whatLen, with);
        pos += withLen;
    }
}

bool Utils::IsStringNumber(const std::string& str) 
{
	for (char c : str) 
	{
		if (!std::isdigit(c))
			return false;
	}

	return true;
}

void Utils::RemoveBadCharacters(std::string& str) 
{
	str.erase(std::remove_if(str.begin(), str.end(), [](char c) 
	{
		return !std::isalnum(c) && c != ' ' && c != '!' && c != '"' && c != '#' &&
			c != '$' && c != '%' && c != '&' && c != '\'' && c != '(' && c != ')' &&
			c != '*' && c != '+' && c != ',' && c != '-' && c != '.' && c != '/' &&
			c != ':' && c != ';' && c != '<' && c != '=' && c != '>' && c != '?' &&
			c != '@' && c != '[' && c != '\\' && c != ']' && c != '^' && c != '_' &&
			c != '`' && c != '{' && c != '}' && c != '~';
	}), str.end());

	str.erase(std::remove(str.begin(), str.end(), '|'), str.end());
}

void Utils::TrimSpacesLeftOfString(std::string& s) 
{
	const char* start = s.c_str();
	const char* end = start + s.size();
	while (start < end && std::isspace(*start))
		start++;

	s.erase(0, start - s.c_str());
}

void Utils::TrimSpacesRightOfString(std::string& s) 
{
	const char* start = s.c_str();
	const char* end = start + s.size();
	const char* last_non_space = end;
	while (last_non_space > start && std::isspace(*(last_non_space - 1)))
		last_non_space--;

	s.erase(last_non_space - s.c_str(), end - last_non_space);
}

void Utils::TrimSpaceBothSidesOfString(std::string& s) 
{
	TrimSpacesLeftOfString(s);
	TrimSpacesRightOfString(s);
}

void Utils::RemoveExtraSpaces(std::string& str) 
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int c) { return !std::isspace(c); }));
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int c) { return !std::isspace(c); }).base(), str.end());
	auto last =
		std::unique(str.begin(), str.end(), [](char a, char b) { return std::isspace(a) && std::isspace(b); });
	str.erase(last, str.end());
}

void Utils::RemoveSpaces(std::string& str) 
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

uint32_t Utils::HashString(const void* pMem, uint32_t dataLength) 
{
    if (!pMem) 
		return 0;

    uint32_t hash = 0x55555555;

    for (uintmax_t i = 0; i < dataLength; ++i)
        hash = (hash >> 27) + (hash << 5) + static_cast<const uint8_t*>(pMem)[i];

    return hash;
}

int32_t Utils::GenerateUniqueTag(const std::string& name, const std::string& relativeId, const std::string& key) 
{
	std::hash<std::string> hasher;
	size_t hashValue = hasher(name + relativeId + key + std::to_string(time(NULL)));
	int32_t uniqueNumber = (hashValue % 900) + 100;

	if (uniqueNumber < 100) 
		uniqueNumber += 100;
	else if (uniqueNumber > 999)
		uniqueNumber %= 900 + 100;
		
	return uniqueNumber;
}

std::string Utils::ResolveIPAddress(const uint32_t& ip) 
{
    std::ostringstream oss;
    oss  << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);
    return oss.str();
}

std::string Utils::NormalizeString(const std::string& str) 
{
	std::string normalizedStr = str;
	std::transform(normalizedStr.begin(), normalizedStr.end(), normalizedStr.begin(), [](unsigned char c) { return std::tolower(c); });
	return normalizedStr;
}

bool Utils::SaveToFile(const std::string& fName, const std::string& content) 
{
    std::ofstream outputFile(fName);
    if (!outputFile.is_open())
		return false;

    outputFile << content;
    outputFile.close();
    return true;
}

unsigned int Utils::GetHashOfFile(const std::string& fName) 
{
	unsigned int hash;
	int size;
	uint8_t* pData;

#ifdef _CONSOLE
#else 
	pData = GetFileManager()->Get(fName, &size, false, false);
#endif

	if (!pData) 
		return 0; //no file, no hash

	hash = HashString((char*)pData, size);
	delete[] pData;
	return hash;
}