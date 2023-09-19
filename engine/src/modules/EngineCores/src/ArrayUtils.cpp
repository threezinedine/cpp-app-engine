#include "EngineCores/ArrayUtils.hpp"


namespace ntt
{
    int GetValid(int value, int min, int max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
} // namespace ntt
