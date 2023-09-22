#pragma once
#include <cstring>
#include <string>
#include "InputType.hpp"
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Timestep;
    class DataStorage;

    template <int N>
    class String
    {
        public:
            String(const char* name)
                : name_(name), value_("")
            {

            } 

            String(const char* name, std::string defaultValue)
                : name_(name)
            {
                SetValue(defaultValue);
            }

            String(const char* name, Ref<DataStorage> storage)
                : name_(name) , storage_(storage)
            {
                SetValue(storage_->GetValue(GetName(), ""));
            }

            ~String()
            {
                if (storage_ != nullptr)
                {
                    storage_->SaveValue(GetName(), std::string(value_));
                }
            }

            std::string Value()
            {
                return std::string(value_);
            }

            void SetValue(std::string value)
            {
                if (value.length() > N)
                {
                    std::strcpy(value_, value.substr(0, N).c_str());
                }
                else
                {
                    std::strcpy(value_, value.c_str());
                }
            }
                
            void OnUpdate(Timestep ts, InputType type)
            {
                switch (type)
                {
                case INPUT:
                    ImGui::InputText(GetName(), value_, N+1);
                    break;
                
                default:
                    break;
                }
            }

            std::string ToString()
            {
                std::stringstream ss;
                ss << GetName() << ": " << value_;
                return ss.str();
            }

            inline const char* GetName() const { return name_; }

        private:
            const char* name_;
            char value_[N+1];
            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
