#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Data.hpp"


namespace ntt
{
    template <>
    Data<int>::Data(const char* name, int defaultValue, int minValue, 
                int maxValue, Ref<DataStorage> storage)
        : name_(name), minValue_(minValue), 
            maxValue_(maxValue), storage_(storage)
    {
        SetValue(storage_->GetInteger(GetName(), defaultValue));
    }

    template <>
    Data<float>::Data(const char* name, float defaultValue, float minValue, 
                float maxValue, Ref<DataStorage> storage)
        : name_(name), minValue_(minValue), 
            maxValue_(maxValue), storage_(storage)
    {
        SetValue(storage_->GetFloat(GetName(), defaultValue));
    }

    template <>
    Data<int>::~Data()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveInteger(GetName(), value_);
        }
    }

    template <>
    Data<float>::~Data()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveFloat(GetName(), value_);
        }
    }

    template <>
    void Data<int>::OnUpdate(Timestep ts, InputType type)
    {
        switch (type)
        {
            case SLIDER:
                ImGui::SliderInt(GetName(), &value_, minValue_, maxValue_);
                break;
            case INPUT:
                ImGui::InputInt(GetName(), &value_);
                break;
            
            default:
                break;
        }
    }

    template <>
    void Data<float>::OnUpdate(Timestep ts, InputType type)
    {
        switch (type)
        {
            case SLIDER:
                ImGui::SliderFloat(GetName(), &value_, minValue_, maxValue_);
                break;
            case INPUT:
                ImGui::InputFloat(GetName(), &value_);
                break;
            
            default:
                break;
        }
    }
} // namespace ntt
