#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Data.hpp"


namespace ntt
{
    template <>
    void Data<int>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        std::stringstream ss;

        switch (type)
        {
            case SLIDER:
                ImGui::SliderInt(GetName(), &value_, minValue_, maxValue_);
                break;
            case INPUT:
                ImGui::InputInt(GetName(), &value_);
                break;
            case WITH_CHOICES:
                ss << GetName() << ": Choose an option";
                ImGui::Text(ss.str().c_str());
                if (args != nullptr)
                {
                    DataOptions<int>* options = static_cast<DataOptions<int>*>(args);

                    if (options->choices.size() != 0)
                    {
                        ImGui::Indent();
                        for (int i=0; i<options->choices.size(); i++)
                        {
                            auto option = options->choices[i];
                            if (ImGui::Selectable(option.first.c_str(), option.second == value_))
                            {
                                SetValue(option.second);
                            }
                        }
                        ImGui::Unindent();
                    }
                }
                break;
            
            default:
                break;
        }
    }

    template <>
    void Data<float>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        std::stringstream ss;

        switch (type)
        {
            case SLIDER:
                ImGui::SliderFloat(GetName(), &value_, minValue_, maxValue_);
                break;
            case INPUT:
                ImGui::InputFloat(GetName(), &value_);
                break;
            case WITH_CHOICES:
                ss << GetName() << ": Choose an option";
                ImGui::Indent();
                if (args != nullptr)
                {
                    DataOptions<float>* options = static_cast<DataOptions<float>*>(args);

                    if (options->choices.size() != 0)
                    {
                        for (int i=0; i<options->choices.size(); i++)
                        {
                            auto option = options->choices[i];
                            if (ImGui::Selectable(option.first.c_str(), option.second == value_))
                            {
                                SetValue(option.second);
                            }
                        }
                    }
                }
                ImGui::Unindent();
                break;

            default:
                break;
        }
    }
} // namespace ntt
