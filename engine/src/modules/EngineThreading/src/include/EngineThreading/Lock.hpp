#pragma once
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class LockableVariable;

    class Lock
    {
        public:
            Lock(Ref<LockableVariable> var);
            ~Lock();

        private:
            Ref<LockableVariable> var_;
    }; 
} // namespace ntt
