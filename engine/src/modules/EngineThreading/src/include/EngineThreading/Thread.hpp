#pragma once
#include <thread>
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Timestep;

    class Thread
    {
        public:
            Thread(const char* name);
            virtual ~Thread() = default;
            virtual void Start();
            virtual void StartImpl() = 0;

            virtual void Stop();
            virtual void StopImpl() = 0;

            virtual void OnUpdate(Timestep ts, bool testing = false);
            virtual void OnUpdateImpl(Timestep ts) = 0;

            virtual bool IsRunning() const;
            virtual void SetRunning(bool running);

            virtual void OnRun();
            virtual void OnRunImpl() = 0;

            long long MainLoop();

            inline const char* GetName() const { return name_; }

        private:
            const char* name_;
            bool isRunning_;
            Scope<std::thread> thread_;
    }; 
} // namespace ntt
