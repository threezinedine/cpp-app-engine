#pragma once
#include <vector>
#include "InputType.hpp"
#include "PreInclude.hpp"


namespace ntt
{
    template <typename T, int N>
    class Array
    {
        public:
            Array(const char* name, std::vector<T> defaultValue, T minValue, T maxValue)
                : name_(name), minValue_(minValue), maxValue_(maxValue)
            {
                SetValue(defaultValue);
            }

            Array(const char* name, std::vector<T> defaultValue, 
                        T minValue, T maxValue, Ref<DataStorage> storage)
                : name_(name), minValue_(minValue), maxValue_(maxValue),
                    storage_(storage)
            {
                SetValue(storage->GetValues(GetName(), defaultValue));
            }

            Array(const char* name)
                : name_(name), value_(std::vector<T>(N, 0)), minValue_(0), maxValue_(100)
            {

            }

            Array(const char* name, std::vector<T> defaultValue)
                : name_(name), minValue_(0), maxValue_(100), storage_(nullptr)
            {
                SetValue(defaultValue);
            }

            ~Array()
            {
                if (storage_ != nullptr)
                {
                    storage_->SaveValues(GetName(), value_);
                }
            }

            inline const char* GetName() const { return name_; }

            std::vector<T> Value() { return value_; }

            void OnUpdate(Timestep ts, InputType type = NONE);

            void SetValue(std::vector<T> value)
            {
                if (value.size() != N) return;

                for (int i=0; i<value.size(); i++)
                {
                    value[i] = GetValid(value[i], minValue_, maxValue_);
                }

                value_ = value;
            }

        private:
            const char* name_;
            std::vector<T> value_;
            T minValue_;
            T maxValue_;
            Ref<DataStorage> storage_;
    };
} // namespace ntt
