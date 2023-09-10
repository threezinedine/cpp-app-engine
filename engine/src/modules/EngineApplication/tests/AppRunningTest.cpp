#include "PreInclude.hpp"

#include "EngineApplication/EngineApplication.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include "EngineExceptions/ApplicationConfigErrorException.hpp"


class WindowMocking : public ntt::Window 
{
    public:
        MOCK_METHOD0(Init, void());
};


TEST(AppRunningTest, WhenInitializeTheApplicationThenTheWindowIsAlsoInitialized)
{
    std::shared_ptr<WindowMocking> window = std::make_shared<WindowMocking>();

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