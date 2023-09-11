#pragma once


namespace ntt
{
    class Window
    {
        public:
            virtual void Init() = 0;
            virtual void OnUpdate() = 0;
            virtual void Release() = 0;
    }; 
} // namespace ntt
