#include "EngineExceptions/ImGuiApplicationConfigErrorException.hpp"


namespace ntt
{
    ImGuiApplicationConfigErrorException::ImGuiApplicationConfigErrorException(const char* message)
        : message_(message)
    {

    } 

    const char* ImGuiApplicationConfigErrorException::what() const noexcept 
    {
        return message_;
    }
} // namespace ntt
