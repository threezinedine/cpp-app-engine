#pragma once
#include <queue>
#include "EngineThreading/Thread.hpp"
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Command;

    class WorkPool: public Thread
    {
        public:
            WorkPool(const char* name);
            ~WorkPool();

            void AddWork(Ref<Command> command);
            bool IsEmpty() const { return commandQueue_.empty(); }

            void StartImpl() override;
            void StopImpl() override;
            void OnUpdateImpl(Timestep ts) override;
            void OnRunImpl() override;

        private:
            std::queue<Ref<Command>> commandQueue_;            

            void ClearQueue();
    };    
} // namespace ntt
