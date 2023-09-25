#include "PreInclude.hpp"
#include "EngineThreading/Thread.hpp"


class CameraThread: public ntt::Thread
{
    public:
        CameraThread(int camId)
            : camId_(camId)
        {

        }

        ~CameraThread()
        {

        }

        MOCK_METHOD(void, StartImpl, (), (override));
        MOCK_METHOD(void, StopImpl, (), (override));
        MOCK_METHOD(void, OnRunImpl, (), (override));
        MOCK_METHOD(bool, IsRunning, (), (const));
        MOCK_METHOD(void, SetRunning, (bool), (override));


        void IgnoreSetRunning()
        {
            EXPECT_CALL(*this, SetRunning(testing::_)).Times(testing::AnyNumber());
        }

        void IgnoreStartImplExpect()
        {
            EXPECT_CALL(*this, StartImpl()).Times(testing::AnyNumber());
        }

        void IgnoreStopImplExpect()
        {
            EXPECT_CALL(*this, StopImpl()).Times(testing::AnyNumber());
        }

        void SetupIsRunningReturnFalseAt(int period)
        {
            testing::Sequence sequence;
            for (int i=0; i<period; i++)
            {
                EXPECT_CALL(*this, IsRunning())
                        .InSequence(sequence)
                        .WillOnce(testing::Return(true));
            }
            EXPECT_CALL(*this, IsRunning())
                        .InSequence(sequence)
                        .WillOnce(testing::Return(false));
        }

    private:
        int camId_;
};


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


TEST_F(EngineThreadTest, InitializeTheCameraThread)
{
    CameraThread cam(0);

    cam.IgnoreStopImplExpect();
    EXPECT_CALL(cam, StartImpl()).Times(1);
    EXPECT_CALL(cam, SetRunning(true)).Times(1);
    EXPECT_CALL(cam, SetRunning(false)).Times(1);

    cam.Start();
    cam.Stop();
}

TEST_F(EngineThreadTest, TheThreadRunsTheStopImplWhenBeStop)
{
    CameraThread cam(0);
    
    cam.IgnoreStartImplExpect();
    cam.IgnoreSetRunning();
    EXPECT_CALL(cam, StopImpl()).Times(1);

    cam.Start();

    cam.Stop();
}

TEST_F(EngineThreadTest, ThreadMainLoop)
{
    CameraThread cam(0);
    cam.SetupIsRunningReturnFalseAt(5);
    EXPECT_CALL(cam, OnRunImpl()).Times(5);

    auto loop = cam.MainLoop();

    EXPECT_THAT(loop, testing::Eq(5));
}