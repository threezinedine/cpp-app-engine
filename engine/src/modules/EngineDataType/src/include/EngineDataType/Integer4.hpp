#pragma once
#include <vector>
#include "EngineCores/EngineCores.hpp"
#include "InputType.hpp"


namespace ntt
{
    class Timestep;
    class DataStorage;

    class Integer4
    {
        public:
            Integer4(const char* name, std::vector<int> defaultValue, int minValue, int maxValue);
            Integer4(const char* name, std::vector<int> defaultValue, int minValue, int maxValue, 
                                Ref<DataStorage> storage);
            Integer4(const char* name, std::vector<int> defaultValue);
            Integer4(const char* name);
            ~Integer4();

            inline const char* GetName() const { return name_; }
            std::vector<int> Value();

            void OnUpdate(Timestep ts, InputType type = NONE);
            void SetValue(std::vector<int> value);

        private:
            const char* name_;
            std::vector<int> value_;
            int minValue_;
            int maxValue_;
            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
