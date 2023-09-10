#include "EngineApplication/PreInclude.hpp"
#include "EngineApplication/ApplicationBuilder.hpp"
#include "EngineApplication/Application.hpp"
#include "EngineWindow/Window.hpp"
#include "EngineExceptions/ApplicationConfigErrorException.hpp"


namespace ntt
{
    ApplicationBuilder::ApplicationBuilder()
    {

    } 

    ApplicationBuilder::ApplicationBuilder(const ApplicationBuilder& builder)
    {
        this->window_ = builder.window_;
    }

    ApplicationBuilder::~ApplicationBuilder()
    {

    }

    ApplicationBuilder& ApplicationBuilder::UseWindow(std::shared_ptr<Window> window)
    {
        this->window_ = window;
        return *this;
    }

    Application ApplicationBuilder::Build()
    {
        if (window_ == nullptr)
        {
            throw ApplicationConfigErrorException("The Window was not set.");
        }

        Application application(window_);
        return application;
    }
} // namespace ntt
