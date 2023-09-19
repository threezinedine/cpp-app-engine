#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Integer2.hpp"


namespace ntt
{
    Integer2::Integer2(const char* name, std::vector<int> defaultValue, int minValue, int maxValue)
        : name_(name), minValue_(minValue), maxValue_(maxValue), storage_(nullptr)
    {
        SetValue(defaultValue);
    }

    Integer2::Integer2(const char* name, std::vector<int> defaultValue)
        : name_(name), minValue_(0), maxValue_(100), storage_(nullptr)
    {
        SetValue(defaultValue);
    }

    Integer2::Integer2(const char* name)
        : name_(name), value_({ 0, 0 }), minValue_(0), maxValue_(100), storage_(nullptr)
    {

    }

    Integer2::Integer2(const char* name, std::vector<int> defaultValue, 
                int minValue, int maxValue, Ref<DataStorage> storage)
        : name_(name), value_(defaultValue), minValue_(minValue), 
                maxValue_(maxValue), storage_(storage)
    {
        SetValue(storage->GetInteger2(GetName(), defaultValue));
    }

    Integer2::~Integer2()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveInteger2(GetName(), value_);
        }
    }

    std::vector<int> Integer2::Value()
    {
        return value_;
    }

    void Integer2::OnUpdate(Timestep ts, InputType type)
    {
        switch (type)
        {
            case NONE:
                break;
            case SLIDER:
                ImGui::SliderInt2(GetName(), &value_[0], minValue_, maxValue_);
                break;
            case INPUT:
                ImGui::InputInt2(GetName(), &value_[0], ImGuiInputTextFlags_CharsDecimal);
                break;
            
            default:
                break;
        }
    }

    void Integer2::SetValue(std::vector<int> value)
    {
        if (value.size() != 2) return;

        for (int i=0; i<value.size(); i++)
        {
            value[i] = GetValid(value[i], minValue_, maxValue_);
        }

        value_ = value;
    }

} // namespace ntt
