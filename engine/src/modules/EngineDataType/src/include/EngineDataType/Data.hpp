#pragma once
#include <vector>
#include "InputType.hpp"
#include "EngineCores/EngineCores.hpp"
#include "DataStorage.hpp"


namespace ntt
{
    template <typename T, int N>
    class Data
    {
        public:
            Data(const char* name, std::vector<T> defaultValue, T minValue, T maxValue)
                : name_(name), minValue_(minValue), maxValue_(maxValue)
            {
                SetValue(defaultValue);
            }

            Data(const char* name, std::vector<T> defaultValue, 
                        T minValue, T maxValue, Ref<DataStorage> storage)
                : name_(name), minValue_(minValue), maxValue_(maxValue),
                    storage_(storage)
            {
                SetValue(storage->GetIntegers(GetName(), defaultValue));
            }

            Data(const char* name)
                : name_(name), value_(std::vector<T>(N, 0)), minValue_(0), maxValue_(100)
            {

            }

            Data(const char* name, std::vector<T> defaultValue)
                : name_(name), minValue_(0), maxValue_(100)
            {
                SetValue(defaultValue);
            }

            ~Data()
            {
                if (storage_ != nullptr)
                {
                    storage_->SaveIntegers(GetName(), value_);
                }
            }

            inline const char* GetName() const { return name_; }

            std::vector<T> Value() { return value_; }

            void OnUpdate(Timestep ts, InputType type = NONE)
            {
                
            }

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
