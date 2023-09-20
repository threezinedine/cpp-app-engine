#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Integer4.hpp"


namespace ntt
{
    Integer4::Integer4(const char* name, std::vector<int> defaultValue, int minValue, int maxValue)
        : name_(name), minValue_(minValue), maxValue_(maxValue)
    {
        SetValue(defaultValue);
    }

    Integer4::Integer4(const char* name, std::vector<int> defaultValue, int minValue, int maxValue,
                            Ref<DataStorage> storage)
        : name_(name), minValue_(minValue), 
                maxValue_(maxValue), storage_(storage)
    {
        SetValue(storage_->GetInteger4(GetName(), defaultValue));
    }

    Integer4::Integer4(const char* name)
        : name_(name), value_({ 0, 0, 0, 0 }), minValue_(0), maxValue_(100)
    {

    }

    Integer4::Integer4(const char* name, std::vector<int> defaultValue)
        : name_(name), minValue_(0), maxValue_(100)
    {
        SetValue(defaultValue);
    }

    Integer4::~Integer4()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveInteger4(GetName(), value_);
        }
    }

    std::vector<int> Integer4::Value()
    {
        return value_;
    }

    void Integer4::OnUpdate(Timestep ts, InputType type)
    {
        switch (type)
        {
            case NONE:
                break;
            case SLIDER:
                ImGui::SliderInt4(GetName(), &value_[0], minValue_, maxValue_);
                break;
            case INPUT:
                ImGui::InputInt4(GetName(), &value_[0]);
                break;
            
            default:
                break;
        }
    }

    void Integer4::SetValue(std::vector<int> value)
    {
        if (value.size() != 4) return;

        for (int i=0; i<value.size(); i++)
        {
            value[i] = GetValid(value[i], minValue_, maxValue_);
        }

        value_ = value;
    }
} // namespace ntt
