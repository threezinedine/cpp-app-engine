#include "PreInclude.hpp"
#include "EngineThreading/mock/ThreadMock.hpp"


class EngineThreadTest : public testing::Test
{
    protected:
        void SetUp() override
        {

        }

        void TearDown() override
        {

        }
};


TEST_F(EngineThreadTest, InitializeTheThreadMock)
{
    ThreadMock cam("Test Thread", 0);

    cam.IgnoreStopImplExpect();
    cam.SetupIsRunningReturnFalseAt(7);
    cam.IgnoreOnRunImpl();
    EXPECT_CALL(cam, StartImpl()).Times(1);
    EXPECT_CALL(cam, SetRunning(true)).Times(1);
    EXPECT_CALL(cam, SetRunning(false)).Times(1);

    cam.Start();
    cam.Stop();
}

TEST_F(EngineThreadTest, TheThreadRunsTheStopImplWhenBeStop)
{
    ThreadMock cam("Test Thread", 0);
    
    cam.IgnoreStartImplExpect();
    cam.IgnoreSetRunning();
    cam.SetupIsRunningReturnFalseAt(5);
    cam.IgnoreOnRunImpl();
    EXPECT_CALL(cam, StopImpl()).Times(1);

    cam.Start();

    cam.Stop();
}

TEST_F(EngineThreadTest, ThreadMainLoop)
{
    ThreadMock cam("Test Thread", 0);
    cam.SetupIsRunningReturnFalseAt(5);
    EXPECT_CALL(cam, OnRunImpl()).Times(5);

    auto loop = cam.MainLoop();

    EXPECT_THAT(loop, testing::Eq(5));
}

TEST_F(EngineThreadTest, WithOnUpdateMethod)
{
    ThreadMock cam("Test Thread", 0);
    ntt::Timestep ts;

    EXPECT_CALL(cam, OnUpdateImpl(testing::_)).Times(1);

    EXPECT_NO_THROW(cam.OnUpdate(ts, true));
}

TEST_F(EngineThreadTest, ShouldHaveTheName)
{
    ThreadMock cam("Test Thread", 0);

    EXPECT_THAT(cam.GetName(), testing::StrEq("Test Thread"));
}