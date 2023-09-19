#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Integer3.hpp"

namespace ntt
{
    Integer3::Integer3(const char* name, std::vector<int> defaultValue, 
                    int minValue, int maxValue,
                    Ref<DataStorage> storage)
        : name_(name), minValue_(minValue), maxValue_(maxValue),
                storage_(storage)
    {
        SetValue(storage_->GetInteger3(GetName(), defaultValue));
    }

    Integer3::Integer3(const char* name, std::vector<int> defaultValue, int minValue, int maxValue)
        : name_(name), minValue_(minValue), maxValue_(maxValue),
                storage_(nullptr)
    {
        SetValue(defaultValue);
    }

    Integer3::Integer3(const char* name)
        : name_(name), value_({ 0, 0, 0 }), minValue_(0), maxValue_(100), storage_(nullptr)
    {

    }

    Integer3::Integer3(const char* name, std::vector<int> defaultValue)
        : name_(name), minValue_(0), maxValue_(100), storage_(nullptr)
    {
        SetValue(defaultValue);
    }

    Integer3::~Integer3()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveInteger3(GetName(), value_);
        }
    }

    std::vector<int> Integer3::Value()
    {
        return value_;
    }

    void Integer3::OnUpdate(Timestep ts, InputType type)
    {
        switch (type)
        {
            case NONE:
                break;
            case SLIDER:
                ImGui::SliderInt3(GetName(), &value_[0], minValue_, maxValue_);
                break;
            case INPUT:
                ImGui::InputInt3(GetName(), &value_[0], ImGuiInputTextFlags_CharsDecimal);
                break;
            
            default:
                break;
        } 
    }

    void Integer3::SetValue(std::vector<int> value)
    {
        if (value.size() != 3) return;

        for (int i=0; i<value.size(); i++)
        {
            value[i] = GetValid(value[i], minValue_, maxValue_);
        }

        value_ = value;
    }
} // namespace ntt
