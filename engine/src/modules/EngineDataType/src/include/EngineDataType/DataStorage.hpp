#pragma once
#include <vector>


namespace ntt
{
    class DataStorage
    {
        public:
            virtual void SaveInteger(const char* name, int value);
            virtual int GetInteger(const char* name, int defaultValue = 0);

            virtual void SaveIntegers(const char* name, std::vector<int> value);
            virtual std::vector<int> GetIntegers(const char* name, std::vector<int> defaultValue);

            virtual void SaveFloat(const char* name, float value);
            virtual float GetFloat(const char* name, float defaultValue = 0.0f);
    };
} // namespace ntt
