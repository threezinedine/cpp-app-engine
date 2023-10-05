#pragma once
#include <queue>
#include <map>
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

            static Ref<WorkPool> CreateRef(const char* name)
            {
                return std::make_shared<WorkPool>(name);
            }

            static void Init();
            static void AddWorkPool(Ref<WorkPool> workPool);
            static Ref<WorkPool> GetWorkPool(const char* name);
            static void Release();

        private:
            std::queue<Ref<Command>> commandQueue_;            

            static std::map<std::string, Ref<WorkPool>> workPools_;

            void ClearQueue();
    };    
} // namespace ntt
