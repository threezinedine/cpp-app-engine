#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/Thread.hpp"


#define HERE() std::cout << "Here" << std::endl;
#define IS_RUNNING() std::cout << ( IsRunning() ? "running" : "no" ) << std::endl;


namespace ntt
{
    void Thread::Start()
    {
        SetRunning(true);

        StartImpl();
        thread_ = std::make_unique<std::thread>(&Thread::MainLoop, this);
    }

    void Thread::Stop()
    {
        SetRunning(false);
        StopImpl();
        thread_->join();
    }

    void Thread::OnRun()
    {
        OnRunImpl();
    }

    void Thread::OnUpdate(Timestep ts)
    {
        OnUpdateImpl(ts);
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
