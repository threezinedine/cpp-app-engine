#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/String.hpp"


namespace ntt
{
    String::String(const char* name)
        : name_(name), value_(std::string(""))
    {

    } 

    String::String(const char* name, std::string defaultValue)
        : name_(name), value_(defaultValue)
    {

    }

    String::String(const char* name, Ref<DataStorage> storage)
        : name_(name) , storage_(storage)
    {
        value_ = storage_->GetValue(GetName(), "");
    }

    String::~String()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveValue(GetName(), value_);
        }
    }

    std::string String::Value()
    {
        return value_;
    }

    void String::SetValue(std::string value)
    {
        value_ = value;
    }
        
    void String::OnUpdate(Timestep ts, InputType type)
    {

    }
} // namespace ntt
