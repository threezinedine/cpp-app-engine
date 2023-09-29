#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/Lock.hpp"
#include "EngineDataType/LockableVarible.hpp"

#include <iostream>


namespace ntt
{
    Lock::Lock(Ref<LockableVariable> var)
        : var_(var)
    {
        var->Lock();
    }    

    Lock::~Lock()
    {
        var_->UnLock();
    }
} // namespace ntt
