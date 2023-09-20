#pragma once
#include <vector>
#include <iostream>


namespace ntt
{
    class DataStorage
    {
        public:
            virtual void SaveValue(const char* name, int value);
            virtual void SaveValue(const char* name, float value);

            virtual int GetValue(const char* name, int defaultValue);
            virtual float GetValue(const char* name, float defaultValue);

            virtual void SaveValues(const char* name, std::vector<int> value);
            virtual void SaveValues(const char* name, std::vector<float> value);

            virtual std::vector<int> GetValues(const char* name, std::vector<int> defaultValue);
            virtual std::vector<float> GetValues(const char* name, std::vector<float> defaultValue);
    };
} // namespace ntt
