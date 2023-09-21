#pragma once
#include "PreInclude.hpp"
#include "InputType.hpp"


namespace ntt
{
    template <typename T>
    class Data
    {
        public:
            Data(const char* name)
                : name_(name), value_(0), minValue_(0), maxValue_(100), storage_(nullptr)
            {

            }

            Data(const char* name, T defaultValue)
                : name_(name), minValue_(0), maxValue_(100), storage_(nullptr)
            {
                SetValue(defaultValue);
            }

            Data(const char* name, T defaultValue, T minValue, T maxValue)
                : name_(name), minValue_(minValue), 
                    maxValue_(maxValue), storage_(nullptr)
            {
                SetValue(defaultValue);
            }

            Data(const char* name, T defaultValue, T minValue, T maxValue, Ref<DataStorage> storage)
                : name_(name), minValue_(minValue), 
                    maxValue_(maxValue), storage_(storage)
            {
                SetValue(storage_->GetValue(GetName(), defaultValue));
            }

            ~Data()
            {
                if (storage_ != nullptr)
                {
                    storage_->SaveValue(GetName(), value_);
                }
            }

            inline const char* GetName() const { return name_; }

            T Value() { return value_; }

            void OnUpdate(Timestep ts, InputType type = NONE);

            void SetValue(T value)
            {
                value_ = GetValid<T>(value, minValue_, maxValue_);
            }

            std::string ToString()
            {
                std::stringstream ss;

                ss << GetName() << ": " << value_;
                return ss.str();
            }

        private:
            const char* name_;
            T value_;
            T minValue_;
            T maxValue_;
            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
