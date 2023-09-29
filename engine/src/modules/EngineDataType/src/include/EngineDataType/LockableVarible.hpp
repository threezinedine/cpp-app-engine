#pragma once
#include <mutex>


namespace ntt
{
    class LockableVariable
    {
        public:
            virtual void Lock() = 0;
            virtual void UnLock() = 0;
    }; 
} // namespace ntt
