#pragma once
#include <cstring>
#include <string>
#include "InputType.hpp"
#include "EngineCores/EngineCores.hpp"
#include "DataTypeBase.hpp"


namespace ntt
{
    class Timestep;
    class DataStorage;

    struct StringOptions
    {
        std::vector<std::string> choices;
    };

    template <int N>
    class String: public DataTypeBase
    {
        public:
            String(const char* name)
                : DataTypeBase(name), value_("")
            {

            } 

            String(const char* name, std::string defaultValue)
                : DataTypeBase(name)
            {
                SetValue(defaultValue);
            }

            String(const char* name, Ref<DataStorage> storage)
                : DataTypeBase(name) , storage_(storage)
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
                
            void OnUpdate(Timestep ts, InputType type, void* args = nullptr)
            {
                std::stringstream title;

                switch (type)
                {
                    case INPUT:
                        ImGui::InputText(GetName(), value_, N+1);
                        break;
                    case WITH_CHOICES:
                        title << GetName() << ": Choose an option";
                        if (args != nullptr)
                        {
                            StringOptions* opts = static_cast<StringOptions*>(args);

                            ImGui::Text(title.str().c_str());
                            ImGui::Indent();
                            if (opts->choices.size() != 0)
                            {
                                for (int i=0; i<opts->choices.size(); i++)
                                {
                                    std::string option = opts->choices[i];
                                    if (ImGui::Selectable(option.c_str(), option == value_))
                                    {
                                        SetValue(option);
                                    }
                                }
                            }
                            ImGui::Unindent();
                        }
                        break;
                    
                    default:
                        break;
                }
            }

            std::string ToString() const
            {
                std::stringstream ss;
                ss << GetName() << ": " << value_;
                return ss.str();
            }

        private:
            char value_[N+1];
            Ref<DataStorage> storage_;
    }; 
} // namespace ntt
