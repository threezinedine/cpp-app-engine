#pragma once
#include <string>


namespace ntt
{
    bool FileExists(const char* fileName);    
    bool FileExists(const std::string& fileName);    

    std::string GetFolder(const std::string& filePath);
} // namespace ntt
