#pragma once
#include <vector>


namespace ntt
{
    class DataStorage
    {
        public:
            virtual void SaveInteger(const char* name, int value);
            virtual int GetInteger(const char* name, int defaultValue = 0);

            virtual void SaveInteger2(const char* name, std::vector<int> value);
            virtual std::vector<int> GetInteger2(const char* name, 
                                std::vector<int> defaultValue = { 0, 0 });

            virtual void SaveInteger3(const char* name, std::vector<int> value);
            virtual std::vector<int> GetInteger3(const char* name,
                                std::vector<int> defaultValue = { 0, 0, 0 });

            virtual void SaveInteger4(const char* name, std::vector<int> value);
            virtual std::vector<int> GetInteger4(const char* name,
                                std::vector<int> defaultValue = { 0, 0, 0, 0 });
    };
} // namespace ntt
