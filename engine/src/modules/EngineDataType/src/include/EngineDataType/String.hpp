#pragma once
#include <string>
#include "InputType.hpp"
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Timestep;
    class DataStorage;

    class String
    {
        public:
            String(const char* name);
            String(const char* name, std::string defaultValue);
            String(const char* name, Ref<DataStorage> storage);
            ~String();

            std::string Value();
            void SetValue(std::string value);

            inline const char* GetName() const { return name_; }

            void OnUpdate(Timestep ts, InputType type = NONE);

        private:
            const char* name_;
            std::string value_;
            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
