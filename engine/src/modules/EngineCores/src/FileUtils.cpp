#include "EngineCores/FileUtils.hpp"
#include <vector>
#include <fstream>
#include "EngineCores/StringUtils.hpp"


namespace ntt
{
    bool FileExists(const char* fileName)
    {
        std::ifstream file(fileName);
        return file.good();
    }

    bool FileExists(const std::string& fileName)
    {
        return FileExists(fileName.c_str());
    }

    std::string GetFolder(const std::string& filePath)
    {
        std::vector<std::string> splittedWords = SplitString(filePath, '/');
        return ConcatString(std::vector<std::string>(splittedWords.begin(), splittedWords.end() - 1), '/');
    }
} // namespace ntt
