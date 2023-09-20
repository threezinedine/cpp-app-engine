#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Data.hpp"


namespace ntt
{
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
} // namespace ntt
