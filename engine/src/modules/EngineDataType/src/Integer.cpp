#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Integer.hpp"
#include "EngineDataType/DataStorage.hpp"


namespace ntt
{
    Integer::Integer(const char* name)
        : name_(name), value_(0), min_(0), max_(100), storage_(nullptr)
    {

    }

    Integer::Integer(const char* name, int defaultValue)
        : name_(name), min_(0), max_(100), storage_(nullptr)
    {
        SetValue(defaultValue);
    }

    Integer::Integer(const char* name, int defaultValue, int min, int max)
        : name_(name), min_(min), max_(max), storage_(nullptr)
    {
        SetValue(defaultValue);
    }

    Integer::Integer(const char* name, int defaultValue, int min, int max, Ref<DataStorage> storage)
        : name_(name), value_(defaultValue), min_(min), max_(max), storage_(storage)
    {
        SetValue(storage_->GetInteger(name, defaultValue));
    }

    Integer::~Integer()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveInteger(GetName(), value_);
        }
    }

    int Integer::Value() const
    {
        return value_;
    }

    void Integer::OnUpdate(Timestep ts, InputType type)
    {
        switch (type)
        {
            case NONE:
                break;
            
            case SLIDER:
                ImGui::SliderInt(GetName(), &value_, min_, max_);
                break;
            case INPUT:
                ImGui::InputInt(GetName(), &value_);
                break;

            default:
                break;
        }
    }

    void Integer::SetValue(int value)
    {
        if (value > max_) 
        {
            value_ = max_;
        }
        else if (value < min_)
        {
            value_ = min_;
        }
        else 
        {
            value_ = value;
        }
    }
} // namespace ntt
