#pragma once
#include "InputType.hpp"
#include <vector>
#include <EngineCores/EngineCores.hpp>


namespace ntt
{
    class Timestep;
    class DataStorage;

    class Integer2
    {
        public:
            Integer2(const char* name);
            Integer2(const char* name, std::vector<int> defaultValue);
            Integer2(const char* name, std::vector<int> defaultValue, int minValue, int maxValue);
            Integer2(const char* name, std::vector<int> defaultValue, 
                        int minValue, int maxValue, Ref<DataStorage> storage);
            ~Integer2();

            std::vector<int> Value();
            void OnUpdate(Timestep ts, InputType type = NONE);
            inline const char* GetName() const { return name_; }
            void SetValue(std::vector<int> value);

        private:
            const char* name_;
            std::vector<int> value_;
            int minValue_;
            int maxValue_;
            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
