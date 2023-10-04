#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/WorkPool/Command.hpp"


static std::function<void()> emptyFunc = []()
{

};


namespace ntt
{
    Command::Command()
        : func_(emptyFunc)
    {

    }

    Command::Command(std::function<void()> func)
        : func_(func)
    {

    }

    Command::~Command()
    {

    }

    void Command::OnExecute()
    {
        func_();
    } 

    bool Command::IsExecutable() const 
    {
        return true;
    }
} // namespace ntt
