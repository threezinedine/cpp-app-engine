#pragma once
#include <string>
#include "EngineCores/EngineCores.hpp"
#include "InputType.hpp"


namespace ntt
{
    class DataStorage;
    class Timestep;

    class Bool
    {
        public:
            Bool(const char* name);
            Bool(const char* name, bool value);
            Bool(const char* name, Ref<DataStorage> storage);
            ~Bool();

            inline const char* GetName() const { return name_; }
            bool Value();

            void OnUpdate(Timestep ts, InputType type = CHECK_BOX);
            void SetValue(bool value);

            std::string ToString();

        private:
            const char* name_;
            bool value_;
            Ref<DataStorage> storage_;
    };
} // namespace ntt
