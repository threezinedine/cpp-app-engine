#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/Thread.hpp"


namespace ntt
{
    void Thread::Start()
    {
        SetRunning(true);
        StartImpl();
    }

    void Thread::Stop()
    {
        SetRunning(false);
        StopImpl();
    }

    void Thread::OnRun()
    {
        OnRunImpl();
    }

    long long Thread::MainLoop()
    {
        long long result = 0;

        while (IsRunning())
        {
            OnRun();
            result ++;
        }

        return result;
    }

    bool Thread::IsRunning() const 
    { 
        return isRunning_; 
    }

    void Thread::SetRunning(bool running)
    {
        isRunning_ = running;
    }
} // namespace ntt
