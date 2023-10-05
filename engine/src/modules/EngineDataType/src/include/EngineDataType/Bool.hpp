#pragma once
#include <string>
#include "EngineCores/EngineCores.hpp"
#include "InputType.hpp"
#include "DataTypeBase.hpp"
#include "LockableVarible.hpp"
#include <mutex>


namespace ntt
{
    class DataStorage;
    class Timestep;

    class Bool: public DataTypeBase, public LockableVariable
    {
        public:
            Bool(const char* name);
            Bool(const char* name, bool value);
            Bool(const char* name, Ref<DataStorage> storage);
            ~Bool();

            bool Value();

            bool OnUpdate(Timestep ts, InputType type = CHECK_BOX, void* args = nullptr);
            void SetValue(bool value);

            std::string ToString() const;

            void Lock() override;
            void UnLock() override;

        private:
            bool value_;
            Ref<DataStorage> storage_;
            std::mutex mutex_;
    };
} // namespace ntt
