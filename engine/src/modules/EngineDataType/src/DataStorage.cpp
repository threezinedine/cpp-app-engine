#include "EngineDataType/DataStorage.hpp"


namespace ntt
{
    void DataStorage::SaveValue(const char* name, int value)
    {

    }

    void DataStorage::SaveValue(const char* name, float value)
    {

    }

    int DataStorage::GetValue(const char* name, int defaultValue)
    {
        return defaultValue;
    }

    float DataStorage::GetValue(const char* name, float defaultValue)
    {
        return defaultValue;
    }

    void DataStorage::SaveValues(const char* name, std::vector<int> value)
    {

    }

    void DataStorage::SaveValues(const char* name, std::vector<float> value)
    {

    }

    std::vector<int> DataStorage::GetValues(const char* name, std::vector<int> defaultValue)
    {
        return defaultValue;
    }

    std::vector<float> DataStorage::GetValues(const char* name, std::vector<float> defaultValue)
    {
        return defaultValue;
    }
} // namespace ntt
