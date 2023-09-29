#include <chrono>
#include <iostream>
#include "EngineCores/TimeUtils.hpp"


namespace ntt
{
    TimeTrigger::TimeTrigger()
    {
        Reset();
    }

    TimeTrigger::~TimeTrigger()
    {

    }


    void TimeTrigger::Reset()
    {
        start_ = std::chrono::system_clock::now();
    }

    bool TimeTrigger::IsTrigger(long long miliSeconds)
    {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_);

        bool isTrigger = duration.count() > miliSeconds;

        if (isTrigger)
        {
            Reset();
        }

        return isTrigger;
    }

    bool TimeTrigger::IsTriggerInSeconds(long long seconds)
    {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start_);

        bool isTrigger = duration.count() > seconds;

        if (isTrigger)
        {
            Reset();
        }

        return isTrigger;
    }

    bool TimeTrigger::IsTriggerInMicroSeconds(long long microSeconds)
    {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);

        bool isTrigger = duration.count() > microSeconds;

        if (isTrigger)
        {
            Reset();
        }

        return isTrigger;
    }

    Time::Time(const char* name)
    {
        auto currentTime = std::chrono::system_clock::now();

        // Convert the current time to a time_t object
        std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);

        // Convert the current time to a tm struct
        std::tm timeInfo = *std::localtime(&currentTimeT);

        // Get the microseconds part
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
            currentTime.time_since_epoch()) % 1000000;

        // Format the time as "HH:mm:ss"
        char timeStr[19]; // 18 characters for "HH:mm:ss.microseconds" + null terminator
        std::strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeInfo);

        // Append microseconds to the time string
        sprintf(timeStr + 8, ".%06lld", microseconds.count());

        std::cout << "Start Time " << name << ": " << timeStr << std::endl;
    }

    Time::~Time()
    {

    }
} // namespace ntt
