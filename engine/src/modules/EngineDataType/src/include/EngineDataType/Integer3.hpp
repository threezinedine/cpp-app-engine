#pragma once
#include <vector>
#include "InputType.hpp"
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Timestep;
    class DataStorage;

    class Integer3
    {
        public:
            Integer3(const char* name, std::vector<int> defaultValue, 
                        int minValue, int maxValue,
                        Ref<DataStorage> storage);
            Integer3(const char* name, std::vector<int> defaultValue, int minValue, int maxValue);
            Integer3(const char* name, std::vector<int> defaultValue);
            Integer3(const char* name);
            ~Integer3();

            inline const char* GetName() const { return name_; }
            std::vector<int> Value();
            void SetValue(std::vector<int> value);

            void OnUpdate(Timestep ts, InputType type = NONE);

        private:
            const char* name_;
            std::vector<int> value_;
            int minValue_;
            int maxValue_;
            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
