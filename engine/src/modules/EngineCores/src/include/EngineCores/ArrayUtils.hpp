#pragma once
#include <vector>

namespace ntt
{
    int GetValid(int value, int min, int max);

    template <typename T>
    bool VectorsEqual(std::vector<T> vec1, std::vector<T> vec2)
    {
        if (vec1.size() != vec2.size()) return false;

        for (int i=0; i<vec1.size(); i++)
        {
            if (vec1[i] != vec2[i]) return false;
        }
        return true;
    }
} // namespace ntt
