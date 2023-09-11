#include "PreInclude.hpp"

#include "EngineApplication/EngineApplication.hpp"
#include "EngineExceptions/EngineExceptions.hpp"
#include "EngineWindow/EngineWindow.hpp"


class WindowMocking : public ntt::Window 
{
    public:
        MOCK_METHOD0(Init, void());
        MOCK_METHOD(void, OnUpdate, (ntt::Timestep), (override));
        MOCK_METHOD0(Release, void());

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
    EXPECT_CALL(*window, OnUpdate(testing::_)).Times(1);
    EXPECT_CALL(*window, Release()).Times(1);

    {
        auto application = builder.Build();

        application.OnUpdate();
    }
}

TEST(AppRunningTest, WhenInitializeTheApplicationWithoutTheWindowThenThrowException)
{
    auto builder = ntt::ApplicationBuilder();

    EXPECT_THROW(builder.Build(), ntt::ApplicationConfigErrorException);
}