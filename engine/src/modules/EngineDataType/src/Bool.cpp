#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Bool.hpp"
#include "EngineDataType/DataStorage.hpp"


namespace ntt
{
    Bool::Bool(const char* name)
        : DataTypeBase(name), value_(false), storage_(nullptr)
    {

    }

    Bool::Bool(const char* name, bool value)
        : DataTypeBase(name), value_(value), storage_(nullptr)
    {

    }

    Bool::Bool(const char* name, Ref<DataStorage> storage)
        : DataTypeBase(name), storage_(storage)
    {
        value_ = storage_->GetValue(GetName());
    }

    void Bool::OnUpdate(Timestep ts, InputType type, void* args)
    {
        switch (type)
        {
            case CHECK_BOX:
                ImGui::Checkbox(GetName(), &value_);
                break;
            
            default:
                break;
        }
    }

    Bool::~Bool()
    {
        if (storage_ != nullptr)
        {
            storage_->SaveValue(GetName(), value_);
        }
    }

    bool Bool::Value()
    {
        return value_;
    }

    void Bool::SetValue(bool value)
    {
        value_ = value;
    }

    std::string Bool::ToString() const
    {
        std::stringstream ss;
        ss << GetName() << ": ";

        if (value_)
        {
            ss << "true";
        }
        else 
        {
            ss << "false";
        }

        return ss.str();
    }
} // namespace ntt
