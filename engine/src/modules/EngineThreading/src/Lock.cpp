#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/Lock.hpp"
#include "EngineDataType/LockableVarible.hpp"


namespace ntt
{
    Lock::Lock(LockableVariable& var)
        : var_(var)
    {
        var.GetMutex().lock();
    }    

    Lock::~Lock()
    {
        var_.GetMutex().unlock();
    }
} // namespace ntt
