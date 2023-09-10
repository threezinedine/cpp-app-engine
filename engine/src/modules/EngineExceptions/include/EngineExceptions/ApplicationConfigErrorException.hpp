#pragma once

#include <stdexcept>


namespace ntt
{
    class ApplicationConfigErrorException: public std::exception
    {
        public:
            ApplicationConfigErrorException(const char* message);

            const char* what() const noexcept override;

        private:
            const char* message_;
    }; 
} // namespace ntt
