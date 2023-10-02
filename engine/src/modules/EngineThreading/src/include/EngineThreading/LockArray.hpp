#pragma once
#include <vector>
#include <initializer_list>
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class LockableVariable;

    class LockArray
    {
        public:
            LockArray(std::initializer_list<Ref<LockableVariable>> locks);
            ~LockArray();

        private:
            std::vector<Ref<LockableVariable>> locks_;
    }; 
} // namespace ntt
