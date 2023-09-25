#include "EngineCores/FileUtils.hpp"
#include <fstream>


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

} // namespace ntt
