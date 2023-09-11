#include "PreInclude.hpp"

#include "EngineApplication/EngineApplication.hpp"
#include "EngineExceptions/EngineExceptions.hpp"
#include "EngineWindow/EngineWindow.hpp"


class WindowMocking : public ntt::Window 
{
    public:
        MOCK_METHOD0(Init, void());
        MOCK_METHOD0(OnUpdate, void());

        static ntt::Ref<WindowMocking> CreateRef()
        {
            return std::make_shared<WindowMocking>();
        }
};


TEST(AppRunningTest, WhenInitializeTheApplicationThenTheWindowIsAlsoInitialized)
{
    ntt::Ref<WindowMocking> window = WindowMocking::CreateRef();

    auto builder = ntt::ApplicationBuilder()
                    .UseWindow(window);

    EXPECT_CALL(*window, Init()).Times(1);

    auto application = builder.Build();
}

TEST(AppRunningTest, WhenInitializeTheApplicationWithoutTheWindowThenThrowException)
{
    auto builder = ntt::ApplicationBuilder();

    EXPECT_THROW(builder.Build(), ntt::ApplicationConfigErrorException);
}

TEST(AppRunningTest, WhenRunOnUpdateThenTheWindowOnUpdateIsAlsoRun)
{
    ntt::Ref<WindowMocking> window = WindowMocking::CreateRef();

    auto application = ntt::ApplicationBuilder()
                        .UseWindow(window)
                        .Build();

    EXPECT_CALL(*window, OnUpdate()).Times(1);

    application.OnUpdate();
}