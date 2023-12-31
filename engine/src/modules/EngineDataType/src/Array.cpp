#include "EngineDataType/Array.hpp"


namespace ntt
{

    template<>
    bool Array<int, 2>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        switch (type)
        {
            case INPUT:
                ImGui::InputInt2(GetName(), &value_[0]);
                break;
            case SLIDER:
                ImGui::SliderInt2(GetName(), &value_[0], minValue_, maxValue_);
                break;
            
            default:
                break; 
        }
        return true;
    }

    template<>
    bool Array<int, 3>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        switch (type)
        {
            case INPUT:
                ImGui::InputInt3(GetName(), &value_[0]);
                break;
            case SLIDER:
                ImGui::SliderInt3(GetName(), &value_[0], minValue_, maxValue_);
                break;
            
            default:
                break; 
        }
        return true;
    }

    template<>
    bool Array<int, 4>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        switch (type)
        {
            case INPUT:
                ImGui::InputInt4(GetName(), &value_[0]);
                break;
            case SLIDER:
                ImGui::SliderInt4(GetName(), &value_[0], minValue_, maxValue_);
                break;
            
            default:
                break; 
        }
        return true;
    }

    template<>
    bool Array<float, 2>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        switch (type)
        {
            case INPUT:
                ImGui::InputFloat3(GetName(), &value_[0]);
                break;
            case SLIDER:
                ImGui::SliderFloat3(GetName(), &value_[0], minValue_, maxValue_);
                break;
            
            default:
                break; 
        }
        return true;
    }

    template<>
    bool Array<float, 3>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        switch (type)
        {
            case INPUT:
                ImGui::InputFloat3(GetName(), &value_[0]);
                break;
            case SLIDER:
                ImGui::SliderFloat3(GetName(), &value_[0], minValue_, maxValue_);
                break;
            case COLOR_PICKER:
                ImGui::ColorPicker3(GetName(), &value_[0], ImGuiColorEditFlags_Uint8);
                break;
            
            default:
                break; 
        }
        return true;
    }

    template<>
    bool Array<float, 4>::OnUpdate(Timestep ts, InputType type, void* args)
    {
        switch (type)
        {
            case INPUT:
                ImGui::InputFloat4(GetName(), &value_[0]);
                break;
            case SLIDER:
                ImGui::SliderFloat4(GetName(), &value_[0], minValue_, maxValue_);
                break;
            case COLOR_PICKER:
                ImGui::ColorPicker4(GetName(), &value_[0], ImGuiColorEditFlags_Uint8);
                break;
            
            default:
                break; 
        }
        return true;
    }
} // namespace ntt
