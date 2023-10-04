#pragma once
#include "EngineCores/EngineCores.hpp"
#include <functional>


namespace ntt
{
    class Command
    {
        public:
            Command();
            Command(std::function<void()> func);
            ~Command();

            virtual void OnExecute();
            virtual bool IsExecutable() const;

            static Ref<Command> CreateRef(std::function<void()> func)
            {
                return std::make_shared<Command>(func);
            }

        private:
            std::function<void()> func_;
    }; 
} // namespace ntt
