#pragma once


namespace ntt
{
    class DataStorage
    {
        public:
            virtual void SaveInteger(const char* name, int value);
            virtual int GetInteger(const char* name);
    };
} // namespace ntt
