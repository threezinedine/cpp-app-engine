#include "PreInclude.hpp"
#include "EngineThreading/Thread.hpp"
#include "EngineThreading/Lock.hpp"
#include "EngineDataType/EngineDataType.hpp"


static ntt::Ref<ntt::Data<int>> value 
            = std::make_shared<ntt::Data<int>>("ThreadingTestVariable", 0, 0, 50000);


class IntegrationThread: public ntt::Thread
{
    public:
        IntegrationThread(const char* name)
            : ntt::Thread(name)
        {

        }

        ~IntegrationThread()
        {

        }

        void StartImpl() override
        {

        }

        void OnRunImpl() override
        {
            if (index_ < 1000)
            {
                ntt::Lock lock(value);
                value->SetValue(value->Value() + 1);
                index_ ++;
            }
        }

        void StopImpl() override
        {

        }

        void OnUpdateImpl(ntt::Timestep ts) override
        {

        }

    private:
        int index_ = 0;
};


class EngineThreadingIntegraionTest: public testing::Test
{
    protected:
        void SetUp() override
        {

        }

        void TearDown() override
        {

        }
};


TEST_F(EngineThreadingIntegraionTest, LockingVariableWillTurnOnTheMutex)
{
    IntegrationThread t1("Testing Thread");

    t1.Start();

    for (int i=0; i<40000; i++)
    {
        ntt::Lock lock(value);
        value->SetValue(value->Value() + 1);
    }

    t1.Stop();

    EXPECT_THAT(value->Value(), testing::Eq(41000));
}