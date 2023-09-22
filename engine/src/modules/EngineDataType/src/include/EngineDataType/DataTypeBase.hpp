#pragma once
#include <iostream>
#include "PreInclude.hpp"
#include "InputType.hpp"


namespace ntt
{
    class TimeStep;

    template <typename T>
    class DataTypeBase
    {
        public:
            DataTypeBase(const char* name, T defaultVaue)
                : name_(name), value_(defaultVaue), storage_(nullptr)
            {

            }

            DataTypeBase(const char* name, T defaultValue, Ref<DataStorage> storage)
                : name_(name), value_(defaultValue), storage_(storage)
            {

            }

            virtual ~DataTypeBase()
            {
                if (storage_ != nullptr) 
                {
                    storage_->SaveValue(GetName(), value_);
                }
            }

            inline virtual const char* GetName() const { return name_; }

            T Value() { return value_; }

            virtual void SetValue(T value) = 0;
            virtual void OnUpdate(Timestep ts, InputType type = NONE) = 0;

        protected:
            T value_;

            void Initialize()
            {
                if (storage_ != nullptr)
                {
                    SetValue(storage_->GetValue(GetName(), value_));
                }
                else 
                {
                    SetValue(value_);
                }
            }

        private:
            const char* name_;
            Ref<DataStorage> storage_;

    }; 
} // namespace ntt
