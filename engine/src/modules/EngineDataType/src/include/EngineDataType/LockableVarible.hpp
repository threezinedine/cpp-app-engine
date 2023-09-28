#pragma once
#include <mutex>


namespace ntt
{
    class LockableVariable
    {
        public:
            virtual std::mutex& GetMutex() = 0;
    }; 
} // namespace ntt
