#pragma once
#include <cstring>
#include <string>
#include "InputType.hpp"
#include "EngineCores/EngineCores.hpp"
#include "DataTypeBase.hpp"
#include "EngineImGuiComponents/EngineImGuiComponents.hpp"
#include "StringDataType.hpp"


namespace ntt
{
    class Timestep;
    class DataStorage;

    struct StringOptions
    {
        std::vector<std::string> choices;
        FileDialogOptions fileOpts; 
    };

    template <int N>
    class String: public DataTypeBase, StringDataType
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
                StringOptions* opts;
                if (args != nullptr)
                {
                    opts = static_cast<StringOptions*>(args);
                }

                switch (type)
                {
                    case INPUT:
                        ImGui::InputText(GetName(), value_, N+1);
                        break;
                    case WITH_CHOICES:
                        title << GetName() << ": Choose an option";
                        if (args != nullptr)
                        {
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
                    case FILE_DIALOG:
                        if (fileDialog_ == nullptr)
                        {
                            fileDialog_ = FileDialog::CreateScope(this);
                        }

                        if (args != nullptr)
                        {
                            fileDialog_->OnUpdate(opts->fileOpts);
                        }
                        else 
                        {
                            fileDialog_->OnUpdate();
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
            Scope<FileDialog> fileDialog_;
    }; 
} // namespace ntt
