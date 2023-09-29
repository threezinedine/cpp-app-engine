#pragma once
#include <chrono>
#include <string>


namespace ntt
{
    class TimeTrigger
    {
        public:
            TimeTrigger();
            ~TimeTrigger();

            void Reset();
            bool IsTrigger(long long miliSeconds);
            bool IsTriggerInSeconds(long long seconds);
            bool IsTriggerInMicroSeconds(long long microSeconds);
        
        private:
            std::chrono::time_point<std::chrono::system_clock> start_;
    }; 

    class Time
    {
        public:
            Time(const char* name);
            ~Time();
    };
} // namespace ntt
