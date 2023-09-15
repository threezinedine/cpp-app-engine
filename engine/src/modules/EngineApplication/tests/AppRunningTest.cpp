#include "PreInclude.hpp"

#include "EngineApplication/EngineApplication.hpp"
#include "EngineExceptions/EngineExceptions.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include "EngineWindow/mocking/WindowMocking.hpp"


class AppRunningTest: public testing::Test
{
    protected:
        ntt::Ref<WindowMocking> window_;

        void SetUp() override
        {
            window_ = WindowMocking::CreateRef();
        }
};


TEST_F(AppRunningTest, WhenInitializeTheApplicationThenTheWindowIsAlsoInitialized)
{
    auto builder = ntt::ApplicationBuilder()
                    .UseWindow(window_);

    EXPECT_CALL(*window_, Init()).Times(1);
    EXPECT_CALL(*window_, Release()).Times(1);

    window_->WindowShouldCloseAfter(5);
    EXPECT_CALL(*window_, OnUpdateBegin(testing::_)).Times(5);
    EXPECT_CALL(*window_, OnUpdateEnd(testing::_)).Times(5);

    {
        auto application = builder.Build();

        long long loop = application.MainLoop();
        EXPECT_THAT(loop, testing::Eq(5));
    }
}

TEST_F(AppRunningTest, WhenInitializeTheApplicationWithoutTheWindowThenThrowException)
{
    auto builder = ntt::ApplicationBuilder();

    EXPECT_THROW(builder.Build(), ntt::ApplicationConfigErrorException);
}