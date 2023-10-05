#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/WorkPool/Pool.hpp"
#include "EngineThreading/WorkPool/Command.hpp"


namespace ntt
{
    std::map<std::string, Ref<WorkPool>> WorkPool::workPools_;

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
    
    void WorkPool::Init()
    {

    }

    void WorkPool::AddWorkPool(Ref<WorkPool> workPool)
    {
        workPools_[workPool->GetName()] = workPool;
    }

    Ref<WorkPool> WorkPool::GetWorkPool(const char* name)
    {
        return workPools_[name];
    }

    void WorkPool::Release()
    {
        workPools_.clear();
    }
} // namespace ntt
