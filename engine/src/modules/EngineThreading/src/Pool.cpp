#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/WorkPool/Pool.hpp"
#include "EngineThreading/WorkPool/Command.hpp"


namespace ntt
{
    WorkPool::WorkPool(const char* name)
        : Thread(name)
    {

    }

    WorkPool::~WorkPool()
    {

    }

    void WorkPool::AddWork(Ref<Command> commmand)
    {
        commandQueue_.push(commmand);
    } 

    void WorkPool::StartImpl()
    {
        ClearQueue();
    }

    void WorkPool::ClearQueue()
    {
        std::queue<Ref<Command>> emptyQueue;
        std::swap(commandQueue_, emptyQueue);
    }
    
    void WorkPool::StopImpl()
    {
        ClearQueue();
    }
    
    void WorkPool::OnUpdateImpl(Timestep ts)
    {

    }
    
    void WorkPool::OnRunImpl()
    {
        if (!commandQueue_.empty())
        {
            auto command = commandQueue_.front();
            commandQueue_.pop();

            if (command->IsExecutable())
            {
                command->OnExecute();
            }
            else 
            {
                commandQueue_.push(command);
            }
        }
    }
    
} // namespace ntt
