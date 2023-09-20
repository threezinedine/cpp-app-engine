#include "EngineDataType/DataStorage.hpp"


namespace ntt
{
    void DataStorage::SaveInteger(const char* name, int value)
    {

    }

    int DataStorage::GetInteger(const char* name, int defaultValue)
    {
        return defaultValue;
    }

    void DataStorage::SaveIntegers(const char* name, std::vector<int> value)
    {

    }

    std::vector<int> DataStorage::GetIntegers(const char* name, std::vector<int> defaultValue)
    {
        return defaultValue;
    }

    void DataStorage::SaveFloat(const char* name, float value)
    {

    }

    float DataStorage::GetFloat(const char* name, float defaultValue)
    {
        return defaultValue; 
    }
} // namespace ntt
