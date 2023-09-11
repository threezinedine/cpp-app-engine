#include "EngineExceptions/PreInclude.hpp"
#include "EngineExceptions/ApplicationConfigErrorException.hpp"


namespace ntt
{
    ApplicationConfigErrorException::ApplicationConfigErrorException(const char* message)
        : message_(message)
    {

    }

    const char* ApplicationConfigErrorException::what() const noexcept
    {
        return message_;
    }
} // namespace ntt
