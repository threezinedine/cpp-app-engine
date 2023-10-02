#pragma once
#include <string>
#include <vector>


namespace ntt
{
    std::vector<std::string> SplitString(const std::string& word, char separateChar);
    std::string ConcatString(const std::vector<std::string>& vector, char linkChar);
    std::string ConcatString(const std::vector<std::string>& vector);
} // namespace ntt
