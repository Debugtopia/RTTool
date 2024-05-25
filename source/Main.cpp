#include <thread>
#include <iostream>
#include <filesystem>

#include "ProtonSDK/MiscUtils.h"
#include "ProtonSDK/FileSystem/FileManager.h"

int main() 
{
	printf("RTTool by Hexago.\nActions:\n0: decompress RTTEX file to PNG.\n1: compress PNG file to RTTEX.\n2: Get hash of a RTTEX/XML/DAT file.\n");
	
    while (true) 
    {
        int action = -1;
        std::cout << "Select action: ";
        std::cin >> action;

        switch (action) 
        {
        case 0: 
        { // RTTEX -> PNG
            std::string fileName;
            bool bPadded = false;

            std::cout << "File name: ";
            std::cin >> fileName;

            std::cout << "Padding? (0 or 1): ";
            std::cin >> bPadded;

            std::cout << "Current under development." << std::endl;
            break;
        }
        case 1: 
        { // PNG -> RTTEX
            std::string fileName;
            std::string header;

            std::cout << "File name: ";
            std::cin >> fileName;

            std::cout << "Header (RTTEX, ZLIB): ";
            std::cin >> header;

            std::cout << "Current under development." << std::endl;
            break;
        }
        case 2: 
        { // RTHash
            std::string fileName;
            std::cout << "File name: ";
            std::cin >> fileName;

            FileInstance f(fileName);
            if (!f.IsLoaded()) 
            {
                std::cout << "File doesn't exist." << std::endl;
                break;
            }

            char* pCharData = f.GetAsChars();
            int size = f.GetSize();

            std::vector<char> data(pCharData, pCharData + size);
            uint32_t hash = Utils::HashString(pCharData, size);

            const char* fileType = fileName.c_str();
            if (fileName.find(".dat") != std::string::npos) fileType = "items.dat";
            if (fileName.find(".xml") != std::string::npos) fileType = "xml";

            std::cout << "The hash of " << fileType << " is " << hash << std::endl;
            break;
        }
        default: 
        {
            std::cout << "That's not action you can use..." << std::endl;
            break;
        }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}