#pragma once

#include <stdexcept>

namespace ntt
{
    class ImGuiApplicationConfigErrorException: public std::exception
    {
        public:
            ImGuiApplicationConfigErrorException(const char* message);

            const char* what() const noexcept override;

        private:
            const char* message_;
    }; 
} // namespace ntt
