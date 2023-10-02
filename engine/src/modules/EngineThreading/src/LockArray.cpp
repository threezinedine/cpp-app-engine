#include "EngineThreading/LockArray.hpp"
#include "EngineDataType/EngineDataType.hpp"


namespace ntt
{
    LockArray::LockArray(std::initializer_list<Ref<LockableVariable>> locks)
        : locks_(locks)
    {
        for (auto lock: locks)
        {
            lock->Lock();
        }
    }

    LockArray::~LockArray()
    {
        for (auto lock: locks_)
        {
            lock->UnLock();
        }
    }
} // namespace ntt
