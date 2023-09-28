#pragma once


namespace ntt
{
    class LockableVariable;

    class Lock
    {
        public:
            Lock(LockableVariable& var);
            ~Lock();

        private:
            LockableVariable& var_;
    }; 
} // namespace ntt
