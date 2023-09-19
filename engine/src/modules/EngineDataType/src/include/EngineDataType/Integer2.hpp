#pragma once
#include "InputType.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace ntt
{
    class Integer2
    {
        Integer2(const char* name, std::vector<int> defaultValue, int minValue, int maxValue);
        ~Integer2();
    }; 
} // namespace ntt
