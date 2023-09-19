#pragma once

#include "InputType.hpp"
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Timestep;
    class DataStorage;

    class Integer
    {
        public:
            Integer(const char* name);
            Integer(const char* name, int defaultValue);
            Integer(const char* name, int defaultValue, int min, int max);
            Integer(const char* name, int defaultValue, int min, int max, Ref<DataStorage> storage);
            ~Integer();

            int Value() const;
            void OnUpdate(Timestep ts, InputType type = NONE);
            inline const char* GetName() const { return name_; }
            void SetValue(int value);

        private:
            const char* name_;
            int value_;
            int min_;
            int max_;

            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
